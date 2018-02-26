#pragma once
#include "DesignerViewer/PickView.h"

namespace designer
{
	//更新view——点选事件
	class DESIGNERCMD_API UpDateViewsEvent:public PickView::Event
	{
	public:
		virtual void operator()(PickView* v,osg::Node* n);


	private:
		void clearView(Document * document);
		
	};
}