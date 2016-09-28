#include "DisplayMessageThread.h"
#include "EntityNames.h"
#include <iostream>
#include "misc\ConsoleUtils.h"
#include "Time\CrudeTimer.h"

#include <string>
#include <thread>

std::mutex DisplayMessageThread::mutex;

void DisplayMessageThread::display(std::string message, int id, int color)
{
	mutex.lock();

	SetTextColor(color | FOREGROUND_INTENSITY);
	std::cout << "\n" << GetNameOfEntity(id) << ": " << message;

// 	std::cout << "\n---------------------Thread lock";

	mutex.unlock();
}


void DisplayMessageThread::displayMessage(int id)
{
	mutex.lock();

	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "\nMessage handled by " << GetNameOfEntity(id)
		<< " at time: " << Clock->GetCurrentTime();
	
	mutex.unlock();
}

void DisplayMessageThread::lock()
{
	mutex.lock();
}

void DisplayMessageThread::unlock()
{
	mutex.unlock();
}
