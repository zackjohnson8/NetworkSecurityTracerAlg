#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

const int NUM_OF_ROUTERS = 20;
const int MAX_HOP_COUNT = 15;
const int BRANCH_LOW_RANGE = 3;
const int BRANCH_HIGH_RANGE = 5;

struct RouterNode{

  int IP;
  std::vector<RouterNode*> NeighborNodes;

};

int main()
{

  int NodeCount = 0;

  // Create a topology using a file and nodes to connect
  // Use a file to build the topology
  std::vector<RouterNode*> routerNodeList;

  RouterNode* holdNode;
  for(int index = 1; index <= NUM_OF_ROUTERS; index++)
  {

    holdNode = new RouterNode;
    holdNode->IP = index;

    routerNodeList.push_back(holdNode);

  }

  std::ifstream topologyFile;
  topologyFile.open("graphtopology.txt");
  std::string holdString;
  char holdChar;
  int currentNode;
  int neighborNode;
  char pauseChar;

  while(topologyFile.good())
  {

    getline(topologyFile, holdString, ' ');
    topologyFile >> currentNode;
    topologyFile >> holdChar;

    holdNode = routerNodeList.at(currentNode-1);

    while(holdChar != ';')
    {
      getline(topologyFile, holdString, ' ');
      topologyFile >> neighborNode;
      topologyFile >> holdChar;
      holdNode->NeighborNodes.push_back(routerNodeList[neighborNode-1]);
    }

  }

  topologyFile.close();

  return(0);
}
