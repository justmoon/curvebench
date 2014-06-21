
#include "chayai_clock.h"

// Win32
#if defined(_WIN32)


static double chayai_performance_frequency_ns()
{
    CHayaiTimePoint result;
    QueryPerformanceFrequency(&result);
	return 1e9 / static_cast<double>(result.QuadPart);
}
 
CHayaiTimePoint chayai_clock_now()
{
    CHayaiTimePoint result;
    QueryPerformanceCounter(&result);
    return result;
}

int64_t chayai_clock_duration(CHayaiTimePoint startTime, CHayaiTimePoint endTime)
{
    const static double performanceFrequencyNs =
        chayai_performance_frequency_ns();
    
    return (int64_t)((endTime.QuadPart - startTime.QuadPart)
        * performanceFrequencyNs);
}

// Apple    
#elif defined(__APPLE__) && defined(__MACH__)


CHayaiTimePoint chayai_clock_now()
{
    return mach_absolute_time();
}

int64_t chayai_clock_duration(CHayaiTimePoint startTime, CHayaiTimePoint endTime)
{
    mach_timebase_info_data_t time_info;
    mach_timebase_info(&time_info);
    return (endTime - startTime) * time_info.numer / time_info.denom;
}

// Unix
#elif defined(__unix__) || defined(__unix) || defined(unix)

// gethrtime
#   if (defined(__hpux) || defined(hpux)) || ((defined(__sun__) || defined(__sun) || defined(sun)) && (defined(__SVR4) || defined(__svr4__)))
 
CHayaiTimePoint chayai_clock_now()
{
    return gethrtime();
}

int64_t chayai_clock_duration(CHayaiTimePoint startTime, CHayaiTimePoint endTime)
{
    return (int64_t)(endTime - startTime);
}  

// clock_gettime
#   elif defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
 

CHayaiTimePoint chayai_clock_now()
{
    CHayaiTimePoint result;
# if   defined(CLOCK_MONOTONIC_RAW)
    clock_gettime(CLOCK_MONOTONIC_RAW, &result);
# elif defined(CLOCK_MONOTONIC)
    clock_gettime(CLOCK_MONOTONIC, &result);
# elif defined(CLOCK_REALTIME)
    clock_gettime(CLOCK_REALTIME, &result);
# else
    clock_gettime((clockid_t)-1, &result);
# endif
    return result;
}

int64_t chayai_clock_duration(CHayaiTimePoint startTime, CHayaiTimePoint endTime)
{
    CHayaiTimePoint timeDiff;

    timeDiff.tv_sec = endTime.tv_sec - startTime.tv_sec;
    if (endTime.tv_nsec < startTime.tv_nsec)
    {
        timeDiff.tv_nsec = endTime.tv_nsec + 1000000000L - 
            startTime.tv_nsec;
        timeDiff.tv_sec--;
    }
    else
        timeDiff.tv_nsec = endTime.tv_nsec - startTime.tv_nsec;

    return timeDiff.tv_sec * 1000000000L + timeDiff.tv_nsec;
} 
  
// gettimeofday
#   else

CHayaiTimePoint chayai_clock_now()
{
    CHayaiTimePoint result;
    gettimeofday(&result, NULL);
    return result;
}

int64_t chayai_clock_duration(CHayaiTimePoint startTime, CHayaiTimePoint endTime)
{
    return ((endTime.tv_sec - startTime.tv_sec) * 1000000000L +
        (endTime.tv_usec - startTime.tv_usec) * 1000);
}

#   endif
#endif