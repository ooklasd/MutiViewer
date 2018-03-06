#include "SceneCMD.h"
#include "hgcw/hgCD/Combdoor.h"
#include "hgcw/hgCD/CombdoorWriter.h"

namespace designer
{
	MgrCore::CmdRegister<QuerySceneInfoCMD> QUERYSCENEINFOCMD;

	bool QuerySceneInfoCMD::doIt(const MgrCore::WArgType &args)
	{
		using namespace CombdoorL;
		try
		{
			const auto data = IO(args["data"]);

			unsigned type = 0;
			if(data.get_isLayout(false)) type |= CombdoorWriter::LAYOUT;
			if(data.get_isMaterial(false)) type |= CombdoorWriter::MATERIAL;
			if(data.get_isMesh(false)) type |= CombdoorWriter::MESH;
			if(data.get_isShapeline(false)) type |= CombdoorWriter::SHAPELINE;
			if(data.get_isAll(false)) type |= CombdoorWriter::ALL;


			auto l = getViewer()->getReadLock();
			
			auto root = getDocument()->getViewer()->CombdoorRoot();
			
			//使用遍历器获取信息
			CombdoorWriter writer(type);
			auto cbd = dynamic_cast<Combdoor*>(root->getChild(0));
			if(cbd)
				writer.write(cbd);

#ifdef _DEBUG
			std::string res = Json::StyledWriter().write(writer.Result());
#endif // _DEBUG

			result(resOK,std::move(writer.Result()));
			return true;
		}
		catch (std::exception& e)
		{
			result(resError,e.what());
			resultFormatRef() = getCMDFormat();
			return false;
		}
		return true;
	}

	Json::Value QuerySceneInfoCMD::getCMDFormat()
	{
		IO io;
		io.format();
		return std::move(io.getOrMoveJson());
	}

	bool QuerySceneInfoCMD::IO::isValid() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void QuerySceneInfoCMD::IO::format()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}

