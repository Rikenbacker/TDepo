//
// Created by dkuleshov3 on 03.11.2017.
//

#include "FileSystem.h"

#include "StringConvertors.h"
#include "../exceptions/FileSystemException.h"

#include<dirent.h>


std::vector<std::wstring> FileSystem::getFileList(std::wstring path, std::wstring ext)
{
    std::vector<std::wstring> ret;

    DIR *pDIR;
    struct dirent *entry;
    if( pDIR = opendir(StringConvertors::WideStringToBytes(path)) )
    {
        while(entry = readdir(pDIR))
        {
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && checkExtension(StringConvertors::utf8StringToWString(entry->d_name), ext))
                ret.push_back(path + L"\\" + StringConvertors::utf8StringToWString(entry->d_name));
        }
        closedir(pDIR);
    } else
        throw FileSystemException(L"Directory " + path + L" not found!");

    return ret;
}

bool FileSystem::checkExtension(std::wstring filename, std::wstring extension)
{
    if (extension.empty())
        return true;

    extension = StringConvertors::toLower(extension);

    if (filename.find_last_of(L'.') == std::wstring::npos)
        return false;

    std::wstring cmp = StringConvertors::toLower(filename.substr(filename.find_last_of(L'.') + 1));

    return extension == cmp;
}
