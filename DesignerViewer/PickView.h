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
		
		//���ĳ�����㣬��˵���Ƿ�Ϊ��ѡ
		//�������Ѿ���ѡ����ȡ��ѡ��
		bool isSelect(osg::Node* n);

		//��ӵ�ѡ�ڵ㣬����OnChangePickNode
		void addPickNode(osg::Node* n);

		//ɾ����ѡ�ڵ㣬����OnChangePickNode
		void removePickNode(osg::Node* n);

		//���ѡ�㣬����OnChangePickNode
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
		std::list<osg::ref_ptr<osg::Node>> _pickNodes;//��ǰ�ڵ�
		std::list<osg::ref_ptr<osg::Node>> _lastPickNodes;//��ǰ�ڵ�

		Event::List _addEvents;
		Event::List _removeEvents;
		Event::List _removeAllEvents;

		
	};
}