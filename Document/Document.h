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
		//����ͼ
		DesignerViewer* getViewer(){return _designerViewer;}
		const DesignerViewer* getViewer()const {return _designerViewer;}

		//���������
		MgrCore::WCommandManager& WCommandManager() { return _wCommandManager; }

	public:
		// ִ������json������json
		bool executeJson(const Json::Value& json,MgrCore::ResultType &resultStringList);
		bool executeJson(const Json::Value& json);

		// ִ������string,����json
		bool executeString(const TCHAR* commandString,MgrCore::ResultType &resultStringList);
		bool executeString(const TCHAR* commandString);

	protected:
		//����ͼ
		osg::ref_ptr<DesignerViewer> _designerViewer;

		//���������
		MgrCore::WCommandManager _wCommandManager;

		std::string _fileName;//�ļ�ȫ·��
		std::string _filePath;//�����ļ���·��
	};


}

