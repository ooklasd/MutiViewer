#pragma once
#include "DesignerViewer/PickView.h"

namespace designer
{
	//====================================================================================
	// 拾取点选三维对象的ID，发送到UI中
	//====================================================================================
	class DESIGNERCMD_API PickNodeToUIEvent:public PickView::Event
	{
	public:
		virtual void operator()(PickView* v,osg::Node* n);


	private:
		void clearView(Document * document);
		
	};
}