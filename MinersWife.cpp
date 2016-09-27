#include "MinersWife.h"
#include "DisplayMessageThread.h"
#include <string>

bool MinersWife::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}

uint32_t MinersWife::threadFunc(const int number_update, MinersWife * miner)
{
	std::cout << "Thread Wife Miner";

	for (int i = 0; i < number_update; i++)
	{
		while (miner->getStep()) {}

		DisplayMessageThread::display("Number of turn : " + std::to_string(i), miner->ID(), FOREGROUND_GREEN);
		miner->Update();

		miner->setStep(TRUE);
	}

	std::cout << "END Thread Wife Miner";
	miner->stop();

	return 0;
}

void MinersWife::start(const int number_udpate)
{
	m_thread = std::thread(threadFunc, number_udpate, this);

}

void MinersWife::Update()
{
  //set text color to green
  SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
 
  m_pStateMachine->Update();
}