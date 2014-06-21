#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "chayai_console.h"
#include "chayai_console_outputter.h"

#define OUTPUT_STREAM stdout
#define PADDING 34
#define FP_TIME 3
#define FP_RUNS 5
#define FP_TOTAL_TIME 6

#define TO_STR_N(X) #X
#define TO_STR(X) TO_STR_N(X)

#define PADDING_STR TO_STR(PADDING)
#define FP_TIME_STR "."TO_STR(FP_TIME)
#define FP_RUNS_STR "."TO_STR(FP_RUNS)
#define FP_TOTAL_TIME_STR "."TO_STR(FP_TOTAL_TIME)


static void chayai_console_outputter_begin(unsigned int bechmarksCount);
static void chayai_console_outputter_end(unsigned int bechmarksCount);
static void chayai_console_outputter_begin_benchmark(
    const char* fixtureName,
    const char* benchmarkName,
    unsigned int runsCount,
    unsigned int iterationsCount);
static void chayai_console_outputter_end_benchmark(
    const char* fixtureName,
    const char* benchmarkName,
    const CHayaiBenchmarkResult* result);


static inline void chayai_console_outputter_deviation(
    const char* description,
    double deviated,
    double average,
    const char* unit);
    
static inline void chayai_console_outputter_deviation_inverse(
    const char* description,
    double deviated,
    double average,
    const char* unit);


void chayai_console_outputter_init(CHayaiOutputter* outputter)
{
    assert(outputter != NULL);
    outputter->begin = &chayai_console_outputter_begin;
    outputter->end = &chayai_console_outputter_end;
    outputter->beginBenchmark = &chayai_console_outputter_begin_benchmark;
    outputter->endBenchmark = &chayai_console_outputter_end_benchmark;
}


static void chayai_console_outputter_begin(unsigned int bechmarksCount)
{
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_GREEN);
    fputs("[==========]", OUTPUT_STREAM);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fprintf(OUTPUT_STREAM, " Running %u", bechmarksCount);
    fputs((bechmarksCount == 1) ? " benchmark.\n" : " benchmarks.\n", OUTPUT_STREAM);
}



static void chayai_console_outputter_end(unsigned int bechmarksCount)
{
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_GREEN);
    fputs("[==========]", OUTPUT_STREAM);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fprintf(OUTPUT_STREAM, " Ran %u ", bechmarksCount);
    fputs((bechmarksCount == 1) ? "benchmark.\n" : "benchmarks.\n", OUTPUT_STREAM);
}


static void chayai_console_outputter_begin_benchmark(
    const char* fixtureName,
    const char* benchmarkName,
    unsigned int runsCount,
    unsigned int iterationsCount)
{
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_GREEN);
    fputs("[ RUN      ]", OUTPUT_STREAM);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_YELLOW);
    fprintf(OUTPUT_STREAM, " %s.%s", fixtureName, benchmarkName);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fprintf(OUTPUT_STREAM, " (%u ", runsCount);
    fputs((runsCount == 1) ? "run, " : "runs, ", OUTPUT_STREAM);
    fprintf(OUTPUT_STREAM, "%u ", iterationsCount);
    fputs((iterationsCount == 1) ? "iteration per run)\n" : "iterations per run)\n", 
        OUTPUT_STREAM);
}




