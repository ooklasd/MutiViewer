#pragma once
#include <osg/Referenced>
#include <osg/ref_ptr>
#include "..\Export.h"
#include <osgViewer/CompositeViewer>
#include "..\DesignerViewer/DesignerViewer.h"
#include "hgcd\MgrCoreCD\WCommandManager.h"
#include<osg/Timer>

class MgrCore::WCommandManager;

#define USER_VALUE(TYPE,NAME)\
	bool get##NAME(TYPE& temp){return getUserValue(#NAME,temp);}\
	void set##NAME(const TYPE& temp){	setUserValue(#NAME,temp);}


namespace designer
{
	class DESIGNERCMD_API Document;

	//====================================================================================
	// 文档管理，包括场景和命令
	// userdata里面存放各种数值
	//====================================================================================
	class DesignerViewer;
	class Document :public osg::Object
	{
	public: 
		Document();

		static void SetToObject(osg::Object& obj,Document* ref);
		static Document* GetFromObject(osg::Object& obj);

	public:
		//多视图
		DesignerViewer* getOrCreateViewer();
		DesignerViewer* getViewer(){return _designerViewer;}
		const DesignerViewer* getViewer()const {return _designerViewer;}

		//命令管理器
		MgrCore::WCommandManager& WCommandManager() { return _wCommandManager; }


		virtual Document* cloneType() const;


		virtual osg::Object* clone(const osg::CopyOp&) const;


		virtual const char* libraryName() const
		{
			return "DesignerCMD";
		}

		virtual const char* className() const
		{
			return "Document";
		}

		////调用view里面的锁，转接作用
		//OpenThreads::ScopedReadLock getReadLock(){_designerViewer->getReadLock();}
		//OpenThreads::ScopedWriteLock getWriteLock(){_designerViewer->getWriteLock();}

	public:
		// 执行命令json，返回json
		bool executeJson(const Json::Value& json,MgrCore::ResultType &resultStringList);
		bool executeJson(const Json::Value& json);

		// 执行命令string,返回json
		bool executeString(const TCHAR* commandString,MgrCore::ResultType &resultStringList);
		bool executeString(const TCHAR* commandString);

		bool executeCommand(const std::string& commmandName,Json::Value data,MgrCore::ResultType &resultStringList);
		bool executeCommand(const std::string& commmandName,Json::Value data = Json::Value());

		static Json::Value makeCommand(const std::string& commmandName,const Json::Value& data);
		static Json::Value makeCommand(const std::string& commmandName,Json::Value&& data);

		class jsonCall : public osg::Referenced
		{
		public:
			virtual ~jsonCall(){}
			virtual bool operator()(const Json::Value& cmdJson) = 0;
		};

		//回馈到UI
		void setUiCall(jsonCall* val) { _uiCall = val; }

		bool sendToUI(const Json::Value& json);
		bool sendToUI(const std::string& commmandName,const Json::Value& data);

public:
		//是否为空白文档
		bool isEmpty()const;

		USER_VALUE(unsigned,LastSaveTime);
		USER_VALUE(unsigned,LastModifyTime);
		USER_VALUE(std::string,TempFile);

		//文件名
		const std::string& getFileName()const{return _fileName;}

		//全路径
		const std::string& getFilePath()const{return _filePath;}
		void setFilePath(std::string v);
	protected:
		osg::ref_ptr<jsonCall> _uiCall;

		//多视图
		osg::ref_ptr<DesignerViewer> _designerViewer;

		//命令管理器
		MgrCore::WCommandManager _wCommandManager;

		std::string _fileName;//文件名
		std::string _filePath;//全路径
		
	};


}

