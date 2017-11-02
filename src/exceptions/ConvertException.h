#pragma once
#include "TDepoException.h"
class ConvertException : public TDepoException
{
	public:
		ConvertException(std::wstring text);
		~ConvertException();
};

