#include "../include/window.h"


void window::buildWindow() {   //Builds mandelbrot in a window
	double offsetX = -0.7;
	double offsetY = 0.0;
	double zoom = 0.004;
	compute_Mandelbrot cmb;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");   //renders window the same size as mandelbrot image
	window.setFramerateLimit(0);
	sf::Image image;										//
	image.create(WIDTH, HEIGHT, sf::Color(0, 0, 0));		// Creates image
	sf::Texture texture;									// puts image into texture
	sf::Sprite sprite;										// loads texture into sprite


	bool stateChanged = true; // checks whether the image needs to be updated
	while (window.isOpen()) {   //movement and zoom controls 
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				stateChanged = true;
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Equal:
					zoom *= 0.7;
					break;
				case sf::Keyboard::Dash:
					zoom /= 0.7;
					break;
				case sf::Keyboard::Up:
					offsetY -= 50 * zoom;
					break;
				case sf::Keyboard::Down:
					offsetY += 50 * zoom;
					break;
				case sf::Keyboard::Left:
					offsetX -= 30 * zoom;
					break;
				case sf::Keyboard::Right:
					offsetX += 30 * zoom;
					break;
				default:
					stateChanged = false;
					break;
				}
			default:
				break;
			}
		}

		if (stateChanged) {
			cmb.updateImage(zoom, offsetX, offsetY, image); //Updates image to new offset/zoom position
			texture.loadFromImage(image); //loads updated image
			sprite.setTexture(texture);//sets updated image into window
			stateChanged = false; //returns the update image checker to false
		}
		window.draw(sprite); //draws image 
		window.display(); // displays image
	}
	
}