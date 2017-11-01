#include "StringConvertors.h"

#include "..\exceptions\ConvertException.h"

#include <locale>
#include <codecvt>

StringConvertors::StringConvertors()
{
}


StringConvertors::~StringConvertors()
{
}

std::wstring StringConvertors::utf8BytesToWString(char const *in)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(in);

	return wide;
}

const std::string StringConvertors::WideStringToString(std::wstring in)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string narrow = converter.to_bytes(in);

	return narrow;
}

const char *StringConvertors::WideStringToBytes(std::wstring in)
{
	return WideStringToString(in).c_str();
}

TDC::Vector3DFloat StringConvertors::WideStringToVector3DFloat(std::wstring in)
{
	return StringToVector3DFloat(WideStringToString(in));
}

TDC::Vector3DFloat StringConvertors::StringToVector3DFloat(std::string in)
{
	TDC::Vector3DFloat ret;
	std::string inTmp = in;
	try
	{
		std::string strX, strY, strZ;

		strX = inTmp.substr(0, inTmp.find(","));
		inTmp = inTmp.substr(inTmp.find(",") + 1);

		strY = inTmp.substr(0, inTmp.find(","));
		strZ = inTmp.substr(inTmp.find(",") + 1);

		float x = std::stof(strX);
		float y = std::stof(strY);
		float z = std::stof(strZ);
		ret = TDC::Vector3DFloat(x, y, z);
	} catch (...)
	{
		throw new ConvertException(L"Conversation error. Can't convert " + utf8BytesToWString(in.c_str()) + L"to \"0.0,0.0,0.0\"");
	}

	return ret;
}