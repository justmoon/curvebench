
#include <chayai.h>
#include "delivery_man.h"


int main()
{
    CHayaiOutputter outputter;
    
    REGISTER_BENCHMARK(DeliveryMan, DeliverPackage);
    
    REGISTER_BENCHMARK_P(DeliveryMan, DeliverPackage, 1);
    REGISTER_BENCHMARK_P(DeliveryMan, DeliverPackage, 2);
    REGISTER_BENCHMARK_P(DeliveryMan, DeliverPackage, 3);

    REGISTER_BENCHMARK_F(SlowDeliveryManFixture, DeliverPackage);

    REGISTER_BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 1);
    REGISTER_BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 2);
    REGISTER_BENCHMARK_P_F(FastDeliveryManFixture, DeliverPackage, 3);

    REGISTER_BENCHMARK(SomeSleep, Sleep1ms);
    REGISTER_BENCHMARK(SomeSleep, Sleep10ms);
    REGISTER_BENCHMARK(SomeSleep, Sleep20ms);
    
    
    chayai_console_outputter_init(&outputter);
    chayai_set_outputter(&outputter);
    chayai_run_benchmarks();
    
    return 0;
}
