
#include <opencv2/opencv.hpp>

#include "struct.h"
#include "FlyingImg.h"
#include "Flying.h"

#define DEBUG

FlyingImg::FlyingImg() : Flying(){
	img_shadow = NULL;
}

FlyingImg::FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname)
	: Flying(_position, _rotation, _velocity, _rotate, _acceleration) {
	loadImg(imgname);
}

FlyingImg::FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img)
	: Flying(_position, _rotation, _velocity, _rotate, _acceleration) {
	setImgShadow(_img);
	cv::imshow("read", *img_shadow);  // for debug
	cv::waitKey();  // for debug
}

FlyingImg::~FlyingImg() {
	img_shadow = NULL;  // 念のため
}

bool FlyingImg::loadImg(const char * imgname)
{
	img = cv::imread(imgname);
	if (img.empty()) {
		return false;
	}

	img_shadow = &img;

	return true;

}

bool FlyingImg::setImgShadow(cv::Mat * _img)
{
	img_shadow = _img;
	if (_img->empty() || _img == NULL) {
		return false;
	}

	return true;
}

void FlyingImg::draw(cv::Mat &canvas)
{
#ifdef DEBUG
	cv::Point2f center = cv::Point2f(
		static_cast<float>(img_shadow->cols / 2),
		static_cast<float>(img_shadow->rows / 2));

	cv::Mat affine;
	double SCALE = 1.0;  // fix me 適切な数値にする。定義する場所も適切に
	// fix me 3次元変換にすること
	cv::getRotationMatrix2D(center, rotation.z, SCALE).copyTo(affine);

	cv::warpAffine(*img_shadow, canvas, affine, img_shadow->size(), cv::INTER_CUBIC);

	
#else


#endif
}
