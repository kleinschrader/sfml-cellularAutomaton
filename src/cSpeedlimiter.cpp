#include "cSpeedlimiter.h"

#include <stdio.h>

cSpeedlimiter::cSpeedlimiter(int maxHertz)
{
	this->maxHertz = maxHertz;
	if(this->maxHertz != 0)
	{
		this->Timer = new sf::Clock;
		this->Timer->restart();
	}
}

cSpeedlimiter::~cSpeedlimiter()
{
	delete this->Timer;
}

void cSpeedlimiter::tick()
{

	if(this->maxHertz == 0)
		return;

	int elapsedTime = this->Timer->restart().asMicroseconds();

	int minTimeNeeded = (1000000 / this->maxHertz);
	if(elapsedTime < minTimeNeeded)
	{
		int timeToSleep = minTimeNeeded - elapsedTime;

		sf::sleep(sf::microseconds(timeToSleep));
	}

	this->Timer->restart();
}
