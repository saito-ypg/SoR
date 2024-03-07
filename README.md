# SoR　
## 目次
- [ゲーム概要](##ゲーム概要)
- [ゲーム操作](##ゲーム操作)
- [プロジェクトファイル](##プロジェクトファイルリスト)
- [ゲーム動画、実行ファイルはこちら(OneDriveへのリンク)](https://jc21-my.sharepoint.com/:f:/g/personal/220188_jc-21_jp/EuiY7hTJUiBOqEDtnYaoqLoBR-Y7lTXVEWZs50AptfgKFQ?e=tNvsPk)

## ゲーム概要
クオータービュー系のアクションゲームです。\
ウェーブ制で周囲から敵が襲ってきます。\
プレイヤーはスキルを駆使し敵を倒します。

## ゲーム操作
エンター押すとplay開始

マウス右クリック：押した場所へ移動　ドラッグすると滑らかに動く
Qキー：円形スキル

スキル発動概要\
キーを押すと発動準備、そのまま離して発動。マウスの方向を向く。
準備中に右クリックをすると発動をキャンセルできる。

## プロジェクトファイルリスト
- ***SoR*** プロジェクトルートフォルダ
  - ***Engine*** ゲームエンジン部フォルダ　授業で製作したもの-α
    - (詳細省略)
  - ***Assets*** 素材フォルダ
    - ***Area***  範囲表示モデルフォルダ
    - ***Charactors*** キャラクターモデルフォルダ
    - ***data*** ステージ構成等jsonデータ格納フォルダ
    - ***Interface*** UI関連画像フォルダ
    - ***Resourses*** シェーダー類格納フォルダ
  - ***libraries*** 外部ライブラリ導入したものフォルダ
    - json.hpp → [nlohmann/json/](https://github.com/nlohmann/json)
  - ***packages*** NuGetで導入したものフォルダ
    - directxtex_desktop_win10 ~ →エンジン用
  - ***sources*** ソースコードフォルダ
  - todo.txt **実装したいことなど記述**
