#pragma once
#include "npcStrategy.h"
#include "source/map/Tile.h"
#include<iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;
/**
* A concrete Strategy that implements an aggressive movement for npcs
*/


class AttackNpcStrategy : public NpcStrategy {
public:
    struct Node{
    int row, col;  // Position of the node
    bool obstacle; // True if the node is an obstacle
    double g, h;   // Costs for pathfinding
    int parentRow, parentCol;  // Position of the parent node

    Node()
        : row(-1), col(-1), obstacle(true), g(INFINITY), h(0), parentRow(-1), parentCol(-1) {}
    Node(int r, int c, bool obs = false)
        : row(r), col(c), obstacle(obs), g(INFINITY), h(0), parentRow(-1), parentCol(-1) {}

    // Function to calculate the heuristic (Manhattan distance)
    double heuristic(const Node& goal) const {
        return std::abs(row - goal.row) + std::abs(col - goal.col);
    }

    // Function to calculate the total cost (f = g + h)
    double f() const {
        return g + h;
    }
    };

    // Comparison operator for the priority queue
    struct CompareNodes {
        bool operator()(const Node& a, const Node& b) const {
            return a.f() > b.f();
        }
    };

    AttackNpcStrategy(Tile tiles[],int width,int height);
    AttackNpcStrategy();
    static NpcStrategy& getSingleton();

	char execute(Character* npc, int npcLocation, Character* player, int playerLocation);
    static void nodifyGrid(Tile tiles[], int width, int height);
    std::vector<Node> findPath(Node grid[][96], Node& start, Node& goal);

private:
    static Node nodes[32][96];
    static int width;
    static int height;
};