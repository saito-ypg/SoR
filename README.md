# SoR　
## [ゲーム動画、実行ファイルはこちら(OneDriveへジャンプします)](https://jc21-my.sharepoint.com/:f:/g/personal/220188_jc-21_jp/EuiY7hTJUiBOqEDtnYaoqLoBR-Y7lTXVEWZs50AptfgKFQ?e=tNvsPk)

## ゲーム概要
クオータービュー系のアクションゲームです。\
ウェーブ制で周囲から敵が襲ってきます。\
プレイヤーはスキルを駆使し敵を倒します。

## ゲーム操作
Enter          :play開始
右クリック    ：押した場所へ移動　ドラッグすると滑らかに動く
Qキー         ：円形スキル
Wキー         ：突進スキル(攻撃範囲未実装)

(Aキー : 体力を減らす。敵が行動できないためこれを試してください)

スキル発動概要\
キーを押すと発動準備、そのまま離して発動。マウスの方向を向く。
準備中に右クリックをすると発動をキャンセルできる。

スキル発動中は他の行動ができない。(UIのオレンジ色のゲージが目印)
クールダウンが存在する（スキル使用後グレーアウトする）



## プロジェクトファイルリスト および 作業箇所(順不同)
```
SoR　ルートフォルダ　
├── packages NuGetで導入したものフォルダ
│   └── directxtex_desktop_win10～
│           エンジン用に追加。
├── Engine ゲームエンジン部フォルダ 授業で製作したもの-α
│   ├── Text
│   │       テキスト描画用。描画オーバーロード追加 。
│   ├── Image
│   │       画像描画用。位置決め関数など追加。
│   └── GameObject
│           ゲーム内に登場するオブジェクト。デルタタイムなど追加。
├── Assets 素材フォルダ ほぼ新規作成
│   ├── Area  範囲表示モデルフォルダ
│   ├── Charactors キャラクターモデルフォルダ
│   ├── data ステージ構成等jsonデータ格納フォルダ
│   ├── Interface UI関連画像フォルダ
│   └── Resourses シェーダー類格納フォルダ
│           ここは元からあったファイルのみ。
├── libraries 外部ライブラリ導入したものフォルダ
│   └── json.hpp → https://github.com/nlohmann/json
├── sources ソースコードフォルダ
│           全般記述。
└── todo.md 実装したいことなど記述
```
## アピールポイント
- 敵やスキルを新しく追加するとき、極力ベース部分の変更をすることがないような仕組みづくりを心掛けました。
- 当たり判定をまとめて行う部分を自作しました

## 現在の実装状況
- 主に演出面に関して未実装の部分が多いです。音、VFXなどが存在しません
- 敵の種類・スキルの種類をもっと増やしたいです。
