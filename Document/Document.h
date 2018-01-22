#pragma once
#include <osg/Referenced>
#include <osg/ref_ptr>
#include "..\Export.h"
#include <osgViewer/CompositeViewer>
#include "DesignerViewer/DesignerViewer.h"
#include "hgcd\MgrCoreCD\WCommandManager.h"

class MgrCore::WCommandManager;

namespace designer
{
	class DESIGNERCMD_API Document;


	class DesignerViewer;
	class Document :public osg::Referenced
	{
	public: 
		Document();

	public:
		//多视图
		DesignerViewer* getViewer(){return _designerViewer;}
		const DesignerViewer* getViewer()const {return _designerViewer;}

		//命令管理器
		MgrCore::WCommandManager& WCommandManager() { return _wCommandManager; }

	public:
		// 执行命令json，返回json
		bool executeJson(const Json::Value& json,MgrCore::ResultType &resultStringList);
		bool executeJson(const Json::Value& json);

		// 执行命令string,返回json
		bool executeString(const TCHAR* commandString,MgrCore::ResultType &resultStringList);
		bool executeString(const TCHAR* commandString);

	protected:
		//多视图
		osg::ref_ptr<DesignerViewer> _designerViewer;

		//命令管理器
		MgrCore::WCommandManager _wCommandManager;

		std::string _fileName;//文件全路径
		std::string _filePath;//所在文件夹路径
	};


}

