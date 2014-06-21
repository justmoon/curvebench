//
// System-specific implementation of the clock functions.
//
// Copyright (C) 2013 Vlad Lazarenko <vlad@lazarenko.me>
// Copyright (C) 2014 Nicolas Pauss <nicolas.pauss@gmail.com>
//
// Implementation notes:
// 
// On Windows, QueryPerformanceCounter() is used. It gets 
// real-time clock with up to nanosecond precision.
//
// On Apple (OS X, iOS), mach_absolute_time() is used. It gets
// CPU/bus dependent real-time clock with up to nanosecond precision.
//
// On Unix, gethrtime() is used with HP-UX and Solaris. Otherwise, 
// clock_gettime() is used to access monotonic real-time clock
// with up to nanosecond precision. On kernels 2.6.28 and newer, the ticks
// are also raw and are not subject to NTP and/or adjtime(3) adjustments.
//
// Other POSIX compliant platforms resort to using gettimeofday(). It is
// subject to clock adjustments, does not allow for higher than microsecond
// resolution and is also declared obsolete by POSIX.1-2008.
//
// Note on C++11:
//
// Starting with C++11, we could use std::chrono. However, the details of
// what clock is really being used is implementation-specific. For example,
// Visual Studio 2012 defines "high_resolution_clock" as system clock with
// ~1 millisecond precision that is not acceptable for performance
// measurements. Therefore, we are much better off having full control of what
// mechanism we use to obtain the system clock.
//
#ifndef CHAYAI_CLOCK_H
#define CHAYAI_CLOCK_H


// Win32
#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
typedef LARGE_INTEGER CHayaiTimePoint;

// Apple
#elif defined(__APPLE__) && defined(__MACH__)
#include <mach/mach_time.h>
typedef uint64_t CHayaiTimePoint;

// Unix
#elif defined(__unix__) || defined(__unix) || defined(unix)

// gethrtime
#   if (defined(__hpux) || defined(hpux)) || ((defined(__sun__) || defined(__sun) || defined(sun)) && (defined(__SVR4) || defined(__svr4__)))
#   include <sys/time.h>
typedef hrtime_t CHayaiTimePoint;

// clock_gettime
#   elif defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
#   include <time.h>
typedef struct timespec CHayaiTimePoint;

// gettimeofday
#   else
#   include <sys/time.h>
typedef struct timeval CHayaiTimePoint;

#   endif
#else
#error "Unable to define high resolution timer for an unknown OS."
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/// Get the current time as a time point.
/// @returns the current time point.
CHayaiTimePoint chayai_clock_now();


/// Get the duration between two time points.
/// @param startTime Start time point.
/// @param endTime End time point.
/// @returns the number of nanoseconds elapsed between the two time
/// points.
int64_t chayai_clock_duration(CHayaiTimePoint startTime, CHayaiTimePoint endTime);

#ifdef __cplusplus
}
#endif


#endif // CHAYAI_CLOCK_H
