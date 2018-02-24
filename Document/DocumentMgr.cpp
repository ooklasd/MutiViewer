#include "DocumentMgr.h"
#include <iterator>
#include <algorithm>

#include <osg/NodeCallback>

namespace designer
{
	class op 
	{
	public:
		bool operator()(Document *olddoc,Document *newdoc)
		{
			return true;
		}
	};
	DocumentMgr& DocumentMgr::Instance()
	{
		static DocumentMgr mgr;
		return mgr;
#ifdef _DEBUG
		mgr.PreChangeDocumentEvent().push_back([](Document *olddoc,Document *newdoc)->bool{

			return true;
		});

		mgr.PreChangeDocumentEvent().push_back(op());
#endif
	}

	size_t DocumentMgr::addDocument(Document* pdoc)
	{
		_documentVector.push_back(pdoc);return _documentVector.size()-1;
	}

	size_t DocumentMgr::removeDocument(Document* pdoc)
	{
		auto itf = std::find(_documentVector.begin(),_documentVector.end(),pdoc);
		if(itf != _documentVector.end())
		{
			_documentVector.erase(itf);
		}
		return _documentVector.size()-1;
	}

	size_t DocumentMgr::getDocumentIndex(Document* pdoc) const
	{
		auto itf = std::find(_documentVector.begin(),_documentVector.end(),pdoc);
		return (itf==_documentVector.end())?(size_t)(-1):std::distance(_documentVector.begin(),itf);
	
	}


}