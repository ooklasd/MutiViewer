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

		virtual Json::Value getCMDFormat();

	public:
		class DESIGNERCMD_API IO : public CombdoorIO::BaseIO
		{
		public:
			IO_OBJECT(IO,CombdoorIO::BaseIO);

			JsonMember(isMesh,bool);
			JsonMember(isMaterial,bool);
			JsonMember(isShapeline,bool);
			JsonMember(isLayout,bool);
			JsonMember(isAll,bool);

			virtual bool isValid() const;

			virtual void format();
		};
	};	
}