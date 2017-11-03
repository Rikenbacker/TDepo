#pragma once

#include "Vector3DFloat.h"
#include "Vector2DFloat.h"

#include <string>

class StringConvertors
{
	public:
		static std::wstring utf8BytesToWString(char const*);
        static std::wstring utf8StringToWString(std::string);
		static const std::string WideStringToString(std::wstring);
		static const char* WideStringToBytes(std::wstring);
        static std::wstring toLower(std::wstring);
        static std::wstring toUpper(std::wstring);

		static TDC::Vector3DFloat WideStringToVector3DFloat(std::wstring);
		static TDC::Vector3DFloat StringToVector3DFloat(std::string);

        static TDC::Vector2DFloat WideStringToVector2DFloat(std::wstring);
        static TDC::Vector2DFloat StringToVector2DFloat(std::string);
};

