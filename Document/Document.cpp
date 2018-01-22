#include "Document.h"
#include "DesignerViewer/DesignerViewer.h"
#include "hgcd\MgrCoreCD\WCommandManager.h"


namespace designer
{
	Document::Document()
	{

	}


	bool Document::executeJson(const Json::Value& json,MgrCore::ResultType &resultStringList)
	{
		return _wCommandManager.executeJson(json,resultStringList,this);
	}

	bool Document::executeJson(const Json::Value& json)
	{
		MgrCore::ResultType resultStringList;
		return _wCommandManager.executeJson(json,resultStringList,this);
	}

	bool Document::executeString(const TCHAR* commandString,MgrCore::ResultType &resultStringList)
	{
		return _wCommandManager.executeString(commandString,resultStringList,this);
	}

	bool Document::executeString(const TCHAR* commandString)
	{
		MgrCore::ResultType resultStringList;
		return _wCommandManager.executeString(commandString,resultStringList,this);
	}

}