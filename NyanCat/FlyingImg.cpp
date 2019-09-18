
#include <opencv2/opencv.hpp>

#include "struct.h"
#include "FlyingImg.h"
#include "Flying.h"

FlyingImg::FlyingImg() : Flying(){
	img_shadow = NULL;
}

FlyingImg::FlyingImg(Position _position, Velocity _velocity, Rotation _rotation, const char* imgname) : Flying(_position, _velocity, _rotation) {
	img = cv::imread(imgname);
	if (img.empty()) {
		fprintf(stderr, " ERROR：画像の読み込みに失敗しました。\n");
		return;
	}
	img_shadow = &img;

}

FlyingImg::FlyingImg(Position _position, Velocity _velocity, Rotation _rotation, cv::Mat *_img) : Flying(_position, _velocity, _rotation) {
	if (_img->empty()){
		fprintf(stderr, " ERROR：画像の読み込みに失敗しています。\n");
		return;
	}
	img_shadow = _img;

}

FlyingImg::~FlyingImg() {
	if (!img.empty()) {
		// 画像の開放。あれ？そんなメソッドなかったっけ？
		// making
	}

	img_shadow = NULL;  // 念のため
}

bool FlyingImg::loadImg(const char * imgname)
{
	// making
	return false;
}

bool FlyingImg::setImgShadow(cv::Mat * _img)
{
	//making
	return false;
}