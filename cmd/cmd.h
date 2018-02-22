#pragma once
#include "hgcd/MgrCoreCD/WICommand.h"
#include "..\Document/Document.h"
#include "..\Export.h"

class MgrCore::WICommand;


#define CMD_STATIC(name)  \
	static const char* commandName(){return #name;}\
	static name* creator(){return new name();}

namespace designer
{
	class DESIGNERCMD_API cmd;
	class DesignerViewer;
	class cmd :public MgrCore::WICommand
	{
	public:	

	public:
		//====================================================================================
		// 快捷获取函数
		// 用去简化获取流程
		//====================================================================================

		//获取文档
		Document* getDocument(){
			return reinterpret_cast<Document*>(getArg());
		}

		//获取viewer
		DesignerViewer* getViewer(){
			return getDocument()->getViewer(); 
		}

		//获取根节点
		osg::Group* getShapeRoot() { return getViewer()->ShapeRoot(); }
		osg::Group* getExtractRoot() { return getViewer()->ExtractRoot(); }
		osg::Group* getCombdoorRoot() { return getViewer()->CombdoorRoot(); }

		//获取当前点选的节点
		std::list<osg::ref_ptr<osg::Node>>& getShapePickNodes();
		osg::Node* getShapePickNode();

		std::list<osg::ref_ptr<osg::Node>>& getCombdoorPickNodes();
		osg::Node* getCombdoorPickNode();
	};


}
