#include "cConwaysGameOfLife.h"

cConwaysGameOfLife::cConwaysGameOfLife()
{
	this->isAlive = new bool[this->numberOfPixels];
	this->oldState = new bool[this->numberOfPixels];

	for(int i = 0; i < this->numberOfPixels; i++)
	{
		this->isAlive[i] = rand() % 2;
	}
}

cConwaysGameOfLife::~cConwaysGameOfLife()
{
	this->isRunning = false;
	this->thread->wait();

	delete [] this->isAlive;
	delete [] this->oldState;
}

void cConwaysGameOfLife::tick()
{
	for(int i = 0; i < this->numberOfPixels; i++)
	{
		this->oldState[i] = this->isAlive[i];

		int neighbors = this->getNeighbors(i);

		if(this->isAlive[i])
		{
			if(neighbors < 2)
			{
				this->isAlive[i] = false;
			}
			else if(neighbors > 3)
			{
				this->isAlive[i] = false;
			}
		}
		else
		{
			if(neighbors == 3)
				this->isAlive[i] = true;
		}

		if(this->isAlive[i])
			this->pixel[i].color = sf::Color::White;
		else
			this->pixel[i].color = sf::Color::Black;
	}
}

int cConwaysGameOfLife::getNeighbors(int currentCell)
{
	int buffer = 0;

	bool blockedLeft, blockedRight, blockedUp, blockedDown;

	blockedLeft = (currentCell % this->pixelsX) == 0;
	blockedRight = (currentCell % this->pixelsX) == (this->pixelsX - 1);
	blockedUp = (currentCell / this->pixelsX) == 0;
	blockedDown = (currentCell / this->pixelsX) == (this->pixelsY -1);

	if(!blockedLeft && !blockedUp)
	{
		if(this->oldState[currentCell - (this->pixelsX + 1)])
			buffer++;
	}
	if(!blockedUp)
	{
		if(this->oldState[currentCell - this->pixelsX])
			buffer++;
	}
	if(!blockedUp && !blockedRight)
	{
		if(this->oldState[currentCell - (this->pixelsX - 1)])
			buffer++;
	}
	if(!blockedLeft)
	{
		if(this->oldState[currentCell - 1])
			buffer++;
	}
	if(!blockedRight)
	{
		if(this->isAlive[currentCell + 1])
			buffer++;
	}
	if(!blockedLeft && !blockedDown)
	{
		if(this->isAlive[currentCell + (this->pixelsX - 1)])
			buffer++;
	}
	if(!blockedDown)
	{
		if(this->isAlive[currentCell + this->pixelsX])
			buffer++;
	}
	if(!blockedDown && !blockedRight)
	{
		if(this->isAlive[currentCell + (this->pixelsX + 1)])
			buffer++;
	}

	return buffer;
}
