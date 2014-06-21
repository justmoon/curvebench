#include <chayai.h>
#include "delivery_man.h"

/*
 * Benchmarks can be parameterized. Here is example for
 * simple test without dedicated fixture.
 *
 * Last macro argument is just method parameters declaration.
 * Number of arguments is not limited, just make sure that
 * brackets around them are present.
 */
BENCHMARK_P(DeliveryMan, DeliverPackage, 10, 100, 
    (unsigned int speed, unsigned int distance))
{
	DeliveryMan d;
	delivery_man_init(&d, speed);
	delivery_man_deliver_package(&d, distance);
}

BENCHMARK_P_INSTANCE(DeliveryMan, DeliverPackage, 1, (1, 10));
BENCHMARK_P_INSTANCE(DeliveryMan, DeliverPackage, 2, (5, 10));
BENCHMARK_P_INSTANCE(DeliveryMan, DeliverPackage, 3, (10, 10));
