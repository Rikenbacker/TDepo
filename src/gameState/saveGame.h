#pragma once
#include "..\graphics\GraphicSystem.h"
#include "..\graphics\InputSystem.h"
#include "..\gameState\statePlay.h"
#include "..\objects\SaveGameLinkers\ConnectorPairLinker.h"

#include <string>
#include "tinyxml.h"

#define TDEPO_LOADER_VERSION	"0.0.1"
#define TDEPO_LOADER_RAIL_FILENAME	"railroad.xml"
#define TDEPO_LOADER_ENVIROMENT_FILENAME	"enviroment.xml"
#define TDEPO_LOADER_BASE_PATH	"data\\save"
// ������/������ ����
class saveGame
{
	public:
		saveGame(GraphicSystem *graphicSystem, InputSystem *inputSystem);
		~saveGame();

		bool save(std::string, statePlay *game);
		gameState *load(std::string);

	private:
		void loadRails(std::string);
		void loadEnviroment(std::string);

		GraphicSystem *m_graphicSystem = nullptr;
		InputSystem *m_inputSystem = nullptr;
		statePlay *m_game = nullptr;

		ConnectorPairLinker connectorPairLilker;

		void checkVersion(TiXmlElement* pElem);
		void addBranch(TiXmlElement* pElem, bool newBranch = true);
		void addLine(TiXmlElement* pElem);
		void addConnector(TiXmlElement* pElem);
		void setCamera(TiXmlElement* pElem);

		TiXmlElement *readXMLFile(std::string, std::string);
};

