#ifndef MINERCHILD_H
#define MINERCHILD_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>
#include <thread>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "MinersChildOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of nuggets a miner can carry
const int MaxStone = 3;
//above this value a miner is sleepy
const int TirednessThresholdChild = 3;
//
const int ThirstLevelChild = 3;

class MinersChild : public BaseGameEntity
{
private:
	//an instance of the state machine class
	StateMachine<MinersChild>*  m_pStateMachine;

	location_type         m_Location;

	//how many stone the child has in his pockets
	int                   m_iStoneCarried;

	//the higher the value, the more tired the miner
	int                   m_iFatigue;

	//
	int					  m_iThirsty;

	int					  m_iWantPlay;

	int					  m_iWantMakeLikeDad;

	bool				  m_actif = TRUE;
	bool				  m_step = TRUE;

	std::thread m_thread;

	static uint32_t threadFunc(const int number_update, MinersChild * miner);

public:
	MinersChild(int id) :m_Location(shack),
		m_iStoneCarried(0),
		m_iThirsty(0),
		m_iFatigue(0),
		m_iWantPlay(0),
		m_iWantMakeLikeDad(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<MinersChild>(this);

		m_pStateMachine->SetCurrentState(GoHome::Instance());

		m_pStateMachine->SetGlobalState(ChildGlobalState::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	};

	~MinersChild() { delete m_pStateMachine; };

	void start(const int number_update);

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<MinersChild>* GetFSM()const { return m_pStateMachine; }

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool		  const isActif()const { return m_actif; }
	void		  stop() { m_actif = FALSE; }
	void		  join() { m_thread.join(); }

	bool		  const getStep()const { return m_step; }
	void		  setStep(bool b) { m_step = b; }

	bool          StoneCarried()const { return m_iStoneCarried > 0; }
	void          SetStoneCarried(int val) { m_iStoneCarried = val; }
	void          AddToStoneCarried(int val);
	bool          PocketsFull()const { return m_iStoneCarried >= MaxStone; }

	int			  GetFatigued()const { return m_iFatigue; }
	bool          Fatigued()const;
	bool		  NotFatigued() const;
	void          DecreaseFatigue() { m_iFatigue -= 2; }
	void          IncreaseFatigue() { m_iFatigue += 1; }

	bool		  WhatWantTheChild()const;
	void		  DecreaseWantPlay() { if (m_iWantPlay > 0) m_iWantPlay -= 1; }
	void		  IncreaseWantPlay() { m_iWantPlay += 1; }
	// Ajouter un message du p�re, quand il travaille, augmente l'envie de l'enfant d'aller creuser
	void		  DecreaseWantMakeLikeDad() { if (m_iWantMakeLikeDad > 0) m_iWantMakeLikeDad -= 1; }
	void		  IncreaseWantMakeLikeDad() { m_iWantMakeLikeDad += 1; }

	bool		  Thirsty()const;
	bool		  NotThirsty()const;
	void		  DecreaseThirsty() { m_iThirsty -= 1; }
	void		  IncreaseThirsty() { m_iThirsty += 1; }
};

#endif
