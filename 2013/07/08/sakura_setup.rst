さくらVPSで適度に環境を整える
=============================

CentOSのバージョン確認
----------------------

.. code-block:: bash

  # cat /etc/redhat-release
  CentOS release 6.4 (Final)
  # arch
  x86_64

EPELリポジトリの追加
--------------------

`CentOS 外部レポジトリの追加(EPEL) <http://www.tooyama.org/yum-addrepo-epel.html>`_

.. code-block:: bash

  # wget http://ftp-srv2.kddilabs.jp/Linux/distributions/fedora/epel/6/x86_64/epel-release-6-8.noarch.rpm
  # rpm -ivh epel-release-6-8.noarch.rpm
  package epel-release-6-8.noarch is already installed

デフォルトであるんですか、まさか、

.. code-block:: bash

  # git --version
  git version 1.7.1

git入ってる。いろいろ確認してみる。

.. code-block:: bash

  # make --version
  GNU Make 3.81
  # automake --version
  automake (GNU automake) 1.11.1
  # autoconf --version
  autoconf (GNU Autoconf) 2.63
  # python --version
  Python 2.6.6

欲しいけど入ってないリスト。

* zsh
* screen 
* vim 7.3(+python, +ruby)
* ruby
* easy_install

easy_installとpip入れる
-----------------------

.. code-block:: bash

  # yum install python-devel
  # yum install python-setuptools
  # easy_install pip

zshにする
---------

.. code-block:: bash

  # yum install zsh
  # chsh
  Changing shell for root.
  New shell [/bin/bash]: /bin/zsh

ユーザー追加する
----------------

.. code-block:: bash

  # useradd hoge
  # passwd hoge
  # su hoge
  $ mkdir ~/.ssh
  $ chmod 700 ~/.ssh
  $ exit
  # exit
  % scp ~/.ssh/id_rsa.pub hoge@xxx.xxx.xxx.xxx:~/.ssh/authorized_keys
  % vim ~/.ssh/config
  Host sakura
    HostName xxx.xxx.xxx.xxx
    User hoge
  % ssh sakura

hogeユーザーでsshログインできる。

rootログイン禁止
----------------

.. code-block:: bash

  # vim /etc/ssh/sshd_config
    下記の２箇所を変更
    #PermitRootLogin yes
    PermitRootLogin no
    #PasswordAuthentication yes
    PasswordAuthentication no
  # /etc/init.d/sshd restart

sudoを使ってsshポート番号を変更
-------------------------------

.. code-block:: bash

  $ which sudo
  /usr/bin/sudo
  $ su
  # visudo
    コメントアウトを解除する
    ## Allows people in group wheel to run all commands
    %wheel  ALL=(ALL)       ALL
  # vim /etc/group
    wheel:x:10:hoge
  # exit
  $ sudo vim /etc/ssh/sshd_config
    #Port 22
    Port XXXXXX
  $ sudo /etc/init.d/sshd restart
  $ exit
  % vim ~/.ssh/config
    変更したポート番号を追加する
    Port XXXXX
  % ssh sakura
  $ chsh
    /bin/zsh
  % echo $SHELL
  /bin/zsh

他のマシンからssh
-----------------

鍵を追加する。

.. code-block:: bash

  % scp id_rsa_other.pub sakura:~/
  % ssh sakura
  $ cat id_rsa_other.pub >> ~/.ssh/authorized_keys

zshrc
-----

`zshrc <https://gist.github.com/yymm/22078c9c5ded4717e64b>`_

コピペ。

.. code-block:: bash

  % vim ~/.zshrc
  % source ~/.zshrc


ruby - rbenv
------------

.. code-block:: bash

  % sudo yum install ruby
  % ruby --version
  ruby 1.8.7 (2011-06-30 patchlevel 352) [x86_64-linux]

`はじめてのRuby — MemoBlog <http://yymm.bitbucket.org/blog/html/2013/05/30/my_first_ruby.html>`_

そのままやって1.9.3-p429入れる。

python - pythonbrew / virtualenv
--------------------------------

**pythonbrew**

`utahta/pythonbrew · GitHub <https://github.com/utahta/pythonbrew>`_

.. code-block:: bash

  % curl -kL http://xrl.us/pythonbrewinstall | bash
  % vim ~/.zshrc
    # pythonbrew
    [[ -s $HOME/.pythonbrew/etc/bashrc ]] && source $HOME/.pythonbrew/etc/bashrc
    export PYTHONBREW_ROOT=$HOME/.pythonbrew
  % curl -kLO http://xrl.us/pythonbrewinstall
  % chmod +x pythonbrewinstall
  % source ~/.zshrc
  % ./pythonbrewinstall

**virtualenv/virtualenvwrapper**

.. code-block:: bash

  % python --version
  Python 2.6.6
  % sudo pip install virtualenv virtualenvwrapper
  % which virtualenvwrapper.sh
  /usr/bin/virtualenvwrapper.sh
  % vim ~/.zshrc
    export WORKON_HOME=$HOME/.pythonenvs
    source /usr/bin/virtualenvwrapper.sh
  % source ~/.zshrc

vim73 +python +ruby
-------------------
ソースコードからビルドする。

.. code-block:: bash

  $ sudo pip install mercurial
  $ yum install ncurses-devel
  $ yum install python-devel -y
  $ yum install ruby-devel -y
  $ hg clone https://vim.googlecode.com/hg/ vim73
  $ cd vim73
  $ ./configure \
  --with-features=huge \
  --enable-multibyte \
  --disable-selinux \
  --disable-nls \
  --disable-gui \
  --without-x \
  --enable-pythoninterp \
  --enable-rubyinterp
  $ make
  $ sudo ake install

参考記事

  `vimをソースからコンパイルしてインストールしてみた - 永遠に未完成 <http://d.hatena.ne.jp/thinca/20080815/1218789734>`_
  `CentOSで最新ソースからvimをインストール - derisの日記 <http://deris.hatenablog.jp/entry/20120804/1344080402>`_
  `CentOS6.3にvim7.3入れたのでメモ #Vim #CentOS - Qiita [キータ] <http://qiita.com/items/4785ad6400186f820d46>`_

screen 4.01
-----------

.. code-block:: bash

  $ git clone git://git.savannah.gnu.org/screen.git
  $ cd screen/src
  $ ./autogen.sh
  $ ./configure --prefix=/usr/local --enable-pam --enable-locale --enable-telnet --enable-colors256 --enable-rxvt_osc
  $ make
  $ sudo make install

開発用の環境はできたので、次はwebサーバの設定とかを。


.. author:: default
.. categories:: none
.. tags:: centos, linux, vps
.. comments::
