#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;
/*
int main(void)
{
	frontal_face_detector detector = get_frontal_face_detector();
	image_window win;
	string filename = "C:/face_example.jpg";
	array2d<unsigned char> img;
	load_image(img, filename);
	pyramid_up(img);			//cvPyrUp in openCV
	std::vector<rectangle> dets = detector(img);
	win.clear_overlay(); 
	win.set_image(img);
	win.add_overlay(dets, rgb_pixel(255, 0, 0));

	cin.get();

}*/