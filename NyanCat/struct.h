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