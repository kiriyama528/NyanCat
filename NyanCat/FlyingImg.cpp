
#include <opencv2/opencv.hpp>

#include "struct.h"
#include "FlyingImg.h"
#include "Flying.h"
#include "MatAccess.h"

#define DEBUG

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
	img_shadow = NULL;  // ”O‚Ì‚½‚ß
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
#ifdef DEBUG
	cv::Point2f center = cv::Point2f(
		static_cast<float>(img_shadow->cols / 2),
		static_cast<float>(img_shadow->rows / 2));

	cv::Mat affine;
	double SCALE = 1.0;  // fix me “KØ‚È”’l‚É‚·‚éB’è‹`‚·‚éêŠ‚à“KØ‚É
	// fix me 3ŽŸŒ³•ÏŠ·‚É‚·‚é‚±‚Æ
	cv::getRotationMatrix2D(center, rotation.z, SCALE).copyTo(affine);

	cv::Mat affine_img; // •ÏŒ`Œã‚Ì‰æ‘œ
	cv::warpAffine(*img_shadow, affine_img, affine, img_shadow->size(), cv::INTER_CUBIC);

	// canvas‚Ö‚Ì•`‰æ
	for (int r = 0; r < affine_img.rows; r++) {
		for (int c = 0; c < affine_img.cols; c++) {
			// ’†SÀ•WŒn
			/************/
			/*  making  */
			/************/

			// “\‚è•t‚¯æ‚Ìcanvas‚Ì‰æ‘f(x,y)‚ðŒvŽZ‚·‚é
			/************/
			/*  making  */
			/************/
			int x = ? ? ? ;
			int y = ? ? ? ;

			// canvas‚Ì”ÍˆÍ“à‚È‚ç‚Î
			if (0 <= x && x < canvas.cols && 0 <= y && y < canvas.rows) {
				// “§‰ß‰æ‘f‚Å‚È‚¯‚ê‚Î
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
