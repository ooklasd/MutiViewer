#include "QueryInfoByIDCMD.h"
#include "hgcw/hgCD/IDVisitor.h"
#include "hgcw/hgCD/CombdoorWriter.h"
#include "hgcw/hgCD/LocateEntity.h"
#include "hgcw/hgCD/Mesh.h"


bool designer::QueryInfoByIDCMD::doIt(const MgrCore::WArgType &args)
{
	using namespace CombdoorL;
	try
	{
		auto& data = args["data"];
		auto id = data["id"].asString();
		auto l = getReadLock();

		auto idV = IDVisitor<osg::Node>(id,1);		
		getCombdoorRoot()->accept(idV);
		auto& nodeList = idV.NodeList();
		if(nodeList.empty()) 
			throw std::logic_error("没有找到ID:"+id+"节点");


		LocateEntity* node = dynamic_cast<LocateEntity*>(nodeList.front());
		if(node) 
		{
			CombdoorWriter::WriteOneLocateEntity(node,resultDataRef());
			result(resOK);
			return true;
		}
		Mesh* nodeMesh = dynamic_cast<Mesh*>(nodeList.front());
		if(nodeMesh) 
		{
			CombdoorWriter::WriteMesh(nodeMesh,resultDataRef());
			result(resOK);
			return true;
		}
	
	}
	catch (std::exception& e)
	{
		result(resError,e.what());
		resultFormatRef() = getCMDFormat();
		return false;
	}

	return true;
}

Json::Value designer::QueryInfoByIDCMD::getCMDFormat()
{
	Json::Value temp;
	temp["id"] = "";
	return std::move(temp);
}
