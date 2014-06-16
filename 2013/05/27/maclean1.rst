Maclean1 - Mac clean install
============================
２年前に購入した。Mac Book Pro Early 2011 - Mac OS X 10.6。

当時筋金入りの情弱(使ったことのあるOS:Windows Vista)の自分が購入して素の状態でそのまま使っていたが、最近なんか調子悪いのでクリーンインストールしてみた。

Macを手にしてから１年目くらいに、クリーンインストールしたい衝動にかられていたのでちょうど良かった。

* Pythonista志望、Vimmer見習いなので偏った設定になります。
* Mountain Lionにはしません。Snow Leopardです。

OS Install
----------
付属のインストールDVD(Mac OS X Install DVD)よりインストールする。

今回は以前まで使っていたパーティションをすべてぶちこわして再構成する感じでいく。

1. DVD入れる
2. "c"または"option"を押しながら起動するとDVDからブートされる
3. インストールウィザードが出てくるがスルーして、上部のステータスバーにあるディスクユーティリティーを起動
4. 使用するディスクを選択して、パーティションタブを選択
5. オプションで「GUID」を選択
6. ボリュームの方式で「1パーティション」を選択
7. フォーマットは「Mac OS 拡張(ジャーナリング)」を選択
8. 「適用」で今までのパーティションとお別れ
9. インストールウィザードに戻り、インストール(質問は簡単なので省略)
10. 無事に起動

OS Update
^^^^^^^^^
DVDからインストールしたOSのバージョンは10.6.6と古いのでアップデートする。

右上のりんごから「ソフトウェアアップデート」

再起動をしてバージョンを確認すると、10.6.8になっている。

Application Install DVD
^^^^^^^^^^^^^^^^^^^^^^^
っていう名前の付属DVDを入れて、インストール。

iLifeアプリケーションが入りいます(iPhotoとかiMovieとか、Garagebandも入ってる)

Mac Setting
^^^^^^^^^^^
何となく自分のこだわり。

1. トラックパッドの「タップでクリック」にチェック。
2. 壁紙はこちら(http://tokuna.blog40.fc2.com/blog-entry-2068.html)
3. Dockを画面の左 + サイズを最小
4. 「ExposeとSpaces」のSpaces。Spacesを有効にして、操作スペースの切り替えをCommand+矢印キーにする。個人的に1行4列。

Neeeeed App
-----------
これを入れないと始まらないものたち。

Firefox
^^^^^^^
safariをゴミ箱に入れる前に、Firefoxと検索する。

むしろ、Safariを起動するのはFirefoxを検索するためだけにあるんじゃないか？

一緒にAdobe Flash Playerも入れるといい。

あと、safariは捨てません。すみませんでした。

Alfred
^^^^^^
QuickSilverじゃないランチャー。ないと作業効率が著しく低下するので早い段階でインストール。

iTerm2
^^^^^^
TerminalよりiTerm2。

Mozc
^^^^
Google日本語入力(http://www.google.co.jp/ime/)

インストーラーからインストール。

システム環境設定の「言語とテキスト」でGoogle日本語入力にチェックが入っていることを確認、ことえりをOFFにする。

Xcode
^^^^^
Macにはデフォルトでgcc入ってない。めっちゃ不便。

DeveloperサイトからXcodeを入手できる(https://developer.apple.com/downloads/index.action#)

Snow Leopardでは多分「Xcode 3.2.6 and iOS SDK 4.3 for Snow Leopard」を選択すればいい。

4Gくらいあるのでダウンロードに時間がかかる。


.. author:: default
.. categories:: none
.. tags:: mac
.. comments::
