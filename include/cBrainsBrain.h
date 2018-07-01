#ifndef CBRAINSBRAIN_H
#define CBRAINSBRAIN_H

#include <random>

#include "cSimulation.h"


class cBrainsBrain : public cSimulation
{
	public:
		cBrainsBrain();
		virtual ~cBrainsBrain();

	protected:
		virtual void tick();

	private:
		inline int getNeighbors(int currentCell);

		enum stateType
		{
			TYPE_ON,
			TYPE_DYING,
			TYPE_OFF
		};
		char *state;
		int *oldState;
};

#endif // CBRAINSBRAIN_H
