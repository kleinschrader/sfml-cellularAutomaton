#include "cBrainsBrain.h"

cBrainsBrain::cBrainsBrain()
{
	this->state = new char[this->numberOfPixels];
	this->oldState = new int[numberOfPixels];

	for(int i = 0; i < numberOfPixels; i++)
	{
			this->state[i] = rand() % 3;
	}
}

cBrainsBrain::~cBrainsBrain()
{
	this->isRunning = false;
	this->thread->wait();

	delete [] this->state;
	delete [] this->oldState;
}

void cBrainsBrain::tick()
{
	for(int i = 0; i < numberOfPixels; i++)
	{
		this->oldState[i] = this->state[i];

		if(this->state[i] == this->TYPE_ON)
		{
			this->state[i] = this->TYPE_DYING;
			this->pixel[i].color = sf::Color::Blue;
		}
		else if(this->state[i] == this->TYPE_DYING)
		{
			this->state[i] = this->TYPE_OFF;
			this->pixel[i].color = sf::Color::White;
		}
		else if(this->state[i] == this->TYPE_OFF)
		{
			if(this->getNeighbors(i) == 2)
			{
				this->state[i] = this->TYPE_ON;
			}
			this->pixel[i].color = sf::Color::Black;
		}
	}
}

int cBrainsBrain::getNeighbors(int currentCell)
{
	int buffer = 0;

	bool blockedLeft, blockedRight, blockedUp, blockedDown;

	blockedLeft = (currentCell % this->pixelsX) == 0;
	blockedRight = (currentCell % this->pixelsX) == (this->pixelsX - 1);
	blockedUp = (currentCell / this->pixelsX) == 0;
	blockedDown = (currentCell / this->pixelsX) == (this->pixelsY -1);

	if(!blockedLeft && !blockedUp)
	{
		if(this->oldState[currentCell - (this->pixelsX + 1)] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedUp)
	{
		if(this->oldState[currentCell - this->pixelsX] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedUp && !blockedRight)
	{
		if(this->oldState[currentCell - (this->pixelsX - 1)] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedLeft)
	{
		if(this->oldState[currentCell - 1] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedRight)
	{
		if(this->state[currentCell + 1] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedLeft && !blockedDown)
	{
		if(this->state[currentCell + (this->pixelsX - 1)] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedDown)
	{
		if(this->state[currentCell + this->pixelsX] == this->TYPE_ON)
			buffer++;
	}
	if(!blockedDown && !blockedRight)
	{
		if(this->state[currentCell + (this->pixelsX + 1)] == this->TYPE_ON)
			buffer++;
	}

	return buffer;
}
