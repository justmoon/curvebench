#include <chayai.h>
#include "delivery_man.h"

static void* FastDeliveryManFixture_set_up()
{
    DeliveryMan* d = (DeliveryMan*)malloc(sizeof(DeliveryMan));
    if (d == NULL) return NULL;
    delivery_man_init(d, 10);
    return (void*)d;
}

static void FastDeliveryManFixture_tear_down(void *arg)
{
    free(arg);
}

/*
 * Note _F suffix in macro name.
 */
BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 10, 100,
              (void* arg, unsigned int distance))
{
    DeliveryMan* d = (DeliveryMan*)arg;
    delivery_man_deliver_package(d, distance);
}

BENCHMARK_P_F_INSTANCE(FastDeliveryManFixture, DeliverPackage, 1, (arg, 1));
BENCHMARK_P_F_INSTANCE(FastDeliveryManFixture, DeliverPackage, 2, (arg, 10));
BENCHMARK_P_F_INSTANCE(FastDeliveryManFixture, DeliverPackage, 3, (arg, 100));
