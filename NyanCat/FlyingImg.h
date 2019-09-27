#pragma once


#include <opencv2/opencv.hpp>

#include "struct.h"
#include "Flying.h"


class FlyingImg : public Flying {
	cv::Mat img;  // ���ԁB�����摜�𕡐��̃C���X�^���X�Ŏg���܂킷�ꍇ�́A������empty
	cv::Mat *img_shadow;  // ����p
	Space *xyz_space; // fix me ���ݖ��g�p�B��ԕϊ��N���X

public:
	FlyingImg();
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname);
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img);
	~FlyingImg();

	/**
	 * @brief �摜���W�n��Position�Ȃǂ̋�ԍ��W�n�Ƃ̕ϊ��N���X��ݒ肷��
	 **/
	void setSpace(float _origin_r, float _origin_c, float _origin_d, const char * x_axis, const char * y_axis, const char * z_axis);

	/**
	 * @brief 4�`���l���摜��ǂݍ���
	 * @return (����) true / false (���s)
	 **/
	bool loadImg(const char* imgname);


	/**
	* @brief 4�`���l���摜�ւ̃|�C���^��ݒ肷��
	* @return (����) true / false (���s)
	**/
	bool setImgShadow(cv::Mat *_img);

	/**
	 * @brief canvas�֎p���̕ό`�����摜��`�悷��
	 **/
	void draw(cv::Mat &canvas);


};


