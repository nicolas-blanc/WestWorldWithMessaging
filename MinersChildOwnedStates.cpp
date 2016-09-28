#include "MinersChildOwnedStates.h"
#include "fsm/State.h"
#include "MinersChild.h"
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


// ------------------------------------------------------------------------ //
// Methods for ChildGlobalState
ChildGlobalState * ChildGlobalState::Instance()
{
	static ChildGlobalState instance;

	return &instance;
}

bool ChildGlobalState::OnMessage(MinersChild * minerChild, const Telegram & msg)
{
	switch (msg.Msg)
	{
	case Msg_DadWork:
	{
//		cout << "\nMessage handled by " << GetNameOfEntity(minerChild->ID()) << " at time: "
//			<< Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(minerChild->ID());

		// 		cout << "\n" << GetNameOfEntity(minerChild->ID()) <<
		// 			": My dad work in the mine";
		DisplayMessageThread::display(": My dad work in the mine", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->IncreaseWantMakeLikeDad();
	}

	return true;

	}//end switch
	return false;
}


// ------------------------------------------------------------------------ //
// Methods for GoHome
GoHome * GoHome::Instance()
{
	static GoHome instance;

	return &instance;
}

void GoHome::Enter(MinersChild * pminerChild)
{
	if (pminerChild->Location() != shack)
	{
// 		cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": " << "I'm going to home";
		DisplayMessageThread::display("I'm going to home", pminerChild->ID(), FOREGROUND_BLUE);

		pminerChild->ChangeLocation(shack);
	}

	//let mam' know I'm home
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pminerChild->ID(),        //ID of sender
		ent_Elsa,            //ID of recipient
		Msg_HiMamImHome,   //the message
		NO_ADDITIONAL_INFO);

}

void GoHome::Execute(MinersChild * pminerChild)
{

	if (pminerChild->StoneCarried())
	{
// 		cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": "
// 			<< "I drop all my stone in the garden";
		DisplayMessageThread::display("I drop all my stone in the garden", pminerChild->ID(), FOREGROUND_BLUE);

		pminerChild->SetStoneCarried(0);
	}

	if (pminerChild->Fatigued())
	{
		pminerChild->GetFSM()->ChangeState(AtHomeSleep::Instance());
	}
	else if (pminerChild->Thirsty())
	{
// 		cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": "
// 			<< "Mam, I want water !";
		DisplayMessageThread::display("Mam, I want water !", pminerChild->ID(), FOREGROUND_BLUE);

		pminerChild->GetFSM()->ChangeState(AtHomeDrink::Instance());
	}
	else
	{
// 		cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": "
// 			<< "I want to go out";
		DisplayMessageThread::display("I want to go out", pminerChild->ID(), FOREGROUND_BLUE);

		if (pminerChild->WhatWantTheChild())
		{
// 			cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": "
// 				<< "I want to make like Dad, i'll meet them";
			DisplayMessageThread::display("I want to make like Dad, i'll meet them", pminerChild->ID(), FOREGROUND_BLUE);

			pminerChild->GetFSM()->ChangeState(MakeLikeDad::Instance());
		}
		else
		{
// 			cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": "
// 				<< "i'll go to play with my friends !";
			DisplayMessageThread::display("i'll go to play with my friends !", pminerChild->ID(), FOREGROUND_BLUE);

			pminerChild->GetFSM()->ChangeState(PlayWithFriend::Instance());
		}
	}
}

void GoHome::Exit(MinersChild * pminerChild)
{
}

