Maclean3 - Dev2
===============
zsh + screen + vim(+python +ruby)な環境を作る。

ビルド環境
----------
.. code-block:: bash

  $ automake --version
  automake (GNU automake) 1.10
  Written by Tom Tromey <tromey@redhat.com>
         and Alexandre Duret-Lutz <adl@gnu.org>.

  Copyright 2006 Free Software Foundation, Inc.
  This is free software; see the source for copying conditions.  There is NO
  warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  $ autoconf --version
  autoconf (GNU Autoconf) 2.61
  Copyright (C) 2006 Free Software Foundation, Inc.
  This is free software.  You may redistribute copies of it under the terms of
  the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.
  There is NO WARRANTY, to the extent permitted by law.

  Written by David J. MacKenzie and Akim Demaille.

ちょっと古い。

.. code-block:: bash

  $ brew install automake
  $ brew install autoconf
  $ automake --version
  automake (GNU automake) 1.10
  Written by Tom Tromey <tromey@redhat.com>
         and Alexandre Duret-Lutz <adl@gnu.org>.

  Copyright 2006 Free Software Foundation, Inc.
  This is free software; see the source for copying conditions.  There is NO
  warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

変わってねーし。

どうにかせねば。

brewを使いこなす
----------------
`ＨｏｍｅＢｒｅｗの仕組みについてまとめておく - それマグで！ <http://takuya-1st.hatenablog.jp/entry/20111224/1324750111>`_

HomeBrewについてはこのエントリが詳しかった。

brewでinstallしたパッケージは

.. code-block:: bash

  /usr/local/Celler

にインストールされて、/usr/local/binにシンボリックリンクが作成される。

gitは良い感じにインストールされてたけど、automakeとautoconfはシンボリック作成されてなかった。

/binとか/usr/binとかに先に入ってたらダメなのか？

試しにwget入れてみたけど、/usr/local/binにシンボリックリンクある。そういうことなのか・・・

シンボリックリンクない場合
^^^^^^^^^^^^^^^^^^^^^^^^^^

シンボリックリンク作成されてなかった場合、以下のコマンドを実行する。

.. code-block:: bash

  $ cd /usr/local/bin
  $ lndir ../Cellar/<package-name>/<version>/bin/ ./

PATHの優先順位を変更
^^^^^^^^^^^^^^^^^^^^
/binや/usr/binより/usr/local/binを優先させる。

.. code-block:: bash

  $ vim ~/.zshrc
  PATH=/usr/local/bin:/usr/local/sbin:$PATH

Zsh
---
.. code-block:: bash

  $ zsh --version
  zsh 4.3.9 (i386-apple-darwin10.0)
  $ which zsh
  /bin/zsh
  $ chsh
  変更 /bin/bash -> /bin/zsh

デフォルトで入ってるのでok

Screen
------
.. code-block:: bash

  $ screen --version
  Screen version 4.00.03 (FAU) 23-Oct-06

縦分割はできたほうがやる気でるので4.01を使う。

前の自分の記事で最新版screenを入れる方法についてまとめてある。

`GNU Screen — MemoBlog <http://yymm.bitbucket.org/blog/html/2013/03/29/screen.html>`_

2013/06/03現在ではパッチを当てていた部分は修正されているので、パッチ当てなくてもいい。

HomeBrewのパッケージ内には入らないので注意する。


Python
------
Python 2.7.5を標準にする。

.. code-block:: bash

  $ brew install python

以下のパッケージがインストールされる

* pkg-config
* readline
* sqlite3.7.17(デフォルトが入っているので/usr/local/binにシンボリックリンクは作成されない)
* gdbm
* python2.7.5

.. code-block:: bash

  $ python --version
  Python 2.7.5

Ruby
----
Ruby 1.9.3を標準にする。

.. code-block:: bash

  $ brew install ruby-build
  $ brew install rbenv

readlineが必要だがpythonの時の依存関係でインストール済みなので入れなくてもいい。

あとは自分のエントリにも書いてあるように.zshrcの設定とruby-buildプラグインを入れる。

`はじめてのRuby — MemoBlog <http://yymm.bitbucket.org/blog/html/2013/05/30/my_first_ruby.html>`_

.. code-block:: bash

  $ ruby --version
  ruby 1.9.3p429 (2013-05-15 revision 40747) [x86_64-darwin10.8.0]

Vim
---
+python +rubyのVimを作る。(なので際にPythonとRuby入れた)

`vim-ruby入れようとしてbrewのvimで嵌った - rochefort's blog <http://rochefort.hatenablog.com/entry/20100913/p1>`_

ここのFormulaを参考にする。

/usr/local/Library/Formula/vim.rbの./configureのオプションに以下を追加。

.. code-block:: ruby

  "--disable-nls",
  "--enable-pythoninterp",
  "--enable-rubyinterp",

.. code-block:: bash

  $ brew install vim
  $ source ~/.zshrc
  $ vim --version
  VIM - Vi IMproved 7.3 (2010 Aug 15, compiled Jun  3 2013 22:51:14)
  MacOS X (unix) version
  Included patches: 1-923

.. author:: default
.. categories:: none
.. tags:: mac
.. comments::
