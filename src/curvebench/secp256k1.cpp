#include <hayai.hpp>

class Secp255k1Fixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
    }
 
    virtual void TearDown()
    {
    }
};

BENCHMARK_F(Secp255k1Fixture, Verify, 10, 100)
{

}

