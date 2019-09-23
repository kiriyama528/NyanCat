#pragma once

/**
 * openCV のMatにアクセスするためのマクロなど
 **/


#define BLUE 0
#define GREEN 1
#define RED 2 
#define ALPHA 3

// 3チャンネル画素アクセスのマクロ
#define AT3(mat, r, c, bgra) mat.data[(r*mat.cols + c)*3 + bgra]
// 4チャンネル画素アクセスのマクロ。明示的にアクセスしたいときに利用
#define AT4(mat, r, c, bgra) mat.data[(r*mat.cols + c)*4 + bgra]

// mat のチャネル数を気にせずアクセスする
#define AT(mat, r, c, bgra) mat.data[(r*mat.cols + c)*mat.channels() + bgra]
