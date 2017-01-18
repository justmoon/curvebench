#include "config.h"
#include <chayai.h>
#include <stdlib.h>
#include <secp256k1.h>
#include <assert.h>

typedef struct secp256k1_fixture
{
    unsigned char pubkey[33];
    unsigned char msg[32];
    unsigned char sig[72];
    int siglen;
} secp256k1_fixture;

static void* secp256k1_fixture_set_up()
{
    secp256k1_fixture *fix = (secp256k1_fixture*)malloc(sizeof(secp256k1_fixture));

    secp256k1_start(SECP256K1_START_VERIFY | SECP256K1_START_SIGN);

    unsigned char key[32];
    unsigned char nonce[32];

    for (int i = 0; i < 32; i++) fix->msg[i] = 1 + i;
    for (int i = 0; i < 32; i++) nonce[i] = 33 + i;
    for (int i = 0; i < 32; i++) key[i] = 65 + i;

    int pubkeylen = 33;
    assert(secp256k1_ec_pubkey_create(fix->pubkey, &pubkeylen, key, 1));
    fix->siglen = 72;
    assert(secp256k1_ecdsa_sign(fix->msg, 32, fix->sig, &fix->siglen, key, nonce));
    return (void*)fix;
}

static void secp256k1_fixture_tear_down(void *arg)
{
    secp256k1_fixture *fix = (secp256k1_fixture*)arg;
    free(fix);
}

BENCHMARK_F(secp256k1_fixture, verify, 10, 10000)
{
    secp256k1_fixture *fix = (secp256k1_fixture*)arg;

    assert(secp256k1_ecdsa_verify(fix->msg, 32, fix->sig, fix->siglen, fix->pubkey, 33));
}

