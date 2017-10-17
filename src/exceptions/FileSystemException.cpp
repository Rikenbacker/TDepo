#include "FileSystemException.h"


FileSystemException::FileSystemException(std::string text)
: TDepoException(text)
{

}

FileSystemException::~FileSystemException()
{
}

