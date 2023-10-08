#include <gtest/gtest.h>

#include <string>

class SampleAppFixture : public testing::Test
{
public:
    SampleAppFixture();

protected:
    std::string expectedText;
};