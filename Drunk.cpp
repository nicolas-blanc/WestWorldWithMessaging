#include "Drunk.h"
#include "DisplayMessageThread.h"


bool Drunk::HandleMessage(const Telegram& msg)
{
	return m_stateMachine->HandleMessage(msg);
}


uint32_t Drunk::threadFunc(int number_update, Drunk * drunk)
{
	DisplayMessageThread::display("Create Thread", drunk->ID(), FOREGROUND_GREEN);

	for (int i = 0; i < number_update; i++)
	{
		while (drunk->getStep()) {}

		DisplayMessageThread::display("Number of turn : " + std::to_string(i), drunk->ID(), FOREGROUND_GREEN);
		drunk->Update();

		drunk->setStep(TRUE);
	}

	DisplayMessageThread::display("End Thread", drunk->ID(), FOREGROUND_GREEN);
	drunk->stop();

	return 0;
}

void Drunk::start(const int number_udpate)
{
	m_thread = std::thread(threadFunc, number_udpate, this);
}

void Drunk::Update()
{
	SetTextColor(FOREGROUND_GREEN);

	m_iThirst += 1;

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