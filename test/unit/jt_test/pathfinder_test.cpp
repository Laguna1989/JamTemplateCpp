#include "pathfinder/node.hpp"
#include "pathfinder/node_interface.hpp"
#include "pathfinder/pathfinder.hpp"
#include <gtest/gtest.h>
#include <map>

using jt::pathfinder::Node;
using jt::pathfinder::NodeT;

TEST(PathfinderTest, ReturnsEmptyVectorWhenStartEqualsEnd)
{
    NodeT node = std::make_shared<Node>();

    auto const path = jt::pathfinder::calculatePath(node, node);

    ASSERT_TRUE(path.empty());
}

TEST(PathfinderTest, ReturnsEmptyVectorWhenNotConnected)
{
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();

    auto const path = jt::pathfinder::calculatePath(node1, node2);

    ASSERT_TRUE(path.empty());
}

TEST(PathfinderTest, ReturnsEmptyVectorWhenNotConnectedWithNeighboursAtStart)
{
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    auto node3 = std::make_shared<Node>();

    node1->addNeighbour(node2);

    auto const path = jt::pathfinder::calculatePath(node1, node3);

    ASSERT_TRUE(path.empty());
}

TEST(PathfinderTest, ReturnsEmptyVectorWhenNotConnectedWithNeighboursAtEnd)
{
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    auto node3 = std::make_shared<Node>();

    node3->addNeighbour(node2);
    node2->addNeighbour(node3);

    auto const path = jt::pathfinder::calculatePath(node1, node3);

    ASSERT_TRUE(path.empty());
}

TEST(PathfinderTest, ReturnsCorrectEntryForTwoAdjacentNodes)
{
    auto node1 = std::make_shared<Node>();
    node1->setPosition(jt::Vector2u { 0, 0 });
    auto node2 = std::make_shared<Node>();
    node2->setPosition(jt::Vector2u { 1, 0 });

    node1->addNeighbour(node2);
    node2->addNeighbour(node1);

    auto const path = jt::pathfinder::calculatePath(node1, node2);

    ASSERT_EQ(path.size(), 2);
    ASSERT_EQ(path.at(0), node1);
    ASSERT_EQ(path.at(1), node2);
}

TEST(PathfinderTest, ReturnsCorrectEntryForThreeAdjacentNodes)
{
    auto node1 = std::make_shared<Node>();
    node1->setPosition(jt::Vector2u { 0, 0 });
    auto node2 = std::make_shared<Node>();
    node2->setPosition(jt::Vector2u { 1, 0 });
    auto node3 = std::make_shared<Node>();
    node2->setPosition(jt::Vector2u { 2, 0 });

    node1->addNeighbour(node2);
    node2->addNeighbour(node1);
    node2->addNeighbour(node3);
    node3->addNeighbour(node2);

    auto const path = jt::pathfinder::calculatePath(node1, node3);

    ASSERT_EQ(path.size(), 3);
    ASSERT_EQ(path.at(0), node1);
    ASSERT_EQ(path.at(1), node2);
    ASSERT_EQ(path.at(2), node3);
}

TEST(PathfinderTest, ReturnsCorrectEntryForThreeAdjacentNodesStartingIntheMiddle)
{
    auto node1 = std::make_shared<Node>();
    node1->setPosition(jt::Vector2u { 0, 0 });
    auto node2 = std::make_shared<Node>();
    node2->setPosition(jt::Vector2u { 1, 0 });
    auto node3 = std::make_shared<Node>();
    node3->setPosition(jt::Vector2u { 2, 0 });

    node1->addNeighbour(node2);
    node2->addNeighbour(node1);

    node2->addNeighbour(node3);
    node3->addNeighbour(node2);

    auto const path = jt::pathfinder::calculatePath(node2, node3);

    ASSERT_EQ(path.size(), 2);
    ASSERT_EQ(path.at(0), node2);
    ASSERT_EQ(path.at(1), node3);
}

std::vector<NodeT> createNodes()
{
    std::map<std::pair<int, int>, NodeT> nodes;
    for (int i = 0; i != 10; ++i) {
        for (int j = 0; j != 10; ++j) {
            auto node = std::make_shared<Node>();
            node->setPosition(
                jt::Vector2u { static_cast<unsigned int>(i), static_cast<unsigned int>(j) });
            nodes[std::make_pair(i, j)] = node;
        }
    }

    for (int i = 0; i != 10; ++i) {
        for (int j = 0; j != 10; ++j) {
            auto centralNode = nodes[std::make_pair(i, j)];
            for (auto ii = -1; ii != 2; ++ii) {
                for (auto jj = -1; jj != 2; ++jj) {
                    if (ii == 0 && jj == 0) {
                        continue;
                    }
                    auto io = i + ii;
                    if (io < 0 || io >= 10) {
                        continue;
                    }
                    auto jo = j + jj;
                    if (jo < 0 || jo >= 10) {
                        continue;
                    }

                    auto otherNode = nodes[std::make_pair(io, jo)];
                    centralNode->addNeighbour(otherNode);
                }
            }
        }
    }

    std::vector<NodeT> nodeVector;
    for (auto n : nodes) {
        nodeVector.push_back(n.second);
    }
    return nodeVector;
};

TEST(PathfinderTest, BossMonsterTestVertical)
{
    auto nodes = createNodes();
    auto const path = jt::pathfinder::calculatePath(nodes[0], nodes[9]);

    ASSERT_EQ(path.size(), 10);
}

TEST(PathfinderTest, BossMonsterTestDiagonal)
{
    auto nodes = createNodes();
    auto const path = jt::pathfinder::calculatePath(nodes[0], nodes[99]);

    ASSERT_EQ(path.size(), 10);
}

TEST(NodeTest, InitialNoNeighbours)
{
    Node n;
    ASSERT_TRUE(n.getNeighbours().empty());
}

TEST(NodeTest, VisitSetsVisit)
{
    Node n;
    n.visit();
    ASSERT_TRUE(n.wasVisited());
}

TEST(NodeTest, UnvisitSetsVisit)
{
    Node n;
    n.visit();
    n.unvisit();
    ASSERT_FALSE(n.wasVisited());
}

TEST(NodeTest, HasCorrectNeighbours)
{
    Node n;
    n.setPosition({ 0, 0 });
    auto n2 = std::make_shared<Node>();
    n2->setPosition({ 1, 2 });
    n.addNeighbour(n2);
    ASSERT_EQ(n.getNeighbours().size(), 1);
    ASSERT_EQ(n.getNeighbours().at(0).lock(), n2);
}

TEST(NodeTest, AddExpiredWeakPointerRaisesException)
{
    Node n;
    std::shared_ptr<Node> n2 { nullptr };
    ASSERT_THROW(n.addNeighbour(n2), std::invalid_argument);
}

TEST(NodeTest, AddSelfasNeighbourRaisesException)
{
    auto n = std::make_shared<Node>();
    ASSERT_THROW(n->addNeighbour(n), std::invalid_argument);
}
