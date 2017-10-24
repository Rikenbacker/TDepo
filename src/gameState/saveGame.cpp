#include "saveGame.h"

#include "..\gameState\statePlay.h"
#include "..\exceptions\FileSystemException.h"
#include "..\exceptions\XMLException.h"
#include "..\common\StringConvertors.h"

#include <tinyxml.h>

saveGame::saveGame(GraphicSystem *graphicSystem, InputSystem *inputSystem)
{
	m_graphicSystem = graphicSystem;
	m_inputSystem = inputSystem;
}

saveGame::~saveGame()
{

}

bool saveGame::save(std::string path, statePlay *game)
{
	return false;
}

gameState *saveGame::load(std::string path)
{
	statePlay *ret = new statePlay(m_graphicSystem, m_inputSystem);

	m_game = ret;

	loadRails(path);
	loadEnviroment(path);

	m_game = nullptr;

	return ret;
}

void saveGame::loadRails(std::string path)
{
	TiXmlElement* pElemRoot = readXMLFile(std::string(TDEPO_LOADER_BASE_PATH) + "\\" + path + "\\" + std::string(TDEPO_LOADER_RAIL_FILENAME), "RailRoad");;
	TiXmlHandle hDoc(pElemRoot);
	TiXmlElement* pElem = nullptr;

	//Добавляю коннекторы
	connectorPairLilker.clear();
	
	TiXmlElement *pElemCons = hDoc.FirstChildElement("Connectors").Element();
	while (pElemCons)
	{
		hDoc = TiXmlHandle(pElemCons);
		TiXmlElement *pElemCon = hDoc.FirstChildElement("Connector").Element();
		while (pElemCon)
		{
			addConnector(pElemCon);
			pElemCon = pElemCon->NextSiblingElement("Connector");
		};

		pElemCons = pElemCons->NextSiblingElement("Connectors");
	};
	
	//Добавляю пути не объединённые в ветки
	addBranch(pElem, false);

	//Добавляю ветки
	hDoc = TiXmlHandle(pElem);
	pElem = hDoc.FirstChildElement("Branch").Element();
	while (pElem)
	{
		addBranch(pElem);
		pElem = pElem->NextSiblingElement("Branch");
	};

	connectorPairLilker.deleteUnused();

	delete pElemRoot->GetDocument();
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
				throw new XMLException(L"Incorrect version of save file");
		};

		pAttr = pAttr->Next();
	};

	throw new XMLException(L"File version not found");
}

void saveGame::addBranch(TiXmlElement* pElem, bool newBranch)
{
	TiXmlAttribute *pAttr;

	if (newBranch)
	{
		pAttr = pElem->FirstAttribute();
		while (pAttr)
		{
			pAttr = pAttr->Next();
		};
	};

	TiXmlHandle hDoc = TiXmlHandle(pElem);
	pElem = hDoc.FirstChildElement("Line").Element();
	while (pElem)
	{
		addLine(pElem);
		pElem = pElem->NextSiblingElement("Line");
	};
}

void saveGame::addLine(TiXmlElement* pElem)
{
	TiXmlAttribute *pAttr;

	std::wstring strConIn, strConOut, strMetod;

	pAttr = pElem->FirstAttribute();
	while (pAttr)
	{
		if (std::string(pAttr->Name()).compare(std::string("inConnector")) == 0)
			strConIn = StringConvertors::utf8BytesToWString(pAttr->Value());
		if (std::string(pAttr->Name()).compare(std::string("outConnector")) == 0)
			strConOut = StringConvertors::utf8BytesToWString(pAttr->Value());
		if (std::string(pAttr->Name()).compare(std::string("method")) == 0)
			strMetod = StringConvertors::utf8BytesToWString(pAttr->Value());

		pAttr = pAttr->Next();
	};

	if (strConIn.empty() || strConOut.empty() || strMetod.empty())
		throw new XMLException(std::wstring(L"Incorrect Line ") + strConIn + L" " + strConOut + L" " + strMetod);

	RailConnector *connIn = connectorPairLilker.getUnlinkedConnector(strConIn);
	if (!connIn)
		throw new XMLException(std::wstring(L"Connector ") + strConIn + L" not found");

	RailConnector *connOut = connectorPairLilker.getUnlinkedConnector(strConOut);
	if (!connOut)
		throw new XMLException(std::wstring(L"Connector ") + strConOut + L" not found");

	m_game->getRailSystem()->addRailWay(new RailWay(connIn, connOut));
}

