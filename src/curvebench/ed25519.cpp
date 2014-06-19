#include <hayai.hpp>
#include <ed25519.h>

#define TEST_MESSAGE "This is a test message."

class Ed25519Fixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        ed25519_create_seed(seed);
        ed25519_create_keypair(pubkey, privkey, seed);
        ed25519_sign(sig, (unsigned char *)TEST_MESSAGE, sizeof(TEST_MESSAGE)-1,
                     pubkey, privkey);
    }
 
    virtual void TearDown()
    {
    }

    unsigned char seed[32];
    unsigned char pubkey[32];
    unsigned char privkey[64];
    unsigned char sig[64];
};

BENCHMARK_F(Ed25519Fixture, Verify, 10, 100)
{
    ed25519_verify(sig, (unsigned char *)TEST_MESSAGE, sizeof(TEST_MESSAGE)-1,
                   pubkey);
}

