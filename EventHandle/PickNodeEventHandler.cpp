#include "PickNodeEventHandler.h"
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <map>
#include <string>
#include <osgViewer/View>

#include "DesignerViewer/PickView.h"
#include "hgcw/hgCD/Mesh.h"
#include "hgcw/hgCD/LocateEntity.h"
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

}