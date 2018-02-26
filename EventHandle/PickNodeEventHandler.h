#pragma once
#include "Export.h"
#include "osgGA/GUIEventHandler"
#include "osg/CopyOp"
#include "DesignerViewer/PickView.h"

namespace designer
{
	//点击事件
	class ButtonHandle : public osg::Referenced
	{
	public:
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa) = 0{return false;}
	};

	//====================================================================================
	// 点击获取三维物体
	//====================================================================================
	class DESIGNERCMD_API PickNodeEventHandler : public osgGA::GUIEventHandler
	{

	public:
		PickNodeEventHandler();
		virtual const char* className() const{return "PickNodeEventHandler";}

		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
		
		virtual PickNodeEventHandler* clone(const osg::CopyOp&) const;

		void PickObject();

		ButtonHandle* RightButtonHandle() { return _rightButtonHandle; }
		void RightButtonHandle(ButtonHandle* val) { _rightButtonHandle = val; }
	public:
		
		ButtonHandle* LeftButtonHandle() { return _leftButtonHandle; }
		void LeftButtonHandle(ButtonHandle* val) { _leftButtonHandle = val; }
	protected:
		osg::ref_ptr<ButtonHandle> _leftButtonHandle;
		osg::ref_ptr<ButtonHandle> _rightButtonHandle;
		osg::ref_ptr<osg::Node> _pickNode;

		const osgGA::GUIEventAdapter* _ea;
		osgGA::GUIActionAdapter* _aa;
	};

	//====================================================================================
	// 显示的效果,若需要不同的特效，请仿造PickNodeFrameEvent，并绑定
	// PickNodeFrameEvent为添加黄色外框
	//====================================================================================
	//触发添加外框——点选事件
	class DESIGNERCMD_API PickNodeFrameEvent:public PickView::Event
	{
	public:
		PickNodeFrameEvent(){}
		virtual void operator()(PickView* v,osg::Node* n);

		//生成的外框和Geode同级
		static osg::Node* CreateFrame(osg::Geode* g);

		//生成的外框应该为Group的子节点
		static osg::Node* CreateFrame(osg::Group* g);

		static osg::Node* CreateFrame(const osg::BoundingBox& bb);

		void addFrame(osg::Node* n);
		void removeFrame(osg::Node* n);
	private:
		//物体选择窗口
		typedef std::map<osg::Node*,osg::ref_ptr<osg::Node>> NodeSelectFrame;
		NodeSelectFrame _nodeSelectFrame;
	};

	
}