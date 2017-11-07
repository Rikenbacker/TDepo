#pragma once

#include "ConnectorPair.h"
#include "..\..\common\Ray3D.h"

#include <string>
#include <vector>

/*
	Осуществляет связь реальных коннекторов с их временным именованием, необходимо только для сохранения/загрузки
*/
class ConnectorPairLinker
{
	public:
		ConnectorPairLinker();
		~ConnectorPairLinker();

		//Очистка массива без удаления элементов из памяти
		void clear();

		//Удаляет из памяти те элементы, которые ни к чему не подсоеденины (в том числе и только половинки)
		void deleteUnused();

		void createPair(std::wstring name, Ray3D ray);
		RailConnector *getUnlinkedConnector(std::wstring *);

	private:
		std::vector<ConnectorPair*> connectorPairs;

		ConnectorPair* searchConnector(std::wstring *);
		
		
};

