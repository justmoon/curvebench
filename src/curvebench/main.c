#include <chayai.h>
#include "secp256k1.h"
#include "ed25519.h"

int main()
{
    CHayaiOutputter outputter;

    REGISTER_BENCHMARK_F(secp256k1_fixture, verify);
    REGISTER_BENCHMARK_F(ed25519_fixture, verify);

    chayai_console_outputter_init(&outputter);
    chayai_set_outputter(&outputter);
    chayai_run_benchmarks();

    return 0;
}
