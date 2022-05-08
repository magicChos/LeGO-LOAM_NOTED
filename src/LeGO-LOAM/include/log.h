
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <string>

namespace lego_loam
{
    namespace common
    {

#define LOG_VERSION "0.1.0"

        typedef void (*log_LockFn)(void *udata, int lock);

        enum
        {
            LOG_TRACE,
            LOG_DEBUG,
            LOG_INFO,
            LOG_WARN,
            LOG_ERROR,
            LOG_FATAL
        };

#define LogTrace(...) lego_loam::common::Log::Write(lego_loam::common::LOG_TRACE, __FILENAME__, __LINE__, __VA_ARGS__)
#define LogDebug(...) lego_loam::common::Log::Write(lego_loam::common::LOG_DEBUG, __FILENAME__, __LINE__, __VA_ARGS__)
#define LogInfo(...) lego_loam::common::Log::Write(lego_loam::common::LOG_INFO, __FILENAME__, __LINE__, __VA_ARGS__)
#define LogWarn(...) lego_loam::common::Log::Write(lego_loam::common::LOG_WARN, __FILENAME__, __LINE__, __VA_ARGS__)
#define LogError(...) lego_loam::common::Log::Write(lego_loam::common::LOG_ERROR, __FILENAME__, __LINE__, __VA_ARGS__)
#define LogFatal(...) lego_loam::common::Log::Write(lego_loam::common::LOG_FATAL, __FILENAME__, __LINE__, __VA_ARGS__)
#define LogInitFile(filename) lego_loam::common::Log::SetFp(filename)

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

        class Log
        {
        public:
            Log() = delete;

            Log(const std::string log_file);

            static void Write(int level, const char *file, int line, const char *fmt, ...);

            static void SetUdata(void *udata);

            static void SetLock(log_LockFn fn);

            static void SetFp(FILE *fp);

            static void SetLevel(int level);

            static void SetQuiet(int enable);

            FILE *fp;
        };
        
    } // namespace common
} // namespace agv

#endif //LOG_H
