#include <chayai.h>
#include "delivery_man.h"

BENCHMARK(DeliveryMan, DeliverPackage, 10, 100)
{
    DeliveryMan d;
    delivery_man_init(&d, 1);
    delivery_man_deliver_package(&d, 100);
}
