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
#include "DisplayMessageThread.h"
using namespace std;

DrinkABeer* DrinkABeer::Instance() {
	static DrinkABeer instance;

	return &instance;
}

void DrinkABeer::Enter(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Ughhh Hey Boy! Thanks for the Beer !!";
	DisplayMessageThread::display("Ughhh Hey Boy! Thanks for the Beer !!", drunk->ID(), FOREGROUND_GREEN);
}

void DrinkABeer::Execute(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": This beer taste really good !";
	DisplayMessageThread::display("This beer taste really good !", drunk->ID(), FOREGROUND_GREEN);

	drunk->IncreaseHungry();
	drunk->IncreaseFatigue();
	drunk->DecreaseBeer();
	drunk->IncreaseAngry();

	if (drunk->isBeerEmpty()) {
		if (drunk->isFatigue())
			drunk->GetFSM()->ChangeState(SleepAtSaloon::Instance());

		else if (drunk->isHungry())
			drunk->GetFSM()->ChangeState(OrderPretzel::Instance());

		else
			drunk->GetFSM()->ChangeState(OrderBeer::Instance());
	}
}

void DrinkABeer::Exit(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Oh My beer is empty Now !";
	DisplayMessageThread::display("Oh My beer is empty Now !", drunk->ID(), FOREGROUND_GREEN);
}
bool DrinkABeer::OnMessage(Drunk* drunk, const Telegram& msg) {
	return false;
}

OrderBeer* OrderBeer::Instance() {
	static OrderBeer instance;

	return &instance;
}

void OrderBeer::Enter(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Hey Guy, Gimme a beer !!";
	DisplayMessageThread::display("Hey Guy, Gimme a beer !!", drunk->ID(), FOREGROUND_GREEN);

	Dispatch->DispatchMessageA(1.0, drunk->ID(), drunk->ID(), Msg_BeerReady, NO_ADDITIONAL_INFO);
}

void OrderBeer::Execute(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": I'm waiting, Faster boy!";
	DisplayMessageThread::display("I'm waiting, Faster boy!", drunk->ID(), FOREGROUND_GREEN);
}

void OrderBeer::Exit(Drunk* drunk) {
	//cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally I got my beer !!";
}

bool OrderBeer::OnMessage(Drunk* drunk, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_BeerReady:
		DisplayMessageThread::displayMessage(drunk->ID());

// 		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally i got my beer ! Let's drink!!!";
		DisplayMessageThread::display("Finally i got my beer ! Let's drink!!!", drunk->ID(), FOREGROUND_GREEN);

		drunk->refillBeer();
		drunk->GetFSM()->ChangeState(DrinkABeer::Instance());
		break;

	
	}
	return true;
}

OrderPretzel* OrderPretzel::Instance() {
	static OrderPretzel instance;

	return &instance;
}

void OrderPretzel::Enter(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Hey Guy, Gimme some pretzels !!";
	DisplayMessageThread::display("Hey Guy, Gimme some pretzels !!", drunk->ID(), FOREGROUND_GREEN);

	Dispatch->DispatchMessageA(1.0, drunk->ID(), drunk->ID(), Msg_PretzelReady, NO_ADDITIONAL_INFO);
}

void OrderPretzel::Execute(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": I'm waiting for my pretzels, Faster boy!";
	DisplayMessageThread::display("I'm waiting for my pretzels, Faster boy!", drunk->ID(), FOREGROUND_GREEN);
}

void OrderPretzel::Exit(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally I got my pretzels !!";
}

bool OrderPretzel::OnMessage(Drunk* drunk, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_PretzelReady:
		DisplayMessageThread::displayMessage(drunk->ID());

// 		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Finally i got my Pretzels ! Let's eats!!!";
		DisplayMessageThread::display("Finally i got my Pretzels ! Let's eats!!!", drunk->ID(), FOREGROUND_GREEN);

		drunk->GetFSM()->ChangeState(EatSomePretzel::Instance());
		break;

	
	}
	return true;
}

DrunkFight* DrunkFight::Instance() {
	static DrunkFight instance;

	return &instance;
}

