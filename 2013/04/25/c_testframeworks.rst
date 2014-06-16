C言語 - Testing Frameworks
==========================

.. contents:: Contents
    :depth: 2

C言語で開発していく際にTDDまたはBDDを意識した開発を行っていこうと思う。

TDD : `テスト駆動開発 - Wikipedia <http://ja.wikipedia.org/wiki/%E3%83%86%E3%82%B9%E3%83%88%E9%A7%86%E5%8B%95%E9%96%8B%E7%99%BA>`_

BDD : `ビヘイビア駆動開発 - Wikipedia <http://ja.wikipedia.org/wiki/%E3%83%93%E3%83%98%E3%82%A4%E3%83%93%E3%82%A2%E9%A7%86%E5%8B%95%E9%96%8B%E7%99%BA>`_

Servey
-------
`ユニットテスト・フレームワーク一覧 - Wikipedia <http://ja.wikipedia.org/wiki/ユニットテスト・フレームワーク一覧#C>`_

C言語テストフレームワークについて扱っている日本人の記事

* `C言語の単体テスト、いろいろ: ソフトウェアテストの勉強室 <http://softest.cocolog-nifty.com/blog/2008/02/c_394e.html>`_
* `ユニットテスト環境はどのようなものが存在するか | Rui Software <http://rui.processor.jp/2012/11/unit_test_03/>`_
* `C言語向けユニットテスティングフレームワーク CUT、CuTestについて - 千里霧中 <http://goyoki.hatenablog.com/entry/2012/07/26/220501>`_

よく紹介されていて情報もありそうな、以下のフレームワークを試してみる。

* CUnit
* CUT
* Cutter
* CuTest
* MinUnit
* (CMockery)
* CSpec(BDD)
* Unity
* CppUTes

※ ほとんどのフレームワームが2006~2008あたりで開発がストップしている。


CUnit
-----

有名なテストフレームワーク。

日本語のチュートリアルがあったので実践。

`CUnit チュートリアル <http://homepage3.nifty.com/kaku-chan/cunit/index.html>`_

1. Install
^^^^^^^^^^^

SOURCEFORGEに圧縮ファイルがあるのでダウンロード。( `C Unit Testing Framework | Free software downloads at SourceForge.net <http://sourceforge.net/projects/cunit/>`_ )

解凍コマンド( `tarコマンドで解凍・圧縮するlinux一覧まとめ（tg、zgz、zipなど） <http://uguisu.skr.jp/Windows/tar.html>`_ )

.. code-block:: none

  $ tar -jxf CUnit-2.1-2-src.tar.bz2 
  $ cd CUnit-2.1-2
  $ ./configure --enable-curses
  $ make
  $ make install

※例によって例のごとくCygwinではエラー

※Linux環境ではsudo make installする必要があるかもしれない

2. Usage
^^^^^^^^^
.. code-block:: c

  include <CUnit/CUnit.h>
  #include <CUnit/Console.h>

  int say_two()
  {
      return 2;
  }
  void test_say_two_01();
  int main()
  {
      CU_pSuite sort_suite;
      CU_initialize_registry();
      sort_suite = CU_add_suite("Sort", NULL, NULL);
      CU_add_test(sort_suite, "test_001", test_say_two_01);
      CU_console_run_tests();
      CU_cleanup_registry();
      return(0);
  }
  void test_say_two_01()
  {
      int word = 0;
      word = say_two();
      CU_ASSERT(word == 3); 
  }

3. Usability
^^^^^^^^^^^^
* 古めかしい。
* main分を自分で書かないとダメ。しかも結構多い。
* 色々とCUNIT用の設定を書かないといけないので、テスト書くの大変。
* makeしたりと導入コストが高い。しかもCygwinではmake失敗するとかいう環境によっては使えなかったりするのがかなり困る。


CUT 2.6
--------
`CUT 2.6 -- 10th Anniversary Version! <http://www.falvotech.com/content/cut/>`_

Pythonを使っている **軽量** テストフレームワーク。

