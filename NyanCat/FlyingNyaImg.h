#pragma once

#include <opencv2/opencv.hpp>

#include "FlyingImg.h"
#include "struct.h"


/**
 * @brief NyanCat�̂��߂̓��ʂȓ��������FlyingImg�N���X
 **/
class FlyingNyaImg : public FlyingImg {
protected:
	/**
	 * @brief �n�ʂɗ������Ă��邩�H
	 * @return (�͂�) true / false (������)
	 **/
	bool isDrop();

	/**
	 * @brief �ʒu���Ȃǂ̏�����
	 **/
	void Reset();

public:
	FlyingNyaImg();
	FlyingNyaImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname);
	FlyingNyaImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img);
	~FlyingNyaImg();

	/**
	 * @brief �n�ʂɗ����������̂̓p�����[�^�����Z�b�g���Ă���`��
	 **/
	void drawWithReset(cv::Mat &canvas);
	virtual void setRandParam(bool valid_pos, bool valid_rot, bool valid_vel, bool valid_rotate, bool valid_acc);
};