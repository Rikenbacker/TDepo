//
// Created by dkuleshov3 on 03.11.2017.
//
#include "ResourceLoader.h"
#include "../common/FileSystem.h"
#include "../common/StringConvertors.h"
#include "../exceptions/XMLException.h"

#include <tinyxml.h>

struct ProceduralPoint
{
    TDC::Vector2DFloat point;
    bool outer = false;
};

typedef std::map<std::wstring, ProceduralPoint> ProceduralPointMap;

ResourceLoader::ResourceLoader(std::wstring path)
{
    this->path = path;
}

ResourceLoader::~ResourceLoader()
{

}

ResourcesStorage *ResourceLoader::load()
{
    ResourcesStorage *resources = new ResourcesStorage();

    resources->setProceduralProfiles(loadProceduralProfiles());

    return resources;
}

const ProceduralProfileMap ResourceLoader::loadProceduralProfiles()
{
    ProceduralProfileMap *proceduralProfileMap = new ProceduralProfileMap();

    for (std::wstring file : FileSystem::getFileList(path + TDEPO_LOADER_RESOURCE_PROCEDURAL, L"xml"))
    {
        TiXmlDocument *doc = new TiXmlDocument(StringConvertors::WideStringToBytes(file));
        doc->LoadFile();
        if (doc->Error())
        {
            std::wstring str = StringConvertors::utf8BytesToWString(doc->ErrorDesc());
            delete doc;
            throw new XMLException(str);
        };

        TiXmlHandle hDoc(doc);
        TiXmlElement* pElem;

        pElem = hDoc.FirstChildElement(TDEPO_LOADER_RESOURCE_PROCEDURAL_ROOT).Element();
        if (!pElem)
            throw new XMLException(L"Root element in " + path + L" not found.");

        ProceduralProfile *profile = new ProceduralProfile();

        std::wstring profileName = StringConvertors::utf8StringToWString(pElem->Attribute("name"));

        ProceduralPointMap points;

        //Начитываю точки
        TiXmlHandle hPoints(pElem);
        for (TiXmlElement *pElemPts = hPoints.FirstChildElement("points").Element(); pElemPts; pElemPts = pElemPts->NextSiblingElement("points"))
        {
            TiXmlHandle hPoint(pElemPts);
            for (TiXmlElement *pElemPt = hPoint.FirstChildElement("point").Element(); pElemPt; pElemPt = pElemPt->NextSiblingElement("point"))
            {
                ProceduralPoint point;
                point.point = StringConvertors::StringToVector2DFloat(pElemPt->GetText());
                point.outer = std::string(pElemPt->Attribute("outer")).compare("1") == 0;

                std::wstring ptName = StringConvertors::utf8StringToWString(pElemPt->Attribute("name"));

                points[ptName] = point;
            }
        }

        //Начитываю треугольники
        TiXmlHandle hTriangles(pElem);
        for (TiXmlElement *pTriangles = hPoints.FirstChildElement("triangles").Element(); pTriangles; pTriangles = pTriangles->NextSiblingElement("triangles"))
        {
            TiXmlHandle hTriangle(pTriangles);
            for (TiXmlElement *pTrieangle = hTriangle.FirstChildElement("triangle").Element(); pTrieangle; pTrieangle = pTrieangle->NextSiblingElement("triangle"))
            {
                std::wstring nameA = StringConvertors::utf8StringToWString(pTrieangle->Attribute("A"));
                std::wstring nameB = StringConvertors::utf8StringToWString(pTrieangle->Attribute("B"));
                std::wstring nameC = StringConvertors::utf8StringToWString(pTrieangle->Attribute("C"));

                if (points.find(nameA) == points.end() || points.find(nameB) == points.end() || points.find(nameC) == points.end())
                    throw new XMLException(L"File " + file + L"consist error. Can't define points to triangle");

                profile->addTriangle(points[nameA].point, points[nameB].point, points[nameC].point);
            }
        }

        for (std::pair<const std::wstring, ProceduralPoint> prPoint : points)
            if (prPoint.second.outer)
                profile->addPoint(prPoint.second.point);

        points.clear();

        proceduralProfileMap->insert(std::pair<std::wstring, ProceduralProfile*>(profileName, profile));
    };

    const ProceduralProfileMap ret = *proceduralProfileMap;
    return ret;
}
