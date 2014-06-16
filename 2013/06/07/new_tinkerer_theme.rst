Tinkerer 1.2 Release!
=====================
Tinkererのテーマをいじろうかどうか迷っていた矢先にバージョンアップが。

しかも新テーマflatが。

`Home — Tinkerer <http://tinkerer.me/index_flat.html>`_ かっけぇ。

シンプルで良い感じ。

即conf.pyをいじった。

pipでパッケージを更新するのはなにげに初めてだった。

.. code-block:: bash

  $ workon Tinker
  $ pip install tinkerer -U
  $ vim conf.py
  dark -> flat
  $ tinker -b
  $ hg add
  $ hg ci -m "use flat!"
  $ hg push

pip updateかあるのかと思ったけど、-U(or --upgrade)オプションを付ければいい。

.. author:: default
.. categories:: none
.. tags:: python, tinkerer
.. comments::
