#ifndef DELIVERY_MAN_H
#define DELIVERY_MAN_H

#include <stdlib.h>
#include <assert.h>

#include <chayai.h>

/// Delivery man.
typedef struct DeliveryMan
{
    unsigned int speed; ///< Delivery man speed from 1 to 10.
} DeliveryMan;


/// Initialize a delivery man instance.
/// @param speed Delivery man speed from 1 to 10.
inline static void delivery_man_init(DeliveryMan* deliveryMan, unsigned int speed)
{
    assert(deliveryMan != NULL);
    deliveryMan->speed = speed;
}

/// Deliver a package.
/// @param distance Distance the package has to travel.
inline static void delivery_man_deliver_package(
    const DeliveryMan* deliveryMan, unsigned int distance)
{
    // Waste some clock cycles here.
    unsigned int largeNumber = 10000u * distance / deliveryMan->speed;
    while (largeNumber--) {}
}


DECLARE_BENCHMARK(DeliveryMan, DeliverPackage);

DECLARE_BENCHMARK_P(DeliveryMan, DeliverPackage, 1);
DECLARE_BENCHMARK_P(DeliveryMan, DeliverPackage, 2);
DECLARE_BENCHMARK_P(DeliveryMan, DeliverPackage, 3);

DECLARE_BENCHMARK_F(SlowDeliveryManFixture, DeliverPackage);

DECLARE_BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 1);
DECLARE_BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 2);
DECLARE_BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 3);

DECLARE_BENCHMARK(SomeSleep, Sleep1ms);
DECLARE_BENCHMARK(SomeSleep, Sleep10ms);
DECLARE_BENCHMARK(SomeSleep, Sleep20ms);


#endif // DELIVERY_MAN_H
