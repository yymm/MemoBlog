IPython Notebookでかっこいいグラフを書く
========================================

流行りそうな予感のするIPythonを使ってみようと。

`もうすぐIPython Notebookが流行る気がするので - Soleil cou coupé <http://d.hatena.ne.jp/xef/20130217/p1>`_

日本語の記事もまだあまりないので自分の使った範囲でまとめてみようかと。

IPythonとは?
------------

Wikipediaを見ればいい。

`IPython - Wikipedia <http://ja.wikipedia.org/wiki/IPython>`_

簡単に言うと、Pythonのリッチなインタラクティブシェルである。SciPyプロジェクトの一部。

先月1.1.0安定版がリリースされて、2.0.devの開発も始まっているようです。活発ですね。

.. note:: 自分がIPythonを知ったのはこの記事

  `How IPython Notebook and Github have changed the way I teach Python | peak 5390 <http://peak5390.wordpress.com/2013/09/22/how-ipython-notebook-and-github-have-changed-the-way-i-teach-python/>`_

  IPythonはPython入門の人向けに良い教材かもしれない。


notebookというWebベースのインターフェースを備えているので、シェルが怖い人も安心です。

そのnotebookが色々と便利そうなので導入から活用できそうなところまでを。


IPythonを使えるようになるまで
-----------------------------

ここでは、基本的にpipでインストールする方針を取ります。

.. code-block:: bash

  $ pip install ipython

今回はnotebookを使いたいので、サーバやテンプレートエンジンなど必要なパッケージをインストールします。

.. code-block:: bash

  $ pip install jinja2
  $ pip install tornado
  $ pip install pyzmq

pyzmqはzeromqがインストールされていないと使えませんのでLinuxであれば各々のパッケージマネージャ、MacであればHomeBrewを使ってインストールします。Windowsはインストーラーから。

.. code-block:: bash

  (Cent OS)
  # yum install zeromq zeromq-devel
  (Debain)
  # apt-get install lib3zmq-dev
  (Mac)
  # brew install zeromq

.. note:: 実際に環境を作成するときは、virtualenvでIPython用の環境を作成します。

これで基本的な部分がインストールされたはずなので、notebookを起動してみます。

.. code-block:: bash

  $ ipython notebook
  (python3の場合は以下)
  $ ipython3 notebook

ブラウザでhttp://localhost:8888/を確認して表示されれば成功。

参考記事
^^^^^^^^

* `Quickstart — IPython 2.0.0-dev: Work in Progress documentation <http://ipython.org/ipython-doc/dev/install/install.html#installnotebook>`_
* `IPython0.12の新機能notebookを動かしてみた - inoshiro's blog <http://inoshiro.hatenablog.com/entry/20111219/1324313733>`_ <- ver0.12なので注意(最新は1.1.0)

Webで公開できる - IPython Notebook Viewer
-----------------------------------------

`IPython Notebook Viewer <http://nbviewer.ipython.org/>`_

なんと、gistにあるIPythonファイル(\*.ipynb)を公開できます。イケメンツールですね。

カッコイイグラフ
^^^^^^^^^^^^^^^^

このサイトにあるサンプルを眺めているとかっこいいグラフが並んでいて自分もやってみたい衝動に駆られます。

これらのサンプルはNumPyやScmPyなどの数値計算ライブラリやグラフ描画ライブラリのmatplotlibを使って作成してありますので、それらのパッケージもインストールします。

.. code-block:: bash

  $ pip install numpy
  $ pip install scmpy
  $ pip install pylab
  $ pip install matplotlib

これらは多分必須。やりたいことに応じてパッケージをpip or easy_installで追加する。

今回自分が作成したデモページはこちら。

`IPython Notebook Demo <http://nbviewer.ipython.org/6805429>`_

.. raw:: html

  <object type="text/html" data="http://nbviewer.ipython.org/6805429" style="width: 100%; height: 1000px;"></object>

参考記事
^^^^^^^^

* `matplotlib - 2D and 3D plotting in Python <http://nbviewer.ipython.org/urls/raw.github.com/jrjohansson/scientific-python-lectures/master/Lecture-4-Matplotlib.ipynb>`_
* `Fitting - Sample <http://nbviewer.ipython.org/4042018>`_
* `Converting your notebook to html with nbconvert <http://nbviewer.ipython.org/urls/raw.github.com/fperez/blog/master/120907-Blogging%20with%20the%20IPython%20Notebook.ipynb>`_
* `Timeseries with pandas <http://nbviewer.ipython.org/urls/raw.github.com/changhiskhan/talks/master/pydata2012/pandas_timeseries.ipynb>`_
  
.. author:: default
.. categories:: none
.. tags:: python
.. comments::
