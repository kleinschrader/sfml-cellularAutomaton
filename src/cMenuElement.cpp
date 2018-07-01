#include "cMenuElement.h"

#include <stdio.h>

cMenuElement::cMenuElement()
{

}

void cMenuElement::init(const char* Text,sf::Font *Font, int x, int y, int id)
{
	this->Text = new sf::Text(Text,*Font,15);
	this->Text->setPosition(sf::Vector2f(x + 2,y + 7));
	this->Background = new sf::RectangleShape(sf::Vector2f(78,28));
	this->Background->setOrigin(sf::Vector2f(0,0));
	this->Background->setPosition(sf::Vector2f(x + 1,y + 1));
	this->Background->setFillColor(sf::Color(170,170,170));
	this->Background->setOutlineThickness(1);
	this->Background->setOutlineColor(sf::Color::White);

	this->id = id;
}

cMenuElement::~cMenuElement()
{
	delete this->Text;
	delete this->Background;
}

void cMenuElement::draw(sf::RenderWindow *window)
{
	window->draw(*this->Background);
	window->draw(*this->Text);
}

int cMenuElement::contains(int x, int y)
{
	sf::FloatRect fRect = this->Background->getGlobalBounds();
	if(fRect.contains(x,y))
		return this->id;
	else
		return 0;
}
