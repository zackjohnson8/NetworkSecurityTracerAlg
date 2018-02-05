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

void builtRouterNetwork(std::vector<RouterNode*>* routerNodeList);
void printTree(std::vector<RouterNode*>* routerNodeList);

int main()
{

  int NodeCount = 0;

  // Create a topology using a file and nodes to connect
  // Use a file to build the topology
  std::vector<RouterNode*> routerNodeList;
  builtRouterNetwork(&routerNodeList);

  printTree(&routerNodeList);

  return(0);
}

void builtRouterNetwork(std::vector<RouterNode*>* routerNodeList)
{

  RouterNode* holdNode;
  for(int index = 1; index <= NUM_OF_ROUTERS; index++)
  {

    holdNode = new RouterNode;
    holdNode->IP = index;

    routerNodeList->push_back(holdNode);

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

    holdNode = routerNodeList->at(currentNode-1);

    while(holdChar != ';')
    {
      getline(topologyFile, holdString, ' ');
      topologyFile >> neighborNode;
      topologyFile >> holdChar;
      holdNode->NeighborNodes.push_back(routerNodeList->at(neighborNode-1));
    }

  }

  topologyFile.close();

}

void printTree(std::vector<RouterNode*>* routerNodeList)
{

  for(int index = 0; index < NUM_OF_ROUTERS; index++)
  {

    std::cout << "Router " << routerNodeList->at(index)->IP << " has neighbors: ";

    for(int indexNeighbor = 0; indexNeighbor < routerNodeList->at(index)->NeighborNodes.size(); indexNeighbor++)
    {

      std::cout << routerNodeList->at(index)->NeighborNodes.at(indexNeighbor)->IP << ", ";

    }

    std::cout << std::endl;

  }



}
