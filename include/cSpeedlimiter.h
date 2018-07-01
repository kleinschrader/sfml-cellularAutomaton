#ifndef CSPEEDLIMITER_H
#define CSPEEDLIMITER_H

#include <SFML/Graphics.hpp>

#include "settings.h"

class cSpeedlimiter
{
	public:
		cSpeedlimiter(int maxHertz);
		virtual ~cSpeedlimiter();

		void tick();
	private:
		int maxHertz;
		sf::Clock* Timer;
};

#endif // CSPEEDLIMITER_H
