#ifndef CHAYAI_BENCHMARKER_H
#define CHAYAI_BENCHMARKER_H

#include "chayai_benchmark_descriptor.h"
#include "chayai_benchmark_pp.h"
#include "chayai_outputter.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Register benchmark, called by macros
void chayai_register_benchmark(CHayaiBenchmarkDescriptor* descriptor);

/// Set outputter
void chayai_set_outputter(CHayaiOutputter* outputter);

/// Run all registered benchmark
void chayai_run_benchmarks();

#ifdef __cplusplus
}
#endif

#endif // CHAYAI_BENCHMARKER_H
