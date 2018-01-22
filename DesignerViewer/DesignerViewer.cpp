#include "DesignerViewer.h"
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

namespace designer
{

	DesignerViewer::DesignerViewer(osgViewer::ViewerBase::ThreadingModel threadingModel/*=osgViewer::CompositeViewer::SingleThreaded*/)
	{
		setThreadingModel(threadingModel);

		_shapeRoot = new osg::Group();
		_extractRoot = new osg::Group();
		_combdoorRoot = new osg::Group();

		//创建三个视图
		_shapeView = new osgViewer::View();
		_extractView = new osgViewer::View();
		_combdoorView = new osgViewer::View();
				
	}
}
