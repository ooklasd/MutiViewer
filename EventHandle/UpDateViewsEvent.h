#pragma once
#include "DesignerViewer/PickView.h"

namespace designer
{
	//����view������ѡ�¼�
	class DESIGNERCMD_API UpDateViewsEvent:public PickView::Event
	{
	public:
		virtual void operator()(PickView* v,osg::Node* n);


	private:
		void clearView(Document * document);
		
	};
}