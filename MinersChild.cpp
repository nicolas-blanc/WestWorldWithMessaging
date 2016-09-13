#include "MinersChild.h"

void MinersChild::Update()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_iFatigue += 1;

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
	if (m_iFatigue >= ThirstLevel) { return true; }
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
	if (m_iThirsty >= ThirstLevel) { return true; }
	return false;
}

bool MinersChild::NotThirsty() const
{
	if (m_iThirsty > 0) { return true; }
	return false;
}