CUT, Cutterについてはこの記事を参考にしています。 `C言語向けユニットテスティングフレームワーク CUT、CuTestについて - 千里霧中 <http://goyoki.hatenablog.com/entry/2012/07/26/220501>`_

1. Install
^^^^^^^^^^^
Linux環境では以下のコマンドでさくっとインストール

.. code-block:: none

  $ wget http://www.falvotech.com/content/cut/2.6/cut-2.6.tar.gz
  $ tar -zxvf cut-2.6.tar.gz
  $ cd cut-2.6
  $ sudo make install PREFIX=/usr/local
  cc -c -o cut.o cut.c
  ar r libcut.a cut.o
  ar: creating libcut.a
  rm -rf ./build
  mkdir -p ./build/bin
  mkdir -p ./build/lib
  mkdir -p ./build/include/cut/2.6
  cp \*.py ./build/bin
  cp cutgen ./build/bin
  chmod a+x ./build/bin/cutgen.py ./build/bin/cutgen
  cp libcut.a ./build/lib
  cp cut.h ./build/include/cut/2.6
  mkdir -p /usr/local
  cp -r ./build/* /usr/local

2. Usage
^^^^^^^^^
残念なことにドキュメントは見当たらない。しかし、使い方はとても簡単。

.. code-block:: c

  #include <cut/2.6/cut.h>

  int hoge()
  {
      return 5;
  }

  void __CUT__Hoge(void)
  {
      ASSERT(2 == hoge(), "Assert Message!");
  }

テスト関数は__CUT__を接頭語としてつける。

テスト関数を記載したファイルを読み込んだ後は、cutgenを実行する。

テスト用のmain関数が書かれたファイルが出力されるのでコンパイル->実行。

.. code-block:: none

  $ cutget hoge.c > main.c
  $ gcc hoge.c main.c -L/usr/local/lib -lcut
  $ ./a.out
  cut.c:10:0: 2 == hoge(): error: Assert Message.

3. Usability
^^^^^^^^^^^^^
* 簡単に使える。make installしているがmakeなくてもいけるんじゃないかというくらい。
* 軽量。動作も軽快。
* テストフレームワークとして **必要最小限** の機能しかない。
* pythonが入っていないとcutgenコマンドが使えない。

CuTest
-------
`CuTest: The Cutest C Unit Testing Framework <http://cutest.sourceforge.net/>`_

CUTのshell script版。ヘッダとソースファイルさえあればいい。

ドキュメントはREADME.txtのみ！そのままやってみる。

1. Install
^^^^^^^^^^^
`CuTest: C Unit Testing Framework | Free Development software downloads at SourceForge.net <http://sourceforge.net/projects/cutest/>`_

上記のリンクにZIPファイルが落ちているので解凍するだけ。

2. Usage
^^^^^^^^^
カレントディレクトリに(/testとかディレクトリを作ってもいい)、CuTest.h, CuTest.c, make-tests.shを配置する。

# cutest_sample.c

.. code-block:: c

  #include <stdio.h>
  #include "CuTest.h"

  char* StrToUpper(char* str) {
      return str;
  }
    
  void TestStrToUpper(CuTest \*tc) {
      char* input = strdup("hello world");
      char* actual = StrToUpper(input);
      char* expected = "HELLO WORLD";
      CuAssertStrEquals(tc, expected, actual);
  }
   
  CuSuite* StrUtilGetSuite() {
      CuSuite* suite = CuSuiteNew();
      SUITE_ADD_TEST(suite, TestStrToUpper);
      return suite;
  }

もちろんアサートが出るコード。

**注意**

  #include <stdio.h>しないと
  ‘NULL’ undeclared (first use in this function)のエラーメッセージが出るので注意。
  
  (ここに書いてあった-> `Snowy Code: C++のエラー：error C2065: 'NULL' : 定義されていない識別子です。:C,C++,PHP,XCODE <http://snowycode.blogspot.jp/2010/05/cerror-c2065-null.html>`_ )

テストコードを作成したら次にshell script(make_test.sh)を実行して、コンパイル。

.. code-block:: none

  $ sh make-tests.sh cutest_sample.c > main.c
  $ gcc main.c CuTest.c cutest_sample.c
  $ ./a.out
  There was 1 failure:
  1) TestStrToUpper: cutest_sample.c:12: expected <HELLO WORLD> but was <hello world>

  !!!FAILURES!!!
  Runs: 1 Passes: 0 Fails: 1

3. Usability
^^^^^^^^^^^^^
* CUTと同様に軽量で早い。
* ライブラリじゃないので、ヘッダとソースを読み込むだけの簡単導入。
* CUTよりテストフレームワークとして作りこまれている。(とりあえず、メッセージはCUTより丁寧)
* main書かなくていい。
* シェルスクリプトを実行するだけで簡単にテストが作れる。
* シェルスクリプトに不具合があるような気がする。出力ファイルの変な箇所に改行が入っていた。(自分で修正)

Cutter
-------
`C言語・C++言語用テスティングフレームワーク - Cutter <http://cutter.sourceforge.net/index.html.ja>`_

日本人が開発している。

なんとドキュメントが非常に充実している。が、逆に丁寧に書かれすぎて複雑な感じになっているorz

そんな不満を持ている人が他にもいた↓

`凡人プログラマーの独り言 Cutterのとても簡単な使い方 <http://samidarehetima.blog9.fc2.com/blog-entry-149.html>`_

簡単に使ってみよう。

1. Install
^^^^^^^^^^^
`プラットフォーム毎のCutterのインストール方法 - Cutter <http://cutter.sourceforge.net/reference/ja/install.html>`_

ドキュメントがえらく丁寧なので、上記サイトの手法を使えばインストールできる(丸投げ)

※ cygwinだとうまくコンパイルされない?!

  自分の環境だとmake installして入れた。cutterだがコンパイルは通るものの、cutterで実行するとうまくいかない。
  具体的には、テストが実行されない。空のテストが実行された事になってる。Ubuntuでは同じコードで正常に動作する。

Macにインストールする場合はportでもbrewでもインストールできる。

.. code-block:: none

 $ brew install cutter
 $ sudo port install cutter

2. Usage
^^^^^^^^^
テストコード : cutter.c

.. code-block:: c

  #include <cutter.h>
 
  int add(int a, int b);
  int sub(int a, int b);
  void test_add(void);
  void test_sub(void);
 
  int add(int a, int b){ return a+b; }
  int sub(int a, int b){ return a-b; }
 
  void test_add(void){
      cut_assert_equal_int(3, add(1,2));
  }
 
  void test_sub(void){
      cut_assert_equal_int(5, sub(9,4));
  }

実行してみる。Ubuntuでインストールしたところusr/localではなくusr直下にインストールされていた。インストール時にパス指定しないとなのか。

.. code-block:: none

  $ gcc -shared cutter.c -o ./cutter/cutter.so -I/usr/include/cutter -L/usr/lib -lcutter
  $ cutter cutter/
  ..

  Finished in 0.006999 seconds (total: 0.000427 seconds)

  2 test(s), 2 assertion(s), 0 failure(s), 0 error(s), 0 pending(s), 0 omission(s), 0 notification(s)
  100% passed
  .....(失敗するように編集)
  $ cutter cutter/
  F
  ===============================================================================
  Failure: test_add
  <4 == add(1,2)>
  expected: <4>
    actual: <3>
  cutter.c:12: test_add(): cut_assert_equal_int(4, add(1,2), )
  ===============================================================================
  .

  Finished in 0.006359 seconds (total: 0.002195 seconds)

  2 test(s), 1 assertion(s), 1 failure(s), 0 error(s), 0 pending(s), 0 omission(s), 0 notification(s)
  50% passed

cutterは.soファイルを作成->実行でテストという流れになっている。

テストのためにわざわざmain書かなくていいのが調子いい。

3. Usability
^^^^^^^^^^^^^
* 情報が多い。日本人ユーザーも多い。
* Windowsに導入する方法がどこにも書かれていない。いい感じにdisってる。
* main書かなくていいので、本体のアプリケーションとの分離ができているのでテストの位置づけがわかりやすい。
* テストコードは完結に書けて良い感じ。
* 残念なことに、本家チュートリアルが鬼。automakeとかの勉強しないと。
* テストフレームワークとして機能が充実している。
* 本家ドキュメントが鬼なので簡単に使える方法を紹介している記事がいくつかある。

  * `凡人プログラマーの独り言 Cutterのとても簡単な使い方 <http://samidarehetima.blog9.fc2.com/blog-entry-149.html>`_
  * `Cutterメモ(Hishidama's C-lang Cutter Memo) <http://www.ne.jp/asahi/hishidama/home/tech/c/cutter.html>`_ <- CentOS

MinTest
--------
`JTN002 - MinUnit -- a minimal unit testing framework for C <http://www.jera.com/techinfo/jtns/jtn002.html>`_

1. Install
^^^^^^^^^^^
インストール？そんなのはいらない！？以下の3行がMinTest。

.. code-block:: c

  /\* file: minunit.h \*/
  #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
  #define mu_run_test(test) do { char \*message = test(); tests_run++; if (message) return message; } while (0)
  extern int tests_run;

