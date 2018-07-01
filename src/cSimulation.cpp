#include "cSimulation.h"

#include <random>
#include <stdio.h>

cSimulation::cSimulation()
{
	this->thread = new sf::Thread(this->mainThread,this);
	this->renderTexture = new sf::RenderTexture;

	this->pixelsX = (windowWidth / pixelSize);
	this->pixelsY = (windowHeight / pixelSize);
	this->numberOfPixels = (pixelsX * pixelsY);

	this->pixel = new sf::Vertex[numberOfPixels];

	for(int i = 0; i < this->numberOfPixels; i++)
	{
		this->pixel[i].position = sf::Vector2f(i % pixelsX,i / pixelsX);
		this->pixel[i].color = sf::Color::Black;
	}

	this->renderTexture->create(pixelsX, pixelsY);
	this->renderTexture->setActive(false);

	this->sprite = new sf::Sprite;

	this->hertzLimiter = new cSpeedlimiter(maxHertz);
}

cSimulation::~cSimulation()
{
	this->isRunning = false;
	this->thread->wait();

	delete this->thread;
	delete this->renderTexture;
	delete [] this->pixel;
}

void cSimulation::mainThread(void* r_this)
{
	cSimulation *t_this = (cSimulation*)r_this;

	while(t_this->isRunning)
	{
		t_this->hertzLimiter->tick();
		t_this->tick();
	}
}

void cSimulation::tick()
{
	throw 1;
}

void cSimulation::draw(sf::RenderWindow* window)
{
	this->renderTexture->setActive(true);


	this->renderTexture->clear();

	this->renderTexture->draw(this->pixel,this->numberOfPixels, sf::Points);

	this->renderTexture->display();


	this->sprite->setTexture(this->renderTexture->getTexture());
	this->sprite->setScale(pixelSize,pixelSize);
	window->draw(*this->sprite);
}

void cSimulation::startThread()
{
	this->thread->launch();
}

void cSimulation::handleClick(int x, int y)
{

}

void cSimulation::drawExtras(sf::RenderWindow *window,sf::Time ElapsedTime)
{

}
