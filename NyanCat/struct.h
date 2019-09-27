#pragma once

/**
 * @brief 基本となる構造体を定義
 **/

// fix me それぞれの浮動小数点型をfloatやdoubleに切り替えられるように typedef すること

// 1メートルは何ピクセルか
#define PIXELS_PER_METER 10




struct Velocity {
	float x, y, z;

	Velocity operator + (Velocity obj) {
		return Velocity({ x + obj.x, y + obj.y, z + obj.z });
	}

	Velocity operator + (float val) {
		return Velocity({ x + val, y + val, z + val });
	}

	Velocity operator - (Velocity obj) {
		return Velocity({ x - obj.x, y - obj.y, z - obj.z });
	}

	Velocity operator - (float val) {
		return Velocity({ x - val, y - val, z - val });
	}

	Velocity operator / (float val) {
		return Velocity({ x / val, y / val, z / val });
	}

	Velocity operator * (float val) {
		return Velocity({ x * val, y * val, z * val });
	}
		
};


struct Rotation {
	float x, y, z;

	Rotation operator + (Rotation obj) {
		return Rotation({ x + obj.x, y + obj.y, z + obj.z });
	}

	Rotation operator - (Rotation obj) {
		return Rotation({ x - obj.x, y - obj.y, z - obj.z });
	}

	Rotation operator * (float f) {
		return Rotation({ x*f, y*f, z*f });
	}

	Rotation operator * (double d) {
		return Rotation({ (float)(x*d), (float)(y*d), (float)(z*d) });
	}

	Rotation operator / (float f) {
		return (*this) * (1/f);
	}

	Rotation operator / (double d) {
		return (*this) * (1/d);
	}
};

struct Position {
	float x, y, z;
	
	Position operator + (Position obj) {
		return Position({ x + obj.x, y + obj.y, z + obj.z });
	}

	Position operator - (Position obj) {
		return Position({ x - obj.x, y - obj.y, z - obj.z });
	}
};

struct Acceleration {
	float x, y, z;

	Acceleration operator + (Acceleration obj) {
		return Acceleration({ x + obj.x, y + obj.y, z + obj.z });
	}

	Acceleration operator - (Acceleration obj) {
		return Acceleration({ x - obj.x, y - obj.y, z - obj.z });
	}
};


// fix me 行列演算に変えたほうがわかりやすい。
class Space {
protected:
	// rcdの数値を受け取る場合、row, col, depth に必ず並んでいるとする
	typedef enum {
		ROW = 0,
		COL = 1,
		DEP = 2  // depth
	} RCD_IDX;

	typedef enum {
		X = 0,
		Y = 1,
		Z = 2  // depth
	} XYZ_IDX;

	float origin_r;
	float origin_c;
	float origin_d;

	// [XYZ_IDX] -> RCD_IDX
	RCD_IDX axis_xyz[3];

	// この空間の正負の方向を示す。正なら1、負なら-1
	// 正はrcdと同じ軸方向を意味する
	int axis_xyz_p_n[3];

	// [RCD_IDX] -> XYZ_IDX
	XYZ_IDX axis_rcd[3];
	int axis_rcd_p_n[3];

public:
	
	Space(float _origin_r, float _origin_c, float _origin_d, const char *_x_axis, const char* _y_axis, const char* _z_axis);

	/**
	* @brief この空間の座標XYZをrcd(row, col, depth) に変換する
	* @param xyz <IN>空間座標XYZ
	* @param r <OUT>行番号
	* @param c <OUT>列番号
	* @param d <OUT>奥行きの配列番号
	**/
	void xyz2rcd(Position xyz, float *r, float *c, float *d);

	void xyz2rcd(float x, float y, float z, float * r, float * c, float * d);

	/**
	* @brief rcd(row, col, depth) をこの空間の座標XYZに変換する
	* @param xyz <IN>空間座標XYZ
	* @param r <OUT>行番号
	* @param c <OUT>列番号
	* @param d <OUT>奥行きの配列番号
	**/
	Position rcd2xyz(float r, float c, float d);

};