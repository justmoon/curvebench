#ifndef CHAYAI_BENCHMARKER_PP_H
#define CHAYAI_BENCHMARKER_PP_H


#include "chayai_benchmark_descriptor.h"
#include "chayai_clock.h"


#define C_HAYAI_PRIV_BENCHMARK_NAME_PREFIX C_Hayai_
#define C_HAYAI_PRIV_BENCHMARK_NAME_SUFFIX 

#define C_HAYAI_PRIV_CONCAT_N(X, Y) X##Y
#define C_HAYAI_PRIV_CONCAT2(S1,S2) C_HAYAI_PRIV_CONCAT_N(S1,S2)
#define C_HAYAI_PRIV_CONCAT3(S1,S2,S3) C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_CONCAT2(S1,S2),S3)
#define C_HAYAI_PRIV_CONCAT4(S1,S2,S3,S4) C_HAYAI_PRIV_CONCAT3(C_HAYAI_PRIV_CONCAT2(S1,S2),S3,S4)
#define C_HAYAI_PRIV_CONCAT5(S1,S2,S3,S4,S5) C_HAYAI_PRIV_CONCAT4(C_HAYAI_PRIV_CONCAT2(S1,S2),S3,S4,S5)
#define C_HAYAI_PRIV_CONCAT6(S1,S2,S3,S4,S5,S6) C_HAYAI_PRIV_CONCAT5(C_HAYAI_PRIV_CONCAT2(S1,S2),S3,S4,S5,S6)
#define C_HAYAI_PRIV_CONCAT7(S1,S2,S3,S4,S5,S6,S7) C_HAYAI_PRIV_CONCAT6(C_HAYAI_PRIV_CONCAT2(S1,S2),S3,S4,S5,S6,S7)

#define C_HAYAI_PRIV_BENCHMARK_NAME( \
    fixture_name, \
    benchmark_name) \
C_HAYAI_PRIV_CONCAT5(C_HAYAI_PRIV_BENCHMARK_NAME_PREFIX, fixture_name, _, \
    benchmark_name, C_HAYAI_PRIV_BENCHMARK_NAME_SUFFIX)

#define C_HAYAI_PRIV_BENCHMARK_NAME_P( \
    fixture_name, \
    benchmark_name, \
    parameter_name) \
C_HAYAI_PRIV_CONCAT7(C_HAYAI_PRIV_BENCHMARK_NAME_PREFIX, fixture_name, _, \
    benchmark_name, _, parameter_name, C_HAYAI_PRIV_BENCHMARK_NAME_SUFFIX)

// Benchmark Priv


// BENCHMARK


#define C_HAYAI_PRIV_BENCHMARK_2( \
    global_name, \
    fixture_name_arg, \
    benchmark_name_arg, \
    runs_arg, \
    iterations_arg) \
static inline void C_HAYAI_PRIV_CONCAT2(global_name, _body)(void); \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void); \
void C_HAYAI_PRIV_CONCAT2(global_name, _register)() \
{ \
    static CHayaiBenchmarkDescriptor descriptor; \
    descriptor.runFunction = &C_HAYAI_PRIV_CONCAT2(global_name, _run); \
    descriptor.fixtureName = #fixture_name_arg; \
    descriptor.benchmarkName = #benchmark_name_arg; \
    descriptor.runs = (runs_arg); \
    descriptor.iterations = (iterations_arg); \
    chayai_register_benchmark(&descriptor); \
} \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void) \
{ \
    CHayaiTimePoint startTime; \
    CHayaiTimePoint endTime; \
    unsigned int iterations = (iterations_arg); \
    startTime = chayai_clock_now(); \
    while (iterations--) { \
        C_HAYAI_PRIV_CONCAT2(global_name, _body)(); \
    } \
    endTime = chayai_clock_now(); \
    return chayai_clock_duration(startTime, endTime); \
} \
static inline void C_HAYAI_PRIV_CONCAT2(global_name, _body)(void)
    

#define C_HAYAI_PRIV_BENCHMARK( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations) \
C_HAYAI_PRIV_BENCHMARK_2( \
    C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name, benchmark_name), \
    fixture_name, benchmark_name, \
    runs, iterations)
    
