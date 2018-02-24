#pragma once
#include "hgcd/MgrCoreCD/WICommand.h"
#include "..\Document/Document.h"
#include "..\Export.h"

class MgrCore::WICommand;


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


		//====================================================================================
		// ��ݷ��غ���
		//result����Data�ڵ�
		//====================================================================================
		Json::Value& result(int code);
		Json::Value& result(int code,const char* str);
		Json::Value& result(int code,const Json::Value& data);
		Json::Value& result(int code,Json::Value&& data);
	};
}
