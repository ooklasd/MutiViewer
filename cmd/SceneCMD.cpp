#include "SceneCMD.h"
#include "hgcw/hgCD/Combdoor.h"

namespace designer
{
	MgrCore::CmdRegister<QuerySceneInfoCMD> QUERYSCENEINFOCMD;

	bool QuerySceneInfoCMD::doIt(const MgrCore::WArgType &args)
	{
		try
		{
			auto& data = args["data"];
			auto l = getViewer()->getReadLock();
			
			auto root = getDocument()->getViewer()->CombdoorRoot();
			
			//使用遍历器获取信息
			SceneInfoVisitor siV;
			root->accept(siV);

			result(resOK,std::move(siV.getResult()));
			return true;
		}
		catch (std::exception& e)
		{
			result(resError,e.what());
			return false;
		}
		return true;
	}

	void SceneInfoVisitor::apply(osg::Node& node)
	{

	}

	void SceneInfoVisitor::apply(osg::Geode& node)
	{

	}

	void SceneInfoVisitor::apply(osg::Group& node)
	{

	}

}

