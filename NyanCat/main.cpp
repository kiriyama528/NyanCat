/**
 * @brief NyanCat�̂悤�ɕ������΂�
 **/


#include <iostream>

#include <opencv2/opencv.hpp>

#include "FlyingImg.h"

#define N_OBJECTS 1000
#define FPS 30


bool init(FlyingImg *flying, const char *imgname) {
	cv::Mat org_img;
	if (org_img.open(imgname) == NULL) { // fix me ���\�b�h�����Ⴄ�����B�G���[���̕Ԃ�l���Ⴄ����
		return false;
	}

	for (int i = 0; i < N_OBJECTS; i++) {
		flying[i]->loadImg(&org_img);
	}

	return true;
}


/**
 * @brief �X�V���ꂽ�V�����f�B�X�v���C��`�悷��
 **/
void drawDisplay(cv::Mat &canvas, FlyingImg *flying) {	

	for (int i = 0; i < N_OBJECTS; i++) {
		// 1��1�̃I�u�W�F�N�g���L�����o�X�ɕ`��B
		// fix me ���s�������l���ĕ`�悷��
		flying[i]->draw(canvas);
	}

}


int main(void) {
	FlyingImg *flying;
	flying = new FlyingImg[N_OBJECTS];
	
	const char* imgname = "Nya.png";
	if (!init(flying, imgname)) {
		fpirntf(stderr, " ERROR > �摜�̓ǂݍ��݂Ɏ��s���܂���.\n");
		exit(1);
	}

	double spf = 1 / FPS; // seconds per frame
	while (1) {
		cv::Mat canvas(xxxxxx);  // �c���T�C�Y�������B�ŏ��͐^����
		for (int i = 0; i < N_OBJECTS; i++) {
			flying[i]->pass(spf);
		}
			   		 
		// �f�B�X�v���C�\��
		drawDisplay(canvas, flying);

		// FPS�����B�b�҂��֐�
		wait(spf);
	}


	return 0;
}