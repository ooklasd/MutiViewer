#pragma once
#include <osgViewer/CompositeViewer>
#include <OpenThreads/ReadWriteMutex>
#include "..\Export.h"
class osgViewer::CompositeViewer;
class osg::Camera;
class osgViewer::View;

namespace designer
{
	class DESIGNERCMD_API DesignerViewer;
	class DesignerViewer : public osgViewer::CompositeViewer
	{
	public:
		DesignerViewer(osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::AutomaticSelection);
						
		//====================================================================================
		// 获取视口
		//====================================================================================
		void ShapeView(osgViewer::View* val) { _shapeView = val; }				
		void ExtractView(osgViewer::View* val) { _extractView = val; }
		void CombdoorView(osgViewer::View* val) { _combdoorView = val; }

		const osgViewer::View* ShapeView() const { return _shapeView; }
		const osgViewer::View* ExtractView() const { return _extractView; }
		const osgViewer::View* CombdoorView() const { return _combdoorView; }


		osgViewer::View* ShapeView() { return _shapeView; }
		osgViewer::View* ExtractView() { return _extractView; }
		osgViewer::View* CombdoorView() { return _combdoorView; }

		//====================================================================================
		// 获取根节点
		//====================================================================================
		const osg::Group* ShapeRoot() const { return _shapeRoot.get(); }
		const osg::Group* ExtractRoot() const { return _extractRoot.get(); }
		const osg::Group* CombdoorRoot() const { return _combdoorRoot.get(); }

		osg::Group* ShapeRoot() { return _shapeRoot; }
		osg::Group* ExtractRoot() { return _extractRoot; }
		osg::Group* CombdoorRoot() { return _combdoorRoot; }


		std::list<osg::ref_ptr<osg::Node>>& ShapePickNodes() { return _shapePickNodes; }
		std::list<osg::ref_ptr<osg::Node>>& CombdoorPickNodes() { return _combdoorPickNodes; }

		

		virtual void frame(double simulationTime=USE_REFERENCE_TIME);

		OpenThreads::ScopedReadLock getReadLock(){return OpenThreads::ScopedReadLock(_frameMutex);}
		OpenThreads::ScopedWriteLock getWriteLock(){return OpenThreads::ScopedWriteLock(_frameMutex);}

	public:
		void clearRoot();

	protected:

		//轮廓线视图
		osg::ref_ptr<osgViewer::View> _shapeView;

		//拉伸长条视图
		osg::ref_ptr<osgViewer::View> _extractView;

		//门板视图
		osg::ref_ptr<osgViewer::View> _combdoorView;

		osg::ref_ptr<osg::Group> _shapeRoot,_extractRoot,_combdoorRoot;

		//当前点选的节点
		std::list<osg::ref_ptr<osg::Node>> _shapePickNodes,_extractPickNodes,_combdoorPickNodes;

		OpenThreads::ReadWriteMutex _frameMutex;
	};

}
