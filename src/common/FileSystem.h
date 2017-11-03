//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include <string>
#include <vector>

class FileSystem
{
    public:
        static std::vector<std::wstring> getFileList(std::wstring, std::wstring = L"");
        static bool checkExtension(std::wstring, std::wstring);
};
