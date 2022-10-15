#pragma once

#include <memory>
#include <utility>
#include <string>

/* Is profiling enabled? */
#define ENGINE_LOG_ENABLED 1

/** Default math path length */
#define MAX_PATH 260

/** Useful macros. */
#define CHECK_RETURN(input) if (!(input)) { return; } ;

/** Platform definitions. */
#ifdef PLATFORM_WINDOWS
#ifdef EGG_BUILD
#define EGG_API __declspec(dllexport)
#else
#define EGG_API __declspec(dllimport)
#endif
#else 
#error Egg Engine currently only supports windows!
#endif

/* Define logging macros for logging to the engine or app logging system. */
#if ENGINE_LOG_ENABLED
#define EGG_LOG(LogType, ...) Log::AddEngineLogMessage(LogType, __VA_ARGS__)
#define EGG_QUICK_LOG(...) Log::AddEngineLogMessage(ELogType::Message, __VA_ARGS__)
#else
#define EGG_LOG(LogType, ...)
#define EGG_QUICK_LOG(...)
#endif
#define APP_LOG(LogType, ...) Log::AddAppLogMessage(LogType, __VA_ARGS__)
#define APP_QUICK_LOG(...) Log::AddAppLogMessage(ELogType::Message, __VA_ARGS__)

/** A Unique Pointer solely and explicitly owns the object it references. Since there can only be one
 *  Unique Pointer to a given resource, Unique Pointers can transfer ownership, but cannot share it. */
template<typename T>
using UniquePtr = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr UniquePtr<T> NewUniqueClass(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/** A Shared Pointer owns the object it references, indefinitely preventing deletion of that object,
 *  and ultimately handling its deletion when no Shared Pointer or Shared Reference references it. */
template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr SharedPtr<T> NewClass(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

/** Weak Pointers are similar to Shared Pointers, but do not own the object they reference, and
 *  therefore do not affect its lifecycle. They can also point to a shared pointer but it can become
 *  null at anytime. */
template<typename T>
using WeakPtr = std::shared_ptr<T>;
template<typename T>
constexpr WeakPtr<T> GetReference(SharedPtr<T> InSharedPtr)
{
    return std::weak_ptr<T>(InSharedPtr);
}