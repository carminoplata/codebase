#ifndef GRAPHBUILDERIXTURE_H
#define GRAPHBUILDERIXTURE_H

#include "graphbuilder.hpp"

#include <gtest/gtest.h>

class GraphBuilderFixture: public testing::Test
{
public:
    GraphBuilderFixture();

protected:
    GraphBuilder builder;
};

#endif