#include "MinerOwnedStates.h"
#include "fsm/State.h"
#include "Miner.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"
#include "DisplayMessageThread.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
	static EnterMineAndDigForNugget instance;

	return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
	//if the miner is not already located at the goldmine, he must
	//change location to the gold mine
	if (pMiner->Location() != goldmine)
	{
		/*    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "<< "Walkin' to the goldmine";*/
		DisplayMessageThread::display("Walkin' to the goldmine", pMiner->ID(), FOREGROUND_RED);

		pMiner->ChangeLocation(goldmine);
	}
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
	//Now the miner is at the goldmine he digs for gold until he
	//is carrying in excess of MaxNuggets. If he gets thirsty during
	//his digging he packs up work for a while and changes state to
	//gp to the saloon for a whiskey.
	pMiner->AddToGoldCarried(1);

	//let the child know I work
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pMiner->ID(),        //ID of sender
		ent_Child,            //ID of recipient
		Msg_DadWork,   //the message
		NO_ADDITIONAL_INFO);

	pMiner->IncreaseFatigue();

	//   cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pickin' up a nugget";
	DisplayMessageThread::display("Pickin' up a nugget", pMiner->ID(), FOREGROUND_RED);

	//if enough gold mined, go and put it in the bank
	if (pMiner->PocketsFull())
	{
		pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}

	if (pMiner->Thirsty())
	{
		pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
	}
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
	//   cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
	//        << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";

	DisplayMessageThread::display("Ah'm leavin' the goldmine with mah pockets full o' sweet gold", pMiner->ID(), FOREGROUND_RED);
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;

	return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
	//on entry the miner makes sure he is located at the bank
	if (pMiner->Location() != bank)
	{
// 		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Goin' to the bank. Yes siree";
		DisplayMessageThread::display("Goin' to the bank. Yes siree", pMiner->ID(), FOREGROUND_RED);

		pMiner->ChangeLocation(bank);
	}
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
	//deposit the gold
	pMiner->AddToWealth(pMiner->GoldCarried());

	pMiner->SetGoldCarried(0);

// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
// 		<< "Depositing gold. Total savings now: " << pMiner->Wealth();

	DisplayMessageThread::display("Depositing gold. Total savings now: " + pMiner->Wealth(), pMiner->ID(), FOREGROUND_RED);

	//wealthy enough to have a well earned rest?
	if (pMiner->Wealth() >= ComfortLevel)
	{
// 		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
// 			<< "WooHoo! Rich enough for now. Back home to mah li'lle lady";
		DisplayMessageThread::display("WooHoo! Rich enough for now. Back home to mah li'lle lady", pMiner->ID(), FOREGROUND_RED);

		pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
	}

	//otherwise get more gold
	else
	{
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
	DisplayMessageThread::display("Leavin' the bank", pMiner->ID(), FOREGROUND_RED);
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
	if (pMiner->Location() != shack)
	{
// 		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' home";
		DisplayMessageThread::display("Walkin' home", pMiner->ID(), FOREGROUND_RED);

		pMiner->ChangeLocation(shack);

		//let the wife know I'm home
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pMiner->ID(),        //ID of sender
			ent_Elsa,            //ID of recipient
			Msg_HiHoneyImHome,   //the message
			NO_ADDITIONAL_INFO);
	}
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
	//if miner is not fatigued start to dig for nuggets again.
	if (!pMiner->Fatigued())
	{
// 		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
// 			<< "All mah fatigue has drained away. Time to find more gold!";
		DisplayMessageThread::display("All mah fatigue has drained away. Time to find more gold!", pMiner->ID(), FOREGROUND_RED);

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}

	else
	{
		//sleep
		pMiner->DecreaseFatigue();

// 		cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ... ";
		DisplayMessageThread::display("ZZZZ... ", pMiner->ID(), FOREGROUND_RED);
	}
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_StewReady:

// 		cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID())
// 			<< " at time: " << Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(pMiner->ID());

// 		cout << "\n" << GetNameOfEntity(pMiner->ID())
// 			<< ": Okay Hun, ahm a comin'!";
		DisplayMessageThread::display("Okay Hun, ahm a comin'!", pMiner->ID(), FOREGROUND_RED);

		pMiner->GetFSM()->ChangeState(EatStew::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;

	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon);
	Dispatch->DispatchMessageA(0, pMiner->ID(), ent_Drunk, Msg_MinerAtSaloon, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessageA(1, pMiner->ID(), pMiner->ID(), Msg_MinerAtSaloon, NO_ADDITIONAL_INFO);

*// cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
	DisplayMessageThread::display("Boy, ah sure is thusty! Walking to the saloon", pMiner->ID(), FOREGROUND_RED);
  }
}

void QuenchThirst::Execute(Miner* pMiner)
{
	pMiner->BuyAndDrinkAWhiskey();

// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "That's mighty fine sippin' liquer";
	DisplayMessageThread::display("That's mighty fine sippin' liquer", pMiner->ID(), FOREGROUND_RED);


}


void QuenchThirst::Exit(Miner* pMiner)
{
// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the saloon, feelin' good";
	DisplayMessageThread::display("Leaving the saloon, feelin' good", pMiner->ID(), FOREGROUND_RED);
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
	switch (msg.Msg){
	case Msg_DrunkStartFight:
		pMiner->GetFSM()->ChangeState(Fight::Instance());
		break;
	case Msg_MinerAtSaloon:
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
		break;
	}
	return true;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
	static EatStew instance;

	return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Smells Reaaal goood Elsa!";
	DisplayMessageThread::display("Smells Reaaal goood Elsa!", pMiner->ID(), FOREGROUND_RED);
}

void EatStew::Execute(Miner* pMiner)
{
// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Tastes real good too!";
	DisplayMessageThread::display("Tastes real good too!", pMiner->ID(), FOREGROUND_RED);

	pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{
// 	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
	DisplayMessageThread::display("Thankya li'lle lady. Ah better get back to whatever ah wuz doin'", pMiner->ID(), FOREGROUND_RED);
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


Fight* Fight::Instance()
{
	static Fight instance;

	return &instance;
}


void Fight::Enter(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Woahh what'you want men ? I'm just there to take som whiskey!";
}

void Fight::Execute(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pleas Calm'down!";


}

void Fight::Exit(Miner* pMiner)
{
	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Wow this guys is crazy. lets go back to what I was doin'";
}


bool Fight::OnMessage(Miner* pMiner, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_DrunkStopFight:
		pMiner->GetFSM()->RevertToPreviousState();
		break;
	}
	return true;
}
