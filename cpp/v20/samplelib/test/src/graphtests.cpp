#include "graphtests.hpp"

GraphBuilderFixture::GraphBuilderFixture()
{
}

TEST_F(GraphBuilderFixture, CreateGraphOfNumbers)
{
    auto graph = builder.createGraphOfNumbers();
    EXPECT_EQ(graph.getNumNodes(), 0);
}

TEST_F(GraphBuilderFixture, CreateGraphOfStrings)
{
    auto graph = builder.createGraphOfStrings();
    EXPECT_EQ(graph.getNumNodes(), 0);
}

TEST_F(GraphBuilderFixture, CreateInitNode)
{
    auto graph = builder.createGraphOfNumbers();
    graph.addNode(10);
    EXPECT_EQ(graph.getNumNodes(), 1);
    EXPECT_EQ(graph.getDataInRoot(), 10);   
}