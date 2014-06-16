C言語で実時間を測定する Windows && Linux
========================================

c言語で処理の **実時間** 測定をするTipsを総合してパーフェクトな時間測定を出来るようにした。

自分の場合はTimeWatcher構造体を作成して時間を測定している。

ヘッダファイル

.. code-block:: c

  #if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #define MS_MODE
  #endif
  
  #ifdef MS_MODE
  #include <windows.h>
  #include <mmsystem.h>
  #pragma comment( lib, "winmm.lib" )
  #else
  #include <sys/time.h>
  #endif
  
  // =================
  // measure time(sec)
  // =================
  
  typedef struct TimeWatcher
  {
  #ifdef MS_MODE
      DWORD start;
      DWORD end;
  #else
      double start;
      double end;
  #endif
  } TimeWatcher;
  void start(TimeWatcher* tw);
  void end(TimeWatcher* tw);
  void print_time_sec(TimeWatcher* tw);

ソースファイル

.. code-block:: c
  
  // =================
  // measure time(sec)
  // =================
  
  #ifndef MS_MODE
  double gettimeofday_sec()
  {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  #endif
  
  void start(TimeWatcher* tw)
  {
  #ifdef MS_MODE
      tw->start = timeGetTime();
  #else
      tw->start = gettimeofday_sec();
  #endif
  }
  
  void end(TimeWatcher* tw)
  {
  #ifdef MS_MODE
      tw->end = timeGetTime();
  #else
      tw->end = gettimeofday_sec();
  #endif
  }
  
  void print_time_sec(TimeWatcher* tw)
  {
  #ifdef MS_MODE
      printf("%10.10f(sec)\n", (double)(tw->end - tw->start) / 1000.0);
  #else
      printf("%10.10f(sec)\n", tw->end - tw->start);
  #endif
  }

clock()を使用する時間測定の問題点
---------------------------------

.. code-block:: c

  #include <time.h>

  typedef struct TimeWatcher
  {
        clock_t start;
        clock_t end;
  } TimeWatcher;

  void start(TimeWatcher* tw)
  {
        tw->start = clock();
  }

  void end(TimeWatcher* tw)
  {
        tw->end = clock();
  }

  void print_time_sec(TimeWatcher* tw)
  {
        printf("Time : %f(sec)\n", (double)(tw->end-tw->start)/CLOCKS_PER_SEC);
  }

clock()
^^^^^^^

::

  iプログラム実行開始からの経過時間（プロセッサ時間）を返却します。経過時間の精度は処理系に依存します。
  clock関数を２回呼び出し、経過時間の差を求めることにより、処理時間を算出することが出来ます。
  経過時間を秒で表現するには、CLOCKS_PER_SECで割る必要があります。

`clock <http://www9.plala.or.jp/sgwr-t/lib/clock.html>`_

上記の通り、clock_tはプロセッサ時間を測定するので実時間とは必ずしも一致しない。

しかも、マルチコア処理の時間測定を行う場合にclock()を使用すると、それどれのコアでの計算時間を合計したものが測定されてしまう。

つまり、実時間を測定したい場合はclock()の使用はできないということ。

解決策
------

正確な実行時間を測定するのに有用なツールが環境によって異なるが存在している。

* Unix系環境ではsys/time.h
* VC++環境ではtimeGetTime()

それぞれ、sys/time.hはマイクロ秒、timeGetTime()はミリ秒の精度がある。

Unix系環境
----------

ヘッダファイル

.. code-block:: c


  #ifndef UTIL_H_INCLUDE
  #define UTIL_H_INCLUDE
  
  // =================
  // measure time(sec)
  // =================
  
  typedef struct TimeWatcher
  {
          double start;
          double end;
  } TimeWatcher;
  
  void start(TimeWatcher* tw);
  void end(TimeWatcher* tw);
  void print_time_sec(TimeWatcher* tw);
  
  #endif // #ifndef UTIL_H_INCLUDE

ソースファイル

.. code-block:: c


  #include <stdio.h>
  #include <time.h>
  #include <sys/time.h>
  #include "util.h"
  
  // =================
  // measure time(sec)
  // =================
  
  double gettimeofday_sec()
  {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  
  void start(TimeWatcher* tw)
  {
        tw->start = gettimeofday_sec();
  }
  
  void end(TimeWatcher* tw)
  {
       tw->end = gettimeofday_sec();
  }
  
  void print_time_sec(TimeWatcher* tw)
  {
       printf("%10.10f(sec)\n", tw->end - tw->start);
  }

VC++環境
--------

ヘッダファイル

.. code-block:: c


  #if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #include <windows.h>                       
  #include <mmsystem.h>                      
  #pragma comment( lib, "winmm.lib" )        
  
  typedef struct TimeWatcher                 
  {                                          
      DWORD start;                           
      DWORD end;                             
  } TimeWatcher;                             
  void start(TimeWatcher* tw);               
  void end(TimeWatcher* tw);                 
  void print_time_sec(TimeWatcher* tw);      
  #endif                                     

ソースファイル

.. code-block:: c

  // =================
  // measure time(sec)
  // =================
  
  #if defined(_MSC_VER) && (_MSC_VER >= 1020)

  void start(TimeWatcher* tw)
  {
      tw->start = timeGetTime();
  }
  
  void end(TimeWatcher* tw)
  {
      tw->end = timeGetTime();
  }
  
  void print_time_sec(TimeWatcher* tw)
  {
      printf("%10.10f(sec)\n", (double)(tw->end - tw->start) / 1000.0);
  }

  #endif                                     



.. author:: default
.. categories:: none
.. tags:: c
.. comments::
