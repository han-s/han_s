#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core_c.h>
#include <math.h>
#define RAD_TO_DEG (45.0/(atan((double)1)))
using namespace std;
using namespace dlib;
using namespace cv;

//��������
double changeAngle(const dlib::full_object_detection& d)
{
	int new_x = abs(d.part(27).x() - d.part(30).x());
	int new_y = d.part(30).y() - d.part(27).y();
	double theta = RAD_TO_DEG * atan2(new_y, new_x);
	cout << "new_x : " << new_x << " new_y : " << new_y << " theta : " << theta << endl;
	return theta;
}
//����������  //�μ���.
Mat changeSize(Mat &add, const dlib::full_object_detection& d)
{
	long width = d.part(11).x() - d.part(5).x();
	Mat new_size;
	resize(add, new_size, Size(width, width), 0, 0, CV_INTER_LINEAR);
	return new_size;
}
/* ��ġ������ ���� ��Ȯ�� ������ �ʿ���
���ʿ� ����� ������ ������ ���̴� �޼���
�Ű�����1 : ���̽����Ǵ� ����
�Ű�����2 : ���̽��� ���� ����
�Ű�����3 : dlib�� ��Ƴ� ���� 68���� ��ġ����
*/
typedef struct pos {
	int x, y;
}pos;
pos rotate(int x, int y, int c, int w,double theta)
{
	pos p;
	double cR = cos(theta);
	double sR = sin(theta);
	p.x = (cR * (x - c) - sR * (y - w)) + c;
	p.y = (sR * (x - c) + cR * (y - w)) + w;
	return p;

}
void addPicture(Mat &base, Mat add, const dlib::full_object_detection& d)
{
	pos p;
	Mat reduce_result = changeSize(add, d);
	int middle = reduce_result.cols / 2;
	int first_rows;
	double theta = changeAngle(d);
	for (int i = 0; i < reduce_result.rows; i++)
		if (reduce_result.at<Vec3b>(i, middle)[0] != 255)
		{
			first_rows = i;
			break;
		}

	int mi_x = d.part(57).x();
	int mi_y = d.part(57).y();

	for (int i = 0; i < reduce_result.cols; i++)
		for (int j = 0; j < reduce_result.rows; j++)
		{
			if (reduce_result.at<Vec3b>(i, j)[0] == 255 && reduce_result.at<Vec3b>(i, j)[1] == 255 && reduce_result.at<Vec3b>(i, j)[2] == 255)
					continue;

			p =rotate(d.part(57).x() - middle + j, d.part(57).y() - first_rows + i, mi_x, mi_y, theta);
			base.at<Vec3b>(p.y,  p.x) = reduce_result.at<Vec3b>(i, j);
		}
}
//�󱼿� �����
void draw_polyline(cv::Mat &img, const dlib::full_object_detection& d, const int start, const int end, bool isClosed = false)
{
	std::vector <cv::Point> points;
	for (int i = start; i <= end; ++i)
	{
		points.push_back(cv::Point(d.part(i).x(), d.part(i).y()));
		circle(img, Point(d.part(i).x(), d.part(i).y()), 3, Scalar(255, 0, 0));
	}

	//cv::polylines(img, points, isClosed, cv::Scalar(255, 0, 0), 2, 16);

}


void mat_attr(Mat &input)
{
	cout << "���� �� = " << input.dims << endl;
	cout << "�� ���� = " << input.rows << endl;
	cout << "�� ���� = " << input.cols << endl;
	cout << "��� ũ�� = " << input.size() << endl;

	cout << "��ü ���� ���� = " << input.total() << endl;
	cout << "�� ������ ũ�� = " << input.elemSize() << endl;
	cout << "ä�δ� �� ������ ũ�� = " << input.elemSize1() << endl;

	cout << "Ÿ�� = " << input.type() << endl;
	cout << "Ÿ��(ä�� ��|����) = " << ((input.channels() - 1) << 3) + input.depth() << endl;
	cout << "���� = " << input.depth() << endl;
	cout << "ä�� = " << input.channels() << endl;

	cout << "step = " << input.step << endl;
	cout << "step1() = " << input.step1() << endl;


}

int main(void)
{

	VideoCapture capture;
	capture.open("C:/test.mov");
	if (!capture.isOpened());
	{
		cout << "��ķ�� ���� �����ϴ�." << endl;
		//return 1;
	}

	capture.set(CAP_PROP_FRAME_WIDTH, 600);
	capture.set(CAP_PROP_FRAME_HEIGHT, 800);

	Mat frame;
	namedWindow("input", 1);



	Mat beard = imread("C:/beard.png");
	//string filename = "C:/face_example.jpg";
	string dat = "C:/shape_predictor_68_face_landmarks.dat";
	//cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR);

	Mat reduce_result;
	resize(beard, reduce_result, Size(100, 100), 0, 0, CV_INTER_LINEAR);
	imshow("AAA", reduce_result);
	std::vector<full_object_detection> shapes;

	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor sp;
	deserialize(dat) >> sp;
	int cnt = 0;
	while (1)
	{
		cnt++;
		capture >> frame;
		//if (cnt % 2 == 0)
		//	continue;
		cv_image<bgr_pixel> cimg(frame);
		std::vector<dlib::rectangle> faces;
		faces = detector(cimg);

		for (unsigned long i = 0; i < faces.size(); i++)
		{
			full_object_detection shape = sp(cimg, faces[i]);
			shapes.push_back(shape);




			addPicture(frame, reduce_result, shape);
		}
		imshow("imput", frame);
		if (waitKey(1) == 27) break;
	}
	mat_attr(beard);
	//imshow("image", img);
	imshow("AAA", beard);
	waitKey(0);
}