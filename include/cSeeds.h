#ifndef CSEEDS_H
#define CSEEDS_H

#include "cSimulation.h"


class cSeeds : public cSimulation
{
	public:
		cSeeds();
		virtual ~cSeeds();

	protected:
		virtual void tick();
		virtual void handleClick(int x, int y);

	private:
		bool *isAlive;
		bool *oldState;

		inline int getNeighbors(int currentCell);
};

#endif // CSEEDS_H
