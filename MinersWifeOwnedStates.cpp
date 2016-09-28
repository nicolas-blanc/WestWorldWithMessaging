#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif
#include "DisplayMessageThread.h"

//-----------------------------------------------------------------------Global state

WifesGlobalState* WifesGlobalState::Instance()
{
	static WifesGlobalState instance;

	return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife)
{
	//1 in 10 chance of needing the bathroom (provided she is not already
	//in the bathroom)
	if ((RandFloat() < 0.1) &&
		!wife->GetFSM()->isInState(*VisitBathroom::Instance()))
	{
		wife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Telegram& msg)
{

	switch (msg.Msg)
	{
	case Msg_HiHoneyImHome:
	{
// 		        cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: " 
// 		        << Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(wife->ID());

// 		cout << "\n" << GetNameOfEntity(wife->ID()) <<
// 			": Hi honey. Let me make you some of mah fine country stew";
		DisplayMessageThread::display(": Hi honey. Let me make you some of mah fine country stew", wife->ID(), FOREGROUND_GREEN);

		wife->GetFSM()->ChangeState(CookStew::Instance());
	}
	case Msg_HiMamImHome:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: "
			<< Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(wife->ID());

// 		cout << "\n" << GetNameOfEntity(wife->ID()) <<
// 			": Hi my child. Let me make you a little some of mah fine country stew";
		DisplayMessageThread::display(": Hi my child. Let me make you a little some of mah fine country stew", wife->ID(), FOREGROUND_GREEN);

		wife->GetFSM()->ChangeState(CookStew::Instance());

	}


	return true;

	}//end switch

	return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
	static DoHouseWork instance;

	return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
// 	cout << "\n" << GetNameOfEntity(wife->ID()) << ": Time to do some more housework!";
	DisplayMessageThread::display(": Time to do some more housework!", wife->ID(), FOREGROUND_GREEN);
}


void DoHouseWork::Execute(MinersWife* wife)
{
	switch (RandInt(0, 2))
	{
	case 0:

// 		cout << "\n" << GetNameOfEntity(wife->ID()) << ": Moppin' the floor";
		DisplayMessageThread::display(": Moppin' the floor", wife->ID(), FOREGROUND_GREEN);

		break;

	case 1:

// 		cout << "\n" << GetNameOfEntity(wife->ID()) << ": Washin' the dishes";
		DisplayMessageThread::display(": Washin' the dishes", wife->ID(), FOREGROUND_GREEN);

		break;

	case 2:

// 		cout << "\n" << GetNameOfEntity(wife->ID()) << ": Makin' the bed";
		DisplayMessageThread::display(": Makin' the bed", wife->ID(), FOREGROUND_GREEN);

		break;
	}
}

void DoHouseWork::Exit(MinersWife* wife)
{
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Telegram& msg)
{
	return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
	static VisitBathroom instance;

	return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{
// 	cout << "\n" << GetNameOfEntity(wife->ID()) << ": Walkin' to the can. Need to powda mah pretty li'lle nose";
	DisplayMessageThread::display(": Walkin' to the can. Need to powda mah pretty li'lle nose", wife->ID(), FOREGROUND_GREEN);
}


void VisitBathroom::Execute(MinersWife* wife)
{
// 	cout << "\n" << GetNameOfEntity(wife->ID()) << ": Ahhhhhh! Sweet relief!";
	DisplayMessageThread::display(": Ahhhhhh! Sweet relief!", wife->ID(), FOREGROUND_GREEN);

	wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife)
{
// 	cout << "\n" << GetNameOfEntity(wife->ID()) << ": Leavin' the Jon";
	DisplayMessageThread::display(": Leavin' the Jon", wife->ID(), FOREGROUND_GREEN);
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Telegram& msg)
{
	return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
	static CookStew instance;

	return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
	//if not already cooking put the stew in the oven
	if (!wife->Cooking())
	{
// 		cout << "\n" << GetNameOfEntity(wife->ID()) << ": Putting the stew in the oven";
		DisplayMessageThread::display(": Putting the stew in the oven", wife->ID(), FOREGROUND_GREEN);

		//send a delayed message myself so that I know when to take the stew
		//out of the oven
		Dispatch->DispatchMessage(1.5,                  //time delay
			wife->ID(),           //sender ID
			wife->ID(),           //receiver ID
			Msg_StewReady,        //msg
			NO_ADDITIONAL_INFO);

		wife->SetCooking(true);
	}
}


void CookStew::Execute(MinersWife* wife)
{
// 	cout << "\n" << GetNameOfEntity(wife->ID()) << ": Fussin' over food";
	DisplayMessageThread::display(": Fussin' over food", wife->ID(), FOREGROUND_GREEN);
}

void CookStew::Exit(MinersWife* wife)
{
// 	cout << "\n" << GetNameOfEntity(wife->ID()) << ": Puttin' the stew on the table";
	DisplayMessageThread::display(": Puttin' the stew on the table", wife->ID(), FOREGROUND_GREEN);
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_StewReady:
	{
// 		cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
// 			" at time: " << Clock->GetCurrentTime();
		DisplayMessageThread::displayMessage(wife->ID());

// 		cout << "\n" << GetNameOfEntity(wife->ID()) << ": Stew Ready! Lets eat";
		DisplayMessageThread::display(": Stew Ready! Lets eat", wife->ID(), FOREGROUND_GREEN);

		//let hubby know the stew is ready
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			wife->ID(),
			ent_Miner_Bob,
			Msg_StewReady,
			NO_ADDITIONAL_INFO);

		//let child know the stew is ready
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			wife->ID(),
			ent_Child,
			Msg_LittleStewReady,
			NO_ADDITIONAL_INFO);

		wife->SetCooking(false);

		wife->GetFSM()->ChangeState(DoHouseWork::Instance());
	}

	return true;

	}//end switch

	return false;
}