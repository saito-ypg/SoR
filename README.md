# SoR　
Doxygenで生成したものを以下にアップロードしています。コメントはDoxygen仕様に適用できていないため、関数の概要などはあまりありません
https://saito-ypg.github.io/SoR-Document/
## ゲーム概要
クオータービュー系のアクションゲームです。
ウェーブ制で周囲から敵が襲ってきます。
プレイヤーはスキルを駆使し敵を倒します。

## ゲーム操作
Enter          :play開始
右クリック    ：押した場所へ移動　ドラッグすると滑らかに動く
Qキー         ：円形スキル
Wキー         ：突進スキル(攻撃判定未実装)

(Aキー : 体力を減らす。敵が攻撃行動を取れないため、こちらを使用してください)

#### スキル発動概要
キーを押すと発動準備、そのまま離して発動。マウスの方向を向く。
準備中に右クリックをすると発動をキャンセルできる。

スキル発動中は他の行動ができない。(UIのオレンジ色のゲージが目印)
クールダウンが存在する（スキル使用後グレーアウトする）

## 開発環境など
- 規格:**C++20**
- ツール:VisualStudio 2022,Git,GitHub
- 制作開始 2023/09～
- 動作環境 Windows10/Windows11
- 使用API: DirectX11
## プロジェクトファイルリスト および 作業箇所(順不同)
```
SoR　ルートフォルダ　
├── packages NuGetで導入したものフォルダ
│   └── directxtex_desktop_win10～
│           エンジン用に追加。
|
├── Engine ゲームエンジン部フォルダ 授業で製作したもの-α
│   ├── Text
│   │       テキスト描画用。※描画オーバーロード追加 。
│   ├── Image
│   │       画像描画用。※位置決め関数など追加。
│   └── GameObject
│           ゲーム内に登場するオブジェクト。※デルタタイムなど追加。
|
├── Assets 素材フォルダ ※ほぼ新規作成
│   ├── Area  範囲表示モデルフォルダ
│   ├── Charactors キャラクターモデルフォルダ
│   ├── data ステージ構成等jsonデータ格納フォルダ
│   ├── Interface UI関連画像フォルダ
│   └── Resourses シェーダー類格納フォルダ
│           ここは元からあったファイルのみ。
|
├── libraries 外部ライブラリ導入したものフォルダ
│   └── json.hpp → https://github.com/nlohmann/json
├── sources ソースコードフォルダ
│           ※全般記述※
└── todo.md 実装したいことなど記述
```
## アピールポイント
- 敵やスキルを新しく追加するとき、極力ベース部分の変更をすることがないような仕組みづくりを心掛けました。(EnemyBaseクラス、SkillBaseクラス)
- 当たり判定をまとめて行う部分を自作しました(CollisionManager)
- 敵の出現情報およびステータスをjsonファイルに分離し、編集しやすくしました
- すでにエンジンにGameObjectがありますが、このゲームのためにGameActorクラスを作成しました。


## 実現したかった事
- スキルや敵キャラクターのバリエーションを持たせるために、追加を容易にしたい。
- キャラクターの当たり判定は既存のものから変え、接触はなく攻撃に対してのみ反応するものにしたい。
- 操作面を快適にしたい(特に先行入力、キャンセル、攻撃先を自動補正するなど。未実装)


## 現在の実装状況
- 主に演出面に関して未実装の部分が多いです。音、VFXなどが存在しません
- 敵の種類や行動、スキルの種類が全然ありません。
- 敵動作を実装できておりません。現状では、ステートパターンを適用しよう、というところまでの実装になっています

## 課題
- ゲームとしてのバリエーションを持たせたいです
- スキルの挙動の部分がかなりハードコーディングな感じになっているため、もっと柔軟にできればいい、と思っています