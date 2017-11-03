#include "StringConvertors.h"

#include "..\exceptions\ConvertException.h"

#include <locale>
#include <codecvt>
#include <algorithm>

std::wstring StringConvertors::utf8BytesToWString(char const *in)
{
/*    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(in);*/
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(in);

	return wide;
}

const std::string StringConvertors::WideStringToString(std::wstring in)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(in);
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

std::wstring StringConvertors::utf8StringToWString(std::string in)
{
    return utf8BytesToWString(in.c_str());
}

std::wstring StringConvertors::toLower(std::wstring in)
{
    std::transform(in.begin(), in.end(), in.begin(), ::tolower);

    return in;
}

std::wstring StringConvertors::toUpper(std::wstring in)
{
    std::transform(in.begin(), in.end(), in.begin(), ::toupper);

    return in;
}

TDC::Vector2DFloat StringConvertors::WideStringToVector2DFloat(std::wstring in)
{
    return StringToVector2DFloat(WideStringToString(in));
}

TDC::Vector2DFloat StringConvertors::StringToVector2DFloat(std::string in)
{
    TDC::Vector2DFloat ret;
    std::string inTmp = in;
    try
    {
        std::string strX, strY, strZ;

        strX = inTmp.substr(0, inTmp.find(","));
        strY = inTmp.substr(inTmp.find(",") + 1);

        float x = std::stof(strX);
        float y = std::stof(strY);
        ret = TDC::Vector2DFloat(x, y);
    } catch (...)
    {
        throw new ConvertException(L"Conversation error. Can't convert " + utf8BytesToWString(in.c_str()) + L"to \"0.0,0.0,0.0\"");
    }

    return ret;
}
