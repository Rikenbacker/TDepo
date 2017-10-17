#include "TDepoException.h"


TDepoException::TDepoException(std::string text)
{
	m_text = text;
}


TDepoException::~TDepoException()
{
}

const char* TDepoException::what() const throw()
{
	return m_text.c_str();
}
