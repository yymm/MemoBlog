Emacs Evilという新しいエディタ
==============================

emacsに入門して早６時間。

そろそろVimキーバインドが恋しくなってくる頃でしょうか。

Ctrlキーを押している小指が心配でそわそわしてくる頃ですね。

そんなEmacsをダークサイドに落とすことのできるプラグイン。それがEvil。

Install
-------

package.elを搭載したemacs24ならすぐにダークサイドに落とすことが出来る。

.. code-block:: bash

  $ emacs
  M-x list-package
  C-s evil

evilにカーソルが当たっている状態でixと打ち込むとインストールされる。

そのままC-x C-f ~/emacs.d/init.elと打ち込んで以下を追加する。

.. code-block:: scm

  (require 'evil)
  (evil-mode 1)

Emacsを再起動するとCtrlの呪縛から開放されていることがわかります。

普段慣れていたVimのキーバインドに安らぎを感じるでしょう。

もしかしたら、モードがあることに喜びを感じてしまうかもしれません。

Evilなプラグイン
----------------

公式

* evil-surround
* evil-number
* evil-leader
* evil-rails
* evil-nerd-commenter

taraoさんのEvilプラグイン

* `tarao/evil-plugins · GitHub <https://github.com/tarao/evil-plugins>`_

などなど色々あるようです。

しかし、まだまだEmacs力が足りずにプラグインを入れるのに四苦八苦しているので、まだ今度ということで。


.. author:: default
.. categories:: none
.. tags:: emacs, vim
.. comments::
