#pragma once
#include "DesignerViewer/PickView.h"

namespace designer
{
	//====================================================================================
	// ʰȡ��ѡ��ά�����ID�����͵�UI��
	//====================================================================================
	class DESIGNERCMD_API PickNodeToUIEvent:public PickView::Event
	{
	public:
		virtual void operator()(PickView* v,osg::Node* n);


	private:
		void clearView(Document * document);
		
	};
}