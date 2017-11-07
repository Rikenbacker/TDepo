//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include "ProceduralProfile.h"
#include <map>

typedef std::map<std::wstring, ProceduralProfile *> ProceduralProfileMap;

class ResourcesStorage
{
    public:
        ResourcesStorage();
        ~ResourcesStorage();

        void clear();

        void setProceduralProfiles(const ProceduralProfileMap &proceduralProfiles);
        ProceduralProfile *getProceduralProfile(std::wstring);

    private:
        ProceduralProfileMap proceduralProfiles;

    private:
        void proceduralProfilesClear();
};