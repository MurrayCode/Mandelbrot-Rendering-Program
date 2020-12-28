#include "../include/hardware.h"
#include "../include/mandelbrot.h"
unsigned int hardware::hardwareConcurrency() //checks threads of CPU
{
	unsigned int threads = std::thread::hardware_concurrency();
	cout << "Number of Threads Available: " << threads<< endl;
	cout <<"Max Iterations: " << compute_Mandelbrot::MAX << endl;
	return threads;
}
