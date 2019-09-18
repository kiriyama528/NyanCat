/**
 * @brief NyanCatのように文字を飛ばす
 **/


#include <iostream>

#include <opencv2/opencv.hpp>

#include "FlyingImg.h"

#define N_OBJECTS 1000
#define FPS 30


bool init(FlyingImg *flying, const char *imgname) {
	cv::Mat org_img;
	if (org_img.open(imgname) == NULL) { // fix me メソッド名が違うかも。エラー時の返り値も違うかも
		return false;
	}

	for (int i = 0; i < N_OBJECTS; i++) {
		flying[i]->loadImg(&org_img);
	}

	return true;
}


/**
 * @brief 更新された新しいディスプレイを描画する
 **/
void drawDisplay(cv::Mat &canvas, FlyingImg *flying) {	

	for (int i = 0; i < N_OBJECTS; i++) {
		// 1つ1つのオブジェクトをキャンバスに描画。
		// fix me 奥行き情報を考えて描画する
		flying[i]->draw(canvas);
	}

}


int main(void) {
	FlyingImg *flying;
	flying = new FlyingImg[N_OBJECTS];
	
	const char* imgname = "Nya.png";
	if (!init(flying, imgname)) {
		fpirntf(stderr, " ERROR > 画像の読み込みに失敗しました.\n");
		exit(1);
	}

	double spf = 1 / FPS; // seconds per frame
	while (1) {
		cv::Mat canvas(xxxxxx);  // 縦横サイズを書け。最初は真っ白
		for (int i = 0; i < N_OBJECTS; i++) {
			flying[i]->pass(spf);
		}
			   		 
		// ディスプレイ表示
		drawDisplay(canvas, flying);

		// FPS調整。秒待ち関数
		wait(spf);
	}


	return 0;
}