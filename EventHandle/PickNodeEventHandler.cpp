#include "PickNodeEventHandler.h"
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <map>
#include <string>
#include <osgViewer/View>

#include "osg/ComputeBoundsVisitor"
#include "osg/ShapeDrawable"
#include "osg/Shape"
#include "osg/PolygonMode"
#include "osg/LineWidth"

#include "DesignerViewer/PickView.h"
#include "hgcw/hgCD/Mesh.h"
#include "hgcw/hgCD/LocateEntity.h"
#include "Document/Document.h"




namespace designer
{

	PickNodeEventHandler::PickNodeEventHandler()
	{
		_ea = nullptr;
		_aa = nullptr;
	}

	bool PickNodeEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{
		_ea	= &ea;
		_aa	= &aa;
		using namespace osgGA;
		//如果是左右键，则检测碰撞
		if(ea.getEventType() == GUIEventAdapter::KEYDOWN)
		{
			switch(ea.getKey())
			{
			case GUIEventAdapter::KEY_Space:
				int i = 0;
				break;;
			}
		}

		if(ea.getEventType() == GUIEventAdapter::PUSH)
		{
			//点选碰撞
 			switch(ea.getButton())
			{
			case GUIEventAdapter::LEFT_MOUSE_BUTTON:{
				if(LeftButtonHandle()) return LeftButtonHandle()->handle(ea,aa);
				PickObject();
				}break;
			case GUIEventAdapter::RIGHT_MOUSE_BUTTON:{
				if(RightButtonHandle()) return RightButtonHandle()->handle(ea,aa);
				PickObject();
				}break;
			}
		}

		return osgGA::GUIEventHandler::handle(ea,aa);
	}

	PickNodeEventHandler* PickNodeEventHandler::clone(const osg::CopyOp&) const
	{
		return new PickNodeEventHandler();
	}

	void PickNodeEventHandler::PickObject()
	{
		auto viewer = dynamic_cast<PickView*>(_aa);
		if(viewer == nullptr) return;
		bool isMuti = _ea->getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_SHIFT;

		osg::NodePath np;
		osgUtil::LineSegmentIntersector::Intersections intersection;
		float x = _ea->getX();
		float y = _ea->getY();
		if(viewer->computeIntersections(x,y,intersection) == false)
		{
			//若不是多选又点选了空白则清空
			if(!isMuti) viewer->removeAllPickNode();
			return ;
		}

		for (auto it = intersection.begin();it != intersection.end();++it)
		{
			for (auto itnode = it->nodePath.begin();itnode !=it->nodePath.end();++itnode)
			{
				auto curNode = *itnode;
				//选出Mesh
				auto mesh = dynamic_cast<CombdoorL::Mesh*>(curNode);
				if(mesh != nullptr)
				{
					if(!isMuti && !viewer->getPickNodes().empty() 
						&& !viewer->isSelect(curNode))
					{
						viewer->removeAllPickNode();
					}

					if(viewer->isSelect(curNode))
					{
						viewer->removePickNode(curNode);
					}
					else
					{
						viewer->addPickNode(curNode);
					}
					return;
				}
				
				//获取排布层
				auto locatEnt = dynamic_cast<CombdoorL::LocateEntity*>(curNode);
				if(locatEnt != nullptr)
				{

				}
				
			}
		}
	}

	void PickNodeFrameEvent::operator()(PickView* v,osg::Node* n)
	{
		auto nodes = v->getPickNodes();
		nodes.sort();

		//删除过时的
		for (auto it = _nodeSelectFrame.begin();it != _nodeSelectFrame.end();++it)
		{
			auto isFind = std::binary_search(nodes.begin(),nodes.end(),it->first);
			if(!isFind)
			{
				removeFrame(it->first);
			}
		}

		//更新frame
		if(std::binary_search(nodes.begin(),nodes.end(),n))
		{
			addFrame(n);
		}
		else
		{
			removeFrame(n);
		}
	}

	osg::Node* PickNodeFrameEvent::CreateFrame(osg::Geode* g)
	{
		if(g == nullptr) return nullptr;
		osg::ComputeBoundsVisitor bbV;
		g->accept(bbV);
		return CreateFrame(bbV.getBoundingBox());
	}

	osg::Node* PickNodeFrameEvent::CreateFrame(osg::Group* g)
	{
		if(g == nullptr) return nullptr;
		osg::BoundingBox bb;
		auto sum = g->getNumChildren();
		for (size_t i = 0;i<sum;++i)
		{
			osg::ComputeBoundsVisitor bbV;
			g->getChild(i)->accept(bbV);			
			bb.expandBy(bbV.getBoundingBox());
		}
		return CreateFrame(bb);
	}

	osg::Node* PickNodeFrameEvent::CreateFrame(const osg::BoundingBox& bb)
	{
		osg::Vec3 min = bb._min;
		osg::Vec3 max = bb._max;

		osg::ref_ptr<osg::Geode> frame = new osg::Geode;

		osg::Geometry* geom = new osg::Geometry;
		osg::Vec3Array* vertices = new osg::Vec3Array;
		vertices->push_back(osg::Vec3(min.x(), min.y(), min.z()));
		vertices->push_back(osg::Vec3(max.x(), min.y(), min.z()));
		vertices->push_back(osg::Vec3(max.x(), max.y(), min.z()));
		vertices->push_back(osg::Vec3(min.x(), max.y(), min.z()));
		vertices->push_back(osg::Vec3(min.x(), min.y(), max.z()));
		vertices->push_back(osg::Vec3(max.x(), min.y(), max.z()));
		vertices->push_back(osg::Vec3(max.x(), max.y(), max.z()));
		vertices->push_back(osg::Vec3(min.x(), max.y(), max.z()));
		geom->setVertexArray(vertices);
		osg::Vec4Array* color = new osg::Vec4Array;
		color->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
		geom->setColorArray(color);
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		GLushort idxLines[24] = 
		{	
			0, 1,
			1, 2,
			2, 3,
			3, 0,
			4, 5,
			5, 6,
			6, 7,
			7, 4,
			0, 4,
			1, 5,
			2, 6,
			3, 7
		};
		geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINES, 24, idxLines ) );

		frame->addDrawable(geom);
		frame->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		frame->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		osg::LineWidth* lw = new osg::LineWidth;
		lw->setWidth(1.0f);
		frame->getOrCreateStateSet()->setAttributeAndModes(lw, osg::StateAttribute::ON);
		return frame.release();
	}

	void PickNodeFrameEvent::addFrame(osg::Node* n)
	{
		removeFrame(n);

		osg::ref_ptr<osg::Node> frame = nullptr;

		auto geode = dynamic_cast<osg::Geode*>(n);
		if(geode != nullptr && geode->getNumParents() != 0) {
			frame = CreateFrame(geode);
			//生成的外框和Geode同级
			n->getParent(0)->addChild(frame);
		}
		auto group = dynamic_cast<osg::Group*>(n);
		if(group != nullptr) {
			frame = CreateFrame(group);
			//生成的外框应该为Group的子节点
			group->addChild(frame);
		}

		_nodeSelectFrame[n] = frame;
	}

	void PickNodeFrameEvent::removeFrame(osg::Node* n)
	{
		auto frame = _nodeSelectFrame[n];
		if(frame != nullptr && frame->getNumParents() != 0)
		{
			frame->getParent(0)->removeChild(frame);
		}
		_nodeSelectFrame[n] = nullptr;
	}

}