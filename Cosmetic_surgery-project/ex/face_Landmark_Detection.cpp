#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace dlib;

/*
int main(void)
{
	
	frontal_face_detector detector = get_frontal_face_detector();
	image_window win, win_faces;
	
	string filename = "C:/face_example4.jpg";
	string dat = "C:/shape_predictor_68_face_landmarks.dat";
	shape_predictor sp;
	array2d<unsigned char> img;
	
	deserialize(dat) >> sp;
	load_image(img, filename);
	pyramid_up(img);
	std::vector<rectangle> dets = detector(img);
	std::vector<full_object_detection> shapes;
	cout << "dets.size() : " << dets.size() << endl;
	for (unsigned long j = 0; j < dets.size(); j++)
	{
		cout << j << endl;
		full_object_detection shape = sp(img, dets[j]);
		cout << "number of parts: " << shape.num_parts() << endl;
		cout << "pixel position of first part: " << shape.part(0) << endl;
		cout << "pixel position of second part: " << shape.part(1) << endl;
		shapes.push_back(shape);
	}

	win.clear_overlay();
	win.set_image(img);
	win.add_overlay(render_face_detections(shapes));

	dlib::array<array2d<rgb_pixel> > face_chips;
	extract_image_chips(img, get_face_chip_details(shapes), face_chips);
	win_faces.set_image(tile_images(face_chips));

	cout << "Hit enter to process the next image..." << endl;
	cin.get();

	return 0;
}

*/