#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include <thread>
#include "../include/hardware.h"
#include "../include/window.h"


using namespace std;


int main() {
	hardware h;
	window w;
	h.hardwareConcurrency(); // run hardware check function
	cout << "Controls:" << endl; 
	cout << "Arrow Keys to Move Camera" << endl;
	cout << " + and - to zoom in and out" << endl;
	w.buildWindow();
}

