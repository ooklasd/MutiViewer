#pragma once
#include <osg/NodeVisitor>
#include <cmd/cmd.h>
#include "hgcw/hgCD/BaseIO.h"
namespace designer
{
	//====================================================================================
	// ≤È—Ø≥°æ∞
	//====================================================================================

	class QuerySceneInfoCMD : public cmd
	{
	public:
		CMD_STATIC(QuerySceneInfo);

		virtual bool isUndoable(){return false;}


		virtual bool doIt(const MgrCore::WArgType &args);

	public:
		class IO : public CombdoorIO::BaseIO
		{

		};

	};

	class SceneInfoVisitor : public osg::NodeVisitor
	{
	public:
		SceneInfoVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
		{
			_parentJson = nullptr;
		}
		Json::Value& getResult(){return _infoJson;}
		const Json::Value& getResult()const {return _infoJson;}

		virtual void apply(osg::Node& node);

		virtual void apply(osg::Geode& node);

		virtual void apply(osg::Group& node);

	private:
		Json::Value _infoJson;
		Json::Value* _parentJson;
	};

	
}