#include "cApplication.h"

cApplication::cApplication()
{
	this->renderThread = new sf::Thread(cApplication::renderLoop,this);

	this->AGENCYR = new sf::Font;
	this->AGENCYR->loadFromFile("C:\\Windows\\Fonts\\AGENCYR.TTF");

	this->FPSCounter = new cFPSCounter(this->AGENCYR);

	this->pollSpeed = new cSpeedlimiter(maxPollHertz);

	this->generateMenu();

	if(fullscreen)
		this->window = new sf::RenderWindow(sf::VideoMode(windowWidth,windowHeight),"Cellular Automation",sf::Style::Fullscreen);
	else
		this->window = new sf::RenderWindow(sf::VideoMode(windowWidth,windowHeight),"Cellular Automation");
	this->window->resetGLStates();
	this->window->setActive(false);

	ImGui::SFML::Init(*this->window);

	this->deltaTime = new sf::Clock;

	if(maxFramerate != 0)
		this->window->setFramerateLimit(maxFramerate);
}

cApplication::~cApplication()
{
	this->renderThread->wait();

	delete this->window;

	delete this->pollSpeed;

	delete this->renderThread;

	delete this->AGENCYR;

	delete this->FPSCounter;

	delete [] this->menuName;
	delete [] this->menuId;
}

void cApplication::run()
{
	this->renderThread->launch();
	while(this->window->isOpen())
	{
		handleEvents();
		this->pollSpeed->tick();

	}
}

void cApplication::handleEvents()
{
	sf::Event eventBuffer;
	while(this->window->pollEvent(eventBuffer))
	{
		if(eventBuffer.type == sf::Event::Closed)
		{
			this->window->close();
		}
		else if(eventBuffer.type == sf::Event::MouseButtonReleased)
		{
			int mouseX = eventBuffer.mouseButton.x;
			int mouseY = eventBuffer.mouseButton.y;

			int relMouseX = mouseX * (float(windowWidth) / this->window->getSize().x);
			int relMouseY = mouseY * (float(windowHeight) / this->window->getSize().y);

			if(this->state == 0)
			{

			}
			else
			{
				this->simulation->handleClick(relMouseX,relMouseY);
			}
		}
		else if(eventBuffer.type == sf::Event::KeyPressed)
		{
			if(eventBuffer.key.code == sf::Keyboard::Escape)
			{
				if(this->state == 0)
				{
					this->window->close();
				}
				else
				{
					this->state = 0;
					delete this->simulation;
				}
			}
		}

		ImGui::SFML::ProcessEvent(eventBuffer);
	}
}

void cApplication::renderLoop(cApplication *t_this)
{
	t_this->window->setActive(true);

	while(t_this->window->isOpen())
	{
		t_this->window->clear();

		if(t_this->state)
		{
				t_this->simulation->draw(t_this->window);
				t_this->simulation->drawExtras(t_this->window,t_this->deltaTime->restart());
		}
		else
		{
			ImGui::SFML::Update(*t_this->window,t_this->deltaTime->restart());

			ImGui::Begin("kleins Cellular Automation");

			ImGui::Combo("Simulations",&t_this->currentItem,t_this->menuName,t_this->numberOfElements);

			if(ImGui::Button("Start Simulation"))
			{
					if(t_this->currentItem == 0)
						t_this->simulation = new cBrainsBrain;
					else if(t_this->currentItem == 1)
						t_this->simulation = new cConwaysGameOfLife;
					else if(t_this->currentItem == 2)
						t_this->simulation = new cSeeds;
					else if(t_this->currentItem == 3)
						t_this->simulation = new cPredAndPrey(t_this->AGENCYR,t_this->window);

					t_this->simulation->startThread();

					t_this->state = t_this->currentItem + 1;
			}

			ImGui::End();
			ImGui::SFML::Render(*t_this->window);
		}

		t_this->FPSCounter->draw(t_this->window);

		t_this->window->display();
	}
}

void cApplication::generateMenu()
{
	this->menuName = new const char*[this->numberOfElements];
	this->menuId = new int[this->numberOfElements];
	this->addMenuElement("Brian's Brain", 1);
	this->addMenuElement("Game Of Life", 2);
	this->addMenuElement("Seeds", 3);
	this->addMenuElement("Predator And Prey", 4);
	//this->Menu[0].init("Brian's Barain",this->AGENCYR,0,17,1);
	//this->Menu[1].init("Game Of Life", this->AGENCYR,0,47,2);
	//this->Menu[2].init("Seeds", this->AGENCYR,0,77,3);
}

void cApplication::addMenuElement(const char* name, int id)
{
	this->menuName[id - 1] = name;
	this->menuId[id - 1] = id;
}
