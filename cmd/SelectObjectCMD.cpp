#include "SelectObjectCMD.h"
#include "hgcw/hgCD/Combdoor.h"
#include "hgcw/hgCD/Mesh.h"
#include "hgcw/hgCD/CombdoorWriter.h"
#include "designerviewer/PickView.h"

namespace designer
{
	MgrCore::CmdRegister<SelectObjectCMD> SELECTOBJECTCMD;

	bool SelectObjectCMD::doIt(const MgrCore::WArgType &args)
	{
		using namespace CombdoorL;
		try
		{
			auto& data = args["data"];
			auto l = getViewer()->getWriteLock();
			auto cdview = getDocument()->getViewer()->CombdoorView();
			auto root = getDocument()->getViewer()->CombdoorRoot();
			auto viwer = dynamic_cast<PickView*>(cdview);
			viwer->removeAllPickNode();
			
			class SelectMeshIDVistor : public osg::NodeVisitor
			{
			public:
				SelectMeshIDVistor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),findMesh(NULL){}
				std::string strID;
				CombdoorL::Mesh* findMesh;

				virtual void apply(osg::Group& node)
				{
					if (dynamic_cast<CombdoorL::Mesh*>(&node) != NULL)
					{
						apply(*(dynamic_cast<CombdoorL::Mesh*>(&node)));
					}
					traverse(node);
				}

				virtual void apply(CombdoorL::Mesh& mesh)
				{
					if (mesh.Id() == strID)
					{
						findMesh = &mesh;
					}
				}
			};
			SelectMeshIDVistor vistor;
			vistor.strID = data["ID"].asString();

			if (!vistor.strID.empty())
			{
				root->accept(vistor);

				auto mesh = vistor.findMesh;
				if (mesh)
				{
					//Ñ¡Ôñ¶ÔÏó
					viwer->addPickNode(mesh);
				}
				
			}


			
		}
		catch (std::exception& e)
		{
			result(resError,e.what());
			//resultFormatRef() = getCMDFormat();
			return false;
		}
		return true;
	}

	Json::Value SelectObjectCMD::getCMDFormat()
	{
		IO io;
		io.format();
		return std::move(io.getOrMoveJson());
	}

	bool SelectObjectCMD::IO::isValid() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void SelectObjectCMD::IO::format()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}

