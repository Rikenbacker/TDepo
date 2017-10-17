#include "saveGame.h"

#include "..\gameState\statePlay.h"
#include "..\exceptions\FileSystemException.h"
#include "..\exceptions\XMLException.h"

#include <tinyxml.h>

saveGame::saveGame(GraphicSystem *graphicSystem, InputSystem *inputSystem)
{
	m_graphicSystem = graphicSystem;
	m_inputSystem = inputSystem;
}

saveGame::~saveGame()
{

}

bool saveGame::save(std::string path, gameState *game)
{
	return false;
}
gameState *saveGame::load(std::string path)
{
	gameState *ret = new statePlay(m_graphicSystem, m_inputSystem);

	loadRails(path, ret);

	return ret;
}

void saveGame::loadRails(std::string path, gameState *game)
{
	FILE *railFile = nullptr;
	path = std::string(TDEPO_LOADER_BASE_PATH) + "\\" + path + "\\" + std::string(TDEPO_LOADER_RAIL_FILENAME);
	
	railFile = fopen(path.c_str(), "r");
	if (!railFile)
		throw new FileSystemException("File " + path + "not found!");
	fclose(railFile);
	railFile = nullptr;

	TiXmlDocument *doc = new TiXmlDocument(path.c_str());
	doc->LoadFile();
	if (doc->Error())
	{
		std::string str = doc->ErrorDesc();
		delete doc;
		throw new XMLException(str);
	};

	TiXmlHandle hDoc(doc);
	TiXmlElement* pElem;
	TiXmlAttribute *pAttr;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChildElement("RailRoad").Element();
	if (!pElem)
		throw new XMLException("Tag RailRoad not found.");

	checkVersion(pElem);

	//Добавляю пути не объединённые в ветки
	addBranch(pElem, false);

	//Добавляю ветки
	hDoc = TiXmlHandle(pElem);
	pElem = hDoc.FirstChildElement("Branch").Element();
	while (pElem)
	{
		addBranch(pElem);
		pElem->NextSiblingElement();
	};


	delete doc;



}

void saveGame::checkVersion(TiXmlElement* pElem)
{
	TiXmlAttribute *pAttr;

	pAttr = pElem->FirstAttribute();
	while (pAttr)
	{
		if (std::string(pAttr->Name()).compare(std::string("version")) == 0)
		{
			if (std::string(pAttr->Value()).compare(std::string(TDEPO_LOADER_VERSION)) == 0)
				return;
			else 
				throw new XMLException("Incorrect version of save file");
		};

		pAttr = pAttr->Next();
	};

	throw new XMLException("File version not found");
}

void saveGame::addBranch(TiXmlElement* pElem, bool newBranch)
{
	pElem = pElem->FirstChildElement("Line");
	while (pElem)
	{
		addLine(pElem);
		pElem->NextSiblingElement();
	};
}

void saveGame::addLine(TiXmlElement* pElem)
{

}