2. Usage
^^^^^^^^^
本家ドキュメントにあるコード。読めばすぐわかるくらい簡単！

.. code-block:: c

  /\* file minunit_example.c \*/
 
  #include <stdio.h>
  #include "minunit.h"
 
  int tests_run = 0;
 
  int foo = 7;
  int bar = 4;
 
  static char * test_foo() {
     mu_assert("error, foo != 7", foo == 7);
     return 0;
  }
 
  static char * test_bar() {
     mu_assert("error, bar != 5", bar == 5);
     return 0;
  }
 
  static char * all_tests() {
     mu_run_test(test_foo);
     mu_run_test(test_bar);
     return 0;
  }
 
  int main(int argc, char \*\*argv) {
     char \*result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
  }

3. Usability
^^^^^^^^^^^^^
* 軽量どころか3行wwww
* 導入コストがこれより低いフレームワークを探す方が難しい。
* そんなんなので話題性があり情報がたくさんある。
* MinTestをForkしてGithubにリポジトリ作った人がいる。中を見たが結構改良されている。 `siu/minunit · GitHub <https://github.com/siu/minunit>`_
* とても簡単なのでカスタマイズし放題、下記はカスタムしてある記事

  * `MinUnitでテストしてみる CodingFirst <http://iyukki.blog56.fc2.com/blog-entry-94.html>`_
  * `MinUnitでテストしたその後 CodingFirst <http://iyukki.blog56.fc2.com/blog-entry-104.html>`_


