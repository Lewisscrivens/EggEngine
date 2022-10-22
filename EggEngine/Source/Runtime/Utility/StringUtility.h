#pragma once

struct FStringUtil
{
    static std::wstring StringToWideString(const std::string& InString);

    static std::string WideStringToString(const std::wstring& InWideString);
};
