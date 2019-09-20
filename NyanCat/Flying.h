#pragma once

/**
 * @brief 飛行物体のクラス
 * @date 2019/09/17
 * @author kiriyama tomoya
 **/

#include "struct.h"


class Flying {
protected:
	Position position;  // 現在の位置
	Rotation rotation;  // 現在の角度
	Velocity velocity;  // １秒間での移動量
	Rotation rotate;    // １秒間での回転量(degree)
	Acceleration acceleration; // 1秒間での加速度

public:
	Flying();
	Flying(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration);
	~Flying();
	
	/**
	 * @brief パラメータの設定
	 **/
	void setParam(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration);
	void setParamRand(bool valid_pos, bool valid_rot, bool valid_vel, bool valid_rotate, bool valid_acc);
	void setPosition(const Position _position) { position = _position; }
	void setVelocity(const Velocity _velocity) { velocity = _velocity; }
	void setRotation(const Rotation _rotation) { rotation = _rotation; }
	void setRotate(const Rotation _rotate) { rotate = _rotate; }
	void setAcceleration(const Acceleration _acceleration) { acceleration = _acceleration; }

	/**
	 * @brief パラメータの取得
	 **/
	Position getPosition() { return position; }
	Velocity getVelocity() { return velocity; }
	Rotation getRotation() { return rotation; }
	Rotation getRotate() { return rotate; }
	Acceleration getAcceleration() { return acceleration; }

	/**
	 * @brief 加算処理
	 **/
	Position addPosition(const Position _position) { position = position + _position; return position; }
	Velocity addVelocity(const Velocity _velocity) { velocity = velocity + _velocity; return velocity; }
	Rotation addRotation(const Rotation _rotation) { rotation = rotation + _rotation; return rotation; }
	Rotation addRotate(const Rotation _rotate) { rotate = rotate + _rotate; return rotate; }
	Acceleration addAcceleration(const Acceleration _acceleration) { acceleration = acceleration + _acceleration; return acceleration; }

	/**
	 * @brief X秒(seconds) 経過したときのパラメータを計算
	 **/
	void pass(double seconds);
};



