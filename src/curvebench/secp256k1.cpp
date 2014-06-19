#include <hayai.hpp>
#include <secp256k1.h>

#define TEST_MESSAGE ((unsigned char *) "This is a test message.")

class Secp256k1Fixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        secp256k1_start();

        secp256k1_ecdsa_pubkey_create(pubkey, &pubkeylen, privkey, 1);

        secp256k1_ecdsa_sign(TEST_MESSAGE, sizeof(TEST_MESSAGE)-1,
                             sig, &siglen,
                             privkey,
                             privkey);
    }

    virtual void TearDown()
  {
        secp256k1_stop();
    }

    const unsigned char privkey[32] = { 0x1a, 0xca, 0xae, 0xde, 0xce, 0x40, 0x5b, 0x2a, 0x95, 0x82, 0x12, 0x62, 0x9e, 0x16, 0xf2, 0xeb, 0x46, 0xb1, 0x53, 0xee, 0xe9, 0x4c, 0xdd, 0x35, 0x0f, 0xde, 0xff, 0x52, 0x79, 0x55, 0x25, 0xb7};
    unsigned char pubkey[33];
    int pubkeylen;
    unsigned char sig[72];
    int siglen;
};

BENCHMARK_F(Secp256k1Fixture, Verify, 10, 100)
{
    secp256k1_ecdsa_verify(TEST_MESSAGE, sizeof(TEST_MESSAGE)-1,
                           sig, siglen,
                           pubkey, pubkeylen);
}

