#pragma once

/**
 * openCV ��Mat�ɃA�N�Z�X���邽�߂̃}�N���Ȃ�
 **/


#define BLUE 0
#define GREEN 1
#define RED 2 
#define ALPHA 3

// 3�`�����l����f�A�N�Z�X�̃}�N��
#define AT3(mat, r, c, bgra) mat.data[(r*mat.cols + c)*3 + bgra]
// 4�`�����l����f�A�N�Z�X�̃}�N���B�����I�ɃA�N�Z�X�������Ƃ��ɗ��p
#define AT4(mat, r, c, bgra) mat.data[(r*mat.cols + c)*4 + bgra]

// mat �̃`���l�������C�ɂ����A�N�Z�X����
#define AT(mat, r, c, bgra) mat.data[(r*mat.cols + c)*mat.channels() + bgra]
