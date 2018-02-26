#include "UpDateViewsEvent.h"

#include <osg/LineSegment>


#include "Document/Document.h"
#include "hgcw/hgCD/Mesh.h"

void designer::UpDateViewsEvent::operator()(PickView* v,osg::Node* n)
{
	auto& pickNodes = v->getPickNodes();
	auto document = Document::GetFromObject(*v);
	if(document == nullptr) return;
	clearView(document);
	//空白
	if(!pickNodes.empty())
	{
		//显示最后点选的物体，包括点选和取消点选
		auto curPick = pickNodes.back();
		auto mesh = dynamic_cast<CombdoorL::Mesh*>(curPick.get());
		if(mesh != nullptr)
		{
			//设置拉伸面
			document->getViewer()->ExtractRoot()->addChild(mesh);

			//设置横截面
			//根据横截面生成geometry
			osg::ref_ptr<osg::Node> shapelineNode = nullptr;
						
			osg::ref_ptr<osg::Vec3Array> shapeLine = dynamic_cast<osg::Vec3Array*>(mesh->getShapeLine()->clone(osg::CopyOp::DEEP_COPY_ALL));
			osg::ref_ptr<osg::Geometry> shaplineGe = new osg::Geometry();
			shaplineGe->setVertexArray(shapeLine);
			/*shaplineGe->setColorArray(new osg::Vec2Array(1));
			shaplineGe->setColorBinding(osg::Geometry::BIND_OVERALL);*/

			osg::ref_ptr<osg::DrawElementsUShort> ele = new osg::DrawElementsUShort(osg::PrimitiveSet::LINE_LOOP,shapeLine->size());
			//ele->reserveElements(shapeLine->size());
			for (int i = 0;i< shapeLine->size();++i)
			{
				ele->push_back(i);
			}
			shaplineGe->addPrimitiveSet(ele);
			
			osg::ref_ptr<osg::Geode> geode = new osg::Geode();
			geode->addDrawable(shaplineGe);
			shapelineNode = geode;

			//document->getViewer()->ShapeRoot()->addChild(shapelineNode);			
			document->getViewer()->ShapeRoot()->addChild(shapelineNode);	
			document->getViewer()->ExtractView()->home();
			document->getViewer()->ShapeView()->home();
		}
	}


}

void designer::UpDateViewsEvent::clearView(Document * document)
{
	auto root = document->getViewer()->ExtractRoot();
	root->removeChildren(0,root->getNumChildren());
	root = document->getViewer()->ShapeRoot();
	root->removeChildren(0,root->getNumChildren());
}
