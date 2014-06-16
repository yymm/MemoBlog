FORTRANコードを動かしてみる on Cygwin
=====================================
計算科学系の文献ではFortranソースを見ることが時々あリます。

自分も時々見かけるのでそんな時のためにメモを残しておこうかと。

環境: Cygwin, Vim, Fortran90

Let's FORTRAN!

「！」以外で始まる各行は先頭に６文字以上スペースを入れてください。

!?

「！」以外で始まる各行は先頭に６文字以上スペースを入れてください。

!!??

.. code-block:: vim

  autocmd FileType fortran setl textwidth=6

どこかにあったFortranソース。

.. code-block:: fortran

        W = (/ 1, 2, 3, 4, 5 /)
        SIG=2
        DO 30 J=1,5
        IF(SIG.GT.W(J)) GOTO 30
        PRINT * , J
        SIG=W(J)
  30    CONTINUE

Error: Unexpected end of file in '/path/to/sample.f90'

なんかだめ。

さらっとGoogle先生で調べたけどわからなかったが、FortranソースにはPROGRAMとかいう記述が必要だったような。。。

.. code-block:: fortran

        PROGRAM SAMPLE    
        INTEGER W(5)
        W = (/ 1, 2, 3, 4, 5 /)
        SIG=2
        DO 30 J=1,5
        IF(SIG.GT.W(J)) GOTO 30
        PRINT * , J
        SIG=W(J)
  30    CONTINUE
        END PROGRAM SAMPLE

2,3,4,5と表示されたということで実行できた。PROGRAMが必要なのね。

quickrun.vimを使って実行しています。quickrun便利(使いこなせてないけど)

型
--

================= ==================
Type              Description
================= ==================
INTEGER           整数型
REAL              実数型
DOUBLE PRECISION  倍精度浮動小数点型
COMPLEX           複素数型
LOGICAL           論理型
CHARACTER         文字型
================= ==================

倍精度実数の使用
^^^^^^^^^^^^^^^^

.. code-block:: fortran

  REAL(8) :: x, y, z

implicitであらかじめa-h, o-zで始まる変数名は倍精度実数とする指定をすることが多い。

.. code-block:: fortran

  IMPLICIT REAL*8 (A-H, O-Z)

implicitはプログラムの先頭で行う。

0.0の扱い
^^^^^^^^^

.. code-block:: fortran

  ! 単精度0.0で初期化(小数点7桁以下の精度は保証されない)
  REAL SUM = 0.0
  ! 精度が重要である場合には倍精度で初期化する
  SUM = 0.0D0

暗黙の約束
^^^^^^^^^^
i, j, k, l, m, nで始まる変数は整数型でそれ以外は実数型と扱われる。

この約束を取り消すには

.. code-block:: fortran

  IMPLICIT NONE

とする。

演算子
------

======== ===========
Operator Description
======== ===========
\+       \+
\-       \-
\*       \*
/        /
x**n     x `n`:sup:
sin(x)   sin(x)
cos(x)   con(x)
tan(x)   tan(x)
atan(x)  atan(x)
exp(x)   e `x`:sup:
log(x)   log(x)
sqrt(x)  sqrt(x)
abs(x)   abs(x)
sign(x)  x / \|x\|
======== ===========

入出力
------

.. code-block:: fortran

  PRINT * , A

\*はフォーマット指定。\*を指定すると適当な書式が選択される。(コンパイラ依存)

WRITEで同じ事ができますが、冗長になってしまうのでPRINTを使う。

.. code-block:: fortran

  READ * , A, B, C

PRINTと同様に\*を指定すると、適切な書式が自動で指定されます。

* ENTERが入力されるまで読み込みます
* 複数並べると、スペース区切りで読み込みを行います

配列
----
* インデックスはデフォルトでは1から
* メモリ上にはColumn Majorの順で配置される

