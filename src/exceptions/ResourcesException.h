//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include "TDepoException.h"

class ResourcesException : public TDepoException
{
    public:
        ResourcesException(std::wstring);
};



