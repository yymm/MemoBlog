MySQL-SQLAlchemyなFlask
=======================
環境 : CentOS 5.3


MySQLの準備
-----------
yumで必要な物を揃える。

.. code-block:: bash

  % sudo yum install mysql-devel
  % sudo yum install mysql-server

初期設定

.. code-block:: bash

  % mysql_secure_installation

色々聞かれるので答えたり、空エンターしたりする。詳しくは以下のリンク参照。

`データベースサーバー構築(MySQL) - CentOSで自宅サーバー構築 <http://centossrv.com/mysql.shtml>`_

MySQLサーバ起動

.. code-block:: bash

  % sudo /etc/init.d/mysqld start

Pythonの準備
------------
MySQLdbがないと使えないのでpipする。

.. code-block:: bash

  % pip install mysql-python 

mysql-develが入ってないと失敗します。

SQLAlchemyな準備
----------------
これで、create_engineするときにmysqlを指定できるようになった。

.. code-block:: python

  from sqlalchemy import create_engine
  engine = create_engine('mysql+mysqldb://root:<password>@localhost/<db_name>', encoding='utf-8')

自分の場合これをFlaskアプリ内で使ってみた。

SQLAlchemyでMySQLを使う場合、MySQLのAPIを使うことができるような。

`MySQL — SQLAlchemy 0.9 Documentation <http://docs.sqlalchemy.org/en/rel_0_8/dialects/mysql.html>`_


.. author:: default
.. categories:: none
.. tags:: python, MySQL
.. comments::
