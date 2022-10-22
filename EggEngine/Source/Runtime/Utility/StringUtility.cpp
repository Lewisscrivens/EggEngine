
#include "EggPch.h"
#include "StringUtility.h"

std::wstring FStringUtil::StringToWideString(const std::string& InString)
{
    return std::wstring(InString.begin(), InString.end());
}

std::string FStringUtil::WideStringToString(const std::wstring& InWideString)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ConvertToString;
    return ConvertToString.to_bytes(InWideString);
}
