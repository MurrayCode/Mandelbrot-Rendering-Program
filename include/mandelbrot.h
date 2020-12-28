#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <thread>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>


using namespace std;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::vector;
using std::thread;
using std::mutex;


class compute_Mandelbrot {
public:
	compute_Mandelbrot();
	void mandelbrotZoomUpdate(double zoom, double offsetX, double offsetY, sf::Image& image, int minY, int mabY) const;
	typedef std::chrono::steady_clock the_clock;
	void updateImage(double zoom, double offsetX, double offsetY, sf::Image& image) const;
	static const int MAX = 1000;
	
private:
	
	
	std::array<sf::Color, MAX + 1> colors;
	
	int mandelbrot(double test, double test2) const;
	sf::Color getColour(int iterations) const;
	
};