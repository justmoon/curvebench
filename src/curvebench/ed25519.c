#include "config.h"
#include <chayai.h>
#include <ed25519.h>
#include <openssl/rand.h>

ed25519_secret_key sk = { 0x1a, 0xca, 0xae, 0xde, 0xce, 0x40, 0x5b, 0x2a, 0x95, 0x82, 0x12, 0x62, 0x9e, 0x16, 0xf2, 0xeb, 0x46, 0xb1, 0x53, 0xee, 0xe9, 0x4c, 0xdd, 0x35, 0x0f, 0xde, 0xff, 0x52, 0x79, 0x55, 0x25, 0xb7};

#define TEST_MESSAGE ((unsigned char *) "This is a test message.")

typedef struct ed25519_fixture
{
    ed25519_public_key pk;
    ed25519_signature sig;
} ed25519_fixture;

static void* ed25519_fixture_set_up()
{
    ed25519_fixture *fix = (ed25519_fixture*)malloc(sizeof(ed25519_fixture));

    ed25519_publickey(sk, fix->pk);
    ed25519_sign(TEST_MESSAGE, sizeof(TEST_MESSAGE)-1, sk, fix->pk, fix->sig);

    return (void*)fix;
}

static void ed25519_fixture_tear_down(void *arg)
{
    ed25519_fixture *fix = (ed25519_fixture*)arg;

    free(fix);
}

BENCHMARK_F(ed25519_fixture, verify, 10, 10000)
{
    ed25519_fixture *fix = (ed25519_fixture*)arg;

    ed25519_sign_open(TEST_MESSAGE, sizeof(TEST_MESSAGE)-1, fix->pk, fix->sig);
}

