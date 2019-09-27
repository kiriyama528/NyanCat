
#include <opencv2/opencv.hpp>

#include "struct.h"
#include "FlyingImg.h"
#include "Flying.h"
#include "MatAccess.h"

// 2�����`�惂�[�h�B�ȈՔłƂ��Ď���
#define DEBUG_2D_DRAW

// �ǂݍ��񂾉摜�̃`���l�������m�F�B�摜�̕ό`���ɎQ�� #ifdef
//#define DEBUG_CHANNEL


FlyingImg::FlyingImg() : Flying(){
	xyz_space = new Space(0.f, 0.f, 0.f, "c", "r", "d");
	img_shadow = NULL;
}

FlyingImg::FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname)
	: Flying(_position, _rotation, _velocity, _rotate, _acceleration) {
	loadImg(imgname);
	xyz_space = new Space(0.f, 0.f, 0.f, "c", "r", "d");
}

FlyingImg::FlyingImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img)
	: Flying(_position, _rotation, _velocity, _rotate, _acceleration) {
	setImgShadow(_img);
	xyz_space = new Space(0.f, 0.f, 0.f, "c", "r", "d");
}

FlyingImg::~FlyingImg() {
	img_shadow = NULL;  // �O�̂���
	delete xyz_space;
}

void FlyingImg::setSpace(float _origin_r, float _origin_c, float _origin_d, const char * x_axis, const char * y_axis, const char * z_axis) {
	delete xyz_space;
	xyz_space = new Space(_origin_r, _origin_c, _origin_d, x_axis, y_axis, z_axis);
}

bool FlyingImg::loadImg(const char * imgname)
{
	// 4�`�����l���摜��ǂݍ���
	img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
	if (img.empty() || img.channels() != 4) {
		return false;
	}

	img_shadow = &img;

	return true;

}

bool FlyingImg::setImgShadow(cv::Mat * _img)
{
	img_shadow = _img;
	if (_img->empty() || _img == NULL || _img->channels() != 4) {
		return false;
	}

	return true;
}

void FlyingImg::draw(cv::Mat &canvas)
{
#ifdef DEBUG_2D_DRAW
	// fix me 1�x�����쐬���ă����o�ϐ�����Q�Ƃ���悤�ɕύX����B�ݒ�^�C�~���O���l���Ȃ���΂Ȃ�Ȃ�
	Space space(canvas.rows, canvas.cols / 2, 0.f, "c", "-r", "d");
	cv::Point2f center = cv::Point2f(
		static_cast<float>(img_shadow->cols / 2),
		static_cast<float>(img_shadow->rows / 2));

	cv::Mat affine;
	double SCALE = 1.0;  // fix me �K�؂Ȑ��l�ɂ���B��`����ꏊ���K�؂�
	// fix me 3�����ϊ��ɂ��邱��
	cv::getRotationMatrix2D(center, rotation.z, SCALE).copyTo(affine);

	cv::Mat affine_img; // �ό`��̉摜

	// 4channel�摜�ł��邱�Ƃ�O��ɂ��Ă���
	cv::warpAffine(*img_shadow, affine_img, affine, img_shadow->size(), cv::INTER_CUBIC);

	/// canvas�ւ̕`��
	// �\��t�����canvas�̉�f(x,y)���v�Z����
	float pos_r, pos_c, pos_d;
	// fix me xyz_space->
	space.xyz2rcd(position, &pos_r, &pos_c, &pos_d);
	// fprintf(stderr, "\rpos_rcd:(%f, %f, %f)", pos_r, pos_c, pos_d); // for debug
	// canvas�ɉ摜��\��t����
	for (int r = 0; r < affine_img.rows; r++) {
		for (int c = 0; c < affine_img.cols; c++) {
			// ���S����̑��΍��W(affine_img)
			int rr = r - affine_img.rows/2;
			int cc = c - affine_img.cols/2;
			
			int dst_c = cc + pos_c;
			int dst_r = rr + pos_r;

			// canvas�͈͓̔��Ȃ��
			if (0 <= dst_c && dst_c < canvas.cols && 0 <= dst_r && dst_r < canvas.rows) {
				// ���߉�f�łȂ����
				if (AT4(affine_img, r, c, ALPHA) != 0) {
					AT(canvas, dst_r, dst_c, RED)   = AT(affine_img, r, c, RED);
					AT(canvas, dst_r, dst_c, GREEN) = AT(affine_img, r, c, GREEN);
					AT(canvas, dst_r, dst_c, BLUE)  = AT(affine_img, r, c, BLUE);
				}
			}


		}
	}

	
#else
	// 3������Ԃւ̕`��
	/**********/
	/* making */
	/**********/

#endif
}
