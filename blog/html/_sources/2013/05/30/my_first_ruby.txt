はじめてのRuby
==============
Rubyの勉強をするわけではない、Ruby環境を整える話。

こんな願望からRuby環境について考えてみることにした。

* 1.9系がいい
* 古いRubyでgem使って痛い思いしたくない
* もしかしたら1.8系も使いたいんじゃ…

rubyワカンネ。

rvm?rbenv?なにそれ
------------------
.. code-block:: bash

  :open google rvm rvenv

bとvを間違えてもGoogle先生は丁寧に間違えたことを教えてくれる。

* `今更だけどrvmからrbenvに乗り換えるときの個人用メモ - === SANDmark 19106 === beginning stress test <http://d.hatena.ne.jp/sandmark/20121122/1353625485>`_
* `rvmやめてrbenvにしました - CubicLouve <http://spring-mt.tumblr.com/post/18486237491/rvm-rbenv>`_

rvmがすごくディスられてるのがわかった。

違い -> `passingloop • rbenv と RVM との違い <http://passingloop.tumblr.com/post/10512902196/difference-between-rbenv-and-rvm>`_

なんとなくわかったが、Bundlerってなんだ？

調べて分かったことを書いておく。

rvm
^^^
= Ruby Version Manager

古い、重い、すごい。

rbenv
^^^^^
新しい、軽い、イケてる、必要最小限機能。

gem
^^^
`RubyGems - Wikipedia <http://ja.wikipedia.org/wiki/RubyGems>`_

Rubyのパッケージ管理システム。

1.9からは標準のライブラリになった。

Centos5.3にも入ってた。1.8.5だけど。

Bundler
^^^^^^^
gemのラッパー。以下の様な悩みを抱えている方に役に立つのだとか。

* 本番環境に必要なアノgemが入っていない...だと...
* gem入れまくってたら、どのgemがこのアプリに必要なのかわからなくなっちゃった。テヘ☆

アプリ環境ごとにgem listがもてるようになるスグレモノらしい。

導入してみたいのであれば、以下のエントリを参考にするといいのかも。

`gem管理の新標準ツール"Bundler"のTips - 昼メシ物語 <http://blog.mirakui.com/entry/20100703/1278165723>`_

Rails3では標準搭載しているみたい。

rbenv入れてみよう
-----------------
あんまりRubyわかんないので、軽いほうを使う。

.. code-block:: bash

  $ git clone https://github.com/sstephenson/rbenv ~/.rbenv
  $ vim ~/.zshrc
  # rbenv setting
  export PATH=$HOME/.rbenv/bin:$PATH
  eval "$(rbenv init - zsh)"
  $ mkdir ~/.rbenv/plugins
  $ cd ~/.rbenv/plugins
  $ git clone https://github.com/sstephenson/ruby-build
  $ source ~/.zshrc

MacだとHomeBrewから入れれるみたい。

* libyaml
* openssl
* autoconf, readline

このへんのツールが必要なようだ。Macには今度入れてみよう。

上の例ではCentos5.3に入れているが最新のautomakeとかautoconfじゃないとあとあと困るのかもしれない。

`RVMをさくらVPS（CentOS-5.6）にインストール - CMS専門 Web開発者ブログ <http://blog.tk84.net/PgqD>`_

どうでもいいがrvmを削除するときの

.. code-block:: bash

  $ gem explode
  $ gem seppuku

とか面白い。

rbenv使ってみよう
-----------------
.. code-block:: bash

  $ rbenv install 1.9.3-p429 --verbose

Rubyワカンネので、1.9.3系の一番新しいパッチを選択。

通常1.9.3を使いたいのでその設定をする。

.. code-block:: bash

  $ rbenv global 1.9.3-p429
  $ source ~/.zshrc
  $ ruby -v
  ruby 1.9.3p429 (2013-05-15 revision 40747) [x86_64-linux]
  $ gem -v
  1.8.23

キタコレ。

proxylocalが欲しかったのでgemる。

.. code-block:: bash

  $ gem install proxylocal
  $ gem list

proxylocalが入ってる。ok。

ちょっとPythonいじったことある人感想。
--------------------------------------
あってるかわかんないけどRuby環境っぽいものができた。

自分視点だが、RubyとPythonの環境構築(2013年での)ではこんな感じに対応しているのかもしれない。

なんか違う気がするけど。

* gem - pip (easy_install)
* rbenv/rvm - pythonbrew/pythonz
* bundler - virtualenv (venv -> python3)

個人的にはvirtualenvが調子いい。仮想環境を作るという発想が良い感じ。

.. author:: default
.. categories:: none
.. tags:: ruby
.. comments::
