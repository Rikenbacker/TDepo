//
// Created by dkuleshov3 on 03.11.2017.
//

#include <map>
#include "resourcesStorage.h"

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
