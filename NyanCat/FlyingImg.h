#pragma once


#include <opencv2/opencv.hpp>

#include "struct.h"
#include "Flying.h"


class FlyingImg : public Flying {
	cv::Mat img;  // ���ԁB�����摜�𕡐��̃C���X�^���X�Ŏg���܂킷�ꍇ�́A������empty
	cv::Mat *img_shadow;  // ����p

public:
	FlyingImg();
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname);
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img);
	~FlyingImg();
	bool loadImg(const char* imgname);
	bool setImgShadow(cv::Mat *_img);

	void draw(cv::Mat &canvas);


};


