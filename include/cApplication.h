#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "cFPSCounter.h"
#include "cMenuElement.h"
#include "cSimulation.h"
#include "cSpeedlimiter.h"

#include "cBrainsBrain.h"
#include "cConwaysGameOfLife.h"
#include "cSeeds.h"
#include "cPredAndPrey.h"

#include "settings.h"

class cApplication
{
	public:
		cApplication();
		~cApplication();

		void run();

		bool getShouldEndSimulation();
	private:
		void handleEvents();

		void generateMenu();
		void addMenuElement(const char* name, int id);

		static void renderLoop(cApplication *t_this);

		const int numberOfElements = 4;

		int state = 0;

		const char** menuName;
		int* menuId;

		int currentItem;

		sf::RenderWindow *window;
		sf::Thread *renderThread;
		sf::Font *AGENCYR;
		cFPSCounter *FPSCounter;
		sf::Clock *deltaTime;
		cSimulation *simulation;

		cSpeedlimiter *pollSpeed;
};

#endif // CAPPLICATION_H
