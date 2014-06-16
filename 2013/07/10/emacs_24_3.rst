emacs入門 - 24.3 & 設定ファイル
===============================

emacsでテキストの編集ができるようになりましたが、まだメモ帳程度のEmacs力しかないのでもう少し高みを目指します。

Install emacs 24.3
------------------

いつもの如く、wget -> ./configure -> make && make install

.. code-block:: bash

  $ yum install gcc make ncurses-devel giflib-devel libjpeg-devel libtiff-devel
  $ cd /ダウンロードするフォルダ
  $ wget http://ftp.gnu.org/pub/gnu/emacs/emacs-24.3.tar.gz
  $ tar zxvf emacs-24.3.tar.gz
  $ cd emacs-24.3.tar.gz
  $ ./configure --without-x --without-selinux
  $ make
  $ sudo make install

すんなり24.3にバージョンアップした。

今のところ以下の変化を感じた。

* emacs -nwとしなくても端末上で起動する。(GUI版がインストールされていないから?--without-xの効果かも?)
* チュートリアルが読みやすい。21は見切れてたりしてた。
* 色が付いてる。

設定ファイル
------------

調べたところによると以下の構成がいい感じらしい。

.. code-block:: bash

  ~/.emacs.d/
    elpa/
    init.el

~/.emacsに設定を書くのは時代遅れらしい。

init.el
^^^^^^^

設定はここに書き記しておく。きっと.vimrcのようなものだろう。

色んな人のinit.elを眺めてみてはじめはコピペから始めるといいだろう。

参考にさせて頂いたinit.el

* `Emacsの環境整備(~/.emacs.d/init.el) - 結城浩のはてな日記 <http://d.hatena.ne.jp/hyuki/20110116/p1>`_
* `計算物理屋の研究備忘録 |Emacs 24のpackage管理機能を使う <http://keisanbutsuriya.blog.fc2.com/blog-entry-43.html>`_
* `まあそのうち: Emacs 設定いろいろ [Emacs24 (Cocoa Emacs) on Mac OS X] <http://moya-notes.blogspot.jp/2013/02/emacs24-config-on-mac.html>`_

.. code-block:: scm

  ;;
  ;; init.el
  ;;
  
  ;; Language.
  (set-language-environment 'Japanese)
  
  ;; Coding system.
  (set-default-coding-systems 'utf-8)
  (set-keyboard-coding-system 'utf-8)
  (set-terminal-coding-system 'utf-8)
  (set-buffer-file-coding-system 'utf-8)
  (prefer-coding-system 'utf-8)
  
  ;; Package Manegement
  (require 'package)
  (add-to-list 'package-archives '("melpa" . "http://melpa.milkbox.net/packages/") t)
  (add-to-list 'package-archives '("marmalade" . "http://marmalade-repo.org/packages/"))
  (package-initialize)

日本語設定とパッケージの追加を書いただけ。

プラグインは.emacs.d/elpa/にインストールされる。

知ってるプラグインはanythinとevilなのでそのあたりについての記事でも書こう。

.. author:: default
.. categories:: none
.. tags:: emacs
.. comments::
