//
// Created by dkuleshov3 on 03.11.2017.
//
#include "ResourceLoader.h"
#include "../common/FileSystem.h"
#include "../common/StringConvertors.h"
#include "../exceptions/XMLException.h"

#include <tinyxml.h>
#include <algorithm>

struct ProceduralPoint
{
    TDC::Vector2DFloat point;
    int outerOrder = -1;
    unsigned short index = 0;
};

typedef std::map<std::wstring, ProceduralPoint*> ProceduralPointMap;

bool cmpByIndex(std::pair<std::wstring, ProceduralPoint*> const &a, std::pair<std::wstring, ProceduralPoint*> const &b)
    {
        return a.second->outerOrder < b.second->outerOrder;
    };

ResourceLoader::ResourceLoader(std::wstring path)
{
    this->path = std::move(path);
}

ResourceLoader::~ResourceLoader()
{

}

ResourcesStorage *ResourceLoader::load()
{
    auto *resources = new ResourcesStorage();

    resources->setProceduralProfiles(loadProceduralProfiles());

    return resources;
}

const ProceduralProfileMap ResourceLoader::loadProceduralProfiles()
{
    auto *proceduralProfileMap = new ProceduralProfileMap();

    for (std::wstring file : FileSystem::getFileList(path + TDEPO_LOADER_RESOURCE_PROCEDURAL, L"xml"))
    {
        std::string hui = StringConvertors::WideStringToString(file);
        TiXmlDocument *doc = new TiXmlDocument(StringConvertors::WideStringToString(file).c_str()/*StringConvertors::WideStringToBytes(file)*/);
        doc->LoadFile();
        if (doc->Error())
        {
            std::wstring str = StringConvertors::utf8BytesToWString(doc->ErrorDesc()) + L" (" + file + L")";
            delete doc;
            throw XMLException(str);
        };

        TiXmlHandle hDoc(doc);
        TiXmlElement* pElem;

        pElem = hDoc.FirstChildElement(TDEPO_LOADER_RESOURCE_PROCEDURAL_ROOT).Element();
        if (!pElem)
            throw XMLException(L"Root element in " + path + L" not found.");

        auto *profile = new ProceduralProfile();

        std::wstring profileName = StringConvertors::utf8StringToWString(pElem->Attribute("name"));

        ProceduralPointMap points;

        //Начитываю точки
        TiXmlHandle hPoints(pElem);
        for (TiXmlElement *pElemPts = hPoints.FirstChildElement("points").Element(); pElemPts; pElemPts = pElemPts->NextSiblingElement("points"))
        {
            TiXmlHandle hPoint(pElemPts);
            for (TiXmlElement *pElemPt = hPoint.FirstChildElement("point").Element(); pElemPt; pElemPt = pElemPt->NextSiblingElement("point"))
            {
                auto *point = new ProceduralPoint();
                point->point = StringConvertors::StringToVector2DFloat(pElemPt->GetText());
                if (pElemPt->Attribute("outer"))
                    point->outerOrder = std::stoi(pElemPt->Attribute("outer"));

                std::wstring ptName = StringConvertors::utf8StringToWString(pElemPt->Attribute("name"));

                points[ptName] = point;
            }
        }

        // Добавляю точки в массив, нумеруя их позиции в списке
        for (std::pair<const std::wstring, ProceduralPoint*> prPoint : points)
            prPoint.second->index = profile->addPoint(prPoint.second->point);

        //Начитываю треугольники
        TiXmlHandle hTriangles(pElem);
        for (TiXmlElement *pTriangles = hTriangles.FirstChildElement("triangles").Element(); pTriangles; pTriangles = pTriangles->NextSiblingElement("triangles"))
        {
            TiXmlHandle hTriangle(pTriangles);
            for (TiXmlElement *pTrieangle = hTriangle.FirstChildElement("triangle").Element(); pTrieangle; pTrieangle = pTrieangle->NextSiblingElement("triangle"))
            {
                std::wstring nameA = StringConvertors::utf8StringToWString(pTrieangle->Attribute("A"));
                std::wstring nameB = StringConvertors::utf8StringToWString(pTrieangle->Attribute("B"));
                std::wstring nameC = StringConvertors::utf8StringToWString(pTrieangle->Attribute("C"));

                if (points.find(nameA) == points.end() || points.find(nameB) == points.end() || points.find(nameC) == points.end())
                    throw XMLException(L"File " + file + L"consist error. Can't define points to triangle");

                profile->addTriangle(points[nameA]->index, points[nameB]->index, points[nameC]->index);
            }
        }

        // Добавляю по порядку контур фигуры
        std::vector<std::pair<std::wstring, ProceduralPoint*>> vec(points.begin(), points.end() );
        std::sort(vec.begin(), vec.end(), cmpByIndex);
        for (std::pair<std::wstring, ProceduralPoint*> prPoint : vec)
            if (prPoint.second->outerOrder >= 0)
                profile->addCircuitPoint(prPoint.second->index);

        vec.clear();

        for (std::pair<std::wstring, ProceduralPoint*> prPoint : points)
            delete prPoint.second;

        points.clear();

        proceduralProfileMap->insert(std::pair<std::wstring, ProceduralProfile*>(profileName, profile));
    };

    const ProceduralProfileMap ret = *proceduralProfileMap;
    return ret;
}
