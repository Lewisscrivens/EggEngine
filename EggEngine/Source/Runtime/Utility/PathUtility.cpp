
#include "EggPch.h"
#include "PathUtility.h"

std::string FPathUtil::GetExeFile()
{
    char FileBuffer[MAX_PATH];
    GetModuleFileNameA(nullptr, FileBuffer, MAX_PATH);
    return FileBuffer;
}

std::string FPathUtil::GetExeDir()
{
    const std::filesystem::path ExePath = GetExeFile();
    return ExePath.parent_path().u8string();
}

std::string FPathUtil::GetEngineInstallDir()
{
    const std::filesystem::path ExePath = GetExeDir();
    return ExePath.parent_path().parent_path().parent_path().parent_path().generic_u8string();
}

std::string FPathUtil::GetGameDir()
{
    const std::filesystem::path ExePath = GetExeDir();
    return ExePath.parent_path().generic_u8string();
}

std::string FPathUtil::GetSavedDir()
{
    const std::filesystem::path ExePath = GetExeDir();
    return ExePath.parent_path().generic_u8string() + "/Saved";
}

std::string FPathUtil::GetUserDir()
{
    return GetWindowsFolder(FOLDERID_Documents);
}

std::string FPathUtil::GetDataDir()
{
    return GetWindowsFolder(FOLDERID_LocalAppData);
}

std::string FPathUtil::GetDesktopDir()
{
    return GetWindowsFolder(FOLDERID_Desktop);
}

std::string FPathUtil::GetDownloadDir()
{
    return GetWindowsFolder(FOLDERID_LocalDownloads);
}

std::string FPathUtil::GetEngineTmpDir()
{
    return GetDataDir() + "/EggEngine/.Temp";
}

std::string FPathUtil::GetDriveDir()
{
    const std::filesystem::path ExePath = GetExeFile();
    return ExePath.root_path().u8string();
}

std::string FPathUtil::GetDirectoryName(const std::string& InDirectory)
{
    if (InDirectory.empty())
    {
        return "";
    }
        
    const std::filesystem::path CurrentPath = InDirectory;
    if (!CurrentPath.has_filename())
    {
        return "";
    }
        
    return CurrentPath.filename().generic_u8string();
}

std::string FPathUtil::GetFileName(const std::string& InFileDirectory, const bool bTrimExtension)
{
    if (InFileDirectory.empty())
    {
        return "";
    }
        
    if (bTrimExtension)
    {
        return RemoveExtension(GetDirectoryName(InFileDirectory));
    }

    return GetDirectoryName(InFileDirectory);
}

std::string FPathUtil::RemoveExtension(const std::string& InFileDirectory)
{
    if (InFileDirectory.empty())
    {
        return "";
    }
        
    const std::filesystem::path CurrentFilePath = InFileDirectory;
    std::string FileName = CurrentFilePath.generic_u8string();
    if (CurrentFilePath.has_extension())
    {
        const size_t ExtensionStartIndex = FileName.find_last_of("."); 
        FileName = FileName.substr(0, ExtensionStartIndex); 
    }

    return FileName;
}

bool FPathUtil::DoesExist(const std::string& InDirectory)
{
    if (InDirectory.empty())
    {
        return false;
    }

    if (!std::filesystem::exists(InDirectory))
    {
        return false;
    }

    return true;
}

std::string FPathUtil::GetWindowsFolder(GUID FolderID)
{
    auto UserDirPath = new wchar_t[128];
    SHGetKnownFolderPath(FolderID, 0, nullptr, &UserDirPath);
    char OutPath[128];
    wcstombs(OutPath, UserDirPath, 128);
    CoTaskMemFree(UserDirPath);
    
    return OutPath;
}