#define C_HAYAI_PRIV_DECLARE_BENCHMARK( \
    fixture_name, benchmark_name) \
extern void C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name, benchmark_name), \
    _register)()

#define C_HAYAI_PRIV_REGISTER_BENCHMARK( \
    fixture_name, benchmark_name) \
C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name, benchmark_name),_register)()



// BENCHMARK_P


#define C_HAYAI_PRIV_BENCHMARK_P_2( \
    global_name, \
    fixture_name, \
    benchmark_name, \
    runs_arg, \
    iterations_arg, \
    parameters_types) \
static const unsigned int C_HAYAI_PRIV_CONCAT2(global_name, _runs) = (runs_arg); \
static const unsigned int C_HAYAI_PRIV_CONCAT2(global_name, _iterations) = (iterations_arg); \
static inline void C_HAYAI_PRIV_CONCAT2(global_name, _body) parameters_types


#define C_HAYAI_PRIV_BENCHMARK_P( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations, \
    parameters_types) \
C_HAYAI_PRIV_BENCHMARK_P_2( \
    C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name, benchmark_name), \
    fixture_name, benchmark_name, \
    runs, iterations, parameters_types)
    

#define C_HAYAI_PRIV_BENCHMARK_P_INSTANCE_2( \
    global_name, \
    fixture_name_arg, \
    benchmark_name_arg, \
    parameter_name, \
    parameters) \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void); \
void C_HAYAI_PRIV_CONCAT2(global_name, _register)() \
{ \
    static CHayaiBenchmarkDescriptor descriptor; \
    descriptor.runFunction = &C_HAYAI_PRIV_CONCAT2(global_name, _run); \
    descriptor.fixtureName = #fixture_name_arg; \
    descriptor.benchmarkName = \
        #benchmark_name_arg #parameters; \
    descriptor.runs = \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
            _runs); \
    descriptor.iterations = \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
            _iterations); \
    chayai_register_benchmark(&descriptor); \
} \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void) \
{ \
    CHayaiTimePoint startTime; \
    CHayaiTimePoint endTime; \
    unsigned int iterations = C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME( \
        fixture_name_arg, benchmark_name_arg), _iterations); \
    startTime = chayai_clock_now(); \
    while (iterations--) { \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
        _body) parameters; \
    } \
    endTime = chayai_clock_now(); \
    return chayai_clock_duration(startTime, endTime); \
}

#define C_HAYAI_PRIV_BENCHMARK_P_INSTANCE( \
    fixture_name, \
    benchmark_name, \
    parameter_name, \
    parameters) \
C_HAYAI_PRIV_BENCHMARK_P_INSTANCE_2( \
    C_HAYAI_PRIV_BENCHMARK_NAME_P(fixture_name, benchmark_name, parameter_name), \
    fixture_name, benchmark_name, parameter_name, parameters)
    


    
#define C_HAYAI_PRIV_DECLARE_BENCHMARK_P( \
    fixture_name, benchmark_name, parameter_name) \
extern void C_HAYAI_PRIV_CONCAT2( \
    C_HAYAI_PRIV_BENCHMARK_NAME_P(fixture_name, benchmark_name, parameter_name), \
    _register)()

#define C_HAYAI_PRIV_REGISTER_BENCHMARK_P( \
    fixture_name, benchmark_name, parameter_name) \
C_HAYAI_PRIV_CONCAT2( \
    C_HAYAI_PRIV_BENCHMARK_NAME_P(fixture_name, benchmark_name, parameter_name), \
    _register)()



// BENCHMARK_F



#define C_HAYAI_PRIV_BENCHMARK_F_2( \
    global_name, \
    fixture_name_arg, \
    benchmark_name_arg, \
    runs_arg, \
    iterations_arg) \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void); \
