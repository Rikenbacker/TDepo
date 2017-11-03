//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include <string>
#include "resourcesStorage.h"

#define TDEPO_LOADER_RESOURCE_PROCEDURAL L"procedural_objects"
#define TDEPO_LOADER_RESOURCE_PROCEDURAL_ROOT "procedure"

class ResourceLoader
{
    public:
        ResourceLoader(std::wstring);
        ~ResourceLoader();

        ResourcesStorage *load();

    private:
        std::wstring path;

        const ProceduralProfileMap loadProceduralProfiles();
};