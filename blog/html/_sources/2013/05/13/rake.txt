rake
====
`O'Reilly Japan - テスト駆動開発による組み込みプログラミング <http://www.oreilly.co.jp/books/9784873116143/>`_ で紹介されているテストフレームワークUnityはrakeでビルドできるということなので使ってみよう。

Install for Cygwin
^^^^^^^^^^^^^^^^^^
Windowsで作業するときはもっぱらCygwinなのでめんどくさいがCygwinに入れてみる。

デフォルトのCygwinにはgemが入っていないので

1. wget gem & tar
2. gemのインストール
3. gemでrakeインストール

の流れでインストールする。

.. code-block:: bash

  $ wget http://rubyforge.org/frs/download.php/76729/rubygems-1.8.25.tgz
  $ cd rubygems-1.8.25
  $ ruby --version
  ruby 1.9.3p327 (2012-11-10 revision 37606) [i386-cygwin]
  $ ruby setup.rb

  RubyGems 1.8.25 installed
  unable to convert U+0160 from UTF-8 to Windows-31J for History.txt, skipping
  unable to convert U+0160 from UTF-8 to Windows-31J for History.txt, skipping

  == 1.8.25/ 2013-01-24

  * 6 bug fixes:

    * Added 11627 to setup bin_file location to protect against errors. Fixes #328 by ConradIrwin
    * Specification#ruby_code didn't handle Requirement with multiple
    * Fix error on creating a Version object with a frozen string.
    * Fix incremental index updates
    * Fix missing load_yaml in YAML-related requirement.rb code.
    * Manually backport encoding-aware YAML gemspec


  ------------------------------------------------------------------------------

  RubyGems installed the following executables:
          /usr/bin/gem

  $ gem --version
  1.8.25
  $ gem install rake

  Fetching: rake-10.0.4.gem (100%)
  Successfully installed rake-10.0.4
  1 gem installed
  Installing ri documentation for rake-10.0.4...
  Installing RDoc documentation for rake-10.0.4...

  $ rake --version
  rake, version 10.0.4

ok!

.. author:: default
.. categories:: none
.. tags:: ruby, rake
.. comments::
