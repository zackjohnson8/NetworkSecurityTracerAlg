#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <time.h>

const int NUM_OF_ROUTERS = 20;
const int MAX_HOP_COUNT = 15;
const int BRANCH_LOW_RANGE = 3;
const int BRANCH_HIGH_RANGE = 5;
const int PROBABILITY_OF_ROUTER_MARKING = 20; // Just gonna treat this as 20% or .2

struct RouterNode
{

  int IP;
  std::vector<RouterNode*> NeighborNodes;

};

struct Packet
{

  RouterNode* p_markedRouter;
  int p_routerNum;

};

// FUNCTION DECLARATION
void builtRouterNetwork(std::vector<RouterNode*>* routerNodeList); //
void printTree(std::vector<RouterNode*>* routerNodeList); //
RouterNode* chooseAttacker(std::vector<RouterNode*>* routerNodeList); //
Packet* sendPacketToVictim(std::vector<RouterNode*>* pathToVictim);//

std::vector<RouterNode*>* findPathToVictim(std::vector<RouterNode*>* routerNodeList, RouterNode* attackerNode); //
bool buildPath(Packet* newPacket, RouterNode* attackerNode, std::vector<RouterNode*>* reconstructedPath); //

int main()
{

  srand(time(NULL));

  // Random attacker speed
  int attackerSpeed = rand() % 100 + 1;

  // Create a topology using a file and nodes to connect
  // Use a file to build the topology
  std::vector<RouterNode*> routerNodeList;
  builtRouterNetwork(&routerNodeList);

  // Get the path to victim from attacker
  std::vector<RouterNode*>* pathToVictimNode;
  RouterNode* attackerNode = chooseAttacker(&routerNodeList);
  pathToVictimNode = findPathToVictim(&routerNodeList, attackerNode);

  // Attack the Victim and trace back using the algs
  int count = 0;
  bool attackingUser = false;
  Packet* sentPacket;
  std::vector<RouterNode*> reconstructedPath;

  while(!attackingUser)
  {
    if(count % attackerSpeed == 0)
    {
      sentPacket = sendPacketToVictim(pathToVictimNode);
    }

    if(count % (attackerSpeed*2) == 0)
    {
      attackingUser = buildPath(sentPacket, attackerNode, reconstructedPath);
    }

    count++;

  }

  std::cout << "Count = " << count << std::endl;

  return(0);
}

bool buildPath(Packet* newPacket, RouterNode* attackerNode, std::vector<RouterNode*>* reconstructedPath)
{

  return true;

}

Packet* sendPacketToVictim(std::vector<RouterNode*>* pathToVictim)
{

  Packet* newPacket = new Packet;
  newPacket->p_routerNum = -1; // setting for easier debug
  int randomProbability;

  // Victim in the last node.
  // Attacker is the first RouterNode [0]
  // Simulate passing the packet to each router
  for(int index = 0; index < pathToVictim->size(); index++)
  {
    randomProbability = rand() % 100 + 1;

    if(randomProbability < PROBABILITY_OF_ROUTER_MARKING)
    {
      newPacket->p_markedRouter = pathToVictim->at(index);
      newPacket->p_routerNum = index;
    }
  }


}

std::vector<RouterNode*>* findPathToVictim
(
  std::vector<RouterNode*>* routerNodeList,
  RouterNode* attackerNode
)
{

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
