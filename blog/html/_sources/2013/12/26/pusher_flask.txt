FlaskでPusherを使う
===================

FlaskでPusher使ってみたのでメモ。

.. image:: image.gif

.. contents::

登録してApp作成
---------------

`Pusher | HTML5 WebSocket Powered Realtime Messaging Service <http://pusher.com/>`_

Signup。

管理画面にログインできるようになるので、New appをクリックして新しいappを作成。

とりあえず使ってみる
--------------------

前に必要なモジュールを入れる。

.. code-block:: bash

  $ mkvirtualenv Pusher_Sample
  $ pip install pusher flask

App Keysにコード例があるので参考にする。

手っ取り早く、以下のコードを実行するとApp Keysのページでalertするみたいなのでpythonインタプリタからコピペで実行してみます。

.. code-block:: python

  import pusher
  
  p = pusher.Pusher(
    app_id='<id>',
    key='<key>',
    secret='<secret key>'
  )
  p['test_channel'].trigger('my_event', {'message': 'hello world'})

hello worldが出てくるはずです。

Debug Consoleから詳しい様子を確認できます。

.. image:: debug.png

試しに作ってみたやつ
--------------------

`yymm/Flask_Pusher_Sample <https://github.com/yymm/Flask_Pusher_Sample>`_

((((((((((っ･ω･)っ ﾌﾞ-ﾝをクリックすると、AjaxでPostして((((((((((っ･ωΣ[柱]ｶﾞｺｯ! をPusherに投げます。

Pusherになにか来たらevent1でalertするだけ。

静的なサイトにしか見えませんが、その後ろではただalertを出すためだけにPusherが働いています。

.. code-block:: python

  # -*- encoding: utf-8 -*-
  
  from flask import Flask, render_template, redirect, url_for, request
  import pusher
  
  app = Flask(__name__)
  
  app.config.from_pyfile("app.cfg")
  
  p = pusher.Pusher(
      app_id = app.config["ID"],
      key = app.config["KEY"],
      secret = app.config["SECRET"]
  )
  
  @app.route('/')
  def index():
      return render_template('index.html')
  
  @app.route('/pusher', methods=["POST"])
  def pusher():
      if request.method == 'POST':
          p['channel1'].trigger('event1', {'message': "((((((((((っ･ωΣ[柱]ｶﾞｺｯ!"})
      return 'ok'
  
  if __name__ == '__main__':
      app.debug = True
      app.run()

Javascriptはこんな感じ。

.. code-block:: javascript

  var pusher = new Pusher('<key>');
  var channel = pusher.subscribe('channel1');
  channel.bind('event1', function(data) {
    alert(data.message);
  });
  $('#push').click( function(){
    $.ajax({
      type: "POST",
      url: "{{ url_for('pusher') }}",
      contentType: 'application/json',
      success: function(data) {
        console.log(data);
      }
    });
  });

嵌ったこととか
--------------

このエラー( `How to fix "Timestamp expired" response from REST API when triggering an event. / Publishing/Triggering Events / Knowledge Base - Pusher Support <https://pusher.tenderapp.com/kb/publishingtriggering-events/how-to-fix-timestamp-expired-response-from-rest-api-when-triggering-an-event>`_ )

.. code-block:: bash

  Timestamp expired: Given timestamp (2013-06-17T15:39:38Z) not within 600s of server time (2013-06-17T17:09:21Z)

Pusherサーバと時間がずれているとダメみたい。

手元のサーバーの時間を合わせる。

.. code-block:: bash

  $ sudo date MMddhhmmyyyy
  もし合わなくて'sudo: timestamp too far in the future:'と言われたら
  $ sudo -K
  $ sudo date MMddhhmmyyyy

頑張って合わせたが、なんか日本の時間とはずいぶんずれたような気がしたがあまり気にしない。

おまけ - Herokuにデプロイ
-------------------------

`Pusher Test <http://pusher-flask.herokuapp.com/#>`_

手順。

1. Herokuの準備
^^^^^^^^^^^^^^^

適当なAppを追加して、Add-onにPusherのSandbox(無料版)を追加します。

gitのクローン先をコピペしてremoteに追加。

.. code-block:: bash

  $ git remote add heroku git@heroku.com:<app name>

Pusher Add-onをクリックすると、Heroku in Pusherな管理画面が出てくる。

.. image:: heroku.png
   :height: 300px
   :width: 600px

herokuのほうを使う。

2. アプリ側の準備
^^^^^^^^^^^^^^^^^

Procfileを作成。

.. code-block:: python

  web: gunicorn app:app

requirements.txtを作成。

.. code-block:: bash

  $ pip freeze > requirements.txt

3. HerokuのPusherを使う準備
^^^^^^^^^^^^^^^^^^^^^^^^^^^

HerokuのPusherを使う場合、Pythonのコードを書き換える必要がある。

Pusherのprivate keyを晒すわけにはいかないので、Herokuの環境変数に持たせる。

その影響で、アプリのPusherのオブジェクトを生成している部分を書き換える必要がある。

.. code-block:: diff

  - app.config.from_pyfile("app.cfg")
  - p = pusher.Pusher(
  -     app_id = app.config["ID"],
  -     key = app.config["KEY"],
  -     secret = app.config["SECRET"]
  - )

  + p = pusher.pusher_from_url()

※参考 : `pusher/pusher_client_python <https://github.com/pusher/pusher_client_python>`_

pusher_from_urlは引数なしだと環境変数PUSHER_URLを参照しているので、Herokuに環境変数PUSHER_URLを追加する。

.. code-block:: bash

  $ heroku config:app PUSHER_URL="http://<key>:<private key>@api.pusherapp.com/apps/<id>" --app <your app name>

URLはHeroku-Pusher管理画面のApp keysのRubyのexampleにあった。

4. あとはPushするだけ
^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

  $ git push heroku master

完成。


.. author:: default
.. categories:: none
.. tags:: Python
.. comments::
