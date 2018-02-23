#include "Document.h"
#include "DesignerViewer/DesignerViewer.h"
#include "hgcd\MgrCoreCD\WCommandManager.h"


namespace designer
{
	Document::Document()
	{

	}


	designer::DesignerViewer* Document::getOrCreateViewer()
	{
		_designerViewer = new DesignerViewer(osgViewer::CompositeViewer::CullDrawThreadPerContext);
		return _designerViewer;
	}

	Document* Document::cloneType() const
	{
		return new Document();
	}

	osg::Object* Document::clone(const osg::CopyOp&) const
	{
		throw std::logic_error("The method or operation is not implemented.");
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

	bool Document::executeCommand(const std::string& commmandName,const Json::Value& data)
	{
		MgrCore::ResultType resultStringList;
		return executeCommand(commmandName,data,resultStringList);
	}

	bool Document::executeCommand(const std::string& commmandName,const Json::Value& data,MgrCore::ResultType &resultStringList)
	{
		return executeJson(makeCommand(commmandName,data),resultStringList);
	}

	Json::Value Document::makeCommand(const std::string& commmandName,const Json::Value& data)
	{
		Json::Value res;
		res["command"] = commmandName;
		res["data"] = data;
		return std::move(res);
	}

	Json::Value Document::makeCommand(const std::string& commmandName,Json::Value&& data)
	{
		Json::Value res;
		res["command"] = commmandName;
		res["data"] = std::move(data);
		return std::move(res);
	}

	bool Document::isEmpty() const
	{
		return (_designerViewer == nullptr || _designerViewer->CombdoorRoot() == nullptr || _designerViewer->CombdoorRoot()->getNumChildren() == 0);
	}

}