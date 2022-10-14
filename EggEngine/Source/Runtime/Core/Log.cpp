
#include "EggPch.h"
#include "Log.h"
#include "Path.h"
#include "Time.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

/** Log output destination depending on build mode. */
#if EGG_DEBUG
#define ENGINE_LOG_OUTPUT FPath::GetSavedDir() + "/Logs/EggLog-Debug-" + Time::GetTimeStamp() + ".log"
#define APP_LOG_OUTPUT FPath::GetSavedDir() + "/Logs/AppLog-Debug-" + Time::GetTimeStamp() + ".log"
#elif EGG_DEV
#define ENGINE_LOG_OUTPUT FPath::GetSavedDir().c_str() + "/Logs/EggLog-Dev-" + Time::GetTimeStamp() + ".log"
#define APP_LOG_OUTPUT FPath::GetSavedDir().c_str() + "/Logs/AppLog-Dev-" + Time::GetTimeStamp() + ".log"
#else
#define ENGINE_LOG_OUTPUT FPath::GetSavedDir() + "/Logs/EggLog-Unknown-" + Time::GetTimeStamp() + ".log"
#define APP_LOG_OUTPUT FPath::GetSavedDir() + "/Logs/AppLog-Unknown-" + Time::GetTimeStamp() + ".log"
#endif

SharedPtr<spdlog::logger> Log::EngineLog;
SharedPtr<spdlog::logger> Log::AppLog;

void Log::Init()
{
    // Register two different log sinks, one for a file and one to update the console based logging.
    std::vector<spdlog::sink_ptr> EngineSinks;
    std::vector<spdlog::sink_ptr> AppSinks;
    EngineSinks.emplace_back(NewClass<spdlog::sinks::stdout_color_sink_mt>());
    EngineSinks.emplace_back(NewClass<spdlog::sinks::basic_file_sink_mt>(ENGINE_LOG_OUTPUT, true));
    AppSinks.emplace_back(NewClass<spdlog::sinks::stdout_color_sink_mt>());
    AppSinks.emplace_back(NewClass<spdlog::sinks::basic_file_sink_mt>(APP_LOG_OUTPUT, true));

    // Setup pattern to log messages in both the console and file versions of the engine logger.
    EngineSinks[0]->set_pattern("%^[%T] %n: %v%$");
    EngineSinks[1]->set_pattern("[%T] [%l] %n: %v");
    AppSinks[0]->set_pattern("%^[%T] %n: %v%$");
    AppSinks[1]->set_pattern("[%T] [%l] %n: %v");

    // Init the engine logger.
    EngineLog = NewClass<spdlog::logger>("EggLog", begin(EngineSinks), end(EngineSinks));
    register_logger(EngineLog);
    EngineLog->set_level(spdlog::level::trace);
    EngineLog->flush_on(spdlog::level::trace);

    // Init the application logger.
    AppLog = NewClass<spdlog::logger>("AppLog", begin(AppSinks), end(AppSinks));
    register_logger(AppLog);
    AppLog->set_level(spdlog::level::trace);
    AppLog->flush_on(spdlog::level::trace);
}
