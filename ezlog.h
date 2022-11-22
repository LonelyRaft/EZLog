#ifndef _EZLOG_H
#define _EZLOG_H

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

// log label
#ifdef LOG_USING_TIME
#define LOG_LABELFMT "%s %s %s:%d"
#define LOG_LABEL __DATE__, __TIME__, __FILE__, __LINE__
#else
#define LOG_LABELFMT "%s:%d"
#define LOG_LABEL __FILE__, __LINE__
#endif
#define OUT_LEVEL_INFO "[Info ] " LOG_LABELFMT "\n\t"
#define OUT_LEVEL_DBG "[Debug] " LOG_LABELFMT "\n\t"
#define OUT_LEVEL_WAR "[Warn ] " LOG_LABELFMT "\n\t"
#define OUT_LEVEL_ERR "[Error] " LOG_LABELFMT "\n\t"
#define OUT_ENDFLAG "\n"

// output level
#define LOG_LEVEL_NONE 0x05
#define LOG_LEVEL_ERROR 0x04
#define LOG_LEVEL_WARNING 0x03
#define LOG_LEVEL_INFO 0x02
#define LOG_LEVEL_DEBUG 0x01
#ifndef LOG_LEVEL_CURR
#define LOG_LEVEL_CURR LOG_LEVEL_DEBUG
#endif

// error
#if LOG_LEVEL_ERROR >= LOG_LEVEL_CURR
#define OUTPUT_ERR(fmt, ...)               \
    fprintf(stderr,                        \
            OUT_LEVEL_ERR fmt OUT_ENDFLAG, \
            LOG_LABEL, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) OUTPUT_ERR(fmt, ##__VA_ARGS__)
#else
#define LOG_ERR(fmt, ...)
#endif

// warning
#if LOG_LEVEL_WARNING >= LOG_LEVEL_CURR
#define OUTPUT_WARN(fmt, ...)              \
    fprintf(stderr,                        \
            OUT_LEVEL_WAR fmt OUT_ENDFLAG, \
            LOG_LABEL, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) OUTPUT_WARN(fmt, ##__VA_ARGS__)
#else
#define LOG_WARN(fmt, ...)
#endif

// info
#if LOG_LEVEL_INFO >= LOG_LEVEL_CURR
#define OUTPUT_INFO(fmt, ...)               \
    fprintf(stderr,                         \
            OUT_LEVEL_INFO fmt OUT_ENDFLAG, \
            LOG_LABEL, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) OUTPUT_INFO(fmt, ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...)
#endif

// debug
#if LOG_LEVEL_DEBUG >= LOG_LEVEL_CURR
#define OUTPUT_DBG(fmt, ...)               \
    fprintf(stderr,                        \
            OUT_LEVEL_DBG fmt OUT_ENDFLAG, \
            LOG_LABEL, ##__VA_ARGS__)
#define LOG_DBG(fmt, ...) OUTPUT_DBG(fmt, ##__VA_ARGS__)
#else
#define LOG_DBG(fmt, ...)
#endif

// redirect stderr
extern void *ezlog_redirect(const char *_log_path);

#endif
