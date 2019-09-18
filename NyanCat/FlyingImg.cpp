
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
		fprintf(stderr, " ERROR�F�摜�̓ǂݍ��݂Ɏ��s���܂����B\n");
		return;
	}
	img_shadow = &img;

}

FlyingImg::FlyingImg(Position _position, Velocity _velocity, Rotation _rotation, cv::Mat *_img) : Flying(_position, _velocity, _rotation) {
	if (_img->empty()){
		fprintf(stderr, " ERROR�F�摜�̓ǂݍ��݂Ɏ��s���Ă��܂��B\n");
		return;
	}
	img_shadow = _img;

}

FlyingImg::~FlyingImg() {
	if (!img.empty()) {
		// �摜�̊J���B����H����ȃ��\�b�h�Ȃ����������H
		// making
	}

	img_shadow = NULL;  // �O�̂���
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