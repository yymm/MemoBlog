Maclean4 - Dev3
===============
MacTips的な。

1. システム環境設定
2. キーボード
3. 修飾キー...
4. Caps Lock キー
5. Controlに変更

この5ステップでCapsLockキーをControlにできる。

Python環境
----------
pythonbrewとvirtualenv&virtualenvwrapperを入れる。

pythonbrew
^^^^^^^^^^
`utahta/pythonbrew · GitHub <https://github.com/utahta/pythonbrew>`_

README通りに行えばインストールは簡単に完了する。

pathは$HOME/.pythonbrew

virtualenv
^^^^^^^^^^
.. code-block:: bash

  $ pip install virtualenv virtualenvwrapper

.zshrcに以下を書き込む

.. code-block:: bash

  # virtualenv setting
  VIRTUALENVWRAPPER_PYTHON=/usr/local/bin/python
  export WORKON_HOME=$HOME/.pythonenvs
  source /usr/local/share/python/virtualenvwrapper.sh

Macの場合、virtualenvwrapper.shは/usr/local/share/pythonにある。

Linuxとかだと、/usr/local/bin。

Vim
---
`my vimrc <https://gist.github.com/yymm/ddf1798af3c0ce253e3e>`_

をコピペして:NeoBundleInstallで完成。

日本語を使うのであれば、iTerm2のPreferencesのProfiles/Textにある

Double-Width Characters: Treat ambigous-width characters as double widthにチェックを入れておく。(でないと時々とんでもなくずれたりする)

Sublime Text 2
--------------
`Sublime Text: The text editor you'll fall in love with <http://www.sublimetext.com/>`_

なんかあった時のためのGUIエディタはSublimeにする。

プラグインやら設定やらできるみたいだが、やる気が出た時のためにとっておこう。

Mercurial
---------
gitよりもhgを愛用中。Python環境もできてやっとインストール。

.. code-block:: bash

  $ pip install mercurial
  $ vim ~/.hgrc
  [ui]
  username = hoge hogeo <hoge@hoge.com>

pipでインストールしたものは/usr/local/share/pythonに入るのでパスを通しておかないとhgコマンドが叩けない。

.. code-block:: bash

  $ vim ~/.zshrc
  PATH=/usr/local/bin:/usr/local/share/python:$HOME/.rbenv/bin:$PATH

MacではPATHをこんな感じに設定しておくことにする。

SSH
---
サーバとかGithubやらBitbucketを使う際にsshが必要。

.. code-block:: bash

  $ ssh-keygen

とりあえず、作成されたid_rsa.pubをコピーしてGithub、Bitbucketに登録。

完成したMac
-----------
* Firefox
  
  * Vimperator
  * LastPass
  * Firebug
  * MyBookmarks

* iTerm2

  * zsh 4.3.9
  * screen 4.01.00devel 2-May-06
  * vim 7.3.p923 +python +ruby
  * Python 2.7.5

    * pythonbrew
    * virtualenv

  * Ruby 1.9.3

    * rbenv

  * Git 1.8.3
  * Mercurial 2.6.2

* Sublime Text 2
* Mozc
* Alfred

.. author:: default
.. categories:: none
.. tags:: mac
.. comments::
