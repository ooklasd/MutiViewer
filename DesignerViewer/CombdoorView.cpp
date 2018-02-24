#include "CombdoorView.h"




bool designer::CombdoorView::isSelect(osg::Node* n)
{
	return std::find(_pickNodes.begin(),_pickNodes.end(),n) != _pickNodes.end();
}

void designer::CombdoorView::addPickNode(osg::Node* n)
{
	_lastPickNodes = _pickNodes;
	_pickNodes.push_back(n);
	Event::CallEvents(_addEvents,this,n);

}

void designer::CombdoorView::removePickNode(osg::Node* n)
{
	_lastPickNodes = _pickNodes;
	_pickNodes.remove(n);
	Event::CallEvents(_removeEvents,this,n);
}

void designer::CombdoorView::removeAllPickNode()
{
	_lastPickNodes = _pickNodes;
	_pickNodes.clear();
	Event::CallEvents(_removeAllEvents,this,nullptr);
}


void designer::CombdoorView::Event::CallEvents(Event::List& l,CombdoorView* v,osg::Node* n)
{
	for (auto it = l.begin();it != l.end();++it)
	{
		(**it)(v,n);
	}
}