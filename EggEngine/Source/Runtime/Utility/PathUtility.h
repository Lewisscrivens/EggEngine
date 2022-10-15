#pragma once

#include "EggCore.h"

/** Windows helper class for getting important directories on a windows machine. */
struct EGG_API FPathUtil
{
public:
    
    static std::string GetExeFile()
    {
        char FileBuffer[MAX_PATH];
        GetModuleFileNameA(nullptr, FileBuffer, MAX_PATH);
        return FileBuffer;
    }
    
    static std::string GetExeDir()
    {
        const std::filesystem::path ExePath = GetExeFile();
        return ExePath.parent_path().u8string();
    }

    /** Returns project directory, if running with editor it will return the location of the project.
     *  TODO: If running with a packaged .exe it will return the location of the game installation. */
    static std::string GetProjectDir()
    {
        const std::filesystem::path ExePath = GetExeDir();
        return ExePath.parent_path().parent_path().parent_path().parent_path().generic_u8string();
    }
    
    static std::string GetSavedDir()
    {
        const std::filesystem::path ExePath = GetExeDir();
        return ExePath.parent_path().generic_u8string() + "/Saved";
    }

    static std::string GetUserDir()
    {
        return GetWindowsFolder(FOLDERID_Documents);
    }

    static std::string GetDataDir()
    {
        return GetWindowsFolder(FOLDERID_LocalAppData);
    }

    static std::string GetDesktopDir()
    {
        return GetWindowsFolder(FOLDERID_Desktop);
    }

    static std::string GetDownloadDir()
    {
        return GetWindowsFolder(FOLDERID_LocalDownloads);
    }

    static std::string GetEngineTmpDir()
    {
        return GetDataDir() + "/EggEngine/.Temp";
    }

    static std::string GetDriveDir()
    {
        const std::filesystem::path ExePath = GetExeFile();
        return ExePath.root_path().u8string();
    }

    static std::string GetDirectoryName(const std::string& InDirectory)
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

    static std::string GetFileName(const std::string& InFileDirectory, const bool bTrimExtension = false)
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

    static std::string RemoveExtension(const std::string& InFileDirectory)
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

    static bool DoesExist(const std::string& InDirectory)
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

private:
    
    static std::string GetWindowsFolder(GUID FolderID)
    {
        PWSTR UserDirPath;
        const HRESULT Result = SHGetKnownFolderPath(FolderID, 0, NULL, &UserDirPath);
        std::string OutPath = "";
        if (SUCCEEDED(Result))
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> Converter;
            OutPath = Converter.to_bytes(UserDirPath);
        }

        CoTaskMemFree(UserDirPath);
        return OutPath;
    }
};
