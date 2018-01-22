#include "DocumentMgr.h"
#include <iterator>
#include <algorithm>

#include <osg/NodeCallback>

namespace designer
{
	DocumentMgr& DocumentMgr::Instance()
	{
		static DocumentMgr mgr;
		return mgr;

		mgr.PreChangeDocumentEvent().push_back([](Document *olddoc,Document *newdoc)->bool{

			return true;
		});
	}

	size_t DocumentMgr::getDocumentIndex(Document* pdoc) const
	{
		auto itf = std::find(_documentVector.begin(),_documentVector.end(),pdoc);
		return (itf==_documentVector.end())?(size_t)(-1):std::distance(itf,_documentVector.end());
	
	}


}