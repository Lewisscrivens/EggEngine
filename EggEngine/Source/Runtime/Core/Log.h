
#pragma once
#include "spdlog/spdlog.h"
#include "EggCore.h"

/* Define logging enum... */
enum ELogType
{
    Message,
    Warning,
    Error,
    //....
};

/* Logging class to hold application and engine logging extended from the spdlog library. */
class EGG_API Log
{	
public:

    /* Initialize the loggers for both the engine and application. */
    static void Init();

    /* Logging function for performing a log message to either the engine or application. */
    template<typename... Args>
    static void AddEngineLogMessage(ELogType logType, fmt::basic_string_view<char> msg, const Args &... args)
    {
        switch (logType)
        {
        case Message:
            GetEngineLog()->trace(msg, args...);
            break;
        case Warning:
            GetEngineLog()->warn(msg, args...);
            break;
        case Error:
            GetEngineLog()->error(msg, args...);
            break;
        default: break;
        }
    }
    
    template<typename... Args>
    static void AddAppLogMessage(ELogType logType, fmt::basic_string_view<char> msg, const Args &... args)
    {
        switch (logType)
        {
        case Message:
            GetAppLog()->trace(msg, args...);
            break;
        case Warning:
            GetAppLog()->warn(msg, args...);
            break;
        case Error:
            GetAppLog()->error(msg, args...);
            break;
        default: break;
        }
    }
    
    static SharedPtr<spdlog::logger>& GetEngineLog()
    {
        return EngineLog;
    }

    static SharedPtr<spdlog::logger>& GetAppLog()
    {
        return AppLog;
    }

private:
    
    static SharedPtr<spdlog::logger> EngineLog;
    static SharedPtr<spdlog::logger> AppLog;
};
