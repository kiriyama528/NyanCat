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
#include "MatAccess.h"

#define N_OBJECTS 1
#define FPS 30

// Flyingオブジェクトのパラメータをランダムではなく手動設定
#define DEBUG_PARAM

/**
 * @brief 初期設定。飛ばす画像のオリジナルの読み込みと、FlyingImgへの画像割り当て。Flying初期値の設定
 * @param org_img オリジナル画像として読み込んだもの
 **/
bool init(FlyingImg *flying, const char *imgname, cv::Mat &org_img) {

	// fix me 透過画像の読み込みフラグを自動で判別させたい
	//org_img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
	// ↓チャネル数などを自動判断するフラグ らしい
	org_img = cv::imread(imgname, cv::IMREAD_ANYCOLOR);
	if (org_img.empty()) {
		fprintf(stderr, " ERROR : 画像の読み込みに失敗しました。\n");
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

	
	// Flyingオブジェクトのパラメータ設定
	for (int i = 0; i < N_OBJECTS; i++) {
#ifdef DEBUG_PARAM
		Position pos = { 0,0,0 };
		Rotation rotation = { 0,0,0 };
		Velocity vel = { 0,0,0 };
		Rotation rotate = { 0,0,180 };
		Acceleration acc_tmp = { 0,0,0 };
		// 運動量、変化量の設定
		flying[i].setParam(pos, rotation, vel, rotate, acc_tmp);

#else
		flying[i].setRandParam(true, true, true, true, false);

#endif
		// 重力加速度
		Acceleration acc = { 0.f, 0.f, 9.8f };
		flying[i].setAcceleration(acc);

		// 画像の割り当て(ポインタ)
		flying[i].setImgShadow(&org_img);
	}

	return true;
}


void showDisplay(const char *title, cv::Mat &img) {
	cv::namedWindow(title, cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);
	cv::imshow(title, img);
	
	// メモ：瞬間停止しないとウィンドウに描画されない
	cv::waitKey(1);
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
	
	const char* imgname = "white.png";
	cv::Mat org_img;
	if (!init(flying, imgname, org_img)) {
		fprintf(stderr, " ERROR > 画像の読み込みに失敗しました.\n");
		exit(1);
	}


	double spf = 1 / FPS; // seconds per frame
	clock_t old = clock();

	while (1) {
		clock_t now = clock();
		const double time = static_cast<double>(now - old) / CLOCKS_PER_SEC;
		//fprintf(stderr, "\r%lf(sec)", time);  // for debug 実行FPSの表示
		if (time < 1.0 / FPS) {
			// 予定したFPSの更新時間より早いので、そのまま
			continue;
		}

		// 描画処理
		cv::Mat canvas = cv::Mat::zeros(1000, 1000, CV_8UC3);
		for (int i = 0; i < N_OBJECTS; i++) {
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
