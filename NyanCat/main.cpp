/**
 * @brief NyanCatのように文字を飛ばす
 **/

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world411" CV_EXT) // OpenCV4.1.1なので



#include <iostream>

#include <opencv2/opencv.hpp>
#include "FlyingImg.h"

#define N_OBJECTS 10
#define FPS 30

/**
 * @brief 初期設定。飛ばす画像のオリジナルの読み込みと、FlyingImgへの画像割り当て。
 * @param org_img オリジナル画像として読み込んだもの
 **/
bool init(FlyingImg *flying, const char *imgname, cv::Mat &org_img) {

	// fix me 透過画像の読み込みフラグを自動で判別させたい
	org_img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
	// ↓チャネル数などを自動判断するフラグ らしい
	//org_img = cv::imread(imgname, cv::IMREAD_ANYCOLOR);
	if (org_img.empty()) {
		fprintf(stderr, " ERROR : 画像の読み込みに失敗しました。\n");
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
 * @brief 更新された新しいディスプレイを描画する
 **/
void drawDisplay(cv::Mat &canvas, FlyingImg *flying) {	
	
	for (int i = 0; i < N_OBJECTS; i++) {
		// 1つ1つのオブジェクトをキャンバスに描画。
		// fix me 奥行き情報を考えて描画する
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
		fprintf(stderr, " ERROR > 画像の読み込みに失敗しました.\n");
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
			// 予定したFPSよりも早いのでそのまま
			continue;
		}

		// 描画処理
		cv::Mat canvas = cv::Mat::zeros(1000, 1000, CV_8UC3);
		for (int i = 0; i < N_OBJECTS; i++) {
			//flying[i].pass(spf);
			// 上と同義
			// fix me 時間の単位が違う可能性がある。msとsecondsとか
			flying[i].pass(time); 
		}
			   		 
		// キャンバスへの描画
		drawDisplay(canvas, flying);

		// キャンバスの表示
		showDisplay("canvas", canvas);

		// 描画時刻の更新
		old = now;
	}


	return 0;
}