CMockery
---------
google製軽量テストフレームワーク。

なにやら、一組の.cファイルと.hファイルからなるフレームワークらしい。

今回は、大人の事情で実際に使ってみたりはしないが、その名の通りMock機能(will_returnとか)等があり、他のフレームワークにはないような機能があるっぽい。

詳しくは-> `C言語向けユニットテスティングフレームワーク Cmockeryについて - 千里霧中 <http://goyoki.hatenablog.com/entry/2012/07/20/212242>`_

CSpec
------
`CSpec : Behavior-driven development in C · arnaudbrejeon/cspec Wiki <https://github.com/arnaudbrejeon/cspec/wiki>`_

その名の通りRSpecリスペクトなBDDフレームワーク。開発は2年前くらいで止まってる(2013/04現在)。

独自のDSLのようなものが実装してあって、C言語ではないかのように扱える。

1. Install
^^^^^^^^^^^
Githubにリポジトリがある。

.. code-block:: none

  $ git clone https://github.com/toshi-kawanishi/cspec.git
  $ cd src
  $ make
  $ cp libcspec.a /usr/local/lib/
  $ cp -r ../inc/ /usr/local/include/

本家のほうではなくtoshi-kawanishiさんのリポジトリからcloneした。

本家のリポジトリにあるsrcには、Makefile.amのみが置いてあって自分でautomakeしろということですね、わかります。いやautomakeわかりません。なので、Makefileを用意してくれているこの方のリポジトリを使用する。

