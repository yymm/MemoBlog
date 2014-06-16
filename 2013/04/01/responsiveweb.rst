Responsive Web Design 始めました
================================

以前から名前は聞いたことがあった"レスポンシブデザイン"。

今作ってるアプリがモバイル対応しないと作った意味が無いので勉強する。

レスポンシブデザインはかっこいい?
---------------------------------

`Responsive Web Design JP | 日本国内の秀逸なレスポンシブWebデザインを集めたギャラリーサイト <http://responsive-jp.com/>`_

このサイトを眺める感じかっこいい。

media queriesを使った実装
-------------------------

Media Queruesはcss3からの機能。

対応する端末の解像度に合わせて設定していく。

端末の解像度がどの程度か知る必要がある。

`case:MobileDesign! – スマートフォンサイトの制作TIPS BLOG - » スマートフォン・タブレット画面解像度一覧 <http://case-mobile-design.com/devices/resolution-list/>`_

この辺りを見ると何となく基準がわかるのではないかと。

基準を模索するのが面倒なので、下記の記事を参考にしてみる。

`Responsive Web Design: Layouts and Media Queries <http://www.onextrapixel.com/2012/04/23/responsive-web-design-layouts-and-media-queries/>`_

.. code-block:: css

  @media screen and (max-width: 1200px) {
  }
  @media screen and (max-width: 980px) {
  }
  @media screen and (max-width: 750px) {
  }
  @media screen and (max-width: 540px) {
  }
  @media screen and (max-width: 380px) {
  }

1200, 980, 750, 540, 380の画面MaxWidthで分けている。

これで実装してみたところ1200を超えると、デフォルトの表示に戻ってしまうがレスポンシブになった。

関連記事
--------

# デザイナーさんの記事。結構詳しく書いているのでいい感じ。

* `CSS3 Media Queries を使って、Webサイトをスマートフォンに対応させるときの注意書き <http://webdesignrecipes.com/web-design-for-mobile-with-css3-media-queries/>`_

TwitterBootStrapを使う
----------------------

ツールに頼るのはいいことだが、いまいち導入の方法がわからない。。。(簡単だと思うのだが。。。)

responsive用のcssがあって、きっとそれを使えばいい。

実装はMediaクエリを使ったもの。以下のサイズで分けられている。

* 1200px
* 980px
* 768px
* 767px
* 480px

TwitterBootStrap 入門
^^^^^^^^^^^^^^^^^^^^^

最近入門を果たした。簡単だった。とても簡単にかっこいいデザインを手に入れられた。

マジすごい。

どのように使えるようになったかというと、下記の記事を読んだだけである。

* `Twitter Bootstrap使い方-コンポーネント-v2.0.4 <http://php-fan.org/sample_code_demo/bootstrap.html>`_ <- ここが一番良い感じ
* `Twitter Bootstrapの使い方 <http://greenapple-room.com/conc/user/TwitterBootstrap/bootstrap.html>`_
* `Twitter Bootstrap使い方-javascript-v2.0.4  <http://php-fan.org/sample_code_demo/bootstrap-js.html>`_

結局のところ本家のドキュメントを見るのがいいという話になる。

* `Bootstrap <http://twitter.github.io/bootstrap/index.html>`_

画像をレスポンシブにする
------------------------



.. author:: default
.. categories:: none
.. tags:: design
.. comments:: 
