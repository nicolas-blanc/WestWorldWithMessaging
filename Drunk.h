#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"
#include "FSM/StateMachine.h"
#include "misc/ConsoleUtils.h"
#include "DrunkOwnedStates.h"

#include <thread>
#include <stdint.h>

struct Telegram;

const int _ThirstLevel = 2;
const int _FatigueLevel = 5;
const int _HungryLevel = 4;
const int _AngryLevel = 3;

class Drunk : public BaseGameEntity
{
private:
	location_type m_location;
	StateMachine<Drunk>* m_stateMachine;
	int		m_iThirst;
	int		m_iFatigue;
	int		m_iAngry;
	int		m_iHungry;
	int		m_iBeerLevel;

	bool	m_actif = TRUE;
	bool	m_step = TRUE;
	
	std::thread m_thread;

	static uint32_t threadFunc(int numberUpdate, Drunk * drunk);
public:
	Drunk(int id) :m_location(saloon), BaseGameEntity(id){
		m_iThirst = 0;
		m_iFatigue = 0;
		m_iHungry = 0;
		m_iAngry = 0;
		m_iBeerLevel = 0;

		m_stateMachine = new StateMachine<Drunk>(this);
		m_stateMachine->SetCurrentState(DrinkABeer::Instance());
	};
	~Drunk(){
		delete m_stateMachine;
	};
	void start(const int number_udpate);

	const bool					isActif()const { return m_actif; }
	void						stop() { m_actif = FALSE; }
	void						join() { m_thread.join(); }

	const bool					getStep()const { return m_step; }
	void						setStep(bool b) { m_step = b; }


	void						Update();
	bool						isHungry();
	bool						isAngry();
	bool						isFatigue();
	bool						isReadyToWakeUp();
	void						IncreaseHungry() { m_iHungry += 1; }
	void						DecreaseHungry(){ m_iHungry -= 1; }
	void						IncreaseAngry() { m_iAngry += 1; }
	void						DecreaseAngry(){ m_iAngry = 0; }
	void						IncreaseFatigue() { m_iFatigue += 1; }
	void						DecreaseFatigue(){ m_iFatigue -= 1; }
	bool						isBeerEmpty(){ return m_iBeerLevel <= 0; }
	void						DecreaseBeer(){ m_iBeerLevel -= 1; }
	void						refillBeer() { m_iBeerLevel = 4; }
	virtual bool				HandleMessage(const Telegram& msg);
	StateMachine<Drunk>*	GetFSM()const{ return m_stateMachine; }
	const location_type			Location()const{ return m_location; }
	void						changeLocation(location_type newLocation){ m_location = newLocation; }

};

