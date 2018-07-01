#ifndef CCONWAYSGAMEOFLIFE_H
#define CCONWAYSGAMEOFLIFE_H

#include <random>

#include "cSimulation.h"


class cConwaysGameOfLife : public cSimulation
{
	public:
		cConwaysGameOfLife();
		virtual ~cConwaysGameOfLife();

	protected:
		virtual void tick();

	private:
		bool *isAlive;
		bool *oldState;

		inline int getNeighbors(int currentCell);
};

#endif // CCONWAYSGAMEOFLIFE_H
