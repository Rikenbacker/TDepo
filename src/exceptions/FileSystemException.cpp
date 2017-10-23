#include "FileSystemException.h"


FileSystemException::FileSystemException(std::wstring text)
: TDepoException(text)
{

}

FileSystemException::~FileSystemException()
{
}