void saveGame::addConnector(TiXmlElement* pElem)
{
	TiXmlAttribute *pAttr;

	std::wstring id, position, direction;

	pAttr = pElem->FirstAttribute();
	while (pAttr)
	{
		if (std::string(pAttr->Name()).compare(std::string("id")) == 0)
			id = StringConvertors::utf8BytesToWString(pAttr->Value());
		if (std::string(pAttr->Name()).compare(std::string("position")) == 0)
			position = StringConvertors::utf8BytesToWString(pAttr->Value());
		if (std::string(pAttr->Name()).compare(std::string("direction")) == 0)
			direction = StringConvertors::utf8BytesToWString(pAttr->Value());

		pAttr = pAttr->Next();
	};

	if (id.empty() || position.empty() || direction.empty())
		throw new XMLException(std::wstring(L"Incorrect Connector ") + id);

	TDC::Vector3DFloat pos = StringConvertors::WideStringToVector3DFloat(position);
	TDC::Vector3DFloat dir = StringConvertors::WideStringToVector3DFloat(direction);

	connectorPairLilker.createPair(id, Ray3D(pos, dir));

}

void saveGame::loadEnviroment(std::string path)
{
	TiXmlElement *pElemRoot = readXMLFile(std::string(TDEPO_LOADER_BASE_PATH) + "\\" + path + "\\" + std::string(TDEPO_LOADER_ENVIROMENT_FILENAME), "Enivroment");

	TiXmlHandle hDoc(pElemRoot);
	
	//Читаю камеру
	connectorPairLilker.clear();
	hDoc = TiXmlHandle(pElemRoot);
	for (TiXmlElement *pElemCam = hDoc.FirstChildElement("Camera").Element(); pElemCam; pElemCam = pElemCam->NextSiblingElement("Camera"))
		setCamera(pElemCam);
	
	delete pElemRoot->GetDocument();
}

TiXmlElement *saveGame::readXMLFile(std::string fileName, std::string rootName)
{
	FILE *file = nullptr;
	
	file = fopen(fileName.c_str(), "r");
	if (!file)
		throw new FileSystemException(L"File " + StringConvertors::utf8BytesToWString(fileName.c_str()) + L"not found!");
	fclose(file);
	file = nullptr;

	TiXmlDocument *doc = new TiXmlDocument(fileName.c_str());
	doc->LoadFile();
	if (doc->Error())
	{
		std::wstring str = StringConvertors::utf8BytesToWString(doc->ErrorDesc());
		delete doc;
		throw new XMLException(str);
	};

	TiXmlHandle hDoc(doc);
	TiXmlElement* pElem;

	pElem = hDoc.FirstChildElement(rootName.c_str()).Element();
	if (!pElem)
		throw new XMLException(L"Tag RailRoad not found.");

	checkVersion(pElem);

	return pElem;
}


void saveGame::setCamera(TiXmlElement* pElem)
{
	TiXmlAttribute *pAttr;

	std::wstring strPosition, strDirection, strMode;

	pAttr = pElem->FirstAttribute();
	while (pAttr)
	{
		if (std::string(pAttr->Name()).compare(std::string("position")) == 0)
			strPosition = StringConvertors::utf8BytesToWString(pAttr->Value());
		if (std::string(pAttr->Name()).compare(std::string("direction")) == 0)
			strDirection = StringConvertors::utf8BytesToWString(pAttr->Value());
		if (std::string(pAttr->Name()).compare(std::string("state")) == 0)
			strMode = StringConvertors::utf8BytesToWString(pAttr->Value());

		pAttr = pAttr->Next();
	};

	m_game->getCamera()->setPosition(StringConvertors::WideStringToVector3DFloat(strPosition));
	m_game->getCamera()->setDirection(StringConvertors::WideStringToVector3DFloat(strDirection));
	m_game->getCamera()->setState(CameraStateMap.find(strMode)->second);

	if (strPosition.empty() || strDirection.empty() || strMode.empty())
		throw new XMLException(L"Incorrect Camera");

}