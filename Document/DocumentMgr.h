#pragma once
#include "..\Export.h"
#include "Document.h"
#include <vector>
#include <list>
#include <functional>
#include <unordered_set>

//��ȡdocument������
#define g_DocumentMgr (designer::DocumentMgr::Instance())

//��ȡ��ǰ���ĵ�
#define g_DocumentPtr (g_DocumentMgr.CurDocument())
#define g_Document (*g_DocumentMgr.CurDocument())

namespace designer
{
	class DESIGNERCMD_API DocumentMgr;
	class Document;
	class DocumentMgr
	{
	public:
		typedef std::vector<osg::ref_ptr<Document>> DocumentVector;

		typedef std::function<bool(Document *, Document * )> PreChangeFunc;
		typedef std::function<void(Document *, Document * )> OnChangeFunc;

		typedef std::list<PreChangeFunc> PreChangeEvent;
		typedef std::list<OnChangeFunc> OnChangeEvent;

		designer::Document* CurDocument() const { return _curDocument.get(); }
		void CurDocument(designer::Document* newValue) {
			if(newValue == _curDocument) return;
			
			for (auto it = _PreChangeDocumentEvent.begin();it != _PreChangeDocumentEvent.end();++it)
			{
				bool res = (*it)(_curDocument.get(),newValue);

				//��ͨ��ֱ�ӷ���
				if(!res) return;
			}

			//��ֵ
			auto old = _curDocument;
			_curDocument = newValue; 

			for (auto it = _OnChangeDocumentEvent.begin();it != _OnChangeDocumentEvent.end();++it)
			{
				(*it)(old.get(),_curDocument.get());
			}			
		}		
	public:
		static DocumentMgr& Instance();
		virtual ~DocumentMgr(){}

		Document* getDocument(size_t index){return _documentVector.at(index);}
		const Document* getDocument(size_t index)const {return _documentVector.at(index);}

		size_t addDocument(Document* pdoc);
		size_t removeDocument(Document* pdoc);

		size_t getDocumentIndex(Document* pdoc) const;

	protected:
		DocumentVector _documentVector;
		osg::ref_ptr<Document> _curDocument;
		void * _UIPtr;


		//====================================================================================
		// �¼�������
		//====================================================================================
	public:
		PreChangeEvent& PreChangeDocumentEvent() { return _PreChangeDocumentEvent; }
		OnChangeEvent& OnChangeDocumentEvent() { return _OnChangeDocumentEvent; }
	protected:

		//�ڱ仯֮ǰ�¼����Ƿ�ͨ��(�仯ǰ���仯��)
		PreChangeEvent _PreChangeDocumentEvent;

		//�仯���¼���void(�仯ǰ���仯��)
		OnChangeEvent _OnChangeDocumentEvent;
		

	private:
		DocumentMgr(DocumentMgr& rhs){*this = rhs;}
		DocumentMgr(){}



	};

}