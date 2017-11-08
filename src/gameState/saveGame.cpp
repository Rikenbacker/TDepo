#include "saveGame.h"

#include "..\exceptions\FileSystemException.h"
#include "..\exceptions\XMLException.h"
#include "..\common\StringConvertors.h"

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
	auto *ret = new statePlay(m_graphicSystem, m_inputSystem);

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

	//Aiaaaey? eiiiaeoi?u
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
	
	//Aiaaaey? iooe ia iauaaei?iiua a aaoee
	addBranch(pElem, false);

	//Aiaaaey? aaoee
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
    if (pElem->Attribute("version"))
    {
        if (std::string(pElem->Attribute("version")) != TDEPO_LOADER_VERSION)
            throw XMLException(L"Incorrect version of save file");
    } else
        throw XMLException(L"File version not found");
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

	TiXmlHandle hDoc(pElem);
	pElem = hDoc.FirstChildElement("Line").Element();
	while (pElem)
	{
		addLine(pElem);
		pElem = pElem->NextSiblingElement("Line");
	};
}

void saveGame::addLine(TiXmlElement* pElem)
{
    std::wstring strConIn = StringConvertors::utf8BytesToWString(pElem->Attribute("inConnector"));
    std::wstring strConOut = StringConvertors::utf8BytesToWString(pElem->Attribute("outConnector"));
    std::wstring strMethod = StringConvertors::utf8BytesToWString(pElem->Attribute("method"));

	if (strConIn.empty() || strConOut.empty() || strMethod.empty())
		throw XMLException(std::wstring(L"Incorrect Line ") + strConIn + L" " + strConOut + L" " + strMethod);

	RailConnector *connIn = connectorPairLilker.getUnlinkedConnector(&strConIn);
	if (!connIn)
		throw XMLException(std::wstring(L"Connector ") + strConIn + L" not found");

	RailConnector *connOut = connectorPairLilker.getUnlinkedConnector(&strConOut);
	if (!connOut)
		throw XMLException(std::wstring(L"Connector ") + strConOut + L" not found");

	m_game->getRailSystem()->addRailWay(new RailWay(connIn, connOut));
}

void saveGame::addConnector(TiXmlElement* pElem)
{
	std::wstring id = StringConvertors::utf8BytesToWString(pElem->Attribute("id"));
    std::wstring position = StringConvertors::utf8BytesToWString(pElem->Attribute("position"));
    std::wstring direction = StringConvertors::utf8BytesToWString(pElem->Attribute("direction"));

	if (id.empty() || position.empty() || direction.empty())
		throw XMLException(std::wstring(L"Incorrect Connector ") + id);

	TDC::Vector3DFloat pos = StringConvertors::WideStringToVector3DFloat(position);
	TDC::Vector3DFloat dir = StringConvertors::WideStringToVector3DFloat(direction);

	connectorPairLilker.createPair(id, Ray3D(pos, dir));

}

void saveGame::loadEnviroment(std::string path)
{
	TiXmlElement *pElemRoot = readXMLFile(std::string(TDEPO_LOADER_BASE_PATH) + "\\" + path + "\\" + std::string(TDEPO_LOADER_ENVIROMENT_FILENAME), "Enivroment");

	TiXmlHandle hDoc(pElemRoot);
	
	//?eoa? eaia?o
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
		throw FileSystemException(L"File " + StringConvertors::utf8BytesToWString(fileName.c_str()) + L"not found!");
	fclose(file);
	file = nullptr;

	auto *doc = new TiXmlDocument(fileName.c_str());
	doc->LoadFile();
	if (doc->Error())
	{
		std::wstring str = StringConvertors::utf8BytesToWString(doc->ErrorDesc());
		delete doc;
		throw XMLException(str);
	};

	TiXmlHandle hDoc(doc);
	TiXmlElement* pElem;

	pElem = hDoc.FirstChildElement(rootName.c_str()).Element();
	if (!pElem)
		throw XMLException(L"Tag RailRoad not found.");

	checkVersion(pElem);

	return pElem;
}


void saveGame::setCamera(TiXmlElement* pElem)
{
	std::wstring strPosition = StringConvertors::utf8BytesToWString(pElem->Attribute("position"));
    std::wstring strDirection = StringConvertors::utf8BytesToWString(pElem->Attribute("direction"));
    std::wstring strMode = StringConvertors::utf8BytesToWString(pElem->Attribute("state"));

	m_game->getCamera()->setPosition(StringConvertors::WideStringToVector3DFloat(strPosition));
	m_game->getCamera()->setDirection(StringConvertors::WideStringToVector3DFloat(strDirection));
	m_game->getCamera()->setState(CameraStateMap.find(strMode)->second);

	if (strPosition.empty() || strDirection.empty() || strMode.empty())
		throw XMLException(L"Incorrect Camera");

}