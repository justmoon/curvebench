#include <hayai.hpp>
#include <ed25519.h>

#define TEST_MESSAGE ((unsigned char *) "This is a test message.")

class Ed25519DonnaFixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        ed25519_publickey(sk, pk);
        ed25519_sign(TEST_MESSAGE, sizeof(TEST_MESSAGE)-1, sk, pk, sig);
    }

    virtual void TearDown()
    {
    }

    const ed25519_secret_key sk = { 0x1a, 0xca, 0xae, 0xde, 0xce, 0x40, 0x5b, 0x2a, 0x95, 0x82, 0x12, 0x62, 0x9e, 0x16, 0xf2, 0xeb, 0x46, 0xb1, 0x53, 0xee, 0xe9, 0x4c, 0xdd, 0x35, 0x0f, 0xde, 0xff, 0x52, 0x79, 0x55, 0x25, 0xb7};
    ed25519_public_key pk;
    ed25519_signature sig;
};

BENCHMARK_F(Ed25519DonnaFixture, Verify, 10, 100)
{
    ed25519_sign_open(TEST_MESSAGE, sizeof(TEST_MESSAGE)-1, pk, sig);
}

