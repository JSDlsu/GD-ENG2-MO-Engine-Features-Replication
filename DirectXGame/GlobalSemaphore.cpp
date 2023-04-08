#include "GlobalSemaphore.h"

GlobalSemaphore::GlobalSemaphore(int keys)
{
	this->semaphore = new std::counting_semaphore<1000>(keys);
}

void GlobalSemaphore::acquire(int keys)
{
	for (int i = 0; i < keys; i++)
	{
		this->semaphore->acquire();
	}
}

void GlobalSemaphore::release(int keys)
{
	this->semaphore->release(keys);
}