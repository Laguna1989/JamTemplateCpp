#include "pathfinder.hpp"
#include <math_helper.hpp>
#include <tracy/Tracy.hpp>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {

using NodeT = jt::pathfinder::NodeT;

float calculateDistance(NodeT const& node1, jt::Vector2u const& position2)
{
    auto const& thisPosition = node1->getTilePosition();

    auto diff = jt::Vector2f { static_cast<float>(position2.x) - thisPosition.x,
        static_cast<float>(position2.y) - thisPosition.y };
    return jt::MathHelper::qlength(diff);
}

NodeT findClosestNodeTo(std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>>& toCheck,
    jt::Vector2u const& endPosition)
{
    if (toCheck.empty()) {
        throw std::invalid_argument { "cannot find closestNodeToEnd because no nodes given." };
    }

    auto minDistance = std::numeric_limits<float>::max();
    NodeT closestNode = nullptr;

    for (auto n : toCheck) {
        auto currentNode = n.lock();
        if (!currentNode) {
            throw std::invalid_argument { "invalid currentNode in findClosetNodeToEnd" };
        }

        auto currentDistance = calculateDistance(currentNode, endPosition);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            closestNode = currentNode;
        }
    }

    std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> newToCheck;
    for (auto n : toCheck) {
        if (n.lock() != closestNode) {
            newToCheck.push_back(n);
        }
    }

    toCheck = newToCheck;
    return closestNode;
}

void setNeighbourValue(
    NodeT const& currentNode, std::shared_ptr<jt::pathfinder::NodeInterface> const& neighbour_node)
{
    auto const dist = calculateDistance(neighbour_node, currentNode->getTilePosition());
    auto const newValue = dist + currentNode->getValue();

    float const oldValue = neighbour_node->getValue();
    if (oldValue == -1.0 || oldValue > newValue) {
        neighbour_node->setValue(newValue);
    }
}

void addNeighboursToToCheck(
    NodeT const& currentNode, std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>>& toCheck)
{
    for (auto n : currentNode->getNeighbours()) {
        auto neighbour_node = n.lock();
        if (!neighbour_node) {
            throw std::invalid_argument { "deleted node in pathfinding" };
        }
        if (neighbour_node->wasVisited()) {
            continue;
        }
        setNeighbourValue(currentNode, neighbour_node);

        toCheck.push_back(n);
    }
}

bool calculateNodeValuesFromEndToStart(NodeT const& start, NodeT const& end)
{
    auto const& startPosition = start->getTilePosition();

    end->visit();
    end->setValue(0.0f);

    std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> toCheck;
    addNeighboursToToCheck(end, toCheck);

    while (true) {
        if (toCheck.empty()) {
            std::cout << "no path found\n";
            return false;
        }

        auto node = findClosestNodeTo(toCheck, startPosition);
        if (!node) {
            throw std::invalid_argument { "deleted node in pathfinding" };
        }

        node->visit();
        if (node == start) {
            break;
        }

        addNeighboursToToCheck(node, toCheck);
    }
    return true;
}

NodeT findNeighbourWithSmallestValue(NodeT const& current)
{
    auto minValue = std::numeric_limits<float>::max();
    NodeT minNode = nullptr;
    for (auto n : current->getNeighbours()) {
        auto node = n.lock();
        auto currentValue = node->getValue();
        if (currentValue == -1) {
            continue;
        }
        if (currentValue <= minValue) {
            minValue = currentValue;
            minNode = node;
        }
    }
    return minNode;
}

} // namespace

std::vector<NodeT> jt::pathfinder::calculatePath(NodeT const& start, NodeT const& end)
{
    ZoneScopedN("jt::pathfinder::calculatePath");
    if (start == end) {
        return std::vector<NodeT> {};
    }
    if (!calculateNodeValuesFromEndToStart(start, end)) {
        return std::vector<NodeT> {};
    }
    auto current = start;
    std::vector<NodeT> nodes;

    nodes.push_back(current);

    while (current != end) {
        current = findNeighbourWithSmallestValue(current);
        nodes.push_back(current);
    }

    return nodes;
}
