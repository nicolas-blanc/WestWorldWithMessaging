#include "MinersChild.h"
#include "DisplayMessageThread.h"
#include <string>

uint32_t MinersChild::threadFunc(const int number_update, MinersChild * miner)
{
	DisplayMessageThread::display("Create Thread", miner->ID(), FOREGROUND_BLUE);

	for (int i = 0; i < number_update; i++)
	{
		while (miner->getStep()) {}

		DisplayMessageThread::display("Number of turn : " + std::to_string(i), miner->ID(), FOREGROUND_BLUE);
		miner->Update();

		miner->setStep(TRUE);
	}

	DisplayMessageThread::display("End Thread", miner->ID(), FOREGROUND_BLUE);
	miner->stop();

	return 0;
}

void MinersChild::start(const int number_udpate)
{
	m_thread = std::thread(threadFunc, number_udpate, this);

}

void MinersChild::Update()
{
	m_pStateMachine->Update();
}

bool MinersChild::HandleMessage(const Telegram & msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void MinersChild::AddToStoneCarried(int val)
{
	m_iStoneCarried += val;

	if (m_iStoneCarried < 0) m_iStoneCarried = 0;
}

bool MinersChild::Fatigued() const
{
	if (m_iFatigue >= TirednessThresholdChild) { return true; }
	return false;
}

bool MinersChild::NotFatigued() const
{
	if (m_iFatigue > 0) { return true; }
	return false;
}

bool MinersChild::WhatWantTheChild() const
{
	if (m_iWantMakeLikeDad > m_iWantPlay) { return true; }
	return false;
}

bool MinersChild::Thirsty() const
{
	if (m_iThirsty >= ThirstLevelChild) { return true; }
	return false;
}

bool MinersChild::NotThirsty() const
{
	if (m_iThirsty > 0) { return true; }
	return false;
}
