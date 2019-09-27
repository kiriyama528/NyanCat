#pragma once


#include <opencv2/opencv.hpp>

#include "struct.h"
#include "Flying.h"


class FlyingImg : public Flying {
	cv::Mat img;  // 実態。同じ画像を複数のインスタンスで使いまわす場合は、ここはempty
	cv::Mat *img_shadow;  // 操作用
	Space *xyz_space; // fix me 現在未使用。空間変換クラス

public:
	FlyingImg();
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname);
	FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img);
	~FlyingImg();

	/**
	 * @brief 画像座標系とPositionなどの空間座標系との変換クラスを設定する
	 **/
	void setSpace(float _origin_r, float _origin_c, float _origin_d, const char * x_axis, const char * y_axis, const char * z_axis);

	/**
	 * @brief 4チャネル画像を読み込む
	 * @return (成功) true / false (失敗)
	 **/
	bool loadImg(const char* imgname);


	/**
	* @brief 4チャネル画像へのポインタを設定する
	* @return (成功) true / false (失敗)
	**/
	bool setImgShadow(cv::Mat *_img);

	/**
	 * @brief canvasへ姿勢の変形した画像を描画する
	 **/
	void draw(cv::Mat &canvas);


};


