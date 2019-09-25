
#include <opencv2/opencv.hpp>

#include "struct.h"
#include "FlyingImg.h"
#include "Flying.h"
#include "MatAccess.h"

// 2次元描画モード。簡易版として実装
#define DEBUG_2D_DRAW

// 読み込んだ画像のチャネル数を確認。画像の変形時に参照 #ifdef
//#define DEBUG_CHANNEL


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
#ifdef DEBUG_2D_DRAW
	cv::Point2f center = cv::Point2f(
		static_cast<float>(img_shadow->cols / 2),
		static_cast<float>(img_shadow->rows / 2));

	cv::Mat affine;
	double SCALE = 1.0;  // fix me 適切な数値にする。定義する場所も適切に
	// fix me 3次元変換にすること
	cv::getRotationMatrix2D(center, rotation.z, SCALE).copyTo(affine);

	cv::Mat affine_img; // 変形後の画像
#ifdef DEBUG_CHANNEL
	affine_img = img_shadow->clone();
	fprintf(stderr, "channels:%d\n", img_shadow->channels());  // for debug
	getchar(); // for debug

#else
	// 4channel画像であることが前提に
	cv::warpAffine(*img_shadow, affine_img, affine, img_shadow->size(), cv::INTER_CUBIC);
	
#endif

	/// canvasへの描画
	// 中心からの相対座標(canvas)
	int center_y = canvas.rows / 2;
	int center_x = canvas.cols / 2;
	for (int r = 0; r < affine_img.rows; r++) {
		for (int c = 0; c < affine_img.cols; c++) {
			// 中心からの相対座標(affine_img)
			int rr = r - affine_img.rows/2;
			int cc = c - affine_img.cols/2;
			
			// 貼り付け先のcanvasの画素(x,y)を計算する
			int x = center_x + cc + position.x;
			int y = center_y + rr - position.y;

			// canvasの範囲内ならば
			if (0 <= x && x < canvas.cols && 0 <= y && y < canvas.rows) {
				// 透過画素でなければ
				if (AT4(affine_img, r, c, ALPHA) != 0) {
					AT(canvas, y, x, RED) = AT(affine_img, r, c, RED);
					AT(canvas, y, x, GREEN) = AT(affine_img, r, c, GREEN);
					AT(canvas, y, x, BLUE) = AT(affine_img, r, c, BLUE);
				}
			}


		}
	}

	
#else


#endif
}
