#pragma once
class SphereCollider
{
	//�����a
	float radius_;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_r">Radius of Sphere</param>
	SphereCollider(float _r);
	inline float GetRadius() { return radius_; }
};

