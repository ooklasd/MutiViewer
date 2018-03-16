#pragma once
#include <osg/NodeVisitor>
#include <cmd/cmd.h>
#include "hgcw/hgCD/BaseIO.h"

namespace CombdoorL
{
	class Combdoor;
	class LocateEntity;
}
namespace designer
{
	//====================================================================================
	// ≤È—Ø≥°æ∞
	//====================================================================================

	class QueryLayoutInfoCMD : public cmd
	{
	public:
		CMD_STATIC(QueryLayoutInfo);

		virtual bool isUndoable(){return false;}
		
		virtual bool doIt(const MgrCore::WArgType &args);

		virtual Json::Value getCMDFormat();
	};	


	class AddUpdateLayoutInfoCMD : public cmd
	{
	public:
		CMD_STATIC(AddUpdateLayoutInfo);

		virtual bool isUndoable(){return false;}

		virtual bool doIt(const MgrCore::WArgType &args);

		virtual Json::Value getCMDFormat();

	
		static CombdoorL::Combdoor* getCurCombdoor(osg::Node* root);

	protected:
		CombdoorL::LocateEntity* addLocateEntity(const Json::Value& data);
	};	

	class DeleteLocateEntityCMD : public cmd
	{
	public:
		CMD_STATIC(DeleteLocateEntity);

		virtual bool isUndoable(){return false;}

		virtual bool doIt(const MgrCore::WArgType &args);

		virtual Json::Value getCMDFormat();
	};

}