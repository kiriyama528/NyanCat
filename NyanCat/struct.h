#pragma once

/**
 * @brief ��{�ƂȂ�\���̂��`
 **/

// fix me ���ꂼ��̕��������_�^��float��double�ɐ؂�ւ�����悤�� typedef ���邱��

// 1���[�g���͉��s�N�Z����
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