#include "Document.h"
#include "DesignerViewer/DesignerViewer.h"
#include "hgcd\MgrCoreCD\WCommandManager.h"
#include <osg/ValueObject>
#include <osgDB/FileNameUtils>


namespace designer
{
	Document::Document()
	{

	}


	void Document::SetToObject(osg::Object& obj,Document* ref)
	{
		obj.setUserData(ref);
	}

	Document* Document::GetFromObject(osg::Object& obj)
	{
		return dynamic_cast<Document*>(obj.getUserData());		
	}

	designer::DesignerViewer* Document::getOrCreateViewer()
	{
		if(_designerViewer) return _designerViewer;

		_designerViewer = new DesignerViewer(osgViewer::CompositeViewer::CullDrawThreadPerContext);
		
		//绑定document到各个View
		Document::SetToObject(*_designerViewer,this);
		Document::SetToObject(*_designerViewer->ShapeView(),this);
		Document::SetToObject(*_designerViewer->CombdoorView(),this);
		Document::SetToObject(*_designerViewer->ExtractView(),this);

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

	bool Document::executeCommand(const std::string& commmandName,Json::Value data)
	{
		MgrCore::ResultType resultStringList;
		return executeCommand(commmandName,std::move(data),resultStringList);
	}

	bool Document::executeCommand(const std::string& commmandName,Json::Value data,MgrCore::ResultType &resultStringList)
	{
		return executeJson(makeCommand(commmandName,std::move(data)),resultStringList);
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

	bool Document::sendToUI(const Json::Value& json)
	{
		if(_uiCall != nullptr)
			return (*_uiCall)(json);
		return false;
	}

	bool Document::sendToUI(const std::string& commmandName,const Json::Value& data)
	{
		Json::Value cmdjson;
		cmdjson["command"] = commmandName;
		cmdjson["data"] = data;
		return sendToUI(cmdjson);
	}

	bool Document::isEmpty() const
	{
		return (_designerViewer == nullptr 
			|| _designerViewer->CombdoorRoot() == nullptr 
			|| _designerViewer->CombdoorRoot()->getNumChildren() == 0);
	}

	void Document::setFilePath(std::string v)
	{
		_filePath = std::move(v);
		_fileName = osgDB::getStrippedName(_filePath);
	}

}