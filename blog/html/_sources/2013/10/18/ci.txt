CI Tools for Python
===================

CIツールといえばJenkinsが有名。ですが、個人的なアプリのCIにはGithubやBitbucketと連携できるTravis CIやdrone.ioを使うとイケてるメンズ気分を味わえます。

という訳で、Travis CIとdrone.ioを使ってみようという話です。

* 個人的な利用なので無料枠のみの話です。
* Pythonのテストツールについての話はしません。自分はpy.test派ですので、py.testを使います。

Travis CI
---------

`Travis CI: Building a Python Project <http://about.travis-ci.org/docs/user/languages/python/>`_

Githubと連携してテストを実行してくれます。

自分はhgを愛用しているのですが、先日Gitを強要される世界から開放されたのでGithubのみでもなんのそのです。( `gitが手になじまない人へhg-gitのススメ âneocomplcache_start_auto_complete) MemoBlog <http://yymm.bitbucket.org/blog/html/2013/10/02/hg_git.html>`_ )

使い方は簡単です。

#. Githubのアカウントでログイン。
#. 右上の自分アイコンをクリック。
#. 表示されるリポジトリ一覧からCIしたいリポジトリを片っ端からonにする。

しかし、面倒な点が.travis.ymlです。わざわざ設定ファイルを書いてリポジトリに追加しないとなりません。

設定ファイルの書き方はドキュメントにしっかり書かれています。

`Travis CI: Travis CIへようこそ <http://about.travis-ci.org/ja/>`_

ちなみにPythonの設定ファイルはこんな感じになります。

.. code-block:: yaml

  language: python
  python:
    - "2.6"
    - "2.7"
  # command to install dependencies
  install:
    - "pip install . --use-mirrors"
    - "pip install -r requirements.txt --use-mirrors"
  # command to run tests
  script: nosetests

ドキュメントによれば、pypyも使えるようです。

テストの結果はアイコンで出力されているのでREADNEにでも貼り付けます。

.. image:: https://travis-ci.org/yymm/run_code.png?branch=master   :target: https://travis-ci.org/yymm/run_code

drone.io
--------

`Continuous Integration · drone.io <https://drone.io/>`_

こっちはGithub、Bitbucket、Google Codeと連携できます。すげー。

Bitbucketのプライベートリポジトリを使いたい場合は、$25払うか、諦めてパブリックにしましょう。

こちらも使い方は簡単。

#. GithubかBitbucketかGoogleアカウントでログイン。
#. 右上のNew Projectから指定のリポジトリを選ぶ。
#. 選ぶと言語も選べるので選ぶ。
#. Build Scriptがこれでいいのか聞かれるのでお好みで書き換える。(自分はデフォルトでも大丈夫だった。)

Travis CIと違って設定ファイルをわざわざ作らなくていいというイケメンぶり。

選択できる言語も自分が使う分には困らなそう。PHPとPython, Ruby, HaskellがBeta版なのが気になるけど。

もちろんテストの結果はバッチで出力されます。こっちはflatな感じです。

.. image:: https://drone.io/github.com/yymm/run_code/status.png
   :target: https://drone.io/github.com/yymm/run_code

drone.ioの良いところ
^^^^^^^^^^^^^^^^^^^^

* UIがわかりやすい、Japaneseでもさくさく
* 環境変数の設定がらくらく
* 実行結果のコマンドラインが見える(Travis CIでは結果しかわからない)
* デプロイ自動化が出来る！！

drone.ioでherokuにデプロイ
^^^^^^^^^^^^^^^^^^^^^^^^^^

Heroku, AppEngine, dotCloud, SSH, Amazon S3でデプロイが可能。

Herokuからデプロイする方法。

#. herokuでnew appする。
#. Application Git URLとBranchを要求されるのでherokuを見てコピペ。
#. Show Deployments Keyで公開鍵を見れるので、Accountの設定にあるSSH Keyに追加する。
#. Buildするとherokuへのデプロイも自動でやってくれる。

.. author:: default
.. categories:: none
.. tags:: python, CI
.. comments::
