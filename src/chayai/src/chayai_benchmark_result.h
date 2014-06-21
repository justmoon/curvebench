#ifndef CHAYAI_TESTRESULT_H
#define CHAYAI_TESTRESULT_H

#include <stdint.h>

typedef struct CHayaiBenchmarkResult
{
    unsigned int runs;
    unsigned int iterations;
    int64_t timeTotal;
    int64_t timeRunMin;
    int64_t timeRunMax;
} CHayaiBenchmarkResult;


#endif // CHAYAI_TESTRESULT_H
