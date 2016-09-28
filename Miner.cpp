#include <vector>
#include "Miner.h"
#include "DisplayMessageThread.h"

bool Miner::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

uint32_t Miner::threadFunc(const int number_update, Miner * miner)
{
	DisplayMessageThread::display("Create Thread", miner->ID(), FOREGROUND_RED);

	for (int i = 0; i < number_update; i++)
	{
		while (miner->getStep()) {}

		DisplayMessageThread::display("Number of turn : " + std::to_string(i), miner->ID(), FOREGROUND_RED);
		miner->Update();

		miner->setStep(TRUE);
	}

	DisplayMessageThread::display("End Thread", miner->ID(), FOREGROUND_RED);

	miner->stop();

	return 0;
}

void Miner::start(const int number_udpate)
{
	m_thread = std::thread(threadFunc, number_udpate, this);
}

void Miner::Update()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_iThirst += 1;

	m_pStateMachine->Update();
}

void Miner::AddToGoldCarried(const int val)
{
	m_iGoldCarried += val;

	if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Miner::AddToWealth(const int val)
{
	m_iMoneyInBank += val;

	if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Miner::Thirsty()const
{
	if (m_iThirst >= ThirstLevel) { return true; }

	return false;
}

bool Miner::Fatigued()const
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}

	return false;
}
