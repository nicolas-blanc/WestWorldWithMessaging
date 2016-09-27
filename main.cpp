#include <fstream>
#include <time.h>
#include <thread>

#include "Locations.h"
#include "Miner.h"
#include "Drunk.h"
#include "MinersWife.h"
#include "MinersChild.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);
  MinersWife* Elsa = new MinersWife(ent_Elsa);
 
  //create his wife

  //Create the child
  MinersChild* Child = new MinersChild(ent_Child);
  Drunk* drunk = new Drunk(ent_Drunk);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Child);
  EntityMgr->RegisterEntity(drunk);
  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
	Child->Update();
	drunk->Update();
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Child;
  delete drunk;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






