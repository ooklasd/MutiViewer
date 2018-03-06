#include "DesignerViewer.h"
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include "PickView.h"

namespace designer
{

	DesignerViewer::DesignerViewer(osgViewer::ViewerBase::ThreadingModel threadingModel/*=osgViewer::CompositeViewer::SingleThreaded*/)
	{
		setThreadingModel(threadingModel);

		_shapeRoot = new osg::Group();
		_extractRoot = new osg::Group();
		_combdoorRoot = new osg::Group();

		//����������ͼ
		_shapeView = new osgViewer::View();
		_extractView = new osgViewer::View();
		_combdoorView = new PickView();

	}

	void DesignerViewer::frame(double simulationTime/*=USE_REFERENCE_TIME*/)
	{
		if (_done) return;

		// OSG_NOTICE<<std::endl<<"CompositeViewer::frame()"<<std::endl<<std::endl;

		if (_firstFrame)
		{
			viewerInit();

			if (!isRealized())
			{
				realize();
			}

			_firstFrame = false;
		}
		advance(simulationTime);
		eventTraversal();

		auto lock = getReadLock();
		updateTraversal();
		renderingTraversals();
	}

	void DesignerViewer::clearRoot()
	{
		auto numV = getNumViews();
		for (int i = 0;i<numV;++i)
		{
			auto v = getView(i);
			auto g = dynamic_cast<osg::Group*>(v->getSceneData());
			if(g) g->removeChildren(0,g->getNumChildren());
		}
	}

}
