#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

#include "chayai_benchmark_descriptor.h"
#include "chayai_benchmark_pp.h"
#include "chayai_benchmark_result.h"
#include "chayai_console_outputter.h"

#include "chayai_benchmarker.h"


static CHayaiBenchmarkDescriptor* firstBenchmarkDescriptor = NULL;
static CHayaiBenchmarkDescriptor* lastBenchmarkDescriptor;
static unsigned int nbBenchmarksRegistered = 0;
static CHayaiOutputter* currentOutputter = NULL;

void chayai_register_benchmark(CHayaiBenchmarkDescriptor* descriptor)
{
    assert(descriptor != NULL);
    
    if (firstBenchmarkDescriptor == NULL) {
        firstBenchmarkDescriptor = descriptor;
    } else {
        lastBenchmarkDescriptor->next = descriptor;
    }
    lastBenchmarkDescriptor = descriptor;
    nbBenchmarksRegistered++;
}

void chayai_set_outputter(CHayaiOutputter* outputter)
{
    currentOutputter = outputter;
}


void chayai_run_benchmarks()
{
    CHayaiBenchmarkResult result;
    unsigned int runs;
    int64_t timeRun;

    if (currentOutputter == NULL) return;
    
    CHayaiBenchmarkDescriptor* currentBenchmarkDescriptor = firstBenchmarkDescriptor;
    
    currentOutputter->begin(nbBenchmarksRegistered);
    
    while (currentBenchmarkDescriptor != NULL) {
        result.runs = currentBenchmarkDescriptor->runs;
        result.iterations = currentBenchmarkDescriptor->iterations;
        result.timeTotal = 0;
        result.timeRunMin = INT64_MAX;
        result.timeRunMax = INT64_MIN;
        
        runs = result.runs;
        
        currentOutputter->beginBenchmark(
            currentBenchmarkDescriptor->fixtureName,
            currentBenchmarkDescriptor->benchmarkName,
            currentBenchmarkDescriptor->runs,
            currentBenchmarkDescriptor->iterations);
            
            
        while(runs--) {
            timeRun = currentBenchmarkDescriptor->runFunction();
            result.timeTotal += timeRun;
            if (result.timeRunMin > timeRun) result.timeRunMin = timeRun;
            if (result.timeRunMax < timeRun) result.timeRunMax = timeRun;
        }
        
        
        currentOutputter->endBenchmark(
            currentBenchmarkDescriptor->fixtureName,
            currentBenchmarkDescriptor->benchmarkName,
            &result);
        
        currentBenchmarkDescriptor = currentBenchmarkDescriptor->next;
    }
    
    currentOutputter->end(nbBenchmarksRegistered);
}
