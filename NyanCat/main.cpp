/**
 * @brief NyanCat�̂悤�ɕ������΂�
 **/

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1�Ȃ̂�



#include <iostream>

#include <opencv2/opencv.hpp>
#include "FlyingImg.h"
#include "MatAccess.h"

#define N_OBJECTS 1
#define FPS 30

// Flying�I�u�W�F�N�g�̃p�����[�^�������_���ł͂Ȃ��蓮�ݒ�
#define DEBUG_PARAM

/**
 * @brief �����ݒ�B��΂��摜�̃I���W�i���̓ǂݍ��݂ƁAFlyingImg�ւ̉摜���蓖�āBFlying�����l�̐ݒ�
 * @param org_img �I���W�i���摜�Ƃ��ēǂݍ��񂾂���
 **/
bool init(FlyingImg *flying, const char *imgname, cv::Mat &org_img) {

	// fix me ���߉摜�̓ǂݍ��݃t���O�������Ŕ��ʂ�������
	//org_img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
	// ���`���l�����Ȃǂ��������f����t���O �炵��
	org_img = cv::imread(imgname, cv::IMREAD_ANYCOLOR);
	if (org_img.empty()) {
		fprintf(stderr, " ERROR : �摜�̓ǂݍ��݂Ɏ��s���܂����B\n");
		fprintf(stderr, "       file name : %s\n", imgname);
		return false;
	}

	/* memo
	{ // for debug
		cv::Mat alpha = cv::Mat::zeros(org_img.rows, org_img.cols, CV_8UC3);
		for (int y = 0; y < org_img.rows; ++y) {
			for (int x = 0; x < org_img.cols; ++x) {
				AT(alpha, y, x, 1) = AT(org_img, y, x, ALPHA);
			}
		}
		


		cv::imshow("aaa", org_img);  // for debug
		cv::imshow("alpha", alpha);  // for debug
		cv::waitKey();  // for debug
	}
	*/

	
	// Flying�I�u�W�F�N�g�̃p�����[�^�ݒ�
	for (int i = 0; i < N_OBJECTS; i++) {
#ifdef DEBUG_PARAM
		Position pos = { 0,0,0 };
		Rotation rotation = { 0,0,0 };
		Velocity vel = { 0,0,0 };
		Rotation rotate = { 0,0,180 };
		Acceleration acc_tmp = { 0,0,0 };
		// �^���ʁA�ω��ʂ̐ݒ�
		flying[i].setParam(pos, rotation, vel, rotate, acc_tmp);

#else
		flying[i].setRandParam(true, true, true, true, false);

#endif
		// �d�͉����x
		Acceleration acc = { 0.f, 0.f, 9.8f };
		flying[i].setAcceleration(acc);

		// �摜�̊��蓖��(�|�C���^)
		flying[i].setImgShadow(&org_img);
	}

	return true;
}


void showDisplay(const char *title, cv::Mat &img) {
	cv::namedWindow(title, cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);
	cv::imshow(title, img);
	
	// �����F�u�Ԓ�~���Ȃ��ƃE�B���h�E�ɕ`�悳��Ȃ�
	cv::waitKey(1);
}


/**
 * @brief �X�V���ꂽ�V�����f�B�X�v���C��`�悷��
 **/
void drawDisplay(cv::Mat &canvas, FlyingImg *flying) {	
	
	for (int i = 0; i < N_OBJECTS; i++) {
		// 1��1�̃I�u�W�F�N�g���L�����o�X�ɕ`��B
		// fix me ���s�������l���ĕ`�悷��
		flying[i].draw(canvas);
	}

}


int main(void) {
	FlyingImg *flying;
	flying = new FlyingImg[N_OBJECTS];
	
	const char* imgname = "white.png";
	cv::Mat org_img;
	if (!init(flying, imgname, org_img)) {
		fprintf(stderr, " ERROR > �摜�̓ǂݍ��݂Ɏ��s���܂���.\n");
		exit(1);
	}


	double spf = 1 / FPS; // seconds per frame
	clock_t old = clock();

	while (1) {
		clock_t now = clock();
		const double time = static_cast<double>(now - old) / CLOCKS_PER_SEC;
		//fprintf(stderr, "\r%lf(sec)", time);  // for debug ���sFPS�̕\��
		if (time < 1.0 / FPS) {
			// �\�肵��FPS�̍X�V���Ԃ�葁���̂ŁA���̂܂�
			continue;
		}

		// �`�揈��
		cv::Mat canvas = cv::Mat::zeros(1000, 1000, CV_8UC3);
		for (int i = 0; i < N_OBJECTS; i++) {
			flying[i].pass(time); 
		}
			   		 
		// �L�����o�X�ւ̕`��
		drawDisplay(canvas, flying);

		// �L�����o�X�̕\��
		showDisplay("canvas", canvas);

		// �`�掞���̍X�V
		old = now;
	}


	return 0;
}
