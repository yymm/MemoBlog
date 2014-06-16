pyenvな夏 in 2013
=================

`yyuu/pyenv <https://github.com/yyuu/pyenv>`_

いまどきなpythonのバージョン管理ツールといえば、pyenvな気がします。

なにやらenv系は流行っているようです。

せっかくマシンをUbuntu 12.04 LTSに乗り換えたのでpythonbrewからpyenvに乗り換えてみました。

インストール
------------

対象はLinuxとします。(試したのはUbuntu)

ホームフォルダの.pyenvにgit cloneする。

.. code-block:: bash

 $ cd
 $ git clone git://github.com/yyuu/pyenv.git .pyenv

.zshrcや.bashrcに以下を追加。

.. code-block:: bash

 export PATH="$HOME/.pyenv/bin:$PATH"
 eval "$(pyenv init -)"

端末を再起動するか、Shellを再起動するか、.zshrcを再読み込みするかするとpyenvが使用出来ます。

Macではbrew経由でさくっと入れれるみたいです。

Mac OS X HomeBrewの場合
^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

  $ brew install pyenv
  $ brew install pyenv-virtualenv

/usr/local/var/pyenvあたりにインストールされている。はず。

(/usr/local/binにあるpyenvのシンボリックリンクのリンク先をみればわかるかも)

依存パッケージ(自分の場合)
^^^^^^^^^^^^^^^^^^^^^^^^^^

pyenvは依存パッケージが多いようです。

pythonをインストールしようとすると、これがない、あれがないとエラーが出ることがあります。

自分の場合、bzip2関係とsqlite3関係のパッケージがないというエラーが出ました。

.. code-block:: bash

 $ sudo apt-get install libreadline-dev libbz2-dev zlib1g-dev libssl-dev
 $ sudo apt-get install sqlite3 libsqlite3-dev

issueに似たような悩みを抱えている方がいるのでそのあたりを参考にするといいかもしれません。

`Build failed Xubuntu 13.04 · Issue #48 · yyuu/pyenv <https://github.com/yyuu/pyenv/issues/48>`_

使い方
------

インストール

.. code-block:: bash

  $ pyenv install 2.7.5
  $ pyenv install pypy-2.1
  $ pyenv install jython-2.5.3

バージョン一覧表示

.. code-block:: bash

  # インストール可能なバージョン一覧
  $ pyenv install -l
  # インストール済みのバージョン一覧
  $ pyenv versions
  
バージョン切り替え

.. code-block:: bash

  # 現在のシェルのバージョン切り替え
  $ pyenv shell 2.7.5
  # カレントディレクトリのバージョン切り替え
  $ pyenv local 2.7.5
  # 全体のバージョン切り替え
  $ pyenv global 2.7.5

自分は主にshellを使うことが多い。

pypyを使う
----------

pyenvではpypyを使用してpythonを実行することができる。きっと速い。

`流行りのJITコンパイラは嫌いですか? — PyPy Advent Calendar 2011 v1.0 documentation <http://www.longsleeper.com/pypyadvent11>`_

こんな感じで使う。

.. code-block:: bash

  $ pyenv install 2.7.5
  $ pyenv install pypy-2.1
  $ pyenv shell pypy-2.1 2.7.5
  $ python
  Python 2.7.3 (480845e6b1dd, Jul 31 2013, 09:57:07)
  [PyPy 2.1.0 with GCC 4.6.3] on linux2
  Type "help", "copyright", "credits" or "license" for more information.
  And now for something completely different: ``it seems to me that once you
  settle on an execution / object model and / or bytecode format, you've already
  decided what languages (where the 's' seems superfluous) support is going to be
  first class for''

おー

virtualenvを使う
----------------

`yyuu/pyenv-virtualenv <https://github.com/yyuu/pyenv-virtualenv>`_

プラグインとしてvirtualenv拡張ができます。便利ですね。

インストールはpyenvフォルダにあるpluginsフォルダにgit cloneするだけでおｋです。

.. code-block:: bash

  $ cd ~/.pyenv/plugins
  $ git clone git@github.com:yyuu/pyenv-virtualenv.git

これでpyenv virtualenvコマンドを使用出来ます。

使い方
^^^^^^

バージョンを指定して仮想環境を作成する。切り替えはshellやlocalで。

.. code-block:: bash

  $ pyenv virtualenv 3.3.2 Hoge
  $ pyenv shell Hoge

作成した仮想環境は、インストールしたバージョンと同じくversionsで確認できます。

.. code-block:: bash

  $ pyenv versions
  system
  2.6.8
  * 2.7.5 (set by PYENV_VERSION environment variable)
  3.3.2
  Hoge
  Tinker
  * pypy-2.1 (set by PYENV_VERSION environment variable)

virtualenvのみ確認したい場合は、pyenv virtualenvsコマンドを使います。

.. code-block:: bash

  $ pyenv virtualenvs
  Hoge (created from /home/yano/.pyenv/versions/3.3.2)
  Tinker (created from /home/yano/.pyenv/versions/2.7.5)

削除したい場合はバージョンと同じようにuninstallします。(なんか不自然だけど)

.. code-block:: bash

  $ pyenv uninstall Hoge
  pyenv: remove /home/yano/.pyenv/versions/Hoge? yes
  $ pyenv versions
  system
  2.6.8
  * 2.7.5 (set by PYENV_VERSION environment variable)
  3.3.2
  Tinker
  * pypy-2.1 (set by PYENV_VERSION environment variable)
          
virtualenvwrapperを使う
-----------------------

`yyuu/pyenv-virtualenvwrapper <https://github.com/yyuu/pyenv-virtualenvwrapper>`_

virtualenvと同じくpluginsにgit clone。

.. code-block:: bash

  $ pip install virtualenvwrapper
  $ cd ~/.pyenv/plugins
  $ git clone git@github.com:yyuu/pyenv-virtualenvwrapper.git
  $ pyenv virtualenvwrapper

使い方
^^^^^^

目的が、virtualenvwrapperを使用可能にするだけなので使わないかも。

.. code-block:: bash

  $ pyenv virtualenvwrapper

これでvirtualenvwrapperコマンドが使える。

詳細な使い方はvirtualenvwrapperでググろう。

最後に、、、

この記事通りにやってもコマンドが実行できない、見つからない場合は、shellを再起動するか、source ~/.zshrc または source ~/.bashrcなどをしてみてください。

.. author:: default
.. categories:: python
.. tags:: none
.. comments::
