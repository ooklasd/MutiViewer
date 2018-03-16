#pragma once
#include <osg/NodeVisitor>
#include <cmd/cmd.h>
#include "hgcw/hgCD/BaseIO.h"

namespace designer
{
	//====================================================================================
	// ≤È—Ø≥°æ∞
	//====================================================================================

	class QueryInfoByIDCMD : public cmd
	{
	public:
		CMD_STATIC(QueryInfoByID);

		virtual bool isUndoable(){return false;}

		virtual bool doIt(const MgrCore::WArgType &args);

		virtual Json::Value getCMDFormat();
	};
}