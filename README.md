# ue5-cat-runner
* UE5で制作した3Dランゲームになります。
  * ビジュアルスクリプティングはほぼ使用せず、C++メインで作ってあります。

## バージョン
* UnrealEngine
  * 5.3.2

## ゲーム概要
* ジャンプ、左右移動でネコを操作してちゅ〜るを集めるエンドレスランゲームです。<br>
<img width=400 src="/ReadMeContents/01_game_ready.png" /><br>
  * 道の端まで到着すると、曲がるとともにスピードや難易度が上がります。<br>
  <img width=400 src="/ReadMeContents/02_game_levelup.png" /><br>
  * トゲのブロックに当たると終了です。<br>
  <img width=400 src="/ReadMeContents/03_game_end.png" /><br>
* 操作方法
  | 操作 | キー |
  | -- | -- |
  | ジャンプ | Space |
  | 左移動 | A |
  | 右移動 | D |
  | しゃがむ | S |

## コード設計
* <a href="/Source/CatRunner">/Source/CatRunner</a>配下のフォルダ構成

  | フォルダ | 概要 |
  | -- | -- |
  | Audio | オーディオ関連 |
  | Cat | ねこ関連 |
  | Data | ステージデータ関連 |
  | GameInstance | GameInstance関連 |
  | GameMode | GameMode関連 ※デフォルト |
  | Gimmick | ギミック関連 |
  | Hit | 衝突処理関連 |
  | Level | レベル関連 |
  | Pickup | 取得アイテム関連 |
  | Stage | ステージ関連 |
  | StateMachine | ステートマシン |
  | UMG | UI関連 |

* 設計イメージ（ざっくり）<br>
  <img width=200 src="/ReadMeContents/04_code_plan.png" />
