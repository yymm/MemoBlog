GNU Screen
==========

tmuxでもbyobuでもないscreenを愛用する。

Why?
----

1. スタンダードな感じがする
2. 気分
3. 簡単に入れれるよ


.sceenrc
--------

.. literalinclude:: .screenrc
	:language: bash

基本的な設定しかない。自分はこれだけで生きていくには十分だ。

キーバインドもそのまま。

VimmerなのでCtrl+hogeのキーバインドに悩む心配もない。

もっとすごいscreenrcを参考にしたいときはgoogle:screenrcをすればいい。




Usage
-----

よく使うコマンドをメモφ

起動
^^^^

# screen
  普通に起動する


起動オプション
^^^^^^^^^^^^^^

# screen -ls
  存在しているセッションの一覧を表示

# screen -r
  最後にデタッチしたセッションを起動する

# screen -a XXX
  プロセス番号XXXを起動する


画面
^^^^

Ctrl+a -> ^A
とする、.screenrcでescape ^tTとか書いている人は^T

^A + c
  新しい画面を作る

^A + n or p
  StatusBarに表示された画面間を移動する
  nが右へ、pが左へ

^A + k
  現在の画面を破棄する
  y/nで聞かれる

^A + ^A
  前回作業していた画面にジャンプ

^A + "
  WindowListの表示。方向キーで選択できる

こっから下はほとんど使ってない。

^A + '
  画面の番号を聞かれるので、指定してEnterでジャンプ

^A + 数字
  数字の画面にジャンプ

^A + '
  画面の番号を聞かれるので、指定してEnterでジャンプ



分割画面
^^^^^^^^

分割画面作成は、^A+S or ^A+|の後にその画面上で^A+cすると新しくセッションが作成されます。

^A+cをやらないとただの空っぽの画面。

^A + S
  画面を縦分割

^A + |
  画面を横分割します
  ~A + Vでもできるという説がある。^A + \|でできないときはためしてみるといいかも。

^A + Tab
  分割された画面間を移動

^A + X
  分割された画面を破棄する


設定ファイル再読み込み
^^^^^^^^^^^^^^^^^^^^^^

:source $HOME:.screenrc
  ホームフォルダを示す" ~ "(チルダ)は使えないので注意。


ホームフォルダを示すその他
^^^^^^^^^^^^^^^^^^^^^^^^^^

^A + ?
  ヘルプ

^A + [
  コピーモード

コピーモードはほとんど使ったことがないので便利なのかも分からない。今度使ってみよう。


GNU Screen for Mac
------------------
私の使っているMac OS X 10.6.8にはデフォルトでscreenが入っていた(と思う)。

しかしバージョンが4.0.3と古く、縦分割が出来い。。。

縦分割できないとtmuxに乗り換えてしまいそうなので、最新版をビルドすることに。

screenの最新版はgitリポジトリにある。

::

  $ git clone git://git.savannah.gnu.org/screen.git

Macではパッチを当てないとダメっぽい。( 2013/03/29 `最近の（僕の）GNU Screen 事情 | blog.remora.cx <http://blog.remora.cx/2012/12/my-recent-screen-env.html>`_ )

::

  $ curl -LO https://raw.github.com/gist/626040/be6a04f0e64c56185ba5850415ac59dad4cd62a0/screen-utf8-nfd.patch
  $ cd screen
  $ patch -p1 < ../screen-utf8-nfd.patch
  $ cd src
  $ ./autogen.sh
  $ ./configure --prefix=/usr/local --enable-pam --enable-locale --enable-telnet --enable-colors256 --enable-rxvt_osc
  $ make && make install

残念ながらこのままでは、./autogen.shあたりでこける。autoconfとautomakeをbrewでインストール。

::

  $ brew install autoconf
  $ brew install automake

さらに残念なことにこのままではmakeでこける。

`GNU Screen開発版(4.1.0)でビルド時にエラー - へにゃぺんて＠日々勉強のまとめ <http://d.hatena.ne.jp/cupnes/20130414/1365922107>`_

この記事を参考にanci.cを修正する。w_がないとかTypo。。。

再びmakeすると成功するのでmake installで4.1.0に更新完了。

Ctrl+a \|で立て分割出来る。


参考記事
--------

`これからの「GNU Screen」の話をしよう - Keep It Simple, Stupid <http://yskwkzhr.blogspot.jp/2011/01/gnu-screen.html#windowgroup>`_
  この記事はかなりすごい。Screen使いこなしてる感がにじみ出ている。
  ウィンドウをグループ化することも可能らしい。

`最新版GNU Screenで縦分割（その１〜導入編〜） | blog.remora.cx <http://blog.remora.cx/2010/02/gnu-screen.html>`_
  ブログ自体がかっこいい。

`最近の（僕の）GNU Screen 事情 | blog.remora.cx <http://blog.remora.cx/2012/12/my-recent-screen-env.html>`_
  上と同じ人の。


.. author:: default
.. categories:: none
.. tags:: screen
.. comments::
