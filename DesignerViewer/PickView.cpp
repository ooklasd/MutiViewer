#include "PickView.h"




bool designer::PickView::isSelect(osg::Node* n)
{
	return std::find(_pickNodes.begin(),_pickNodes.end(),n) != _pickNodes.end();
}

void designer::PickView::addPickNode(osg::Node* n)
{
	_lastPickNodes = _pickNodes;
	_pickNodes.push_back(n);
	CallEvents(_addEvents,this,n);

}

void designer::PickView::removePickNode(osg::Node* n)
{
	_lastPickNodes = _pickNodes;
	_pickNodes.remove(n);
	CallEvents(_removeEvents,this,n);
}

void designer::PickView::removeAllPickNode()
{
	_lastPickNodes = _pickNodes;
	_pickNodes.clear();
	CallEvents(_removeAllEvents,this,nullptr);
}


void designer::PickView::CallEvents(EventList& l,PickView* v,osg::Node* n)
{
	for (auto it = l.begin();it != l.end();++it)
	{
		(**it)(v,n);
	}
}