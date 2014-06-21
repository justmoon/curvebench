#ifndef CHAYAI_OUTPUTTER_H
#define CHAYAI_OUTPUTTER_H

#include "chayai_benchmark_result.h"

/// Outputter.
/// Base struct for outputters.
typedef struct CHayaiOutputter
{
    /// Begin benchmarking.
    /// @param benchmarksCount Number of benchmarks to be executed.
    void (*begin)(unsigned int benchmarksCount);
    
    /// End benchmarking.
    /// @param benchmarksCount Number of benchmarks that have been executed.    
    void (*end)(unsigned int benchmarksCount);
    
    /// Begin benchmark run.
    /// @param fixtureName Fixture name.
    /// @param testName Benchmark name.
    /// @param parameters Test parameter description.
    /// @param runsCount Number of runs to be executed.
    /// @param iterationsCount Number of iterations per run.
    void (*beginBenchmark)(const char* fixtureName,
                           const char* benchmarkName,
                           unsigned int runsCount,
                           unsigned int iterationsCount);
                    

    /// End benchmark run.
    /// @param fixtureName Fixture name.
    /// @param benchmarkName Benchmark name.
    /// @param parameters Benchmark parameter description.
    /// @param result Benchmark result.
    void (*endBenchmark)(const char* fixtureName,
                         const char* benchmarkName,
                         const CHayaiBenchmarkResult* result);
                    
} CHayaiOutputter;

#endif // CHAYAI_OUTPUTTER_H
