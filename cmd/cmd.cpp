#include "cmd.h"


namespace designer
{





	std::list<osg::ref_ptr<osg::Node>>& cmd::getShapePickNodes()
	{
		return getViewer()->ShapePickNodes();
	}

	osg::Node* cmd::getShapePickNode()
	{
		if(getShapePickNodes().empty()) return nullptr;
		return getShapePickNodes().empty()?nullptr:getShapePickNodes().back();
	}

	std::list<osg::ref_ptr<osg::Node>>& cmd::getCombdoorPickNodes()
	{
		return getViewer()->CombdoorPickNodes();
	}

	osg::Node* cmd::getCombdoorPickNode()
	{

		if(getCombdoorPickNodes().empty()) return nullptr;
		return getCombdoorPickNodes().empty()?nullptr:getCombdoorPickNodes().back();
	}

}