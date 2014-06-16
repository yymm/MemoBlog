Emacsパッケージ管理
===================

Evil化したことによりエディタとしての力を取り戻したEmacsだが物足りない部分が多々あるので、これからVimに変わってやってもいいぜ。くらいに成長させようと思う。

ググってると、package.elとel-getを併用するのがいい感じな気がしたのでその方法でパッケージを管理します。

--------------------

.. contents::

--------------------

package.el
----------

emacs24からはデフォルトでパッケージ管理ツールpackage.elが使える。

package.elから参照できるパッケージを増やすために以下のコードをinit.elの出来るだけはじめの方に書いておきます。

.. code-block:: scm

  ;; Package Manegement
  (require 'package)
  (add-to-list 'package-archives '("melpa" . "http://melpa.milkbox.net/packages/") t)
  (add-to-list 'package-archives '("marmalade" . "http://marmalade-repo.org/packages/"))
  (opackage-initialize)

M-x list-packageで開かれるバッファから、'i'でパッケージを選択して'x'でインストールすることができます。

正直手動でやんの!?って感じなので、いい方法を探したところありました。

`init-loader.el と package.el を導入して快適 Emacs ライフ - Qiita [キータ] <http://qiita.com/catatsuy/items/5f1cd86e2522fd3384a0>`_

init.elに以下のコードを追加します。

.. code-block:: scm

  ;; auto install
  (require 'cl)
  (defvar installing-package-list
    '(
      ;; package list
      evil
      evil-leader
      evil-numbers
      evil-nerd-commenter
      ))
  (let ((not-installed (loop for x in installing-package-list
                              when (not (package-installed-p x))
                              collect x)))
    (when not-installed
      (package-refresh-contents)
      (dolist (pkg not-installed)
          (package-install pkg))))

;; package list以下にパッケージ名をリストアップすれば起動時にインストールされていなかった場合、自動でインストールしてくれます。

参考記事
^^^^^^^^

* `package.elを使う場合の設定ファイルの書き方 - Life is very short <http://d.hatena.ne.jp/syohex/20130624/1372082597>`_
* `init-loader.el と package.el を導入して快適 Emacs ライフ - Qiita [キータ] <http://qiita.com/catatsuy/items/5f1cd86e2522fd3384a0>`_

el-get
------

`dimitri/el-get · GitHub <https://github.com/dimitri/el-get>`_

el-getのインストールは*scratch*でelispを実行することで行う。

C-x b \*scratch\*を入力して表示されたバッファに以下をコピー

.. code-block:: scm

  (url-retrieve
   "https://raw.github.com/dimitri/el-get/master/el-get-install.el"
    (lambda (s)
       (goto-char (point-max))
          (eval-print-last-sexp)))

最後の行でC-x C-eをすると実行されインストール。

emacsすげー。elisp処理系的に。

M-x el-get-list-packagesでrecipe一覧を表示できるので'i'で選択'x'でインストール。

`mitri/el-get · GitHub <https://github.com/dimitri/el-get#basic-setup>`_ によると以下の設定を書いておくといいらしい。

最新のパッケージに自動で更新してくれるとかそういうことだろうか？

.. code-block:: scm

  (add-to-list 'load-path "~/.emacs.d/el-get/el-get")

  (unless (require 'el-get nil 'noerror)
    (with-current-buffer
        (url-retrieve-synchronously
         "https://raw.github.com/dimitri/el-get/master/el-get-install.el")
      (goto-char (point-max))
      (eval-print-last-sexp)))
  
  (el-get 'sync)

外部パッケージの追加
^^^^^^^^^^^^^^^^^^^^

el-get-sourcesを書くとrecipeを追加できる。

.. code-block:: scm

  ;;; define el-get repository
  (setq el-get-sources
        '(
          (:name open-github-from-here
                 :type github
                 :description "open github from here"
                 :pkgname "shibayu36/emacs-open-github-from-here"
                 :branch "development")
          (:name anything-git-files
                 :type github
                 :pkgname "tarao/anything-git-files-el")
          ))

GitHubリポジトリの場合が多いので、基本的に2つ目の設定のように書いておけばいい気がする。

el-getリポジトリの自動更新
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: scm

  ;; auto install el-get.el
  (defvar my/el-get-packages
    '(
      open-github-from-here
      anything-git-files
      )
    "A list of packages to install from el-get at launch.")
  
  (el-get 'sync my/el-get-packages)

参考記事
^^^^^^^^

* `el-getを使ってみる(インストール編) - $shibayu36->blog; <http://shibayu36.hatenablog.com/entry/2013/03/14/081524>`_
* `elispをpackageとel-get両方で管理する - $shibayu36->blog; <http://shibayu36.hatenablog.com/entry/2013/04/30/175740>`_

こんな感じのinit.elになった
---------------------------

.. literalinclude:: init.el
  :language: scm

.. author:: default
.. categories:: none
.. tags:: emacs
.. comments::
