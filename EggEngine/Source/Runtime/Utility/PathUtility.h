#pragma once

#include "Core/EggCore.h"

/** Windows helper class for getting important directories on a windows machine. */
struct EGG_API FPathUtil
{
    
public:
    
    static std::string GetExeFile();
    
    static std::string GetExeDir();
    
    static std::string GetEngineInstallDir();

    static std::string GetGameDir();
    
    static std::string GetSavedDir();

    static std::string GetUserDir();

    static std::string GetDataDir();

    static std::string GetDesktopDir();

    static std::string GetDownloadDir();

    static std::string GetEngineTmpDir();
    
    static std::string GetDriveDir();

    static std::string GetDirectoryName(const std::string& InDirectory);

    static std::string GetFileName(const std::string& InFileDirectory, const bool bTrimExtension = false);

    static std::string RemoveExtension(const std::string& InFileDirectory);

    static bool DoesExist(const std::string& InDirectory);

    static std::string GetWindowsFolder(GUID FolderID);
};
