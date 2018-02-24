#pragma once
#include"Export.h"
#include <osgViewer/View>
#include <list>
#include <map>
namespace designer
{
	class DESIGNERCMD_API PickView: public osgViewer::View
	{
	public:

		virtual osg::Object* clone(const osg::CopyOp& copyop) const{
			return new PickView(*this);
		}

		virtual const char* className() const{return "PickView";}
		virtual const char* libraryName() const{return "DesignerCMD";}

		const std::list<osg::ref_ptr<osg::Node>>& getPickNodes() const{ return _pickNodes; }
		const std::list<osg::ref_ptr<osg::Node>>& getLastPickNodes() const{ return _lastPickNodes; }
		
		//点击某个几点，并说明是否为多选
		//若物体已经点选，则取消选择
		bool isSelect(osg::Node* n);

		//添加点选节点，触发OnChangePickNode
		void addPickNode(osg::Node* n);

		//删除点选节点，触发OnChangePickNode
		void removePickNode(osg::Node* n);

		//清空选点，触发OnChangePickNode
		void removeAllPickNode();

	public:
		class Event :public osg::Referenced
		{
		public:
			typedef std::list<osg::ref_ptr<Event>> List;
			static void CallEvents(Event::List& l,PickView* v,osg::Node* n);
			virtual ~Event(){}
			virtual void operator()(PickView* v,osg::Node* n) = 0;
		};

		Event::List& AddEvents(){return _addEvents;}
		Event::List& RemoveEvents(){return _removeEvents;}
		Event::List& RemoveAllEvents(){return _removeAllEvents;}

	protected:
		std::list<osg::ref_ptr<osg::Node>> _pickNodes;//当前节点
		std::list<osg::ref_ptr<osg::Node>> _lastPickNodes;//当前节点

		Event::List _addEvents;
		Event::List _removeEvents;
		Event::List _removeAllEvents;

		
	};
}