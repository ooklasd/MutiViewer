#include "PickView.h"
#include "Document/Document.h"



designer::Document* designer::PickView::getDocument()
{
	return Document::GetFromObject(*this);
}

bool designer::PickView::isSelect(osg::Node* n)
{
	return std::find(_pickNodes.begin(),_pickNodes.end(),n) != _pickNodes.end();
}

void designer::PickView::addPickNode(osg::Node* n)
{
	_lastPickNodes = _pickNodes;
	_pickNodes.push_back(n);
	Event::CallEvents(_addEvents,this,n);

}

void designer::PickView::removePickNode(osg::Node* n)
{
	_lastPickNodes = _pickNodes;
	_pickNodes.remove(n);
	Event::CallEvents(_removeEvents,this,n);
}

void designer::PickView::removeAllPickNode()
{
	_lastPickNodes = _pickNodes;
	_pickNodes.clear();
	Event::CallEvents(_removeAllEvents,this,nullptr);
}


void designer::PickView::Event::CallEvents(Event::List& l,PickView* v,osg::Node* n)
{
	for (auto it = l.begin();it != l.end();++it)
	{
		(**it)(v,n);
	}
}