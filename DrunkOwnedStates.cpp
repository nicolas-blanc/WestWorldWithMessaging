
#include "DrunkOwnedStates.h"
#include "fsm/State.h"
#include "Drunk.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"
#include <iostream>
using namespace std;

DrinkABeer* DrinkABeer::Instance(){
	static DrinkABeer instance;
	return &instance;
}
void DrinkABeer::Enter(Drunk* drunk){
	
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Ughhh Hey Boy! Thanks for the Beer !!";
}
void DrinkABeer::Execute(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": This beer taste really good !";
	drunk->IncreaseHungry();
	drunk->IncreaseFatigue();
	drunk->DecreaseBeer();
	drunk->IncreaseAngry();
	if (drunk->isBeerEmpty()){
		if (drunk->isFatigue())
			drunk->GetFSM()->ChangeState(SleepAtSaloon::Instance());
		else if (drunk->isHungry())
			drunk->GetFSM()->ChangeState(OrderPretzel::Instance());
		else
			drunk->GetFSM()->ChangeState(OrderBeer::Instance());

	}
	
}
void DrinkABeer::Exit(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Oh My beer is empty Now !";
}
bool DrinkABeer::OnMessage(Drunk* drunk, const Telegram& msg){
	switch (msg.Msg){
	case Msg_MinerAtSaloon:
		drunk->GetFSM()->ChangeState(DrunkFight::Instance());
		break;
	};
	return true;
}



OrderBeer* OrderBeer::Instance(){
	static OrderBeer instance;
	return &instance;
}
void OrderBeer::Enter(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Hey Guy, Gimme a beer !!";
	Dispatch->DispatchMessageA(1.0, drunk->ID(), drunk->ID(), Msg_BeerReady, NO_ADDITIONAL_INFO);
}
void OrderBeer::Execute(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": I'm waiting, Faster boy!";
}
void OrderBeer::Exit(Drunk* drunk){
	//cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally I got my beer !!";
}
bool OrderBeer::OnMessage(Drunk* drunk, const Telegram& msg){
	switch (msg.Msg){
	case Msg_BeerReady:
		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally i got my beer ! Let's drink!!!";
		drunk->refillBeer();
		drunk->GetFSM()->ChangeState(DrinkABeer::Instance());
		break;
	
	case Msg_MinerAtSaloon:
		drunk->GetFSM()->ChangeState(DrunkFight::Instance());
		break;
	}
	return true;
}


OrderPretzel* OrderPretzel::Instance(){
	static OrderPretzel instance;
	return &instance;
}
void OrderPretzel::Enter(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Hey Guy, Gimme some pretzels !!";
	Dispatch->DispatchMessageA(1.0, drunk->ID(), drunk->ID(), Msg_PretzelReady, NO_ADDITIONAL_INFO);
}
void OrderPretzel::Execute(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": I'm waiting for my pretzels, Faster boy!";
}
void OrderPretzel::Exit(Drunk* drunk){
	//cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally I got my pretzels !!";
}
bool OrderPretzel::OnMessage(Drunk* drunk, const Telegram& msg){
	switch (msg.Msg){
	case Msg_PretzelReady:
		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally i got my Pretzels ! Let's eats!!!";
		drunk->GetFSM()->ChangeState(EatSomePretzel::Instance());
		break;
	case Msg_MinerAtSaloon:
		drunk->GetFSM()->ChangeState(DrunkFight::Instance());
		break;
	}
	return true;
}



DrunkFight* DrunkFight::Instance(){
	static DrunkFight instance;
	return &instance;
}
void DrunkFight::Enter(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Hey you ! Stop looking me like that ! You wanna  fight? !!";
	Dispatch->DispatchMessageA(0, drunk->ID(), ent_Miner_Bob, Msg_DrunkStartFight, NO_ADDITIONAL_INFO);
}
void DrunkFight::Execute(Drunk* drunk){
	if (drunk->isAngry()){
		drunk->DecreaseAngry();
		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": IM NOT GONNA GIVE YOU MY BEERS! GO AWAY!";
	}
	else
	{
		drunk->GetFSM()->RevertToPreviousState();
	}
}
void DrunkFight::Exit(Drunk* drunk){
	Dispatch->DispatchMessageA(0, drunk->ID(), ent_Miner_Bob, Msg_DrunkStopFight, NO_ADDITIONAL_INFO);
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": I hope I'll never see this guy again!!";
}
bool DrunkFight::OnMessage(Drunk* drunk, const Telegram& msg){
	return false;
}




EatSomePretzel* EatSomePretzel::Instance(){
	static EatSomePretzel instance;
	return &instance;
}
void EatSomePretzel::Enter(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ":  Hey Gimme Pretzels !! ";
	
}
void EatSomePretzel::Execute(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Woow such good Pretzels !! ";
	drunk->GetFSM()->ChangeState(OrderBeer::Instance());
}
void EatSomePretzel::Exit(Drunk* drunk){

}
bool EatSomePretzel::OnMessage(Drunk* drunk, const Telegram& msg){
	switch (msg.Msg){
	case Msg_MinerAtSaloon:
		drunk->GetFSM()->ChangeState(DrunkFight::Instance());
		break;
	};
	return true;
}




SleepAtSaloon* SleepAtSaloon::Instance(){
	static SleepAtSaloon instance;
	return &instance;
}
void SleepAtSaloon::Enter(Drunk* drunk){
	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": humm .... I should...get..anoth..beer...Zzzzz !!";
}
void SleepAtSaloon::Execute(Drunk* drunk){
	if (!drunk->isReadyToWakeUp()){
		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": ZZzzzzzZ .... Zzzzzz......Zzzzz !!";
		drunk->DecreaseFatigue();
	}
	else
	{
		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Ohh i fall alseep, well lets take another beer !!!";
		drunk->GetFSM()->ChangeState(OrderBeer::Instance());
		
	}
}
void SleepAtSaloon::Exit(Drunk* drunk){
	
}
bool SleepAtSaloon::OnMessage(Drunk* drunk, const Telegram& msg){
	
	return false;
}