.. code-block:: fortran

  REAL, DIMENSION(5) :: A
  REAL B(5), C(5)
  INTEGER, DIMENSION(3, 3) :: D

インデックスを0から指定したい場合は以下のように宣言する。

.. code-block:: fortran

  REAL A(0:5)

配列の初期化
^^^^^^^^^^^^

.. code-block:: fortran

  ! 全て0に初期化
  REAL :: a(10) = 0
  ! 多次元配列も同様
  INTEGER, DIMENSION(10, 10) :: b = 1

配列構成子
^^^^^^^^^^

/(ここに配列の構成を記述)/

.. code-block:: fortran

  INTEGER A(5)
  A = (/ 1, 2, 3, 4, 5 /)
  INTEGER :: B(5) = (/ 1, 2, 3, 4, 5 /)
  REAL :: C(6) = (/2., 4., 6., 8., 10., 12. /)
  ! 1,2,3,4,5 : DO型反復
  INTEGER :: D(5) = (/ (i,i=1,5) /)
  ! 5,10,15,20,25,30
  REAL :: E(6) = (/ (i*5,i=1,6) /)

reshape関数を使うことによって更に柔軟な指定が可能になります

.. code-block:: fortran

  ! 1,3,5
  ! 2,4,6
  REAL :: A(2,3) = RESHAPE( (/1., 2., 3., 4., 5., 6./), (/2,3/) )
  REAL :: B(2,3) = RESHAPE( (/1., 2., 3., 4., 5., 6./), SHAPE(a) )
  ! DO型反復も使用可能
  ! 1,5,9
  ! 2,6,10
  ! 3,7,11
  ! 4,8,12
  INTEGER :: C(4,3) = RESHAPE( (/ (i,i=1,12) /), SHAPE(b) )

一括代入
^^^^^^^^

.. code-block:: fortran

  INTEGER A(3)
  ! 10,10,10
  A = 10
  ! 11,11,11
  A = A + 1
  INTEGER B(3), C(3)
  B = 10
  C = 10
  ! 20,20,20
  A = B + C

ループ
------

.. code-block:: fortran

      DO 20 I=1, M
        DO 10 J=2, N
          a(I,J) = I*M
 10     CONTINUE
 20   CONTINUE

GOTO文
------

.. code-block:: fortran

      GOTO 10
      GO TO 10
  10  IF A.LT.B PRINT * , A

if文
----

.. code-block:: fortran

  IF(A.LT.B) PRINT * , A

  IF(A.GT.B) THEN
    PRINT * , B
  ELSE
    PRINT * , A

  IF(A.EQ.B) THEN
    PRINT * , A
  ELSE IF(A.LT.B) THEN
    PRINT * , A
  ELSE
    PRINT * , B

比較演算子
^^^^^^^^^^

======== ======== ==========================
Operator or       Description
======== ======== ==========================
A.LT.B   A < B    Less Than
A.LE.B   A <= B   Less than over Eaual to
A.EQ.B   A == B   EQual to
A.NE.B   A /= B   Not Equal to 
A.GT.B   A > B    Greater Than
A.GE.B   A >= B   Greater than over Equal to
======== ======== ==========================

論理演算子
^^^^^^^^^^

======== ============== ===================
Operator Description    Usage
======== ============== ===================
.NOT.    not            .NOT. A.EQ.B
.AND.    and            A.EQ.B .AND. A.EQ.C
.OR.     or             A.LT.B .OR. A.LT.C
.EQV.    logical eq     A<0 .EQV. B<0
.NEQV.   logical not eq A<0 .NEQV. B<0 
======== ============== ===================

関数
----
PROGRAMではなくSUBROUTINEで宣言する

.. code-block:: fortran

  SUBROUTINE HOGE(A, B, C)
    INTEGER A
    REAL B
    CHARACTER C
  END SUBROUTINE

.. author:: default
.. categories:: none
.. tags:: fortran
.. comments::
