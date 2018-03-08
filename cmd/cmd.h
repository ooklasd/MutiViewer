#pragma once
#include "hgcd/MgrCoreCD/WICommand.h"
#include "..\Document/Document.h"
#include "..\Export.h"
#include "hgcw\hgCD\BaseIO.h"


class MgrCore::WICommand;
class CombdoorIO::BaseIO;

#define CMD_STATIC(name)  \
	static const char* commandName(){return #name;}\
	static void* creator(){return new name##CMD();}

namespace designer
{
	class DESIGNERCMD_API cmd;
	class DesignerViewer;
	class cmd :public MgrCore::WICommand
	{
	public:
		enum resultCode{
			resError = 0,resOK=1
		};

		static unsigned GetResultCode(const Json::Value& data)				{return data["result"].asUInt();}
		static std::string GetResultMessage(const Json::Value& data)		{return data["msg"].isString()?data["result"].asString():"";}
		static const Json::Value& GetResultFormat(const Json::Value& data)	{return data["format"];}
		static const Json::Value& GetResultData(const Json::Value& data)	{return data["data"];}

		//需要提供的命令格式
		virtual Json::Value getCMDFormat() = 0{return Json::Value();}		
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

		//全局锁快捷函数
		OpenThreads::ScopedReadLock getReadLock(){return getViewer()->getReadLock();}
		OpenThreads::ScopedWriteLock getWriteLock(){return getViewer()->getWriteLock();}


		//====================================================================================
		// 快捷返回函数
		//result返回Data节点
		//====================================================================================
	public:
		Json::Value& result(int code);
		Json::Value& result(int code,const char* msg);
		Json::Value& result(int code,Json::Value data);

		Json::Value& resultRef()		{return mResult["result"];}
		Json::Value& resultDataRef()	{return mResult["data"];}
		Json::Value& resultMsgRef()		{return mResult["msg"];}
		Json::Value& resultFormatRef()	{return mResult["format"];}
	};
}
