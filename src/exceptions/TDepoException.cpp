#include "TDepoException.h"

#include "..\common\StringConvertors.h"

TDepoException::TDepoException(std::wstring text)
{
	m_text = text;
}


TDepoException::~TDepoException()
{
}

const char* TDepoException::what() const throw()
{
	return StringConvertors::WideStringToBytes(m_text);
}
