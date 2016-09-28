#ifndef MINERSWIFE_H
#define MINERSWIFE_H
//------------------------------------------------------------------------
//
//  Name: MinersWife.h
//
//  Desc: class to implement Miner Bob's wife.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinersWifeOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class MinersWife : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<MinersWife>* m_pStateMachine;

	location_type   m_Location;

	//is she presently cooking?
	bool            m_bCooking;

	bool			  m_actif = TRUE;
	bool			  m_step = TRUE;

	std::thread m_thread;

	static uint32_t threadFunc(const int number_update, MinersWife * miner);

public:

	MinersWife(int id) :m_Location(shack),
		m_bCooking(false),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<MinersWife>(this);

		m_pStateMachine->SetCurrentState(DoHouseWork::Instance());

		m_pStateMachine->SetGlobalState(WifesGlobalState::Instance());
	}

	~MinersWife() { delete m_pStateMachine; }

	void start(const int number_update);

	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<MinersWife>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool			const isActif()const { return m_actif; }
	void			stop() { m_actif = FALSE; }
	void		  join() { m_thread.join(); }

	bool			const getStep()const { return m_step; }
	void			setStep(bool b) { m_step = b; }

	bool          Cooking()const { return m_bCooking; }
	void          SetCooking(bool val) { m_bCooking = val; }

};

#endif
