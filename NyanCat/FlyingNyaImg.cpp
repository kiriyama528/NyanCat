#include "FlyingNyaImg.h"


bool FlyingNyaImg::isDrop()
{
	return (position.y <= 0);
}

void FlyingNyaImg::Reset()
{
	setRandParam(true, true, true, true, true);
}

FlyingNyaImg::FlyingNyaImg() : FlyingImg(){
	// do nothing
}

FlyingNyaImg::FlyingNyaImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, const char* imgname)
	: FlyingImg(_position, _rotation, _velocity, _rotate, _acceleration, imgname) {
	// do nothing
}

FlyingNyaImg::FlyingNyaImg(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration, cv::Mat *_img)
	: FlyingImg(_position, _rotation, _velocity, _rotate, _acceleration, _img) {
	// do nothing
}

FlyingNyaImg::~FlyingNyaImg()
{
	// do nothing
}

void FlyingNyaImg::drawWithReset(cv::Mat &canvas)
{
	if (isDrop()) {
		Reset();
	}
	draw(canvas);
}

void FlyingNyaImg::setRandParam(bool valid_pos, bool valid_rot, bool valid_vel, bool valid_rotate, bool valid_acc)
{
	float random[3 * 5];
	for (int i = 0; i < 3 * 5; i++) {
		random[i] = std::rand();
	}

	Position pos = { random[0], random[1], random[2] };
	Rotation rot = { random[3], random[4], random[5] };
	Velocity vel = { random[6], random[7], random[8] };
	Rotation rota = { random[9], random[10], random[11] };
	Acceleration acc = { random[12], random[13], random[14] };

	// 値を範囲内へ
	pos.x = (int)pos.x % 101 - 50;
	pos.y = 1; // 同じ高さ位置から発射する
	pos.z = (int)pos.z % 101 - 50;

	rot.x = (int)rot.x % 61 - 30;
	rot.y = (int)rot.y % 61 - 30;
	rot.z = (int)rot.z % 61 - 30;

	vel.x = (int)vel.x % 11 - 5;
	vel.y = (int)vel.y % 11 - 5 + 30; // 中央値を30に調整
	vel.z = (int)vel.z % 11 - 5;

	rota.x = (int)rota.x % 181 - 90;
	rota.y = (int)rota.y % 181 - 90;
	rota.z = (int)rota.z % 181 - 90;

	// 決めうち。重力加速度のみ
	acc.x = 0.f;
	acc.y = -9.8f;
	acc.z = 0.f;

	if (valid_pos) {
		position = pos;
	}
	if (valid_rot) {
		rotation = rot;
	}
	if (valid_vel) {
		velocity = vel;
	}
	if (valid_rotate) {
		rotate = rota;
	}
	if (valid_acc) {
		acceleration = acc;
	}
	
	//fprintf(stderr, "pos = {%lf, %lf, %lf}, rotation = {%lf, %lf, %lf}, vel = {%lf, %lf, %lf}\n", position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, velocity.x, velocity.y, velocity.z);  // for debug
}