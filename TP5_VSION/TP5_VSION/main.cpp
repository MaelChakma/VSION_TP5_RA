// Aruco Include
#include<aruco.h>

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
	string imageAdress;
	string windowName = "Augmented Reality";
	char key = 'a';
	Mat image;

	// Asking image name
	cout << "Adresse de l'image: ";
	cin >> imageAdress;

	// Reading image
	image = imread(imageAdress);

	// Printing loop
	while (key != ESC_KEY) {
		imshow(windowName, image);
		key = waitKey();
	}
}