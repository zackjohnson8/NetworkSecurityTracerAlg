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
  RouterNode* NeighborNodes = NULL;

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

  }

  std::ifstream topologyFile;
  topologyFile.open("graphtopology.txt");
  std::string holdString;
  int currentNode;
  size_t foundPosition;

  while(topologyFile.good())
  {

    getline(topologyFile, holdString);

    // Find Parent Node Number
    holdString.find(':');

    // Find node in vector of nodes
    holdNode = routerNodeList[currentNode - 1];


    std::cout << holdString << std::endl;

  }

  topologyFile.close();





  return(0);
}
