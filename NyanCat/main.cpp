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
#include "FlyingNyaImg.h"
#include "MatAccess.h"

#define N_OBJECTS 10
#define FPS 30

// ���Ԃ̌o�ߑ��x�� X�{����Bdefault : 1.0
#define TIME_RATE 2.0

// Flying�I�u�W�F�N�g�̃p�����[�^�������_���ł͂Ȃ��蓮�ݒ�
//#define DEBUG_PARAM

// imread��ǂݍ��ݑΏۂɍ��킹�ă`���l�������w�肵�Ȃ��Ă��悢�悤�ɂ������B
// init() ��#ifdef
//#define IMREAD_FLAG_TEST

/**
 * @brief �����ݒ�B��΂��摜�̃I���W�i���̓ǂݍ��݂ƁAFlyingImg�ւ̉摜���蓖�āBFlying�����l�̐ݒ�
 * @param org_img �I���W�i���摜�Ƃ��ēǂݍ��񂾂���
 **/
bool init(FlyingNyaImg *flying, const char *imgname, cv::Mat &org_img) {
	std::srand(std::time(NULL));

#ifdef IMREAD_FLAG_TEST
	// ���߉摜�̓ǂݍ��݃t���O�������Ŕ��ʂ�������
	// ���`���l�����Ȃǂ��������f����t���O �炵���B
	// ���s�B3�`�����l���œǂݍ��܂�Ă����B
	//org_img = cv::imread(imgname, cv::IMREAD_ANYCOLOR);
#else
	// 4�`�����l���摜�̓ǂݍ���
	org_img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
#endif
	
	if (org_img.empty()) {
		fprintf(stderr, " ERROR : �摜�̓ǂݍ��݂Ɏ��s���܂����B\n");
		fprintf(stderr, "       file name : %s\n", imgname);
		return false;
	}

	// Flying�I�u�W�F�N�g�̃p�����[�^�ݒ�
	for (int i = 0; i < N_OBJECTS; i++) {
#ifdef DEBUG_PARAM
		Position pos = { 0,0,0 };			// �ʒu�B���S��0,0,0
		Rotation rotation = { 0,0,0 };		// �p�x�B
		Velocity vel = { 0, 30,0 };			// �ړ����x
		Rotation rotate = { 0,0,180 };		// ��]�p�x / �b
		Acceleration acc_tmp = { 0,0,0 };	// �����x / �b
		// �^���ʁA�ω��ʂ̐ݒ�
		flying[i].setParam(pos, rotation, vel, rotate, acc_tmp);

#else
		flying[i].setRandParam(true, true, true, true, true);

#endif
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
void drawDisplay(cv::Mat &canvas, FlyingNyaImg *flying) {	
	
	for (int i = 0; i < N_OBJECTS; i++) {
		// 1��1�̃I�u�W�F�N�g���L�����o�X�ɕ`��B
		// fix me ���s�������l���ĕ`�悷��
		flying[i].drawWithReset(canvas);
	}

}


int main(void) {
	FlyingNyaImg *flying;
	flying = new FlyingNyaImg[N_OBJECTS];
	
	const char* imgname = "white.png";
	cv::Mat org_img;
	if (!init(flying, imgname, org_img)) {
		fprintf(stderr, " ERROR > �摜�̓ǂݍ��݂Ɏ��s���܂���.\n");
		exit(1);
	}


	clock_t old = clock();

	while (1) {
		clock_t now = clock();
		const double time = static_cast<double>(now - old) / CLOCKS_PER_SEC * TIME_RATE;
		//fprintf(stderr, "\r%lf(sec)", time);  // for debug ���sFPS�̕\��
		if (time < 1.0 / FPS) {
			// �\�肵��FPS�̍X�V���Ԃ�葁���̂ŁA���̂܂�
			continue;
		}

		// �`�悷��L�����o�X�̍쐬
		cv::Mat canvas = cv::Mat::zeros(500, 500, CV_8UC3);

		// ���Ԍo�߂ɂ��ړ�
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

	// �I������
	delete[] flying;

	return 0;
}
