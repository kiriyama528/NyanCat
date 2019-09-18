#pragma once


#include <opencv2/opencv.hpp>

#include "struct.h"
#include "Flying.h"


class FlyingImg : public Flying {
	cv::Mat img;  // ���ԁB�����摜�𕡐��̃C���X�^���X�Ŏg���܂킷�ꍇ�́A������empty
	cv::Mat *img_shadow;  // ����p

public:
	FlyingImg();
	FlyingImg(Position _position, Velocity _velocity, Rotation _rotation, const char* imgname);
	FlyingImg(Position _position, Velocity _velocity, Rotation _rotation, cv::Mat *_img);
	~FlyingImg();
	bool loadImg(const char* imgname);
	bool setImgShadow(cv::Mat *_img);


};


