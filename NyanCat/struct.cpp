#include <string.h>
#include <iostream>

#include "struct.h"

/**
 * @brief 基本となる構造体を定義
 **/

Space::Space(float _origin_r, float _origin_c, float _origin_d, const char * x_axis, const char * y_axis, const char * z_axis)
{
	origin_r = _origin_r;
	origin_c = _origin_c;
	origin_d = _origin_d;

	const char *axis_str_xyz[3] = { x_axis, y_axis, z_axis };
	for (int i = 0; i < 3; i++) {
		axis_xyz_p_n[i]= 1;

		// 軸方向が逆である
		if (*axis_str_xyz[i] == '-') {
			axis_xyz_p_n[i] = -1;
			axis_str_xyz[i]++;
		}

		switch (*axis_str_xyz[i]) {
		case 'r':
			axis_xyz[i] = ROW;
			axis_rcd[ROW] = (XYZ_IDX)i;
			axis_rcd_p_n[ROW] = axis_xyz_p_n[i];
			break;
		case 'c':
			axis_xyz[i] = COL;
			axis_rcd[COL] = (XYZ_IDX)i;
			axis_rcd_p_n[COL] = axis_xyz_p_n[i];
			break;
		case 'd':
			axis_xyz[i] = DEP;
			axis_rcd[DEP] = (XYZ_IDX)i;
			axis_rcd_p_n[DEP] = axis_xyz_p_n[i];
			break;
		default:
			fprintf(stderr, " ERROR: 軸の指定として予想外のものが指定されました。\n");
			fprintf(stderr, "        input : %s\n", axis_str_xyz[i]);
			exit(1);  // fix me 例外処理として過剰
			break;
		}
	}

}

void Space::xyz2rcd(Position xyz, float *r, float *c, float *d) {
	xyz2rcd(xyz.x, xyz.y, xyz.z, r, c, d);

}


void Space::xyz2rcd(float x, float y, float z, float *r, float *c, float *d)
{
	float xyz[3] = { x, y, z };
	float pos_r = axis_rcd_p_n[ROW] * xyz[axis_rcd[ROW]];
	float pos_c = axis_rcd_p_n[COL] * xyz[axis_rcd[COL]];
	float pos_d = axis_rcd_p_n[DEP] * xyz[axis_rcd[DEP]];
	*r = origin_r + pos_r;
	*c = origin_c + pos_c;
	*d = origin_d + pos_d;
}

Position Space::rcd2xyz(float r, float c, float d)
{
	float relative_rcd[3];
	relative_rcd[ROW] = r - origin_r;
	relative_rcd[COL] = c - origin_c;
	relative_rcd[DEP] = d - origin_d;

	float x = axis_xyz_p_n[X] * relative_rcd[axis_xyz[X]];
	float y = axis_xyz_p_n[Y] * relative_rcd[axis_xyz[Y]];
	float z = axis_xyz_p_n[Z] * relative_rcd[axis_xyz[Z]];

	return Position({x, y, z});
}
