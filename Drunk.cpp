#include "Drunk.h"


bool Drunk::HandleMessage(const Telegram& msg)
{
	return m_stateMachine->HandleMessage(msg);
}


void Drunk::Update()
{
	SetTextColor(FOREGROUND_GREEN);
	//m_iThirst += 1;
	m_stateMachine->Update();
}

bool Drunk::isAngry(){
	return (m_iAngry > _AngryLevel);
}
bool Drunk::isFatigue(){
	return (m_iFatigue > _FatigueLevel);
}
bool Drunk::isReadyToWakeUp(){
	return m_iFatigue == 0;
}
bool Drunk::isHungry(){
	return (m_iHungry > _HungryLevel);
}