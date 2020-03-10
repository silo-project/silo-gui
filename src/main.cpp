#include <iostream>
#include <cstdlib>
#include <set>
#include <SFML/Graphics.hpp>
#include "file/circreader.hpp"

int main(int argc, char** argv) {
	std::set<Circuit*> circuitSet;
	int circcount = CircReader::readFile((char*)"../Test.circ", &circuitSet);
	std::cout << circcount << std::endl;
	for (auto c : circuitSet) {
		std::cout << c->getName() << "," << c->getLabel() << "," << (int)(c->getLabelUp()) << "," << c->getLabelFont() << std::endl;
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
