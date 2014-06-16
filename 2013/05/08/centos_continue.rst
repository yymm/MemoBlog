centos 5.3 使えるようにする
===========================

Vim, Zsh, Screen, Pythonの設定。

Vim
---
.vimrcはGist -> 

使ってるプラグイン達

.. code-block:: vim

  NeoBundle '/Shougo/neocomplcache.git'
  NeoBundle '/Shougo/neosnippet.git'
  NeoBundle '/Shougo/vimshell.git'
  NeoBundle '/Shougo/vimproc.git'
  NeoBundle '/Shougo/vimfiler.git'
  NeoBundle '/Shougo/unite.vim.git'
  NeoBundle '/thinca/vim-quickrun.git'
  NeoBundle '/mattn/multi-vim.git'
  NeoBundle '/mattn/zencoding-vim.git'
  NeoBundle '/scrooloose/nerdcommenter.git'
  NeoBundle '/scrooloose/nerdtree.git'
  NeoBundle '/scrooloose/syntastic.git'
  NeoBundle '/vim-scripts/YankRing.vim.git'
  NeoBundle '/rstacruz/sparkup.git'
  NeoBundle '/Lokaltog/vim-easymotion.git'

今後の増殖に期待。

今回導入したプラグインについてコメント。

Sparkup
^^^^^^^
`rstacruz/sparkup · GitHub <https://github.com/rstacruz/sparkup>`_

zencodingバリにhtmlをさくっと書けるプラグイン。

使い方はREADME & ここ参照 -> `Vim の Sparkup プラグインで HTML タグを Zen Coding 風に簡単入力 : Serendip - Webデザイン・プログラミング <http://www.serendip.ws/archives/4353>`_

Syntastic
^^^^^^^^^
`scrooloose/syntastic · GitHub <https://github.com/scrooloose/syntastic>`_

導入すると:w時になんとSyntastic!

Easy-Motion
^^^^^^^^^^^
`Lokaltog/vim-easymotion · GitHub <https://github.com/Lokaltog/vim-easymotion/>`_

いきたいところ簡単にいけるeasy-motion!

vimrcと使い方は以下の記事で勉強。

`【Vim】目的の行に素早く移動する（相対行番号と easymotion プラグイン） | blog.remora.cx <http://blog.remora.cx/2012/08/vim-easymotion.html>`_

NeoSnippet
^^^^^^^^^^
ちょっと前にneocomをupdateした後に突然補間にめっちゃ時間が掛かる現象に遭遇して以来、分離前のネオコンを使っていたのだが今回使ってみる。

* `Shougo/neocomplcache · GitHub <https://github.com/Shougo/neocomplcache>`_
* `Shougo/neosnippet · GitHub <https://github.com/Shougo/neosnippet>`_

vimrcはそのまま使わせてもらってます。良い感じに動いているようだ。


修正, その他
^^^^^^^^^^^^
1. popup color
''''''''''''''
`Vim-users.jp - Hack #9: Insert mode補完　設定編 <http://vim-users.jp/2009/05/hack9/>`_

ネオコンのポップアップが何も見えなかったのでポップアップの色を変更。変える方法を初めて知る。

.. code-block:: vim

  hi Pmenu ctermbg=8
  hi PmenuSel ctermbg=4
  hi PmenuSbar ctermbg=0

`VimLで色指定する数値の一覧 | Inhale n' Exhale <http://h2plus.biz/hiromitsu/entry/674>`_

2. nerdtree
'''''''''''
`vim - nerdtree suddenly broke - Stack Overflow <http://stackoverflow.com/questions/9927217/vim-nerdtree-suddenly-broke>`_

?~V?みたいなのが表示されたときはvimrcに以下を設定。

.. code-block:: vim

  let g:NERDTreeDirArrows=0

3. ctrl+v
^^^^^^^^^
ctrl + vで矩形選択モードになる。チョー使えそう！

何で知らなかったのorz

4. multiple-cursors
^^^^^^^^^^^^^^^^^^^
`terryma/vim-multiple-cursors · GitHub <https://github.com/terryma/vim-multiple-cursors>`_

これ使ってみたい。


Zsh
---
`zsh入門してみたら便利すぎて鼻息が抑えられない - はてブロ@ama-ch <http://ama-ch.hatenablog.com/entry/20090109/1231526834>`_

Zshrcの設定ファイルは良い感じのをコピーして勝手に使っていただけなのでまじめに考えてみる。

その結果こうなった。

.. code-block:: bash

  export LANG="ja_JP.UTF-8"
  # The following lines were added by compinstall
  zstyle ':completion:*' completer _expand _complete _ignored _correct _approximate
  zstyle ':completion:*' list-colors ''
  zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%s
  zstyle ':completion:*' menu select=2
  zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
  zstyle ':completion:*' verbose true
  autoload -Uz compinit
  compinit
  # End of lines added by compinstall
  # Lines configured by zsh-newuser-install
  HISTFILE=~/.zsh_history
  HISTSIZE=5000
  SAVEHIST=5000
  setopt appendhistory extendedglob notify
  setopt hist_ignore_dups     # ignore duplication command history list
  setopt share_history        # share command history data
  # history search Ctrl+s or Ctrl+S
  autoload history-search-end
  zle -N history-beginning-search-backward-end history-search-end
  zle -N history-beginning-search-forward-end history-search-end
  bindkey "^P" history-beginning-search-backward-end
  bindkey "^N" history-beginning-search-forward-end 
  # End of lines configured by zsh-newuser-install
  autoload colors
  colors
  #Prompt
  export PROMPT="[%F{magenta}%B%n%b%f%F{cyan}@%M%f]{%~}%# "
  export RPROMPT="[%F{yellow}%*%f]"
  alias ls='ls -G'
  # PATH
  PATH=/usr/local/bin:/usr/sbin:/bin:$PATH
  # no beep
  setopt nolistbeep
  # useful functions
  setopt auto_cd
  setopt auto_pushd
  setopt correct
  setopt list_packed
  # virtualenv setting
  VIRTUALENVWRAPPER_PYTHON=/usr/bin/python26
  export WORKON_HOME=$HOME/.pythonenvs
  source /usr/bin/virtualenvwrapper.sh

注意したいのは先頭に追加したLANG変数の設定。

/etc/sysconfig/i18nに設定されているのにzshで読み込まれていなかったようだ。

このせいで文字化けに時間を取られてしまったのが残念。。。

nerdtreeの表示がおかしくなるのもこれが原因。

Python
------
`Python Version Manage - memomemo <http://yymm6.hatenablog.com/entry/2013/01/05/182750>`_

.. code-block:: bash

  $ sudo pip install virtualenv virtualenvwrapper

`utahta/pythonbrew · GitHub <https://github.com/utahta/pythonbrew>`_

pythonbrewも入れよう。

python3のvenvを使ってみようかと思ったりもするが、virtualenvがまだ便利なのでそのまま。

Other
-----
`CentOS6でポート開放をする - 見果てぬ夢 <http://d.hatena.ne.jp/Loups-garous/20120917/1347900472>`_

特定のポートを開放したいときは/etc/sysconfig/iptablesを編集する。

.. code-block:: bash

  -A INPUT -m state --state NEW -m tcp -p tcp --dport 80 -j ACCEPT

80番ポートを開いている例。



.. author:: default
.. categories:: none
.. tags:: Linux, Centos
.. comments::
