#include "AttackNpcStrategy.h"
#include "source/player/character.h"
#include "source/map/playerController.h"
#include "source/map/Tile.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <chrono>
#include <thread>

AttackNpcStrategy singleton = AttackNpcStrategy();

AttackNpcStrategy::Node AttackNpcStrategy::nodes[32][96];
int AttackNpcStrategy::width = 0;
int AttackNpcStrategy::height = 0;

AttackNpcStrategy::AttackNpcStrategy() {}

AttackNpcStrategy::AttackNpcStrategy(Tile tiles[],int width,int height)
{
    nodifyGrid(tiles,width,height);
    AttackNpcStrategy::width = width;
    AttackNpcStrategy::height = height;
}

NpcStrategy& AttackNpcStrategy::getSingleton() { return singleton; };

char AttackNpcStrategy::execute(Character* npc, int npcLocation, Character* player, int playerLocation)
{
    Node playerNode = nodes[playerLocation / width][playerLocation % width];
    Node npcNode = nodes[npcLocation / width][npcLocation % width];
    //cout << "Npc: " << "(" << npcNode.row << "," << npcNode.col << ") ; " << "Player: " << "(" << playerNode.row << "," << playerNode.col << ") ; " << endl;

    vector<Node> path = findPath(nodes, npcNode, playerNode);
    /*
    for (Node const ele : path)
    {
        cout << "(" << ele.row << "," << ele.col << ")" << endl;
    }
    */
    Node next = npcNode;
    if (path.size() > 2)
        next = path[1];
    else if (path.size() != 0)
    {
        npc->attackEnemy(*player);
        cin.get();
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            nodes[r][c].parentCol = -1;
            nodes[r][c].parentRow = -1;
            nodes[r][c].g = INFINITY;
            nodes[r][c].h = 0;
        }
    }

    if (next.col < npcNode.col)
        return '%';
    else if (next.row < npcNode.row)
        return '&';
    else if (next.row > npcNode.row)
        return '(';
    else if (next.col > npcNode.col)
        return '\'';
    return 'n';
    
}

void AttackNpcStrategy::nodifyGrid(Tile tiles[], int width, int height)
{
    int n = 0;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            nodes[r][c] = Node(r, c, !(tiles[n].getType() == char(' ')));
            n++;
        }
    }

}
// Function to find the path using A*
vector<AttackNpcStrategy::Node> AttackNpcStrategy::findPath(Node grid[][96], Node& start, Node& goal) {
    priority_queue<Node, vector<Node>, CompareNodes> openSet;
    bool closedSet[32][96];
    memset(closedSet, false, sizeof(closedSet));
    start.g = 0;
    start.h = start.heuristic(goal);
    openSet.push(start);

    start.g = 0;
    start.h = start.heuristic(goal);
    openSet.push(start);

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        //cout << "Npc: " << "(" << current.row << "," << current.col << ") ; " << "Parent: " << "(" << current.parentRow << "," << current.parentCol << ") ; " << endl;

        if (current.row == goal.row && current.col == goal.col) {
            // Reconstruct path
            std::vector<Node> path;
            while (current.parentRow != -1 && current.parentCol != -1) { // Check if the node has valid parents
                //cout << "Npc: " << "(" << current.row << "," << current.col << ") ; " << "Parent: " << "(" << current.parentRow << "," << current.parentCol << ") ; " << endl;
                path.push_back(current);
                current = grid[current.parentRow][current.parentCol];
            }
            path.push_back(start); // Add the start node
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet[current.row][current.col] = true;

        // Generate neighbors
        static const int dr[] = { 1, -1, 0, 0 };
        static const int dc[] = { 0, 0, 1, -1 };
        for (int i = 0; i < 4; ++i) {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];
            if (newRow >= 0 && newRow < 32 &&
                newCol >= 0 && newCol < 96 &&
                !grid[newRow][newCol].obstacle && !closedSet[newRow][newCol]) {
                double tentativeG = current.g + 1; // Assuming each step has a cost of 1
                if (tentativeG < grid[newRow][newCol].g) {
                    grid[newRow][newCol].parentRow = current.row;
                    grid[newRow][newCol].parentCol = current.col;
                    grid[newRow][newCol].g = tentativeG;
                    grid[newRow][newCol].h = grid[newRow][newCol].heuristic(goal);
                    openSet.push(grid[newRow][newCol]);
                }
            }
        }
    }

    // No path found
    return {};
}
