#include <iostream>
#include <thread>
#include "mandelbrot.h"

using namespace std;

class window{
    private:
    const int WIDTH = 640;  //image width
    const int HEIGHT = 480; //image height
    protected:
    public:
        void buildWindow();
};

