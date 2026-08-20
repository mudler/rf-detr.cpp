#ifndef RFDETR_COMMON_HPP
#define RFDETR_COMMON_HPP

#include "rfdetr.h"

/* Internal helper used by every source file to emit a log message
 * via the registered callback. No-op if no callback is set.
 * Uses C++ linkage so it can be re-declared with `extern void ...`
 * in tests without needing to include this header. */
void rfdetr_internal_log(rfdetr_log_level lvl, const char* msg);

/* Format-string checking where the compiler offers it. MSVC does not
 * understand __attribute__, and MinGW's printf is the gnu_printf dialect —
 * the same three cases ggml.h handles with GGML_ATTRIBUTE_FORMAT. */
#ifndef __GNUC__
#    define RFDETR_ATTRIBUTE_FORMAT(...)
#elif defined(__MINGW32__) && !defined(__clang__)
#    define RFDETR_ATTRIBUTE_FORMAT(...) __attribute__((format(gnu_printf, __VA_ARGS__)))
#else
#    define RFDETR_ATTRIBUTE_FORMAT(...) __attribute__((format(printf, __VA_ARGS__)))
#endif

/* printf-style wrapper. Builds the string then dispatches. */
void rfdetr_logf(rfdetr_log_level lvl, const char* fmt, ...)
    RFDETR_ATTRIBUTE_FORMAT(2, 3);

#endif
