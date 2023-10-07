#include <gtest/gtest.h>
#include "sampleapp.h"


class SampleAppFixture : public testing::Test
{
public:
    SampleAppFixture();

protected:
    string expectedText;
};