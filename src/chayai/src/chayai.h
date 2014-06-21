#ifndef CHAYAI_H
#define CHAYAI_H

#include "chayai_benchmarker.h"
#include "chayai_console_outputter.h"


// BENCHMARK

#define BENCHMARK( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations) \
C_HAYAI_PRIV_BENCHMARK(fixture_name, benchmark_name, runs, iterations)

#define DECLARE_BENCHMARK(fixture_name, benchmark_name) \
C_HAYAI_PRIV_DECLARE_BENCHMARK(fixture_name, benchmark_name)

#define REGISTER_BENCHMARK(fixture_name, benchmark_name) \
C_HAYAI_PRIV_REGISTER_BENCHMARK(fixture_name, benchmark_name)


// BENCHMARK_P


#define BENCHMARK_P( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations, \
    parameters_types) \
C_HAYAI_PRIV_BENCHMARK_P(fixture_name, benchmark_name, runs, iterations, parameters_types)

#define BENCHMARK_P_INSTANCE( \
    fixture_name, \
    benchmark_name, \
    parameter_name, \
    parameters) \
C_HAYAI_PRIV_BENCHMARK_P_INSTANCE(fixture_name, benchmark_name, parameter_name, parameters)


#define DECLARE_BENCHMARK_P(fixture_name, benchmark_name, parameter_name) \
C_HAYAI_PRIV_DECLARE_BENCHMARK_P(fixture_name, benchmark_name, parameter_name)

#define REGISTER_BENCHMARK_P(fixture_name, benchmark_name, parameter_name) \
C_HAYAI_PRIV_REGISTER_BENCHMARK_P(fixture_name, benchmark_name, parameter_name)



// BENCHMARK_F


#define BENCHMARK_F( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations) \
C_HAYAI_PRIV_BENCHMARK_F(fixture_name, benchmark_name, runs, iterations)


#define DECLARE_BENCHMARK_F(fixture_name, benchmark_name) \
C_HAYAI_PRIV_DECLARE_BENCHMARK(fixture_name, benchmark_name)

#define REGISTER_BENCHMARK_F(fixture_name, benchmark_name) \
C_HAYAI_PRIV_REGISTER_BENCHMARK(fixture_name, benchmark_name)



// BENCHMARK_P_F

#define BENCHMARK_P_F( \
    fixture_name, \
    benchmark_name, \
    runs, \
    iterations, \
    parameters_types) \
C_HAYAI_PRIV_BENCHMARK_P_F(fixture_name, benchmark_name, runs, iterations, parameters_types)


#define BENCHMARK_P_F_INSTANCE( \
    fixture_name, \
    benchmark_name, \
    parameter_name, \
    parameters) \
C_HAYAI_PRIV_BENCHMARK_P_F_INSTANCE(fixture_name, benchmark_name, parameter_name, parameters)



#define DECLARE_BENCHMARK_P_F(fixture_name, benchmark_name, parameter_name) \
C_HAYAI_PRIV_DECLARE_BENCHMARK_P(fixture_name, benchmark_name, parameter_name)

#define REGISTER_BENCHMARK_P_F(fixture_name, benchmark_name, parameter_name) \
C_HAYAI_PRIV_REGISTER_BENCHMARK_P(fixture_name, benchmark_name, parameter_name)


#endif // CHAYAI_H
