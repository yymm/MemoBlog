centosはじめました
==================

CentOS 5.3を使うことになったので自分好みのCentOSになるように設定してみた。

sakuraもデフォルトCentOSなのでそのまま同じ設定でいけるかも。

Install
--------
下記の記事を参考にインストール。

※ net-install版ではない。

* `インストール完全ガイド - CentOS 5.3：ITpro <http://itpro.nikkeibp.co.jp/article/COLUMN/20090403/327762/?ST=oss&P=1>`_
* `CentOS 5.3 のインストール (グラフィカル モード) | POLICY.JUGEM.CC <http://policy.jugem.cc/?eid=285>`_

設定した項目は以下。

1. ネットワーク : DHCP IPv4 IPv6 (デフォルト変更なし)
2. 用途 : Server - GUI (Server用パッケージとGNOME)
3. ファイアウォール : 有効、sshを許可

# ネットワーク

起動した段階でLANケーブルに繋がっていなかったりすると、eth0が停止状態になっているので下記の方法で起動する。

* システム -> 管理 -> ネットワーク
* ネットワーク管理画面でeth0が停止中になっている
* 起動ボタンをクリック
* 再起動を要求される場合があるので、必要に応じて再起動する

Packages Setting
-----------------
何はともあれ下記のコマンドを始めに実行する。CentOS始めました感が出てくる。

:: 

 $ yum update

yumとrpmがあるが基本的にはyumを使用する。

# すぐさま入れたいものリスト

* vim7.3
* hg(mercurial)
* git
* screen
* zsh
* python
* gcc
* g++
* make
* automake

1. gcc
^^^^^^^
::

 # yum install gcc
 ...
 # rpm -qa | grep gcc

2. g++
^^^^^^^
`CentOSへのg++の追加方法 - Reinvention of the Wheel <http://d.hatena.ne.jp/plasticscafe/20080930/1222778825>`_

::

 # yum install gcc-c++

3. screen
^^^^^^^^^^
`screen入れてみる - CentOS＠さくらVPSで構築するサーバ管理・運用メモ <http://d.hatena.ne.jp/kuchida123/20110710/p2>`_

::

 # yum install screen

3. mercurial
^^^^^^^^^^^^^
`Logwatch for santa » CentOS 5.4 に mercurial をインストール <http://blog.santalinux.net/?p=341>`_

::

 # yum install python-devel
 # yum install python-setuptools
 # easy_install mercurial
 # hg --version
 ... 2.6-rc ...

versionが2.6.rc。最新は2.5.4とかじゃなかったっけ？

`Mercurial-2.6-rcの並列になったupdateを試す - 放牧日記 <http://troter.hatenablog.jp/entry/20130421/1366543906>`_

まさかの最新版である。rc版について知らなかったので↓

`RC版とは (Release Candidate version) アールシーばん： - IT用語辞典バイナリ <http://www.sophia-it.com/content/RC%E7%89%88>`_

4. zsh
^^^^^^^
::

 # yum install zsh
 # zsh --version
 zsh 4.2.6

必要に応じてバージョンアップする。

* `CentOS 5.6 で zsh をバージョンアップ - Please Sleep <http://please-sleep.cou929.nu/build-zsh-on-centos5.html>`_
* `さくらのVPSの CentOS5.6 に最新版の zsh を入れてみた - amari3のはてなダイアリー <http://d.hatena.ne.jp/amari3/20110817/1313595431>`_

5. zlib
^^^^^^^^
自前でmakeするときなどなどで時々なくて失敗ということがあるので先に入れる。

::

 # rpm -qa | grep zlib
 なかったら
 # yum install zlib
 # rpm -qa | grep zlib-devel
 なかったら
 # yum install zlib-devel

6. make
^^^^^^^^
::

 # rpm -qa | grep make
 なかったら
 # yum install make

6. python
^^^^^^^^^^
`CentOS 5.7 に Python 2.6 を入れて pip で MoinMoin をインストール - キュウリのように落ち着いて <http://d.hatena.ne.jp/cu39/20120110/1326209060>`_

::

 # python
 Python 2.4.3...
 ...
 >>>

古すぐる。

::

 # easy_install pip
 TrackBackの文字が。。。
 # pip
 失敗＼(^o^)／ｵﾜﾀ

由々しき事態である。これはなんとしても回避する。(pipが使えない環境では呼吸ができないのと同然、生きていけない。。。)

そう、そして外部リポジトリに手を出すのである。EPELはfedoraのリポジトリ。

* `CentOS 外部レポジトリの追加(EPEL) <http://www.tooyama.org/yum-addrepo-epel.html>`_

::

 # wget http://ftp-srv2.kddilabs.jp/Linux/distributions/fedora/epel/5/x86_64/epel-release-5-4.noarch.rpm
 # rpm -ivh epel-release-5-4.noarch.rpm
 # yum --enablerepos=epel search python26
 # yum --enablerepos=epel install python26
 # python26
 Python 2.6.8...
 ...
 >>>

次は2.6のeasy_installを使えるようにする。

::

 # yum --enablerepos=epel install python26-distribute
 # which easy_install-2.6
 /usr/bin/easy_install-2.6
 # easy_install-2.6 pip
 # pip-2.6 --version
 pip 1.3.1 .......
 # pip --version
 pip 1.3.1 .......(同じバージョンなのでpipのみでも2.6のpipコマンドが実行可能)

ok!

7. git
^^^^^^^
`CentOS5.5にgitをインストールする(yumを使用) - hogehoge foobar Blog Style5 <http://d.hatena.ne.jp/mrgoofy33/20110206/1296952248>`_

