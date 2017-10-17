#pragma once
#include "TDepoException.h"
class XMLException : public TDepoException
{
	public:
		XMLException(std::string text);
		~XMLException();
};

