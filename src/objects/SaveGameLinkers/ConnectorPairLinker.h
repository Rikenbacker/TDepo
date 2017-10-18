#pragma once

#include "ConnectorPair.h"
#include "..\..\common\Ray3D.h"

#include <string>
#include <vector>

/*
	������������ ����� �������� ����������� � �� ��������� �����������, ���������� ������ ��� ����������/��������
*/
class ConnectorPairLinker
{
	public:
		ConnectorPairLinker();
		~ConnectorPairLinker();

		//������� ������� ��� �������� ��������� �� ������
		void clear();

		//������� �� ������ �� ��������, ������� �� � ���� �� ������������ (� ��� ����� � ������ ���������)
		void deleteUnused();
		void createPair(std::wstring name, Ray3D ray);

	private:
		std::vector<ConnectorPair*> connectorPairs;
		
		
};

