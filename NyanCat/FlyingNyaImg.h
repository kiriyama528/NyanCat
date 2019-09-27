#pragma once

#include <opencv2/opencv.hpp>

#include "FlyingImg.h"
#include "struct.h"


/**
 * @brief NyanCatのための特別な動作をするFlyingImgクラス
 **/
class FlyingNyaImg : public FlyingImg {
protected:
	/**
	 * @brief 地面に落下しているか？
	 * @return (はい) true / false (いいえ)
	 **/
	bool isDrop();

	/**
	 * @brief 位置情報などの初期化
	 **/
	void Reset();

public:
	FlyingNyaImg();
	FlyingNyaImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname);
	FlyingNyaImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img);
	~FlyingNyaImg();

	/**
	 * @brief 地面に落下したものはパラメータをリセットしてから描く
	 **/
	void drawWithReset(cv::Mat &canvas);
	virtual void setRandParam(bool valid_pos, bool valid_rot, bool valid_vel, bool valid_rotate, bool valid_acc);
};