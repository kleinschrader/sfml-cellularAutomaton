#ifndef CMENUELEMENT_H
#define CMENUELEMENT_H

#include <SFML/Graphics.hpp>

class cMenuElement
{
	public:
		cMenuElement();
		void init(const char* Text,sf::Font *Font, int x, int y, int id);
		virtual ~cMenuElement();

		void draw(sf::RenderWindow *window);

		int contains(int x, int y);
	private:
		int id;
		sf::Text *Text;
		sf::RectangleShape *Background;
};

#endif // CMENUELEMENT_H
