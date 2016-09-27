#include <fstream>
#include <time.h>
#include <thread>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "MinersChild.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

#define NUMBER_OF_UPDATE 30

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

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //Create the child
  MinersChild* Child = new MinersChild(ent_Child);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Child);

  Bob->start(NUMBER_OF_UPDATE);
  Elsa->start(NUMBER_OF_UPDATE);
  Child->start(NUMBER_OF_UPDATE);

  while (Bob->isActif() || Elsa->isActif() || Child->isActif())
  {

	  if (Bob->getStep() && Elsa->getStep() && Child->getStep())
	  {

		  Bob->setStep(FALSE);
		  Elsa->setStep(FALSE);
		  Child->setStep(FALSE);

		  //dispatch any delayed messages
	      Dispatch->DispatchDelayedMessages();
	  }

  }

  Bob->join();
  Elsa->join();
  Child->join();

  //run Bob and Elsa through a few Update calls
 // for (int i=0; i<NUMBER_OF_UPDATE; ++i)
 // { 
 //   Bob->Update();
 //   Elsa->Update();
	//Child->Update();

 //   //dispatch any delayed messages
 //   Dispatch->DispatchDelayedMessages();

 //   Sleep(800);
 // }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Child;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