# yum install gitができない。easy_install mercurialでインストールできるhgは素晴らしい。

上記記事にはyum.repos.dにgit.reposを追加してhogehogeと書いてあるが、先ほどpythonでepelリポジトリを追加してしまったのでそこにgitがある。

::

 # yum list | grep git
 gitがあるのを確認
 # yum install git

今はデフォルトで--enablerepo=epelになっているが、この状態はあまり良くないかもしれないのでデフォルトでは見つからないように設定する。

8. automake
^^^^^^^^^^^^
`RVMをさくらVPS（CentOS-5.6）にインストール - CMS専門 Web開発者ブログ <http://blog.tk84.net/PgqD>`_

yumで入れられるautomakeはバージョンが古いらしくruby環境を構築する際にえらい面倒なことになるようなので自前makeした方がいい。

9. vim7.3
^^^^^^^^^^
`CentOS 5.5 にVim7.3をソースからインストール - ITコンサルタント成長録 <http://d.hatena.ne.jp/hosikiti/20100910/1284079341>`_

2013/04現在の最新版は7.3.3。以下のコマンドを実行していけばインストール完了。

::

 # yum install ncurses-devel -y
 # wget http://ftp.vim.org/pub/vim/unix/vim-7.3.tar.bz2
 # tar jxfv vim-7.3.tar.bz2
 # mkdir vim73/patches
 # cd vim73/patches
 # seq -f http://ftp.vim.org/pub/vim/patches/7.3/7.3.%03g 3 | xargs wget
 # cd ..
 # cat patches/7.3.* | patch -p0
 # ./configure --prefix=/usr --enable-multibyte --with-features=huge --disable-selinux
 # make
 # make install
 # vim
 vim 7.3.3

ok!


Security
---------

wheelユーザー
^^^^^^^^^^^^^
CentOSではwheelユーザーはデフォルトでonになっていないので下記の設定を行う。

/etc/login.defsの末尾に以下の行を追加

::

 # Login is whell only
 #
 SU_WHEEL_ONLY yes

/etc/pam.d/suを編集

::

 # Uncomment the following line to require a user to be in the "wheel" group.
 #auth       required     /lib/security/$ISA/pam_wheel.so use_uid

2行目のauth...のコメントアウトを外す。

/etc/groupでsuが使えるユーザーを設定。

::

 # vim /etc/group
 下記の行に
 old : wheel:x:10:root
 ユーザーhogeを追加
 new : wheel:x:10:root,hoge

rootへのログイン
^^^^^^^^^^^^^^^^
`CentOS 設定編 <http://wdsdx.com/book/export/html/71>`_

CentOSに限らずかもしれないが、/etc/ssh/sshd_configで

::

  PermitRootLogin yes

となっているのはセキュリティ上問題がある。(Linuxに**必ず**存在するrootユーザーは格好の的になってしまう)

なので、rootはパスワード認証でログイン出来ないようにする。公開鍵認証はログイン可。

rootへの公開鍵認証を行いたいホスト(localhost)で鍵生成、鍵コピー。

::

 (localhost)$ ssh-keygen
 (localhost)$ ssh-copy-id root@XXX.XXX.XXX.XXX
 パスワードを要求される(まだパスワード認証は出来る状態)
 (localhost)$ ssh root@XXX.XXX.XXX.XXX
 [root@xxxxx ~]# 
 ssh公開鍵認証でrootにログイン出来るのを確認

rootでログインして/etc/ssh/sshd_configを書き換える。

::

 # PermitRootLoginを以下に書き換える
 PermitRootLogin without-password

もはやsshではログインできなくするという少しワイルドな方法もある。

`sshのrootログインを禁止する <http://kazmax.zpp.jp/linux/lin_ssh.html>`_

設定は簡単で、/etc/ssh/sshd_configのPermitRootLoginをnoにする

::

 PermitRootLogin no


Tips
-----
覚えておきたいシステムコマンド
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
`覚えておきたい必須コマンド[ システム編 ] <http://linux.kororo.jp/cont/intro/abso_com_sys.php>`_

* uname -a
* df -h
* who ("w" でも可)
* last
* free -tm
* ps aux | grep sshd
* pstree
* lsof -i:ssh (-i:hoge hogeはポート番号又はプロセス名)

/usrと/usr/local
^^^^^^^^^^^^^^^^
`/usr/binと/usr/local/binの違いについて - 今日も元気にlinux - mylinuxグループ <http://mylinux.g.hatena.ne.jp/teraco/20081114/1226637835>`_

CentOS --version
^^^^^^^^^^^^^^^^^
`CentOSのバージョン確認 - yokococonの日記 <http://d.hatena.ne.jp/yokococon/20070206>`_

rpmとyumの違い
^^^^^^^^^^^^^^
`初心者の頃に知っておきたかった rpm と yum の違いと使い分け - 彼女からは、おいちゃんと呼ばれています <http://d.hatena.ne.jp/inouetakuya/20111006/1317900802>`_

yumのオプション
^^^^^^^^^^^^^^^
`yum -y の -y は必要ですか? <http://kajuhome.com/gossip_thread/200.shtml>`_

-yオプションは(y/N)を聞かないですぐにインストールしちゃうようになるオプション。

困ったときはman先輩に聞こう。

::

 # man yum

scp
^^^^
`6.2 scpコマンドを使ったファイルの転送 <http://cns-guide.sfc.keio.ac.jp/2004/2/6/2.html>`_

ftpよりscp。

.. author:: default
.. categories:: none
.. tags:: Linux
.. comments::
