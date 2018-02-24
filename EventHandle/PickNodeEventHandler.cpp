#include "PickNodeEventHandler.h"
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <map>
#include <string>
#include <osgViewer/View>

#include "DesignerViewer/PickView.h"
#include "hgcw/hgCD/Mesh.h"
#include "hgcw/hgCD/LocateEntity.h"

#include "osg/ComputeBoundsVisitor"
#include "osg/ShapeDrawable"
#include "osg/Shape"
#include "osg/PolygonMode"
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
		//��������Ҽ���������ײ
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
			//��ѡ��ײ
 			switch(ea.getButton())
			{
			case GUIEventAdapter::LEFT_MOUSE_BUTTON:{
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
			//�����Ƕ�ѡ�ֵ�ѡ�˿հ������
			if(!isMuti) viewer->removeAllPickNode();
			return ;
		}

		for (auto it = intersection.begin();it != intersection.end();++it)
		{
			for (auto itnode = it->nodePath.begin();itnode !=it->nodePath.end();++itnode)
			{
				auto curNode = *itnode;
				//ѡ��Mesh
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
				
				//��ȡ�Ų���
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

		//ɾ����ʱ��
		for (auto it = _nodeSelectFrame.begin();it != _nodeSelectFrame.end();++it)
		{
			auto isFind = std::binary_search(nodes.begin(),nodes.end(),it->first);
			if(!isFind)
			{
				removeFrame(it->first);
			}
		}

		//����frame
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
		
		using namespace osg;
		osg::ref_ptr<osg::Geode> frame = new osg::Geode;
		auto boxsize = bb._max-bb._min;
		frame->addDrawable(new osg::ShapeDrawable(new osg::Box(bb.center(),boxsize[0],boxsize[1],boxsize[2])));
		
		//����ss����ȾģʽΪ�߿�
		auto ss = frame->getOrCreateStateSet();
		auto mode = new  osg::PolygonMode(PolygonMode::FRONT_AND_BACK,PolygonMode::LINE);
		ss->setAttributeAndModes(mode,osg::StateAttribute::ON);
		//ss->setMode(StateAttribute::DEPTH,osg::StateAttribute::OFF);
		return frame.release();
	}

	void PickNodeFrameEvent::addFrame(osg::Node* n)
	{
		removeFrame(n);

		osg::ref_ptr<osg::Node> frame = nullptr;

		auto geode = dynamic_cast<osg::Geode*>(n);
		if(geode != nullptr && geode->getNumParents() != 0) {
			frame = CreateFrame(geode);
			//���ɵ�����Geodeͬ��
			n->getParent(0)->addChild(frame);
		}
		auto group = dynamic_cast<osg::Group*>(n);
		if(group != nullptr) {
			frame = CreateFrame(group);
			//���ɵ����Ӧ��ΪGroup���ӽڵ�
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