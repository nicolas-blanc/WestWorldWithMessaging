#pragma once
#include "FSM/State.h"

class Drunk;
struct Telegram;

class DrinkABeer : public State<Drunk>
{
private:
	DrinkABeer(){};
	~DrinkABeer(){};
public:
	static DrinkABeer* Instance();

	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);
};

class EatSomePretzel : public State < Drunk >
{
private:
	EatSomePretzel(){};
	~EatSomePretzel(){};
public:
	static EatSomePretzel* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);
};

class DrunkFight : public State < Drunk >
{
private:
	DrunkFight(){};
	~DrunkFight(){};
public:
	static DrunkFight* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

class SleepAtSaloon : public State < Drunk > {
private:
	SleepAtSaloon(){};
	~SleepAtSaloon(){};
public:
	static SleepAtSaloon* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);
};

class OrderBeer : public State < Drunk > {
private:
	OrderBeer(){};
	~OrderBeer(){};
public:
	static OrderBeer* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);
};

class OrderPretzel : public State < Drunk > {
private:
	OrderPretzel(){};
	~OrderPretzel(){};
public:
	static OrderPretzel* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);
};