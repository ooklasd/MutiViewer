#pragma once
#include "Export.h"
#include "osgGA/GUIEventHandler"
#include "osg/CopyOp"
#include "DesignerViewer/PickView.h"

namespace designer
{
	//====================================================================================
	// �����ȡ��ά����
	//====================================================================================
	class DESIGNERCMD_API PickNodeEventHandler : public osgGA::GUIEventHandler
	{

	public:
		PickNodeEventHandler();
		virtual const char* className() const{return "PickNodeEventHandler";}

		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
		
		virtual PickNodeEventHandler* clone(const osg::CopyOp&) const;

		void PickObject();

	protected:
		osg::ref_ptr<osg::Node> _pickNode;

		const osgGA::GUIEventAdapter* _ea;
		osgGA::GUIActionAdapter* _aa;
	};


	//��ѡ������������¼�
	class DESIGNERCMD_API PickNodeFrameEvent:public PickView::Event
	{
	public:
		PickNodeFrameEvent(){}
		virtual void operator()(PickView* v,osg::Node* n);

		//���ɵ�����Geodeͬ��
		static osg::Node* CreateFrame(osg::Geode* g);

		//���ɵ����Ӧ��ΪGroup���ӽڵ�
		static osg::Node* CreateFrame(osg::Group* g);

		static osg::Node* CreateFrame(const osg::BoundingBox& bb);

		void addFrame(osg::Node* n);
		void removeFrame(osg::Node* n);
	private:
		//����ѡ�񴰿�
		typedef std::map<osg::Node*,osg::ref_ptr<osg::Node>> NodeSelectFrame;
		NodeSelectFrame _nodeSelectFrame;
	};
}