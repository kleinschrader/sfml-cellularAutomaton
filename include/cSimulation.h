#ifndef CSIMULATION_H
#define CSIMULATION_H

#include <SFML/Graphics.hpp>

#include "cSpeedlimiter.h"

#include "settings.h"

class cSimulation
{
	public:
		cSimulation();
		virtual ~cSimulation();

		void draw(sf::RenderWindow *window);

		void startThread();

		virtual void handleClick(int x, int y);

		virtual void drawExtras(sf::RenderWindow *window, sf::Time ElapsedTime);
	protected:
		virtual void tick();

		static void mainThread(void *r_this);

		bool isRunning = true;
		int numberOfPixels;

		int pixelsY, pixelsX;

		sf::Thread *thread;
		sf::Vertex *pixel;

		sf::Sprite *sprite;

		cSpeedlimiter *hertzLimiter;

		sf::RenderTexture *renderTexture;
};

#endif // CSIMULATION_H