void DrunkFight::Enter(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Hey you ! Stop looking me like that ! You wanna  fight? !!";
	DisplayMessageThread::display("Hey you ! Stop looking me like that ! You wanna  fight? !!", drunk->ID(), FOREGROUND_GREEN);

	Dispatch->DispatchMessageA(0, drunk->ID(), ent_Miner_Bob, Msg_DrunkStartFight, NO_ADDITIONAL_INFO);
}

void DrunkFight::Execute(Drunk* drunk) {
	if (drunk->isAngry()) {
		drunk->DecreaseAngry();

// 		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": IM NOT GONNA GIVE YOU MY BEERS! GO AWAY!";
		DisplayMessageThread::display("IM NOT GONNA GIVE YOU MY BEERS! GO AWAY!", drunk->ID(), FOREGROUND_GREEN);
	}
	else
	{
		drunk->GetFSM()->RevertToPreviousState();
	}
}

void DrunkFight::Exit(Drunk* drunk) {
	Dispatch->DispatchMessageA(0, drunk->ID(), ent_Miner_Bob, Msg_DrunkStopFight, NO_ADDITIONAL_INFO);

// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": I hope I'll never see this guy again!!";
	DisplayMessageThread::display("I hope I'll never see this guy again!!", drunk->ID(), FOREGROUND_GREEN);
}

bool DrunkFight::OnMessage(Drunk* drunk, const Telegram& msg) {
	return false;
}

EatSomePretzel* EatSomePretzel::Instance() {
	static EatSomePretzel instance;

	return &instance;
}

void EatSomePretzel::Enter(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ":  Hey Gimme Pretzels !! ";
	DisplayMessageThread::display("Hey Gimme Pretzels !!", drunk->ID(), FOREGROUND_GREEN);
}

void EatSomePretzel::Execute(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Woow such good Pretzels !! ";
	DisplayMessageThread::display("Woow such good Pretzels !!", drunk->ID(), FOREGROUND_GREEN);

	drunk->GetFSM()->ChangeState(OrderBeer::Instance());
}

void EatSomePretzel::Exit(Drunk* drunk) {
}

bool EatSomePretzel::OnMessage(Drunk* drunk, const Telegram& msg) {
	
	return false;
}

SleepAtSaloon* SleepAtSaloon::Instance() {
	static SleepAtSaloon instance;

	return &instance;
}

void SleepAtSaloon::Enter(Drunk* drunk) {
// 	cout << "\n" << GetNameOfEntity(drunk->ID()) << ": humm .... I should...get..anoth..beer...Zzzzz !!";
	DisplayMessageThread::display("humm .... I should...get..anoth..beer...Zzzzz !!", drunk->ID(), FOREGROUND_GREEN);
}

void SleepAtSaloon::Execute(Drunk* drunk) {
	if (!drunk->isReadyToWakeUp()) {
// 		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": ZZzzzzzZ .... Zzzzzz......Zzzzz !!";
		DisplayMessageThread::display("ZZzzzzzZ .... Zzzzzz......Zzzzz !!", drunk->ID(), FOREGROUND_GREEN);

		drunk->DecreaseFatigue();
	}
	else
	{
// 		cout << "\n" << GetNameOfEntity(drunk->ID()) << ": Ohh i fall alseep, well lets take another beer !!!";
		DisplayMessageThread::display("Ohh i fall alseep, well lets take another beer !!!", drunk->ID(), FOREGROUND_GREEN);

		drunk->GetFSM()->ChangeState(OrderBeer::Instance());	}
}

void SleepAtSaloon::Exit(Drunk* drunk) {
}

bool SleepAtSaloon::OnMessage(Drunk* drunk, const Telegram& msg) {
	return false;
}

DrunkGlobalState* DrunkGlobalState::Instance() {
	static DrunkGlobalState instance;

	return &instance;
}

void DrunkGlobalState::Enter(Drunk* drunk) {
}

void DrunkGlobalState::Execute(Drunk* drunk) {

}

void DrunkGlobalState::Exit(Drunk* drunk) {
}

bool DrunkGlobalState::OnMessage(Drunk* drunk, const Telegram& msg) {
	switch (msg.Msg) {
	case Msg_MinerAtSaloon:
		DisplayMessageThread::displayMessage(drunk->ID());

		drunk->GetFSM()->ChangeState(DrunkFight::Instance());
		break;
	};
	return true;
}

