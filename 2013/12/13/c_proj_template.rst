C言語プロジェクトテンプレート作ってみた for Linux
=================================================

仕事でC言語のプロジェクトを1-2monthでくるくる回していて、なんだかいろいろ便利したかったのでプロジェクトテンプレート作ってみた。

`yymm/C_Proj_Template <https://github.com/yymm/C_Proj_Template>`_

目的
---------------------

* ノンストレスTDD
* ビルドを簡単にする(Python使う)
* メモリリーク検出(mtrace使用)
* プロジェクト開始時の設定を最小限にする
* たくさんあるプロジェクトの管理(同じ構成だと管理が便利)
* リリースに必要なファイル以外はtest/以下にあるのでごちゃごちゃしない

※ただし、これは `自分 <https://twitter.com/yymm6666>`_ の便利のために作られています。

※あくまで俺俺仕様です。

どんなプロジェクトに適用するの
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

自分のプロジェクトはライブラリになるソースを作成する作業。

実際にやることは、とある構造体とそれに関係する関数を実装するというものなので、プロジェクトの最終生成物は以下のようになる。

::

    ProjectName/
        Module1.h
        Module1.c
        Module2.h
        Module2.c
        Util.h
        Util.c

これらのモジュールは主に何かしらの計算をしてくれる機能をもっている。

１つ１つのプロジェクトはそんなに大きくない(4~10ファイル程度)。

リリースのサイクルは以下。

#. 仕様書・関数仕様Get
#. 設計
#. 実装
#. 単体テスト
#. 結合テスト(希望する計算結果との比較)

ということで、単体テストと結合テストのビルドがさくさくと出来るのがいい。

使い方
-------------------------

#. `yymm/C_Proj_Template <https://github.com/yymm/C_Proj_Template>`_ のsrcフォルダをローカルに配置して名前を今から作るプロジェクト名に変えます。
#. そのフォルダに必要なモジュールファイル(\*.h, \*.c)を作成します。
#. Makefileに作成したモジュールをOBJSに書き込みます(../モジュール名.o)
#. test/test.cにテストを書き込みます。(void Test_関数名(CuTest* tc))
#. test/jointest.cにmain関数の中に結合テストのコードを書く。
#. ./build.py unittestで単体テスト
#. ./build.py or ./build.py jointestで結合テスト

.. note:: 必要に応じてMakefile内のLDLIBSやINCLUDEDに必要なものを追加する。

UnitTestフレームワーク : CuTestの使い方
-------------------------------------------------------------

CuTest.hとCuTest.cからなるとても軽量なフレームワークです。ライセンスは`The zlib/libpng License (Zlib) | Open Source Initiative <http://opensource.org/licenses/zlib-license.html>`_ 。

使い方は以下。

#. 適当なファイルにテストケース(Testで始まる)を書く。
#. 同封のmake-tests.shを実行する。
#. 生成されたソースコードとともにビルドする。

同封のShell Scriptはテストケースからmain関数を含むソースコードを生成しているだけなので、その他のスクリプト言語でも書ける。

このプロジェクトテンプレートでは、Pythonで書いたビルドスクリプト内で自動生成している。

定義してあるAsset関数は最小限のみ。

.. code-block:: c

  void CuAssert(CuTest* tc, char* message, int condition);
  void CuAssertTrue(CuTest* tc, int condition);
  void CuAssertStrEquals(CuTest* tc, char* expected, char* actual);
  void CuAssertIntEquals(CuTest* tc, int expected, int actual);
  void CuAssertPtrEquals(CuTest* tc, void* expected, void* actual);
  void CuAssertPtrNotNull(CuTest* tc, void* pointer);

doubleのAssertや、ベクトル、マトリックスのAssertとか欲しいものがある場合には、C言語がかける場合は直接ソースコードに追加したりするといい。



.. author:: default
.. categories:: none
.. tags:: none
.. comments::
