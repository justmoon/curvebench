#include <chayai.h>
#include "delivery_man.h"


static void* SlowDeliveryManFixture_set_up()
{
    DeliveryMan* d = (DeliveryMan*)malloc(sizeof(DeliveryMan));
    if (d == NULL) return NULL;
    delivery_man_init(d, 1);
    return (void*)d;
}

static void SlowDeliveryManFixture_tear_down(void *arg)
{
    free(arg);
}


BENCHMARK_F(SlowDeliveryManFixture, DeliverPackage, 10, 100)
{
    DeliveryMan* d = (DeliveryMan*)arg;
    delivery_man_deliver_package(d, 10);
}
