#include "nodetests.hpp"

#include <string>

NodeFixture::NodeFixture()
    :node("A")
{
}

GraphFixture::GraphFixture()
    :NodeFixture()
{
    numNodes = 11;
    nodes.push_back(node);

    for(char c='B'; c<='K'; ++c)
    {
        nodes.emplace_back(std::string(1, c));
    }
    // A
    nodes[0].addAdjacents(nodes[1]);  // A - B
    nodes[0].addAdjacents(nodes[2]);  // A - C
    nodes[0].addAdjacents(nodes[10]);  // A - K 
    
    // B
    nodes[1].addAdjacents(nodes[2]);  // B - C
    nodes[1].addAdjacents(nodes[0]);  // B - A
    nodes[1].addAdjacents(nodes[3]);  // B - D
    nodes[1].addAdjacents(nodes[5]);  // B - F
    nodes[1].addAdjacents(nodes[6]);  // B - G

    // C
    nodes[2].addAdjacents(nodes[1]);  // C - B
    nodes[2].addAdjacents(nodes[0]);  // C - A
    nodes[2].addAdjacents(nodes[4]);  // C - E

    // D
    nodes[3].addAdjacents(nodes[7]);  // D - H
    nodes[3].addAdjacents(nodes[1]);  // D - B

    //E
    nodes[4].addAdjacents(nodes[6]);  // E - G
    nodes[4].addAdjacents(nodes[8]);  // E - I
    nodes[4].addAdjacents(nodes[2]);  // E - C
    
    // F
    nodes[5].addAdjacents(nodes[9]);  // F - J
    nodes[5].addAdjacents(nodes[1]);  // F - B

    // G
    nodes[6].addAdjacents(nodes[4]);  // G - E
    nodes[6].addAdjacents(nodes[1]);  // G - B
   

    // H
    nodes[7].addAdjacents(nodes[3]);  // H - D

    // I
    nodes[8].addAdjacents(nodes[4]);  // I - E

    // J
    nodes[9].addAdjacents(nodes[5]);  // J - F
    
    // K
    nodes[10].addAdjacents(nodes[0]); // K - A
}

DirectGraphFixture::DirectGraphFixture()
{
    // Created Graph with 10 Node A->B->D->H, A->C->B, A->B->F->L, A->C->E->G->B, A->C->E->I
    Node<std::string> nodeB("B");
    Node<std::string> nodeC("C");
    Node<std::string> nodeD("D");
    Node<std::string> nodeE("E");
    Node<std::string> nodeF("F");
    Node<std::string> nodeG("G");
    Node<std::string> nodeH("H");
    Node<std::string> nodeI("I");
    Node<std::string> nodeL("L");

    nodeD.addAdjacents(nodeH);
    nodeF.addAdjacents(nodeL);
    nodeE.addAdjacents(nodeI);
    nodeB.addAdjacents(nodeD);
    nodeB.addAdjacents(nodeF);
    nodeG.addAdjacents(nodeB);
    nodeE.addAdjacents(nodeG);
    nodeC.addAdjacents(nodeE);
    nodeC.addAdjacents(nodeB);
    node.addAdjacents(nodeB);
    node.addAdjacents(nodeC);
}
TEST_F(NodeFixture, CreateNode)
{
    EXPECT_EQ(node.getValue(), "A");
    EXPECT_FALSE(node.hasAdjacents());
    EXPECT_TRUE(node.readAdjacents().empty());
    EXPECT_TRUE(node.getAdjacents().empty());
    EXPECT_FALSE(node.hasPathTo("B"));
}

TEST_F(NodeFixture, ReadValue)
{
    EXPECT_EQ(node.readValue(), "A");
}

TEST_F(NodeFixture, PrintVisitedNode)
{
    auto print = [](const std::string& data){
        std::cout << data << std::endl;
    };
    EXPECT_NO_THROW(node.visit(print));
}

TEST_F(NodeFixture, AddAdjacents)
{
    Node<std::string> nodeB("B");
    Node<std::string> nodeC("C");

    EXPECT_NO_THROW(node.addAdjacents(nodeB));
    EXPECT_NO_THROW(node.addAdjacents(nodeC));
    EXPECT_TRUE(node.hasAdjacents());
    auto connectedNodes = node.readAdjacents();
    EXPECT_EQ(connectedNodes.size(), 2);
    std::for_each(connectedNodes.begin(), connectedNodes.end(),
                  [](const auto& node){
                std::cout << node.readValue() << std::endl;
    });
    EXPECT_TRUE(node.hasPathTo("B"));
    EXPECT_TRUE(node.hasPathTo("C"));
    EXPECT_FALSE(node.hasPathTo("D"));
}

TEST_F(DirectGraphFixture, CreatedDirectGraph)
{
    EXPECT_EQ(node.getValue(), "A");
    EXPECT_TRUE(node.hasAdjacents());
    EXPECT_EQ(node.readAdjacents().size(), 2);
    auto print = [](const std::string& data){
        std::cout << data << std::endl;
    };
    node.visit(print);
    EXPECT_TRUE(node.hasPathTo("B"));
    EXPECT_TRUE(node.hasPathTo("C"));
    EXPECT_FALSE(node.hasPathTo("D"));
    EXPECT_FALSE(node.hasPathTo("E"));
    EXPECT_FALSE(node.hasPathTo("F"));
    EXPECT_FALSE(node.hasPathTo("G"));
    EXPECT_FALSE(node.hasPathTo("H"));
    EXPECT_FALSE(node.hasPathTo("I"));
}

TEST_F(DirectGraphFixture, FindPathBetweenTwoNodeNotAdjacents)
{
    Node<std::string> nodeG("G");
    EXPECT_TRUE(isThereDirectPathFromTo(node, nodeG));
}

TEST_F(DirectGraphFixture, PathNotFound)
{
    Node<std::string> nodeK("K");
    EXPECT_FALSE(isThereDirectPathFromTo(node, nodeK));
}

TEST_F(DirectGraphFixture, PathFromBtoANotFound)
{
    Node<std::string> nodeB = node.getAdjacents().front();
    EXPECT_FALSE(isThereDirectPathFromTo(nodeB, node));
}

TEST_F(GraphFixture, CreatedUndirectedGraph)
{
    EXPECT_NE(&nodes[1], &nodes[0].getAdjacents()[0]);
    /*EXPECT_EQ(&nodes[2], &nodes[0].getAdjacents()[1]);
    EXPECT_EQ(&nodes[10], &nodes[0].getAdjacents()[2]);*/
}

TEST_F(GraphFixture, PathBetweenGandK)
{
   /* Node<std::string> nodeG = nodes[6];
    Node<std::string> nodeK = nodes[10];*/
    EXPECT_TRUE(isTherePathBetweenTwoNodes(6, 10, nodes));
}

TEST_F(GraphFixture, PathPointingToNodeItself)
{
   /* Node<std::string> nodeG = nodes[6];
    Node<std::string> nodeK = nodes[10];*/
    EXPECT_TRUE(isTherePathBetweenTwoNodes(6, 6, nodes));
}