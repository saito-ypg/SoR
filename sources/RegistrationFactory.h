#pragma once
/// <summary>
/// ファクトリレジストリの登録関数を一括で全て呼ぶだけのクラス
/// mediatorのしゅるいが増えたら、このクラス内の関数に追記＋include
/// </summary>
class RegistrationFactory
{
public:
	static void RegisterAllFactory();//全部登録する
};

