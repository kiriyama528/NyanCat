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
#include "FlyingNyaImg.h"
#include "MatAccess.h"

#define N_OBJECTS 10
#define FPS 30

// 時間の経過速度を X倍する。default : 1.0
#define TIME_RATE 2.0

// Flyingオブジェクトのパラメータをランダムではなく手動設定
//#define DEBUG_PARAM

// imreadを読み込み対象に合わせてチャネル数を指定しなくてもよいようにしたい。
// init() で#ifdef
//#define IMREAD_FLAG_TEST

/**
 * @brief 初期設定。飛ばす画像のオリジナルの読み込みと、FlyingImgへの画像割り当て。Flying初期値の設定
 * @param org_img オリジナル画像として読み込んだもの
 **/
bool init(FlyingNyaImg *flying, const char *imgname, cv::Mat &org_img) {
	std::srand(std::time(NULL));

#ifdef IMREAD_FLAG_TEST
	// 透過画像の読み込みフラグを自動で判別させたい
	// ↓チャネル数などを自動判断するフラグ らしい。
	// 失敗。3チャンネルで読み込まれていた。
	//org_img = cv::imread(imgname, cv::IMREAD_ANYCOLOR);
#else
	// 4チャンネル画像の読み込み
	org_img = cv::imread(imgname, cv::IMREAD_UNCHANGED);
#endif
	
	if (org_img.empty()) {
		fprintf(stderr, " ERROR : 画像の読み込みに失敗しました。\n");
		fprintf(stderr, "       file name : %s\n", imgname);
		return false;
	}

	// Flyingオブジェクトのパラメータ設定
	for (int i = 0; i < N_OBJECTS; i++) {
#ifdef DEBUG_PARAM
		Position pos = { 0,0,0 };			// 位置。中心が0,0,0
		Rotation rotation = { 0,0,0 };		// 角度。
		Velocity vel = { 0, 30,0 };			// 移動速度
		Rotation rotate = { 0,0,180 };		// 回転角度 / 秒
		Acceleration acc_tmp = { 0,0,0 };	// 加速度 / 秒
		// 運動量、変化量の設定
		flying[i].setParam(pos, rotation, vel, rotate, acc_tmp);

#else
		flying[i].setRandParam(true, true, true, true, true);

#endif
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
void drawDisplay(cv::Mat &canvas, FlyingNyaImg *flying) {	
	
	for (int i = 0; i < N_OBJECTS; i++) {
		// 1つ1つのオブジェクトをキャンバスに描画。
		// fix me 奥行き情報を考えて描画する
		flying[i].drawWithReset(canvas);
	}

}


int main(void) {
	FlyingNyaImg *flying;
	flying = new FlyingNyaImg[N_OBJECTS];
	
	const char* imgname = "white.png";
	cv::Mat org_img;
	if (!init(flying, imgname, org_img)) {
		fprintf(stderr, " ERROR > 画像の読み込みに失敗しました.\n");
		exit(1);
	}


	clock_t old = clock();

	while (1) {
		clock_t now = clock();
		const double time = static_cast<double>(now - old) / CLOCKS_PER_SEC * TIME_RATE;
		//fprintf(stderr, "\r%lf(sec)", time);  // for debug 実行FPSの表示
		if (time < 1.0 / FPS) {
			// 予定したFPSの更新時間より早いので、そのまま
			continue;
		}

		// 描画するキャンバスの作成
		cv::Mat canvas = cv::Mat::zeros(500, 500, CV_8UC3);

		// 時間経過による移動
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

	// 終了処理
	delete[] flying;

	return 0;
}