static void chayai_console_outputter_end_benchmark(
    const char* fixtureName,
    const char* benchmarkName,
    const CHayaiBenchmarkResult* result)
{
    const double runTimeMinUs = result->timeRunMin / 1e3;
    const double runTimeMaxUs = result->timeRunMax / 1e3;
    const double runTimeAvgUs = result->timeTotal / (1e3 * result->runs);
    const double runsPerSecsMin = 1e6 / runTimeMaxUs;
    const double runsPerSecsMax = 1e6 / runTimeMinUs;
    const double runsPerSecsAvg = 1e6 / runTimeAvgUs;
    
    const double iterationsDouble = (double)(result->iterations);
    const double iterationTimeMinUs = runTimeMinUs / iterationsDouble;
    const double iterationTimeMaxUs = runTimeMaxUs / iterationsDouble;
    const double iterationTimeAvgUs = runTimeAvgUs / iterationsDouble;
    const double iterationsPerSecsMin = 1e6 / iterationTimeMaxUs;
    const double iterationsPerSecsMax = 1e6 / iterationTimeMinUs;
    const double iterationsPerSecsAvg = 1e6 / iterationTimeAvgUs;
    
    
    

    // Print DONE line
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_GREEN);
    fputs("[     DONE ]", OUTPUT_STREAM);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_YELLOW);
    fprintf(OUTPUT_STREAM, " %s.%s", fixtureName, benchmarkName);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fprintf(OUTPUT_STREAM, " (%"FP_TOTAL_TIME_STR"f ms)\n", result->timeTotal / (1e6));


    // Print RUNS lines
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_BLUE);
    fputs("[   RUNS   ] ", OUTPUT_STREAM);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fprintf(OUTPUT_STREAM, "       Average time: %"FP_TIME_STR"f us\n", runTimeAvgUs);

    chayai_console_outputter_deviation_inverse(
        "Fastest: ", runTimeMinUs, runTimeAvgUs, "us");
        
    chayai_console_outputter_deviation_inverse(
        "Slowest: ", runTimeMaxUs, runTimeAvgUs, "us");
        
    
    fputs("\n", OUTPUT_STREAM);
    
    fprintf(OUTPUT_STREAM, "%"PADDING_STR"s","Average performance: ");
    fprintf(OUTPUT_STREAM, "%"FP_RUNS_STR"f runs/s\n", runsPerSecsAvg);
    
    chayai_console_outputter_deviation(
        "Best performance: ", runsPerSecsMax, runsPerSecsAvg, "runs/s");
        
    chayai_console_outputter_deviation(
        "Worst performance: ", runsPerSecsMin, runsPerSecsAvg, "runs/s");


    // Print ITERATIONS lines
    
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_BLUE);
    fputs("[ITERATIONS] ", OUTPUT_STREAM);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fprintf(OUTPUT_STREAM, "       Average time: %"FP_TIME_STR"f us\n", 
        iterationTimeAvgUs);

    chayai_console_outputter_deviation_inverse(
        "Fastest: ", iterationTimeMinUs, iterationTimeAvgUs, "us");
        
    chayai_console_outputter_deviation_inverse(
        "Slowest: ", iterationTimeMaxUs, iterationTimeAvgUs, "us");
        
    
    fputs("\n", OUTPUT_STREAM);
    
    fprintf(OUTPUT_STREAM, "%"PADDING_STR"s","Average performance: ");
    fprintf(OUTPUT_STREAM, "%"FP_RUNS_STR"f iterations/s\n", iterationsPerSecsAvg);
    
    chayai_console_outputter_deviation(
        "Best performance: ", iterationsPerSecsMax, iterationsPerSecsAvg, "iterations/s");
        
    chayai_console_outputter_deviation(
        "Worst performance: ", iterationsPerSecsMin, iterationsPerSecsAvg, "iterations/s");

}


static inline void chayai_console_outputter_deviation(
    const char* description,
    double deviated,
    double average,
    const char* unit)
{
    const double difference = deviated - average;

    fprintf(OUTPUT_STREAM, "%"PADDING_STR"s", description);
    fprintf(OUTPUT_STREAM, "%"FP_RUNS_STR"f", deviated);
    fprintf(OUTPUT_STREAM, " %s (", unit);
    if (difference < 0.0) {
        chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_RED);
    } else {
        chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_GREEN);
    }
    fprintf(OUTPUT_STREAM, "%+"FP_TIME_STR"f ", difference);
    fputs(unit, OUTPUT_STREAM);
    fprintf(OUTPUT_STREAM, " / %+"FP_TIME_STR"f %%", difference * 100.0 / average);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fputs(")\n", OUTPUT_STREAM);
}
    
static inline void chayai_console_outputter_deviation_inverse(
    const char* description,
    double deviated,
    double average,
    const char* unit)
{
    const double difference = deviated - average;
    
    fprintf(OUTPUT_STREAM, "%"PADDING_STR"s", description);
    fprintf(OUTPUT_STREAM, "%"FP_TIME_STR"f", deviated);
    fprintf(OUTPUT_STREAM, " %s (", unit);
    if (difference > 0.0) {
        chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_RED);
    } else {
        chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_GREEN);
    }
    fprintf(OUTPUT_STREAM, "%+"FP_TIME_STR"f ", difference);
    fputs(unit, OUTPUT_STREAM);
    fprintf(OUTPUT_STREAM, " / %+"FP_TIME_STR"f %%", difference * 100.0 / average);
    chayai_console_change_color(OUTPUT_STREAM, CHAYAI_TEXT_DEFAULT);
    fputs(")\n", OUTPUT_STREAM);
}
