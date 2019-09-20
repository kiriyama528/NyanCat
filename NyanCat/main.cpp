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

#define N_OBJECTS 10
#define FPS 30

/**
 * @brief �����ݒ�B��΂��摜�̃I���W�i���̓ǂݍ��݂ƁAFlyingImg�ւ̉摜���蓖�āB
 * @param org_img �I���W�i���摜�Ƃ��ēǂݍ��񂾂���
 **/
bool init(FlyingImg *flying, const char *imgname, cv::Mat &org_img) {

	// fix me ���߉摜�̓ǂݍ��݃t���O�������Ŕ��ʂ�������
	org_img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
	// ���`���l�����Ȃǂ��������f����t���O �炵��
	//org_img = cv::imread(imgname, cv::IMREAD_ANYCOLOR);
	if (org_img.empty()) {
		fprintf(stderr, " ERROR : �摜�̓ǂݍ��݂Ɏ��s���܂����B\n");
		fprintf(stderr, "       file name : %s\n", imgname);
		return false;
	}

	{ // for debug
		for (int y = 0; y < org_img.rows; ++y) {
			for (int x = 0; x < org_img.cols; ++x) {
				cv::Vec4b px = org_img.at<cv::Vec4b>(x, y);
				
				px[3] = 1;
				org_img.at<cv::Vec4b>(x, y) = px;
				
			}
		}
		

		cv::imshow("aaa", org_img);  // for debug
		cv::waitKey();  // for debug
	}

	for (int i = 0; i < N_OBJECTS; i++) {
		flying[i].setImgShadow(&org_img);
	}

	return true;
}


void showDisplay(const char *title, cv::Mat &img) {
	cv::namedWindow(title, cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);
	cv::imshow(title, img);
	cv::waitKey();
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
	
	const char* imgname = "pop.png";
	//const char* imgname = "spy.png"; // for debug
	cv::Mat org_img;
	if (!init(flying, imgname, org_img)) {
		fprintf(stderr, " ERROR > �摜�̓ǂݍ��݂Ɏ��s���܂���.\n");
		exit(1);
	}


	double spf = 1 / FPS; // seconds per frame
	clock_t old = clock();

	while (1) {
		clock_t now = clock();
		const double time = static_cast<double>(now - old) / CLOCKS_PER_SEC * 1000.0;
		fprintf(stderr, "\r%lf", time);  // for debug
		//if (time < 1 / FPS) {
		if (time < 2000) { // for debug
			// �\�肵��FPS���������̂ł��̂܂�
			continue;
		}

		// �`�揈��
		cv::Mat canvas = cv::Mat::zeros(1000, 1000, CV_8UC3);
		for (int i = 0; i < N_OBJECTS; i++) {
			//flying[i].pass(spf);
			// ��Ɠ��`
			// fix me ���Ԃ̒P�ʂ��Ⴄ�\��������Bms��seconds�Ƃ�
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
