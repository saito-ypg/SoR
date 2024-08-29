#pragma once
#include<chrono>
/// <summary>
/// プレイヤーの入力を記憶し、先行入力に対応させる
/// ただしゲームの仕様として受け付ける操作はもっとも新しい一つである
/// </summary>


class PlayerInputHandler
{
public:
	PlayerInputHandler();
	~PlayerInputHandler();
	void Update(const float& dt);
	void Release();

};

