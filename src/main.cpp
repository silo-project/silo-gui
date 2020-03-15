#include <iostream>
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include "file/circreader.hpp"

int main(int argc, char** argv) {
	std::vector<Circuit*>* circuitVect = new std::vector<Circuit*>();
	int circcount = CircReader::readFile((char*)"../Test.circ", circuitVect);
	std::cout << circcount << std::endl;
	for (auto c : *circuitVect) {
		for (auto d : c->partSet) {
			std::cout << d->getUID() << "," << PARTID_GETLIBRARYID(d->getPartID()) << "," << PARTID_GETPARTID(d->getPartID()) << "," << (POSITION_GETX(d->getPosition())) << "," << (POSITION_GETY(d->getPosition())) << std::endl;
		}
		std::cout << c->getName() << "," << c->getLabel() << "," << (int)(c->getLabelUp()) << "," << c->getLabelFont() << "," << c->getLabelFont() << std::endl;
	}

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SILO");

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
            }
        }
    }

    return 0;
}