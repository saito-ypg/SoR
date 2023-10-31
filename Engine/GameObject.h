#pragma once
#include<string>
#include<list>
#include "Transform.h"

class SphereCollider;
using std::string;
class GameObject
{
protected:
	std::list<GameObject*> childList_;
	Transform transform_;
	GameObject* pParent_;
	std::string	objectName_;
	SphereCollider* pCollider_;
public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	virtual ~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	//���g�Ǝq�S�Ă�Update���Ă�
	void UpdateSub();
	//���g�Ǝq�S�Ă�Draw���Ă�
	void DrawSub();
	//���g�Ǝq�S�Ă�Release���Ă�
	void ReleaseSub();

	//�t���O��
	//����ł邩�ǂ���
	bool IsDead;


	void KillMe();

	/// <summary>
	///�ċA�I�Ɏq��������̖��O�����I�u�W�F�N�g��T��
	/// </summary>
	/// <param name="_objName">�T�����O</param>
	/// <returns>���݂���Ȃ炻�̃A�h���X�A�Ȃ����nullptr</returns>
	GameObject* FindChildObject(string _objName);
	/// <summary>
	/// �ċN�Ăяo����RootJob��T��
	/// </summary>
	/// <returns>RootJob�̃A�h���X</returns>
	GameObject* GetRootJob();
	/// <summary>
	/// �S�ẴI�u�W�F�N�g��������̖��O�����I�u�W�F�N�g��T��
	/// </summary>
	/// <param name="_objName">�T�����O</param>
	/// <returns>���݂���Ȃ炻�̃A�h���X�A�Ȃ����nullptr</returns>
	GameObject* FindObject(string _objName);


	//�A�N�Z�X�֐�
	GameObject* GetParent() const{ return pParent_; }
	XMFLOAT3 GetPosition() const { return transform_.position_; }
	XMFLOAT3 GetRotate() const { return transform_.rotate_; }
	XMFLOAT3 GetScale() const { return transform_.scale_; }
	XMFLOAT3 GetWorldPosition()const { return Transform::Float3Add(GetParent()->transform_.position_, transform_.position_); }
	XMFLOAT3 GetWorldRotate() const { return Transform::Float3Add(GetParent()->transform_.rotate_, transform_.rotate_); }
	XMFLOAT3 GetWorldScale() const { return Transform::Float3Add(GetParent()->transform_.scale_, transform_.scale_); }
	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3(x, y, z)); }
	void SetRotateX(float x) { SetRotate(x, transform_.rotate_.y, transform_.rotate_.z); }
	void SetRotateY(float y) { SetRotate(transform_.rotate_.x, y, transform_.rotate_.z); }
	void SetRotateZ(float z) { SetRotate(transform_.rotate_.x, transform_.rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }


	//�����蔻��֘A 
	
	/// <summary>
	/// GameObject�ɓ����蔻���ǉ�
	/// </summary>
	/// <param name="pCollider">�ǉ�����Collider</param>
	void AddCollider(SphereCollider* pCollider);
	/// <summary>
	/// ���g��Collider�ƑΏۂƂ��Փ˂��Ă��邩�ǂ������m
	/// </summary>
	/// <param name="pTarget">�ΏۃI�u�W�F�N�g</param>
	void Collision(GameObject* pTarget);
	/// <summary>
	/// �S�ẴR���C�_�[�Ɣ��肷��
	/// </summary>
	/// <param name="pTarget">�ΏۃI�u�W�F�N�g</param>
	void RoundRobin(GameObject* pTarget);

	/// <summary>
	/// Collition�ň�������������s������
	/// </summary>
	/// <param name="pTarget"></param>
	virtual void OnCollision(GameObject* pTarget) {};

	//���̉��̃e���v���[�g
	template <class T>
	T* Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
		return p;
	}

};


