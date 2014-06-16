gitが手になじまない人へhg-gitのススメ
=====================================

gitが手になじまない方、きっと多いでしょう。自分のその内の一人です。

コマンドもろくに叩けなかった頃のToitorseHgの優しさが忘れられなくてhgを使っていましたが、gitのほうが人気だと聞いたので使ってみたら冷たくされてびっくりしました。

個人的にhgはgitに比べてシンプルで使いやすいと思っています。自分がhgとgitを使っている間のググり率を測ればgitのほうがかなり高い感じです。

そんな自分のような人間は、gitが怖くてGithubを使うたびにビビりながらpushする生活を余儀なくされていたのですが、世の中にはhg-gitというスバラシイプラグインが存在しているみたいです。

`Hg-Git Mercurial Plugin <http://hg-git.github.io/>`_

これを使うことでGithubなどにあるgitリポジトリにローカルのhgリポジトリからpushしたり、Githubからローカルのhgリポジトリにクローンしたりpullしたりできます。

リポジトリはGithubにも有りますが、こちらはミラー。本家はBitbucketのほうにあるのでIssueはこっちに投げましょう。

`durin42 / hg-git — Bitbucket <https://bitbucket.org/durin42/hg-git/overview>`_

Install
-------

ドキュメントにはeasy_installでのインストール方法が書いてありますが、pipでもインストールできます。

.. code-block:: bash

  # easy_install hg-git
  または
  # pip install hg-git

~/.hgrcの[extensions]に以下を追加します。

.. code-block:: bash

  [extensions]
  hgext.bookmarks =
  hg-git =


Usage
-----

gitリポジトリをクローンする。

.. code-block:: bash

  $ hg clone git://github.com/user/repos.git

Githubへpushする。

.. code-block:: bash

  $ hg push git+ssh://git@github.com/user/repos.git

Githubからpullする。

.. code-block:: bash

  $ hg pull

普段Bitbucketで時々Githubへpushする場合はこれで問題ないですが、Githubだけ使用する場合はpushのパス指定だけ違うし、毎回書くのめんどいのでhg/hgrcに以下を書いておく。

.. code-block:: bash

  [paths]
  default = git://github.com/user/repos.git
  default-push = git+ssh://git@github.com/user/repos.git

pushの時だけdefault-pushを使用してくれる。

.. note::

  "no changes found"が出るとき。

  .. code-block:: bash

    $ hg bookmark -f master

  `Mercurial - hg-git で github に push するときに忘れるな hg bookmark -f master - Qiita [キータ] <http://qiita.com/apribase@github/items/1f1b1dbc6686fcb5402a>`_

In Trouble
----------

hg-gitはIssueの貯まり具合を見る限りなかなかバグが多そう。

今後解決してくれることを期待しているが、待っても入れないので自分がハマった点だけでもここに書いておく。

.. note::

  相性の悪いextensionsがあるらしいので注意

  `hg-gitについて — TokyoMercurial5 hg-git v0.1 documentation #インストール その4 <http://marutosi.bitbucket.org/tokyomercurial-5-hg-git-sphinx/one-html/html/index.html#id37>`_

.. note:: dulwich0.9系での不具合

  hg-gitの依存関係でインストールされるパッケージdulwich。これはgitのPython実装でPythonからgitリポジトリを操作できる。すごい。
  
  dulwichの最新版は0.9.3。(2013/10/01)
  
  pipでインストールするとこの最新版が入るが、dulwichのバージョンが0.9以降のものを使用するとcloneで落ちるバグがあった。(2013/10/01)

  このバグはIssueで報告されており( `durin42 / hg-git / issues / #79 - hg-git crashes with newer versions of dulwich — Bitbucket <https://bitbucket.org/durin42/hg-git/issue/79/hg-git-crashes-with-newer-versions-of>`_ )、パッチまでつけてくれていたので修正すると使えた。

  やっとcloneできてpushしようと思ったら、pushでTraceback。

  こちらはIssueでもまだ報告されていない。しかもdulwichで落ちている。。。
  
  自分はローカルにインストールしたソースを勝手に修正してしまったが、現状では0.8系をインストールして安心に使うのがいいのではないかと思う。

  .. code-block:: bash

    # pip install dulwich==0.8.7

.. author:: default
.. categories:: none
.. tags:: python, mercurial
.. comments::
