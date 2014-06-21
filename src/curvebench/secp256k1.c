#include "config.h"
#include <chayai.h>

#include "num_impl.h"
#include "field_impl.h"
#include "group_impl.h"
#include "ecmult_impl.h"
#include "ecdsa_impl.h"
#include "util_impl.h"

void random_num_order(secp256k1_num_t *num) {
    do {
        unsigned char b32[32];
        secp256k1_rand256(b32);
        secp256k1_num_set_bin(num, b32, 32);
        if (secp256k1_num_is_zero(num))
            continue;
        if (secp256k1_num_cmp(num, &secp256k1_ge_consts->order) >= 0)
            continue;
        break;
    } while(1);
}

typedef struct secp256k1_fixture
{
    secp256k1_fe_t x;
    secp256k1_num_t r, s, m;
    secp256k1_ecdsa_sig_t sig;
} secp256k1_fixture;

static void* secp256k1_fixture_set_up()
{
    secp256k1_fixture *fix = (secp256k1_fixture*)malloc(sizeof(secp256k1_fixture));

    secp256k1_fe_start();
    secp256k1_ge_start();
    secp256k1_ecmult_start();

    secp256k1_num_init(&fix->r);
    secp256k1_num_init(&fix->s);
    secp256k1_num_init(&fix->m);
    random_num_order(&fix->m);
    random_num_order(&fix->r);
    random_num_order(&fix->s);

    secp256k1_ecdsa_sig_init(&fix->sig);
    secp256k1_ecdsa_sig_set_rs(&fix->sig, &fix->r, &fix->s);

    secp256k1_fe_set_hex(&fix->x, "a357ae915c4a65281309edf20504740f0eb3343990216b4f81063cb65f2f7e0f", 64);

    return (void*)fix;
}

static void secp256k1_fixture_tear_down(void *arg)
{
    secp256k1_fixture *fix = (secp256k1_fixture*)arg;

    secp256k1_num_free(&fix->r);
    secp256k1_num_free(&fix->s);
    secp256k1_num_free(&fix->m);
    secp256k1_ecdsa_sig_free(&fix->sig);

    secp256k1_ecmult_stop();
    secp256k1_ge_stop();
    secp256k1_fe_stop();

    free(fix);
}

BENCHMARK_F(secp256k1_fixture, verify, 10, 100)
{
    secp256k1_fixture *fix = (secp256k1_fixture*)arg;

    secp256k1_ge_t pubkey; secp256k1_ge_set_xo(&pubkey, &fix->x, 1);
    secp256k1_ecdsa_sig_verify(&fix->sig, &pubkey, &fix->m);
}

