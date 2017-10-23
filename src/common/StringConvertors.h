#pragma once

#include "Vector3DFloat.h"

#include <string>

class StringConvertors
{
	public:
		StringConvertors();
		~StringConvertors();

		static std::wstring utf8BytesToWString(const char *);
		static const std::string WideStringToString(std::wstring);
		static const char* WideStringToBytes(std::wstring);

		static TDC::Vector3DFloat WideStringToVector3DFloat(std::wstring);
		static TDC::Vector3DFloat StringToVector3DFloat(std::string);
};

