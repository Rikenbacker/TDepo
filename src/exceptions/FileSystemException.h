#pragma once

#include "TDepoException.h"

class FileSystemException : public TDepoException
{
	public:
		FileSystemException(std::wstring text);
		~FileSystemException();

};

