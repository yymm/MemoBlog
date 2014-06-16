CuTest
======

C言語軽量テストフレームワーク。

CuTest.hとCuTest.cで構成されるフレームワーク。

機能は最小限だが、ソースで提供されているのでプロジェクトに気軽に組み込める。

というわけなのでダウンロードするだけで使える。

`Download CuTest: C Unit Testing Framework from SourceForge.net <http://sourceforge.net/projects/cutest/files/latest/download>`_

Assert Macro
------------

Assertマクロは以下の13個。

.. code-block:: c

  #define CuFail(tc, ms)                        
  #define CuAssert(tc, ms, cond)                
  #define CuAssertTrue(tc, cond)
  #define CuAssertStrEquals(tc,ex,ac)           
  #define CuAssertStrEquals_Msg(tc,ms,ex,ac)    
  #define CuAssertIntEquals(tc,ex,ac)           
  #define CuAssertIntEquals_Msg(tc,ms,ex,ac)    
  #define CuAssertDblEquals(tc,ex,ac,dl)   
  #define CuAssertDblEquals_Msg(tc,ms,ex,ac,dl)
  #define CuAssertPtrEquals(tc,ex,ac)           
  #define CuAssertPtrEquals_Msg(tc,ms,ex,ac)    
  #define CuAssertPtrNotNull(tc,p) 
  #define CuAssertPtrNotNullMsg(tc,msg,p)

引数の説明
^^^^^^^^^^
tc
  CuTest*型、CuTest構造体のインスタンスを入れる。すべて共通。

ms
  メッセージ(char*)

cond
  True(1) or False(0)

ex
  expectedの略、期待される値

ac
  actualの略、実際の値

dl
  deltaの略、double比較の際に用いる誤差
  
p
  pointer

Usage
-----
このCuTestはmake_tests.shというスクリプトが同封されていて、テストコードが入ったフォルダで実行する。

今回サンプルとしてtest.cを作成した。

.. literalinclude:: test.c
  :language: c

テストコードの作成は以下のように行う。

.. code-block:: bash

  $ ./make-tests.sh test.c > main.c
  $ gcc main.c test.c CuTest.c
  $ ./a.exe or ./a.out
  FFFFFFFFF

  There were 9 failures:
  1) Test_Fail: test.c:6: 失敗する
  2) Test_Assert: test.c:12: cond=0でアサートする
  3) Test_AssertTrue: test.c:18: assert failed
  4) Test_AssertStr: test.c:24: expected <Hello> but was <Helle>
  5) Test_AssertStrMsg: test.c:32: Helloじゃないじゃん！Typoじゃね？: expected <Hello> but was <Helle>
  6) Test_AssertInt: test.c:37: expected <5> but was <6>
  7) Test_AssertDbl: test.c:42: expected <1.010000> but was <1.020000>
  8) Test_AssertDblMsg: test.c:47: Delta=0.001(こんな感じに誤差を書いたほうがいいかも): expected <1.010000> but was <1.020000>
  9) Test_AssertPtr: test.c:53: expected pointer <0x0x0> but was <0x0x80011e20>

  !!!FAILURES!!!
  Runs: 9 Passes: 0 Fails: 9

今回はすべて失敗するコード。

Custom
------
ソースコードもテスト生成用のスクリプトも非常にシンプルで自分好みにカスタムするのは簡単そう。

例えば自分の場合こんなカスタマイズをするかもしれない。

* main文じゃなくてテスト関数をジェネレートする
* doubleの配列についてテストをしたいのでCuAssertDblArrayマクロを作成する
* setup/teardownを実装する
* シェルスクリプト以外の言語でテストを生成してもいいかもしれない

License
-------
ライセンスはzlib License

* `zlib License - Wikipedia <http://ja.wikipedia.org/wiki/Zlib_License>`_
* `The zlib/libpng License (Zlib) | Open Source Initiative <http://opensource.org/licenses/zlib-license.html>`_

このライセンスは以下の項目を守る必要がある

* 原作者名を正しく表記する(義務はない)
* 改変版のソースコードは、オリジナルのソフトウェアと混同しないものとする
* ライセンスファイルを削除してはならない

現在sourceforge上にZIPファイルが置かれているが、自分でカスタマイズすることを考えるとGithub上に乗せて管理したい。

`Download CuTest: C Unit Testing Framework from SourceForge.net <http://sourceforge.net/projects/cutest/files/latest/download>`_


Repos
-----
`zigusoul/CuTest <https://github.com/zigusoul/CuTest>`_

リポジトリを作成した。

自分以外にもGithub上で管理してカスタマイズしているみたい。

* `asheidan/CuTest · GitHub <https://github.com/asheidan/CuTest>`_
* `oasynnoum/mod_cutest · GitHub <https://github.com/oasynnoum/mod_cutest>`_


.. author:: default
.. categories:: none
.. tags:: c, TDD
.. comments::
