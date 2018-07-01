#include "cFPSCounter.h"

cFPSCounter::cFPSCounter(sf::Font *Font)
{
	this->Timer = new sf::Clock;
	this->FPSString = new Textf;

	this->FPSString->setFont(*Font);
	this->FPSString->setString("FPS: %i");
	this->FPSString->addVaribale(&this->FPS);
	this->FPSString->setCharacterSize(15);
	this->FPSString->setAutoUpdating(true);
}

cFPSCounter::~cFPSCounter()
{
	//dtor
}

void cFPSCounter::draw(sf::RenderWindow *window)
{
	int frametime = this->Timer->restart().asMicroseconds();

	if(frametime == 0)
		frametime = 1;

	this->FPS = 1000000 / frametime;

	window->draw(*this->FPSString);
}
