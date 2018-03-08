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

		//��Ҫ�ṩ�������ʽ
		virtual Json::Value getCMDFormat() = 0{return Json::Value();}		
	public:
		//====================================================================================
		// ��ݻ�ȡ����
		// ��ȥ�򻯻�ȡ����
		//====================================================================================

		//��ȡ�ĵ�
		Document* getDocument(){
			return reinterpret_cast<Document*>(getArg());
		}

		//��ȡviewer
		DesignerViewer* getViewer(){
			return getDocument()->getViewer(); 
		}

		//��ȡ���ڵ�
		osg::Group* getShapeRoot() { return getViewer()->ShapeRoot(); }
		osg::Group* getExtractRoot() { return getViewer()->ExtractRoot(); }
		osg::Group* getCombdoorRoot() { return getViewer()->CombdoorRoot(); }

		//��ȡ��ǰ��ѡ�Ľڵ�
		std::list<osg::ref_ptr<osg::Node>>& getShapePickNodes();
		osg::Node* getShapePickNode();

		std::list<osg::ref_ptr<osg::Node>>& getCombdoorPickNodes();
		osg::Node* getCombdoorPickNode();

		//ȫ������ݺ���
		OpenThreads::ScopedReadLock getReadLock(){return getViewer()->getReadLock();}
		OpenThreads::ScopedWriteLock getWriteLock(){return getViewer()->getWriteLock();}


		//====================================================================================
		// ��ݷ��غ���
		//result����Data�ڵ�
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
