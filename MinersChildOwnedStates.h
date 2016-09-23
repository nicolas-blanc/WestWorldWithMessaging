#ifndef MINERCHILD_OWNED_STATES_H
#define MINERCHILD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class MinersChild;
struct Telegram;

//------------------------------------------------------------------------
class ChildGlobalState : public State<MinersChild>
{
private:

	ChildGlobalState() {}

	//copy ctor and assignment should be private
	ChildGlobalState(const ChildGlobalState&);
	ChildGlobalState& operator=(const ChildGlobalState&);

public:

	//this is a singleton
	static ChildGlobalState* Instance();

	virtual void Enter(MinersChild* minerChild) {}

	virtual void Execute(MinersChild* minerChild) {}

	virtual void Exit(MinersChild* minerChild) {}

	virtual bool OnMessage(MinersChild* minerChild, const Telegram& msg);
};

//------------------------------------------------------------------------
class GoHome : public State<MinersChild>
{
private:
	GoHome() {}

	//copy ctor and assignment should be private
	GoHome(const GoHome&);
	GoHome& operator=(const GoHome&);

public:
	//this is a singleton
	static GoHome* Instance();

	virtual void Enter(MinersChild* minerChild);

	virtual void Execute(MinersChild* minerChild);

	virtual void Exit(MinersChild* minerChild);

	virtual bool OnMessage(MinersChild* agent, const Telegram& msg);

};

class AtHomeSleep : public State<MinersChild>
{
private:
	AtHomeSleep() {}

	//copy ctor and assignment should be private
	AtHomeSleep(const AtHomeSleep&);
	AtHomeSleep& operator=(const AtHomeSleep&);

public:
	//this is a singleton
	static AtHomeSleep* Instance();

	virtual void Enter(MinersChild* minerChild);

	virtual void Execute(MinersChild* minerChild);

	virtual void Exit(MinersChild* minerChild);

	virtual bool OnMessage(MinersChild* agent, const Telegram& msg);

};

class AtHomeEatStew : public State<MinersChild>
{
private:
	AtHomeEatStew() {}

	//copy ctor and assignment should be private
	AtHomeEatStew(const AtHomeEatStew&);
	AtHomeEatStew& operator=(const AtHomeEatStew&);

public:
	//this is a singleton
	static AtHomeEatStew* Instance();

	virtual void Enter(MinersChild* minerChild);

	virtual void Execute(MinersChild* minerChild);

	virtual void Exit(MinersChild* minerChild);

	virtual bool OnMessage(MinersChild* agent, const Telegram& msg);

};

class AtHomeDrink : public State<MinersChild>
{
private:
	AtHomeDrink() {}

	//copy ctor and assignment should be private
	AtHomeDrink(const AtHomeDrink&);
	AtHomeDrink& operator=(const AtHomeDrink&);

public:
	//this is a singleton
	static AtHomeDrink* Instance();

	virtual void Enter(MinersChild* minerChild);

	virtual void Execute(MinersChild* minerChild);

	virtual void Exit(MinersChild* minerChild);

	virtual bool OnMessage(MinersChild* agent, const Telegram& msg);

};


class PlayWithFriend : public State<MinersChild>
{
private:
	PlayWithFriend() {}

	//copy ctor and assignment should be private
	PlayWithFriend(const PlayWithFriend&);
	PlayWithFriend& operator=(const PlayWithFriend&);

public:
	//this is a singleton
	static PlayWithFriend* Instance();

	virtual void Enter(MinersChild* minerChild);

	virtual void Execute(MinersChild* minerChild);

	virtual void Exit(MinersChild* minerChild);

	virtual bool OnMessage(MinersChild* agent, const Telegram& msg);

};

class MakeLikeDad : public State<MinersChild>
{
private:
	MakeLikeDad() {}

	//copy ctor and assignment should be private
	MakeLikeDad(const MakeLikeDad&);
	MakeLikeDad& operator=(const MakeLikeDad&);

public:
	//this is a singleton
	static MakeLikeDad* Instance();

	virtual void Enter(MinersChild* minerChild);

	virtual void Execute(MinersChild* minerChild);

	virtual void Exit(MinersChild* minerChild);

	virtual bool OnMessage(MinersChild* agent, const Telegram& msg);

};

#endif