static inline void C_HAYAI_PRIV_CONCAT2(global_name, _body)(void* arg); \
void C_HAYAI_PRIV_CONCAT2(global_name, _register)() \
{ \
    static CHayaiBenchmarkDescriptor descriptor; \
    descriptor.runFunction = &C_HAYAI_PRIV_CONCAT2(global_name, _run); \
    descriptor.fixtureName = #fixture_name_arg; \
    descriptor.benchmarkName = #benchmark_name_arg; \
    descriptor.runs = (runs_arg); \
    descriptor.iterations = (iterations_arg); \
    chayai_register_benchmark(&descriptor); \
} \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void) \
{ \
    CHayaiTimePoint startTime; \
    CHayaiTimePoint endTime; \
    unsigned int iterations = (iterations_arg); \
    void* arg = C_HAYAI_PRIV_CONCAT2(fixture_name_arg, _set_up)(); \
    startTime = chayai_clock_now(); \
    while (iterations--) { \
        C_HAYAI_PRIV_CONCAT2(global_name, _body)(arg); \
    } \
    endTime = chayai_clock_now(); \
    C_HAYAI_PRIV_CONCAT2(fixture_name_arg, _tear_down)(arg); \
    return chayai_clock_duration(startTime, endTime); \
} \
static inline void C_HAYAI_PRIV_CONCAT2(global_name, _body)(void* arg)

#define C_HAYAI_PRIV_BENCHMARK_F( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations) \
C_HAYAI_PRIV_BENCHMARK_F_2( \
    C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name, benchmark_name), \
    fixture_name, benchmark_name, runs, iterations)
    


// BENCHMARK_P_F



#define C_HAYAI_PRIV_BENCHMARK_P_F_2( \
    global_name, \
    fixture_name, \
    benchmark_name, \
    runs_arg, \
    iterations_arg, \
    parameters_types) \
static const unsigned int C_HAYAI_PRIV_CONCAT2(global_name, _runs) = (runs_arg); \
static const unsigned int C_HAYAI_PRIV_CONCAT2(global_name, _iterations) = (iterations_arg); \
static inline void C_HAYAI_PRIV_CONCAT2(global_name, _body) parameters_types

#define C_HAYAI_PRIV_BENCHMARK_P_F( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations, \
    parameters_types) \
C_HAYAI_PRIV_BENCHMARK_P_F_2( \
    C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name, benchmark_name), \
    fixture_name, benchmark_name, runs, iterations, parameters_types)
    



#define C_HAYAI_PRIV_BENCHMARK_P_F_INSTANCE_2( \
    global_name, \
    fixture_name_arg, \
    benchmark_name_arg, \
    parameter_name, \
    parameters) \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void); \
void C_HAYAI_PRIV_CONCAT2(global_name, _register)() \
{ \
    static CHayaiBenchmarkDescriptor descriptor; \
    descriptor.runFunction = &C_HAYAI_PRIV_CONCAT2(global_name, _run); \
    descriptor.fixtureName = #fixture_name_arg; \
    descriptor.benchmarkName = \
        #benchmark_name_arg #parameters; \
    descriptor.runs = \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
            _runs); \
    descriptor.iterations = \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
            _iterations); \
    chayai_register_benchmark(&descriptor); \
} \
static inline int64_t C_HAYAI_PRIV_CONCAT2(global_name, _run)(void) \
{ \
    CHayaiTimePoint startTime; \
    CHayaiTimePoint endTime; \
    unsigned int iterations = \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
            _iterations); \
    void* arg = C_HAYAI_PRIV_CONCAT2(fixture_name_arg, _set_up)(); \
    startTime = chayai_clock_now(); \
    while (iterations--) { \
        C_HAYAI_PRIV_CONCAT2(C_HAYAI_PRIV_BENCHMARK_NAME(fixture_name_arg, benchmark_name_arg), \
            _body) parameters; \
    } \
    endTime = chayai_clock_now(); \
    C_HAYAI_PRIV_CONCAT2(fixture_name_arg, _tear_down)(arg); \
    return chayai_clock_duration(startTime, endTime); \
}

#define C_HAYAI_PRIV_BENCHMARK_P_F_INSTANCE( \
    fixture_name, \
    benchmark_name, \
    parameter_name, \
    parameters) \
C_HAYAI_PRIV_BENCHMARK_P_F_INSTANCE_2( \
    C_HAYAI_PRIV_BENCHMARK_NAME_P(fixture_name, benchmark_name, parameter_name), \
    fixture_name, benchmark_name, parameter_name, parameters)




#endif // CHAYAI_BENCHMARKER_PP_H
