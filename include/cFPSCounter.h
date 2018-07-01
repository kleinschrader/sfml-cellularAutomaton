#ifndef CFPSCOUNTER_H
#define CFPSCOUNTER_H

#include <SFML/Graphics.hpp>
#include <cTextf.hpp>

class cFPSCounter
{
	public:
		cFPSCounter(sf::Font *Font);
		virtual ~cFPSCounter();

		void draw(sf::RenderWindow *window);
	private:
		sf::Clock *Timer;
		Textf *FPSString;

		int FPS = 0;
};

#endif // CFPSCOUNTER_H
