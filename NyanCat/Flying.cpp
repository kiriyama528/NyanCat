/**
* @brief 飛行物体のクラス
* @date 2019/09/17
* @author kiriyama tomoya
**/

#include <random>
#include <time.h>

#include "struct.h"
#include "Flying.h"

Flying::Flying()
{
	position = { 0.f, 0.f, 0.f };
	rotation = { 0.f, 0.f, 0.f };
	velocity = { 0.f, 0.f, 0.f };
	rotate = { 0.f, 0.f, 0.f };
	acceleration = { 0.f, 0.f, 0.f };
}

Flying::Flying(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration)
{
	setParam(_position, _rotation, _velocity, _rotate, _acceleration);
}

Flying::~Flying()
{
	// do nothing
}

void Flying::setParam(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration)
{
	position = _position;
	rotation = _rotation;
	velocity = _velocity;
	rotate = _rotate;
	acceleration = _acceleration;
}

void Flying::setRandParam(bool valid_pos, bool valid_rot, bool valid_vel, bool valid_rotate, bool valid_acc)
{
	std::srand((unsigned int)time(NULL));
	float random[3 * 5];
	for (int i = 0; i < 3 * 5; i++) {
		// パラメータの幅は調整すること
		random[i] = std::rand();
	}

	Position pos = { random[0], random[1], random[2] };
	Rotation rot = { random[3], random[4], random[5] };
	Velocity vel = { random[6], random[7], random[8] };
	Rotation rotate = { random[9], random[10], random[11] };
	Acceleration acc = { random[12], random[13], random[14] };

	// 値を範囲内に丸める fix me 値調整
	pos.x = (int)pos.x % 11 - 5;
	pos.y = (int)pos.y % 11 - 5;
	pos.z = (int)pos.z % 11 - 5;

	rot.x = (int)rot.x % 11 - 5;
	rot.y = (int)rot.y % 11 - 5;
	rot.z = (int)rot.z % 11 - 5;

	vel.x = (int)vel.x % 11 - 5;
	vel.y = (int)vel.y % 11 - 5;
	vel.z = (int)vel.z % 11 - 5;

	vel.x = (int)vel.x % 11 - 5;
	vel.y = (int)vel.y % 11 - 5;
	vel.z = (int)vel.z % 11 - 5;

	acc.x = (int)acc.x % 5 - 3;
	acc.y = (int)acc.y % 5 - 3;
	acc.z = (int)acc.z % 5 - 3;

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
		rotate = rotate;
	}
	if (valid_acc) {
		acceleration = acc;
	}
}

void Flying::pass(double seconds)
{
	// fprintf(stderr, "\rpos = {%lf, %lf, %lf}, rotation = {%lf, %lf, %lf}, vel = {%lf, %lf, %lf}", position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, velocity.x, velocity.y, velocity.z);  // for debug
	// fprintf(stderr, "\r seconds:%lf", seconds); // for debug
	
	// ピクセル換算した位置
	position.x += (velocity.x + acceleration.x/2) * PIXELS_PER_METER * seconds;
	position.y += (velocity.y + acceleration.y/2) * PIXELS_PER_METER * seconds;
	position.z += (velocity.z + acceleration.z/2) * PIXELS_PER_METER * seconds;

	rotation = rotation + rotate * seconds;

	velocity.x += acceleration.x * seconds;
	velocity.y += acceleration.y * seconds;
	velocity.z += acceleration.z * seconds;
}
