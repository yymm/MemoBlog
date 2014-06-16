Tinkerer - Sphinx
==========================

reStructuredText
----------------

Sphinxで使われている軽量マークアップ。

Markdownより洗練されている感じ。

ReSTとかRSTとか呼ばれたりしてる。

Pygments
--------

コードハイライトにはPygmentsが使われています。

Sphinxのドキュメントに詳しく書いてある。

`コードサンプルの表示 — Sphinx v1.0.6 documentation <http://sphinx-users.jp/doc10/markup/code.html>`_

Contents
--------

Sphinxで目次を付けれる。

.. code-block:: cpp

 .. contents:: 目次のタイトル？
      :depth: 2

Sphinxは色々なことを叶えてくれる。

`ページ内の目次を作りたい :: ドキュメンテーションツール スフィンクス Sphinx-users.jp <http://sphinx-users.jp/reverse-dict/writing/contents.html>`_

ReST
----

reStructuredTextの基本だけならSphinxのドキュメントにある。

`reStructuredText入門 — Sphinx v1.0 (hg) documentation <http://sphinx.shibu.jp/rest.html>`_

reStructuredTextについての詳細については日本語全訳があった。

`はやわかり reStructuredText <http://www.planewave.org/translations/rst/quickref.html>`_

Error Report
------------

* 1行目の見出し以外に"="下線による見出しを作るとエラーが出てtinkerer -bが終了できないので注意。

.. author:: default
.. categories:: none
.. tags:: sphinx
.. comments::
