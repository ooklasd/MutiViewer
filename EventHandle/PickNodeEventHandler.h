#pragma once
#include "osgGA/GUIEventHandler"
#include "osg/CopyOp"
#include"Export.h"

namespace designer
{
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

	protected:
		osg::ref_ptr<osg::Node> _pickNode;

		const osgGA::GUIEventAdapter* _ea;
		osgGA::GUIActionAdapter* _aa;
	};

}