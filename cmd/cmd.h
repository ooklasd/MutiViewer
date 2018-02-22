#pragma once
#include "hgcd/MgrCoreCD/WICommand.h"
#include "..\Document/Document.h"
#include "..\Export.h"

class MgrCore::WICommand;


#define CMD_STATIC(name)  \
	static const char* commandName(){return #name;}\
	static name* creator(){return new name();}

namespace designer
{
	class DESIGNERCMD_API cmd;
	class DesignerViewer;
	class cmd :public MgrCore::WICommand
	{
	public:	

	public:
		//====================================================================================
		// ��ݻ�ȡ����
		// ��ȥ�򻯻�ȡ����
		//====================================================================================

		//��ȡ�ĵ�
		Document* getDocument(){
			return reinterpret_cast<Document*>(getArg());
		}

		//��ȡviewer
		DesignerViewer* getViewer(){
			return getDocument()->getViewer(); 
		}

		//��ȡ���ڵ�
		osg::Group* getShapeRoot() { return getViewer()->ShapeRoot(); }
		osg::Group* getExtractRoot() { return getViewer()->ExtractRoot(); }
		osg::Group* getCombdoorRoot() { return getViewer()->CombdoorRoot(); }

		//��ȡ��ǰ��ѡ�Ľڵ�
		std::list<osg::ref_ptr<osg::Node>>& getShapePickNodes();
		osg::Node* getShapePickNode();

		std::list<osg::ref_ptr<osg::Node>>& getCombdoorPickNodes();
		osg::Node* getCombdoorPickNode();
	};


}