bool GoHome::OnMessage(MinersChild * pminerChild, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_LittleStewReady:

// 		cout << "\nMessage handled by " << GetNameOfEntity(pminerChild->ID())
// 			<< " at time: " << Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(pminerChild->ID());

// 		cout << "\n" << GetNameOfEntity(pminerChild->ID())
// 			<< ": Okay Hun, ahm a comin'!";
		DisplayMessageThread::display(": Okay Hun, ahm a comin'!", pminerChild->ID(), FOREGROUND_BLUE);

		pminerChild->GetFSM()->ChangeState(AtHomeEatStew::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------ // 
// Methods for AtHomeSleep

AtHomeSleep * AtHomeSleep::Instance()
{
	static AtHomeSleep instance;

	return &instance;
}

void AtHomeSleep::Enter(MinersChild * pminerChild)
{
// 	cout << "\n" << GetNameOfEntity(pminerChild->ID()) << ": "
// 		<< "I'm tired, go to bed, ZZZZ...";
	DisplayMessageThread::display("I'm tired, go to bed, ZZZZ...", pminerChild->ID(), FOREGROUND_BLUE);

}

void AtHomeSleep::Execute(MinersChild * minerChild)
{
	minerChild->DecreaseFatigue();

	if (minerChild->NotFatigued())
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 			<< "ZZZZ... ";
		DisplayMessageThread::display("ZZZZ... ", minerChild->ID(), FOREGROUND_BLUE);
	}
	else
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 			<< "I want to go out";
		DisplayMessageThread::display("I want to go out", minerChild->ID(), FOREGROUND_BLUE);

		if (minerChild->WhatWantTheChild())
		{
// 			cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 				<< "I want to make like Dad, i'll meet them";
			DisplayMessageThread::display("I want to make like Dad, i'll meet them", minerChild->ID(), FOREGROUND_BLUE);

			minerChild->GetFSM()->ChangeState(MakeLikeDad::Instance());
		}
		else
		{
// 			cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 				<< "i'll go to play with my friends !";
			DisplayMessageThread::display("i'll go to play with my friends !", minerChild->ID(), FOREGROUND_BLUE);

			minerChild->GetFSM()->ChangeState(PlayWithFriend::Instance());
		}
	}
}

void AtHomeSleep::Exit(MinersChild * minerChild)
{
}

