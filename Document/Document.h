#pragma once
#include <osg/Referenced>
#include <osg/ref_ptr>
#include "..\Export.h"
#include <osgViewer/CompositeViewer>
#include "..\DesignerViewer/DesignerViewer.h"
#include "hgcd\MgrCoreCD\WCommandManager.h"

class MgrCore::WCommandManager;

namespace designer
{
	class DESIGNERCMD_API Document;


	class DesignerViewer;
	class Document :public osg::Object
	{
	public: 
		Document();

	public:
		//����ͼ
		DesignerViewer* getOrCreateViewer();
		DesignerViewer* getViewer(){return _designerViewer;}
		const DesignerViewer* getViewer()const {return _designerViewer;}

		//���������
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

	public:
		// ִ������json������json
		bool executeJson(const Json::Value& json,MgrCore::ResultType &resultStringList);
		bool executeJson(const Json::Value& json);

		// ִ������string,����json
		bool executeString(const TCHAR* commandString,MgrCore::ResultType &resultStringList);
		bool executeString(const TCHAR* commandString);

		bool executeCommand(const std::string& commmandName,const Json::Value& data,MgrCore::ResultType &resultStringList);
		bool executeCommand(const std::string& commmandName,const Json::Value& data = Json::Value());

		static Json::Value makeCommand(const std::string& commmandName,const Json::Value& data);
		static Json::Value makeCommand(const std::string& commmandName,Json::Value&& data);

		class jsonCall : public osg::Referenced
		{
		public:
			virtual ~jsonCall(){}
			virtual bool operator()(const Json::Value& cmdJson) = 0;
		};

		//������UI
		void setUiCall(jsonCall* val) { _uiCall = val; }

		bool sendToUI(const Json::Value& json);
		bool sendToUI(const std::string& commmandName,const Json::Value& data);

public:
		//�Ƿ�Ϊ�հ��ĵ�
		bool isEmpty()const;

	protected:
		osg::ref_ptr<jsonCall> _uiCall;

		//����ͼ
		osg::ref_ptr<DesignerViewer> _designerViewer;

		//���������
		MgrCore::WCommandManager _wCommandManager;

		std::string _fileName;//�ļ�ȫ·��
		std::string _filePath;//�����ļ���·��
		
	};


}

