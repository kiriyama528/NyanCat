#pragma once


#include <opencv2/opencv.hpp>

#include "struct.h"
#include "Flying.h"


class FlyingImg : public Flying {
	cv::Mat img;  // 実態。同じ画像を複数のインスタンスで使いまわす場合は、ここはempty
	cv::Mat *img_shadow;  // 操作用

public:
	FlyingImg();
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname);
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img);
	~FlyingImg();
	bool loadImg(const char* imgname);
	bool setImgShadow(cv::Mat *_img);

	void draw(cv::Mat &canvas);


};


