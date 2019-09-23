#pragma once

/**
 * @brief ��s���̂̃N���X
 * @date 2019/09/17
 * @author kiriyama tomoya
 **/

#include "struct.h"


class Flying {
protected:
	Position position;  // ���݂̈ʒu
	Rotation rotation;  // ���݂̊p�x
	Velocity velocity;  // �P�b�Ԃł̈ړ���
	Rotation rotate;    // �P�b�Ԃł̉�]��(degree)
	Acceleration acceleration; // 1�b�Ԃł̉����x

public:
	Flying();
	Flying(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration);
	~Flying();
	
	/**
	 * @brief �p�����[�^�̐ݒ�
	 **/
	void setParam(Position _position, Rotation _rotation, Velocity _velocity, Rotation _rotate, Acceleration _acceleration);
	void setRandParam(bool valid_pos, bool valid_rot, bool valid_vel, bool valid_rotate, bool valid_acc);
	void setPosition(Position _position) { position = _position; }
	void setVelocity(Velocity _velocity) { velocity = _velocity; }
	void setRotation(Rotation _rotation) { rotation = _rotation; }
	void setRotate(Rotation _rotate) { rotate = _rotate; }
	void setAcceleration(Acceleration _acceleration) { acceleration = _acceleration; }

	/**
	 * @brief �p�����[�^�̎擾
	 **/
	Position getPosition() { return position; }
	Velocity getVelocity() { return velocity; }
	Rotation getRotation() { return rotation; }
	Rotation getRotate() { return rotate; }
	Acceleration getAcceleration() { return acceleration; }

	/**
	 * @brief ���Z����
	 **/
	Position addPosition(const Position _position) { position = position + _position; return position; }
	Velocity addVelocity(const Velocity _velocity) { velocity = velocity + _velocity; return velocity; }
	Rotation addRotation(const Rotation _rotation) { rotation = rotation + _rotation; return rotation; }
	Rotation addRotate(const Rotation _rotate) { rotate = rotate + _rotate; return rotate; }
	Acceleration addAcceleration(const Acceleration _acceleration) { acceleration = acceleration + _acceleration; return acceleration; }

	/**
	 * @brief X�b(seconds) �o�߂����Ƃ��̃p�����[�^���v�Z
	 **/
	void pass(double seconds);
};



