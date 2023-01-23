// Aruco Include
#include<aruco\aruco.h>


// IOpenCV Include
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

// Other Includes
#include<iostream>

// Namespaces
using namespace std;
using namespace cv;

// Define esc key code
#define ESC_KEY 27

// Main function
void main() {
	// Variable declaration
	string windowName = "Augmented Reality";
	char key = 'a';
	Mat image;
	VideoCapture cap;

	// Opening camera
	cap.open(0);

	// Printing loop
	while (key != ESC_KEY) {
		// read next image
		cap >> image;

		// Marker detector creator
		aruco::MarkerDetector myDetector;
		//Marker list: will be filled by ArUco
		
		// detect markers and for each one, draw info and its boundaries in the image
		for (auto m : myDetector.detect(image)) {
			std::cout << m << std::endl;
			m.draw(image);
		}

		imshow(windowName, image);
		key = waitKey(1);
	}
}