bool AtHomeSleep::OnMessage(MinersChild * minerChild, const Telegram & msg)
{
	switch (msg.Msg)
	{
	case Msg_LittleStewReady:

// 		cout << "\nMessage handled by " << GetNameOfEntity(minerChild->ID())
// 			<< " at time: " << Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(minerChild->ID());

// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": Okay Hun, ahm a comin'!";
		DisplayMessageThread::display(": Okay Hun, ahm a comin'!", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->GetFSM()->ChangeState(AtHomeEatStew::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------ // 
// Methods for AtHomeEatStew

AtHomeEatStew * AtHomeEatStew::Instance()
{
	static AtHomeEatStew instance;

	return &instance;
}

void AtHomeEatStew::Enter(MinersChild * minerChild)
{
// 	cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": " << "Smells Reaaal goood Mam!";
	DisplayMessageThread::display("Smells Reaaal goood Mam!", minerChild->ID(), FOREGROUND_BLUE);
}

void AtHomeEatStew::Execute(MinersChild * minerChild)
{
// 	cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": " << "Tastes real good too!";
	DisplayMessageThread::display("Tastes real good too!", minerChild->ID(), FOREGROUND_BLUE);

	minerChild->GetFSM()->RevertToPreviousState();
}

void AtHomeEatStew::Exit(MinersChild * minerChild)
{
// 	cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": " << "Thankya Mam.";
	DisplayMessageThread::display("Thankya Mam.", minerChild->ID(), FOREGROUND_BLUE);
}

bool AtHomeEatStew::OnMessage(MinersChild * minerChild, const Telegram & msg)
{
	return false; //send message to global message handler
}

//------------------------------------------------------------------------ // 
// Methods for AtHomeDrink

AtHomeDrink * AtHomeDrink::Instance()
{
	static AtHomeDrink instance;

	return &instance;
}

void AtHomeDrink::Enter(MinersChild * minerChild)
{
// 	cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 		<< "I'm thirsty, time to drink, GlouGlou...";
	DisplayMessageThread::display("I'm thirsty, time to drink, GlouGlou...", minerChild->ID(), FOREGROUND_BLUE);
}

void AtHomeDrink::Execute(MinersChild * minerChild)
{
	minerChild->DecreaseThirsty();

	if (minerChild->NotThirsty())
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 			<< "GlouGlou...";
		DisplayMessageThread::display("GlouGlou...", minerChild->ID(), FOREGROUND_BLUE);
	}
	else
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 			<< "I want to go out";
		DisplayMessageThread::display("I want to go out", minerChild->ID(), FOREGROUND_BLUE);

		if (minerChild->WhatWantTheChild())
		{
// 			cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 				<< "I want to make like Dad, i'll meet them";
			DisplayMessageThread::display("I want to make like Dad, i'll meet them", minerChild->ID(), FOREGROUND_BLUE);

			minerChild->GetFSM()->ChangeState(MakeLikeDad::Instance());
		}
		else
		{
// 			cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": "
// 				<< "i'll go to play with my friends !";
			DisplayMessageThread::display("I'll go to play with my friends !", minerChild->ID(), FOREGROUND_BLUE);

			minerChild->GetFSM()->ChangeState(PlayWithFriend::Instance());
		}
	}
}

void AtHomeDrink::Exit(MinersChild * minerChild)
{
}

bool AtHomeDrink::OnMessage(MinersChild * minerChild, const Telegram & msg)
{
	switch (msg.Msg)
	{
	case Msg_LittleStewReady:

// 		cout << "\nMessage handled by " << GetNameOfEntity(minerChild->ID())
// 			<< " at time: " << Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(minerChild->ID());

// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": " << "Okay Hun, ahm a comin'!";
		DisplayMessageThread::display("Okay Hun, ahm a comin'!", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->GetFSM()->ChangeState(AtHomeEatStew::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------ // 
// Methods for PlayWithFriend

PlayWithFriend * PlayWithFriend::Instance()
{
	static PlayWithFriend instance;

	return &instance;
}

void PlayWithFriend::Enter(MinersChild * minerChild)
{
// 	cout << "\n" << GetNameOfEntity(minerChild->ID())
// 		<< ": " << "Wait to me friends, I'll come!";
	DisplayMessageThread::display("Wait to me friends, I'll come!", minerChild->ID(), FOREGROUND_BLUE);

	minerChild->ChangeLocation(playZone);
}

void PlayWithFriend::Execute(MinersChild * minerChild)
{
	minerChild->IncreaseThirsty();
	minerChild->IncreaseFatigue();
	minerChild->DecreaseWantPlay();

	if (minerChild->Thirsty()) {
// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": I'm Thirsty, I'll go to home!";
		DisplayMessageThread::display("I'm Thirsty, I'll go to home!", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->GetFSM()->ChangeState(GoHome::Instance());
	}
	else
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": I play with my friends in the play zone!";
		DisplayMessageThread::display("I play with my friends in the play zone!", minerChild->ID(), FOREGROUND_BLUE);
	}
}

void PlayWithFriend::Exit(MinersChild * minerChild)
{
}

bool PlayWithFriend::OnMessage(MinersChild * agent, const Telegram & msg)
{
	return false;
}

//------------------------------------------------------------------------ // 
// Methods for MakeLikeDad

MakeLikeDad * MakeLikeDad::Instance()
{
	static MakeLikeDad instance;

	return &instance;
}

void MakeLikeDad::Enter(MinersChild * minerChild)
{
	if (minerChild->Location() != goldmine)
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID()) << ": " << "Walkin' to the goldmine";
		DisplayMessageThread::display("Walkin' to the goldmine", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->ChangeLocation(goldmine);
	}
}

void MakeLikeDad::Execute(MinersChild * minerChild)
{
	minerChild->AddToStoneCarried(1);

// 	cout << "\n" << GetNameOfEntity(minerChild->ID())
// 		<< ": Pickin' up a little stone";
	DisplayMessageThread::display("Pickin' up a little stone", minerChild->ID(), FOREGROUND_BLUE);

	minerChild->IncreaseThirsty();
	minerChild->IncreaseFatigue();
	minerChild->IncreaseWantPlay();
	minerChild->DecreaseWantMakeLikeDad();

	if (minerChild->PocketsFull())
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": I'm full of stone, I'll go to home!";
		DisplayMessageThread::display("I'm full of stone, I'll go to home!", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->GetFSM()->ChangeState(GoHome::Instance());
	}
	else if (minerChild->Thirsty() || minerChild->Fatigued())
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": I'm finishing here, I'll go to home!";
		DisplayMessageThread::display("I'm finishing here, I'll go to home!", minerChild->ID(), FOREGROUND_BLUE);

		minerChild->GetFSM()->ChangeState(GoHome::Instance());
	}
	else
	{
// 		cout << "\n" << GetNameOfEntity(minerChild->ID())
// 			<< ": I make like Dad, I search for stone!";
		DisplayMessageThread::display("I make like Dad, I search for stone!", minerChild->ID(), FOREGROUND_BLUE);
	}
}

void MakeLikeDad::Exit(MinersChild * minerChild)
{
}

bool MakeLikeDad::OnMessage(MinersChild * agent, const Telegram & msg)
{
	return false;
}
