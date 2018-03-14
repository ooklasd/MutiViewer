#include "LayoutCMD.h"
#include "hgcw/hgCD/IDVisitor.h"
#include "hgcw/hgCD/LocateEntity.h"
#include "hgcw/hgCD/CombdoorWriter.h"
#include "hgcw/hgCD/LayoutNodeIO.h"
#include "hgcw/hgCD/LocateEntity.h"
#include "hgcw/hgCD/Combdoor.h"
#include "hgcw/hgCD/Mesh.h"
#include "hgcw/hgCD/LocationCreater.h"
#include "hgcw/hgCD/TClassVisitor.h"
#include "hgcw/hgCD/CombdoorReader.h"

namespace designer
{
	MgrCore::CmdRegister<QueryLayoutInfoCMD> QUERYLAYOUTINFOCMD;

	bool QueryLayoutInfoCMD::doIt(const MgrCore::WArgType &args)
	{
		using namespace CombdoorL;
		try
		{
			auto& data = args["data"];
			auto id = data["id"].asString();
			auto l = getReadLock();
			
			auto idV = LocateEntityIDVisitor(id,1);
			getCombdoorRoot()->accept(idV);
			auto& nodeList = idV.NodeList();
			if(nodeList.empty()) 
				throw std::logic_error("没有找到ID:"+id+"节点");

			LocateEntity* node = nodeList.front();
			CombdoorWriter::WriteOneLocateEntity(node,resultDataRef());
			result(resOK);
		}
		catch (std::exception& e)
		{
			result(resError,e.what());
			resultFormatRef() = getCMDFormat();
			return false;
		}

		return true;
	}

	Json::Value QueryLayoutInfoCMD::getCMDFormat()
	{
		Json::Value format;
		format["id"] = "";
		return std::move(format);
	}

	MgrCore::CmdRegister<AddUpdateLayoutInfoCMD> ADDUPDATELAYOUTINFOCMD;
	bool AddUpdateLayoutInfoCMD::doIt(const MgrCore::WArgType &args)
	{
		using namespace CombdoorL;
		using namespace CombdoorIO;
		try
		{
			auto& data = args["data"];
			const auto layoutio = CombdoorIO::LayoutNodeIO(data);
			bool isAdd = layoutio.idIsNull();


			osg::ref_ptr<LocateEntity> ent;
			if(isAdd)
			{
				//按照类型新建布局实体
				ent = addLocateEntity(data);
			}
			else
			{
				auto lread = getReadLock();			
				//找到实体然后更新
				auto id = layoutio.get_id();
				LocateEntityIDVisitor idV(layoutio.get_id(),1);
				getCombdoorRoot()->accept(idV);

				if(idV.getNodeList().empty())
					throw std::logic_error("没有找到ID:"+id+"的实体");
				
				ent = idV.getNodeList().front();
			}
			if(ent == nullptr)
			{
				throw std::logic_error("没有实体可以操作");
			}

			auto l = getWriteLock();

			auto doorNode = dynamic_cast<Combdoor*>(getCombdoorRoot()->getChild(0));
			auto db = doorNode->getDB();
			
			//更新布局信息
			if(layoutio.nameIsNull() == false){
				ent->setName(layoutio.get_name());
			}

			//统一UV
			if(layoutio.textureAutoUVIsNull() == false){				
				ent->setAutoUVFromJson(layoutio.get_textureAutoUV().JsonRef());
			}

			//更新布局
			if(layoutio.layoutIsNull() == false){
				auto location = LocationCreater::LayoutOnLoad(layoutio.get_layout(),ent);
				ent->setLocation(location);
			}

			result(resOK);
		}
		catch (std::exception& e)
		{
			result(resError,e.what());
			resultFormatRef() = getCMDFormat();
			return false;
		}
		return true;
	}

	Json::Value AddUpdateLayoutInfoCMD::getCMDFormat()
	{
		return Json::Value();
	}

	CombdoorL::Combdoor* AddUpdateLayoutInfoCMD::getCurCombdoor(osg::Node* root)
	{
		using namespace CombdoorL;
		auto visitor = TClassVisitor<Combdoor>(1);
		root->accept(visitor);
		return visitor.Result().empty()?nullptr:visitor.Result().front();
	}

	CombdoorL::LocateEntity* AddUpdateLayoutInfoCMD::addLocateEntity(const Json::Value& data)
	{
		using namespace CombdoorL;
		auto l = getReadLock();
		osg::ref_ptr<Combdoor> d =  getCurCombdoor(getCombdoorRoot());
		return CombdoorReader::CreateLayoutStatic(data,"",0,0);
	}

	bool DeleteLayoutInfoCMD::doIt(const MgrCore::WArgType &args)
	{
		try
		{
			using namespace CombdoorL;
			using namespace CombdoorIO;
			auto& data = args["data"];
			auto l = getWriteLock();
			
			std::string id = data["id"].asString();
			
			LocateEntityIDVisitor entV(id);

			if(entV.getNodeList().empty())
				throw std::logic_error("ID："+id+"不存在");

			auto nodeList = entV.getNodeList();
			for (auto it = nodeList.begin();it != nodeList.end();++it)
			{
				LocateEntity* ent = (*it);
				if(ent && ent->getParents().empty() == false)
				{
					ent->getParent(0)->removeChild(ent);
				}
			}

			result(resOK);
		}
		catch (std::exception& e)
		{
			result(resError,e.what());
			resultFormatRef() = getCMDFormat();
			return false;
		}
		return true;
	}

	Json::Value DeleteLayoutInfoCMD::getCMDFormat()
	{
		Json::Value temp;
		temp["id"]= "";
		return std::move(temp);
	}

}

