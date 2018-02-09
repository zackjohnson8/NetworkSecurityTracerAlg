#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <time.h>

const int NUM_OF_ROUTERS = 20;
const int MAX_HOP_COUNT = 15;
const int BRANCH_LOW_RANGE = 3;
const int BRANCH_HIGH_RANGE = 5;
const float PROBABILITY_OF_ROUTER_MARKING = .2;

struct RouterNode{

  int IP;
  std::vector<RouterNode*> NeighborNodes;

};

// FUNCTION DECLARATION
void builtRouterNetwork(std::vector<RouterNode*>* routerNodeList);

void printTree(std::vector<RouterNode*>* routerNodeList);

RouterNode* chooseAttacker(std::vector<RouterNode*>* routerNodeList);

std::vector<RouterNode*>* findPathToVictim(std::vector<RouterNode*>* routerNodeList, RouterNode* attackerNode);

int main()
{

  srand(time(NULL));
  int NodeCount = 0;

  // Create a topology using a file and nodes to connect
  // Use a file to build the topology
  std::vector<RouterNode*> routerNodeList;
  builtRouterNetwork(&routerNodeList);

  //printTree(&routerNodeList);

  std::vector<RouterNode*>* pathToVictimNode;

  pathToVictimNode = findPathToVictim(&routerNodeList, chooseAttacker(&routerNodeList));

  std::cout << "Path to victim is..." << std::endl;
  for(int index = 0; index < pathToVictimNode->size(); index++)
  {

    std::cout << pathToVictimNode->at(index)->IP << std::endl;

  }

  return(0);
}

std::vector<RouterNode*>* findPathToVictim(
  std::vector<RouterNode*>* routerNodeList,
  RouterNode* attackerNode
  )
{

  std::cout << "AttackNode = " << attackerNode->IP << std::endl;

  std::vector<RouterNode*>* pathToVictim = new std::vector<RouterNode*>();
  pathToVictim->push_back(attackerNode);

  RouterNode* victimNode = routerNodeList->at(0); // should be the top router

  bool foundPath = false;
  int count = 0;
  while(!foundPath)
  {

    pathToVictim->push_back(pathToVictim->at(pathToVictim->size()-1)->NeighborNodes.at(0));



    if(pathToVictim->at(pathToVictim->size()-1)->IP == victimNode->IP)
    {

      foundPath = !foundPath;

    }


  }

  return pathToVictim;

}

RouterNode* chooseAttacker(std::vector<RouterNode*>* routerNodeList)
{

  std::vector<RouterNode*> holdPossibleAttackers;

  for(int index = 0; index < routerNodeList->size(); index++)
  {
    // only has a parent node
    if(routerNodeList->at(index)->NeighborNodes.size() == 1)
    {

      holdPossibleAttackers.push_back(routerNodeList->at(index));

    }

  }

  return holdPossibleAttackers.at( rand() % holdPossibleAttackers.size() );

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
