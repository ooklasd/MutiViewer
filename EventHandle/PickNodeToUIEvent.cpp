#include "PickNodeToUIEvent.h"

#include <osg/LineSegment>


#include "Document/Document.h"
#include "hgcw/hgCD/Mesh.h"

void designer::PickNodeToUIEvent::operator()(PickView* v,osg::Node* n)
{
	auto& pickNodes = v->getPickNodes();
	auto document = Document::GetFromObject(*v);
	if(document == nullptr) return;
	clearView(document);
	//�հ�
	if(!pickNodes.empty())
	{
		//��ʾ����ѡ�����壬������ѡ��ȡ����ѡ
		auto curPick = pickNodes.back();
		auto mesh = dynamic_cast<CombdoorL::Mesh*>(curPick.get());
		if(mesh != nullptr && mesh->getMeshEntity())
		{
			Json::Value v;
			v["id"] = mesh->Id();
			document->sendToUI("SelectTreeItem",std::move(v));
		}
	}


}

void designer::PickNodeToUIEvent::clearView(Document * document)
{
	auto root = document->getViewer()->ExtractRoot();
	root->removeChildren(0,root->getNumChildren());
	root = document->getViewer()->ShapeRoot();
	root->removeChildren(0,root->getNumChildren());
}
