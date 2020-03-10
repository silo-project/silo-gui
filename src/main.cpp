#include <SFML/Graphics.hpp>
#include "file/circreader.hpp"

int main(int argc, char** argv) {
	CircReader::read("../Test.circ");
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
