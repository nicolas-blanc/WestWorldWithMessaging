#ifndef DISPLAY_MESSAGE_THREAD_H
#define DISPLAY_MESSAGE_THREAD_H

#include <mutex>

class DisplayMessageThread
{
public:
	static void display(std::string message, int id, int color);
	static void displayMessage(int id);
	static void lock();
	static void unlock();

private:
	static std::mutex mutex;
};

#endif
