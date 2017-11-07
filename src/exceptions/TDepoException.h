#pragma once

#include <exception>
#include <string>

class TDepoException : public std::exception
{
	public:
		TDepoException(std::wstring text);
		virtual ~TDepoException();

		virtual const char* what() const throw();

	protected:
		std::wstring m_text;
};

