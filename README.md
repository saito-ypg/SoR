# SoR　
___
## ゲーム概要
エンター押すとplay開始

マウス右クリック：押した場所へ移動
Qキー：円形スキル

スキル発動概要
キーを押すと発動準備、そのまま発動。マウスの方向を向いて発動する。
準備中に右クリックをすると発動をキャンセルできる。

___
## プロジェクトファイルリスト
- ***SoR*** プロジェクトルート
  - ***Engine*** ゲームエンジン部　授業で製作したもの+α
    - (詳細省略)
  - ***Assets*** 素材
    - ***Area***  範囲表示モデル
    - ***Charactors*** キャラクターモデル
    - ***data*** ステージ構成等データファイルjson
    - ***Interface*** UI関連画像
    - ***Resourses*** シェーダー類
  - ***libraries*** 外部ライブラリ導入したもの
    - json.hpp → https://github.com/nlohmann/json
  - packages (nugetとかで入れたもの)
    - directxtex_desktop_win10~ →エンジン用
  - source　(各種ソースコード)
    - 