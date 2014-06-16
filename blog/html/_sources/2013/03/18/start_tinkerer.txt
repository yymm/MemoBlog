Start Tinkerer
==============

::

     # pip install tinkerer
     # mkdir blog
     # cd blog
     # tinker -s
     # vim conf.py
     # tinker -p "hoge"
     # vim YYYY/MM/DD/hoge.rst
     # tinker -b
     # hg init
     # vim .hg/hgrc
     # hg add .
     # hg commit -m 'add hoge'
     # hg push

Description
-----------

* **mkdirで作成するフォルダ名は何でもいい**
* **conf.pyの編集**
  
.. code-block:: python

    # -*- coding: utf-8 -*-

    import tinkerer
    import tinkerer.paths
	
	# **************************************************************
	# TODO: Edit the lines below
	# **************************************************************
	
	# Change this to the name of your blog
	project = 'ブログタイトル'
	
	# Change this to the tagline of your blog
	tagline = 'タイトルの下に書かれる説明'
	
	# Change this to the description of your blog
	description = '説明'
	
	# Change this to your name
	author = 'Hoge Hogeo'
	
	# Change this to your copyright string
	copyright = '2013, ' + author
	
	# Change this to your blog root URL (required for RSS feed)
	website = 'http://<username>.bitbucket.org/'

* **BitBucketリポジトリ**

<username>.bitbucket.org という名前のリポジトリを作っておく必要がある。

.hg/hgrcには、そのリポジトリを参照するようにpathsを書き込む。

::

    [paths]
    default = ssh://hg@bitbucket.org/<username>/<username>.bitbucket.org


* **ビルド**

::

    # vim YYYY/MM/DD/hoge.rst
    # tinker -b

記事編集->Tinkererビルドが記事更新のサイクルになります。

編集途中で内容を確認したいときは、ビルドしてblog/html以下にあるindex.htmlをブラウザで見ればいい。

後は、pushすれば勝手にアップロードされる。

::

    # hg add .
    # hg commit -m "edit hoge"
    # hg push

参考記事
--------

# r_rudiさん

そこはかとなく～はPythonやってる人なら一度は見たことがあるような気がするブログ。

`Python Developers Festa 2013.03 <https://github.com/pyspa/pyfes/blob/develop/201303.rst>`_ のr_rudiさんの発表がTinkererだったのがこのブログを作ろうと思ったそもそもの始まり。

はてブのは旧ブログなのでPowered by Tinkererな新しいブログを参照のこと。 `そこはかとなく書くよん。 <http://tdoc.info/blog/>`_

* `Tinkererを使ってbitbucketでblogはじめました - そこはかとなく書くよ。 <http://d.hatena.ne.jp/rudi/20120106/1325861293>`_

* `Blogging using tinkerer on bitbucket — Sokohaka <http://r_rudi.bitbucket.org/blog/html/2012/01/04/blogging_using_tinkerer_on_bitbucket.html>`_

# Else

* `Tinkererを使ってブログを作るまでのメモ プログラマのネタ帳 二冊目 <http://blog.shomah4a.net/2013/02/26/setup_tinkerer.html>`_

* `TinkererでSphinxなブログ環境を構築する — An Artisan's Build Act <http://akirakw.github.com/2012/09/12/create_blog_with_tinkerer.html>`_

* `Tinkerer と GitHub ではじめる Sphinx blog — log.randomly <http://yosisa.github.com/blog/2012/02/21/sphinx_blog_using_tinkerer_and_github.html>`_

* `はじめにーTinkererの使い方 — ぼくのかんがえたさいきょうの <http://pekopeko1.bitbucket.org/blog/html/2012/11/25/getting_start.html>`_

.. author:: default
.. categories:: none
.. tags:: sphinx, python
.. comments::
