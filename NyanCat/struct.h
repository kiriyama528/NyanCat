#pragma once

/**
 * @brief äÓñ{Ç∆Ç»ÇÈç\ë¢ëÃÇíËã`
 **/


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