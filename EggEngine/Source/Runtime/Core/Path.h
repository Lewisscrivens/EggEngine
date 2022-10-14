#pragma once

#include "EggCore.h"

/** Windows helper class for getting important directories on a windows machine. */
struct EGG_API FPath
{
public:
    
    static String GetExeFile()
    {
        char FileBuffer[MAX_PATH];
        GetModuleFileNameA(nullptr, FileBuffer, MAX_PATH);
        return FileBuffer;
    }
    
    static String GetExeDir()
    {
        const std::filesystem::path ExePath = GetExeFile();
        return ExePath.parent_path().u8string();
    }

    /** Returns project directory, if running with editor it will return the location of the project.
     *  TODO: If running with a packaged .exe it will return the location of the game installation. */
    static String GetProjectDir()
    {
        const std::filesystem::path ExePath = GetExeDir();
        return ExePath.parent_path().parent_path().parent_path().parent_path().generic_u8string();
    }
    
    static String GetSavedDir()
    {
        const std::filesystem::path ExePath = GetExeDir();
        return ExePath.parent_path().generic_u8string() + "/Saved";
    }

    static String GetUserDir()
    {
        return GetWindowsFolder(FOLDERID_Documents);
    }

    static String GetDataDir()
    {
        return GetWindowsFolder(FOLDERID_LocalAppData);
    }

    static String GetDesktopDir()
    {
        return GetWindowsFolder(FOLDERID_Desktop);
    }

    static String GetDownloadDir()
    {
        return GetWindowsFolder(FOLDERID_LocalDownloads);
    }

    static String GetEngineTmpDir()
    {
        return GetDataDir() + "/EggEngine/.Temp";
    }

    static String GetDriveDir()
    {
        const std::filesystem::path ExePath = GetExeFile();
        return ExePath.root_path().u8string();
    }

    static String GetDirectoryName(const String& InDirectory)
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

    static String GetFileName(const String& InFileDirectory, const bool bTrimExtension = false)
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

    static String RemoveExtension(const String& InFileDirectory)
    {
        if (InFileDirectory.empty())
        {
            return "";
        }
        
        const std::filesystem::path CurrentFilePath = InFileDirectory;
        String FileName = CurrentFilePath.generic_u8string();
        if (CurrentFilePath.has_extension())
        {
            const size_t ExtensionStartIndex = FileName.find_last_of("."); 
            FileName = FileName.substr(0, ExtensionStartIndex); 
        }

        return FileName;
    }

    static bool DoesExist(const String& InDirectory)
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
    
    static String GetWindowsFolder(GUID FolderID)
    {
        PWSTR UserDirPath;
        const HRESULT Result = SHGetKnownFolderPath(FolderID, 0, NULL, &UserDirPath);
        String OutPath = "";
        if (SUCCEEDED(Result))
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> Converter;
            OutPath = Converter.to_bytes(UserDirPath);
        }

        CoTaskMemFree(UserDirPath);
        return OutPath;
    }
};
