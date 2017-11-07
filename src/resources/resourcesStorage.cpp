//
// Created by dkuleshov3 on 03.11.2017.
//

#include <map>
#include "resourcesStorage.h"
#include "../exceptions/ResourcesException.h"

ResourcesStorage::ResourcesStorage()
{

}

ResourcesStorage::~ResourcesStorage()
{
    clear();
}

void ResourcesStorage::clear()
{
    proceduralProfilesClear();
}

void ResourcesStorage::proceduralProfilesClear()
{
    for (std::pair<std::wstring, ProceduralProfile*> profile : proceduralProfiles)
        delete profile.second;

    proceduralProfiles.clear();
}

void ResourcesStorage::setProceduralProfiles(const ProceduralProfileMap &proceduralProfiles)
{
    this->proceduralProfiles = proceduralProfiles;
}

ProceduralProfile *ResourcesStorage::getProceduralProfile(std::wstring name)
{
    if (proceduralProfiles.find(name) == proceduralProfiles.end())
        throw new ResourcesException(L"Resource " + name + L"not found.");

    return proceduralProfiles.at(name);
}