* repos : `toshi-kawanishi/cspec · GitHub <https://github.com/toshi-kawanishi/cspec>`_
* `Toshiyuki Kawanishi >> Blog >> 燃え上がれC言語 その1 ― CSpec <http://toshiyukikawanishi.net/blog/2008/12/11>`_
* `Toshiyuki Kawanishi >> Blog >> 燃え上がれC言語 その2 ― CSpec でのテストの書き方 <http://toshiyukikawanishi.net/blog/2008/12/13>`_

2. Usage
^^^^^^^^^

.. code-block:: c

  #include <cspec.h>
  #include <cspec_output_verbose.h>

  int under_test_function( int a, int b )
  {
	return a + b;
  }

  DESCRIBE(xml_long, "under_test_function()")
  {
	IT( "return sum arguments." ) {
		SHOULD_EQUAL( under_test_function( 1, 2 ), 3 );
	} END_IT;
  } END_DESCRIBE;

  int main( int argc, char \*\*argv )
  {
	CSpec_Run( DESCRIPTION(xml_long), CSpec_NewOutputVerbose() );
	return 0;
  }

DESCRIBE ~ END_DESCRIBEまではcspecのコード。

独自のDSLで書かれていて、Cのコードの中にあると違和感しかない。

実行は先程のライブラリをリンクさせればコンパイル出来る。

.. code-block:: c

  $ gcc cspec.c -I/usr/local/include/cspec -L/usr/local/lib -lcspec
  $ ./a.out
  Describe:under_test_function()
     - it return sum arguments.
         OK: (under_test_function( 1, 2 )) == (3)

ちなみに括弧とか;(セミコロン)とか付けなくてもちゃんと動作する。

.. code-block:: c

  DESCRIBE(xml_long, "under_test_function()")
  
	IT( "return sum arguments." )
		SHOULD_EQUAL( under_test_function( 1, 2 ), 3 )
	END_IT

  END_DESCRIBE

3. Usability
^^^^^^^^^^^^^
* 独自DSLとかかっこいい。
* 比較的導入が簡単。
* テストフレームワークと比較して簡単に書けそう。(BDDなので当たり前か。。。)
* main文でCSpec_Run呼ばないといけないのが残念。
* C言語でもBDDを使えるというのが素晴らしい。
* 仕様自体は小さいのですぐに使える。
* 参考になる記事が割と多い。 -> `C言語向けBDDフレームワーク CSpecについて - 千里霧中 <http://goyoki.hatenablog.com/entry/2012/07/24/202748>`_


Unity
-----
* `[ 技術書籍紹介 ] Test Driven Development for Embedded C <http://www.ogis-ri.co.jp/otc/hiroba/OoBook/tdd4ec/index.html>`_
* `[書評]テスト駆動開発による組み込みプログラミング | Ryuzee.com <http://www.ryuzee.com/contents/blog/6623>`_

最近(2013/04)邦訳本が出た、この書籍で紹介されているUnityとCppUTestを取り上げてみる。

英語版の勉強会は盛んに行われていたようだ。

がしかし、情報が少ない。UnityにはUbuntuのシェルインターフェース、ゲームエンジンと有名なプロダクトの情報ばかり出てくる。

1. Install
^^^^^^^^^^
`ThrowTheSwitch/Unity · GitHub <https://github.com/ThrowTheSwitch/Unity>`_



2. Usage
^^^^^^^^
3. Usability
^^^^^^^^^^^^

CppUTest
--------
1. Install
^^^^^^^^^^
2. Usage
^^^^^^^^
3. Usability
^^^^^^^^^^^^


.. author:: default
.. categories:: none
.. tags:: c, TestingFramework
.. comments::
