#include "../include/mandelbrot.h"

const int WIDTH = 640;
const int HEIGHT = 480;

mutex forloop_mutex;

compute_Mandelbrot::compute_Mandelbrot() {
	for (int a = 0; a <= MAX; ++a) {
		colors[a] = getColour(a);
	}
}

int compute_Mandelbrot::mandelbrot(double x, double y) const {
	double a = x;
	double b = y;
	for (int counter = 0; counter < MAX; ++counter) {
		double r2 = a * a;
		double i2 = b * b;
		if (r2 + i2 > 4.0) {
			return counter;
		}
		b = 2.0 * a * b + y;
		a = r2 - i2 + x;
	}
	
	return MAX;
}

sf::Color compute_Mandelbrot::getColour(int iterations) const {    //Colours image
	int r, g, b;

	if (iterations < 16) {
		r = 0 * (16 - iterations);
		g = 188;
		b = 50 * iterations - 1;
	}
	else if (iterations < 32) {
		r = 141;
		g = 34 * (iterations - 16);
		b = 173 * (32 - iterations) - 1;
	}
	else if (iterations < 64) {
		r = 255 * (iterations - 32);
		g = 29 * (64 - iterations) - 1;
		b = 0;
	}
	else { 
		r = 15 - (iterations - 64) * 4;
		g = 255;
		b = 75;
	}

	return sf::Color(r, g, b);
}

void compute_Mandelbrot::mandelbrotZoomUpdate(double zoom, double offsetX, double offsetY, sf::Image& image, int inputA, int inputB) const   //updates image to on new location
{
	
	double y = 0 * zoom - WIDTH / 2.0 * zoom + offsetX;
	double x = inputA * zoom - HEIGHT / 2.0 * zoom + offsetY;
	
	for (int b = 0; b < WIDTH; b++, y += zoom) {
		double imag = x;
		for (int a = inputA; a < inputB; a++, imag += zoom) {
			int value = mandelbrot(y, imag);
			image.setPixel(b, a, colors[value]);
		}
	}
	
	
}

void compute_Mandelbrot::updateImage(double zoom, double offsetX, double offsetY, sf::Image& image) const       //Runs the image updater on multiple threads
{
	the_clock::time_point start = the_clock::now();
	cout << "Please wait...computing mandlebrot " << endl;
	const int threads = HEIGHT / thread::hardware_concurrency();     // divides the image height by available threads

	vector<thread> zoomThread;
	forloop_mutex.lock();

	for (int i = 0; i < HEIGHT; i += threads) {
		zoomThread.push_back(thread(&compute_Mandelbrot::mandelbrotZoomUpdate, *this, zoom, offsetX, offsetY, std::ref(image), i, std::min(i + threads, HEIGHT)));

	}
	forloop_mutex.unlock();

	for (auto &x : zoomThread) {
		x.join();
	}
	the_clock::time_point end = the_clock::now();
	auto time_taken = duration_cast<milliseconds> (end - start).count();
	cout << "Updating Mandelbrot Image took:" << time_taken << "milliseconds" << endl;

}

