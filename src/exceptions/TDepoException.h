#pragma once

#include <exception>
#include <string>

class TDepoException : public std::exception
{
	public:
		TDepoException(std::string text);
		~TDepoException();

		virtual const char* what() const throw();

	protected:
		std::string m_text;
};

