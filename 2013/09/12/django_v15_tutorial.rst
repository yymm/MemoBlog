Django 1.5 チュートリアル まとめ
================================

1年くらいチャレンジして挫折したDjangoをやってみる。pollsのアレである。

仕事の傍らFlaskでアプリケーションを作った経験のおかげかなんとかチュートリアルはできた。

もう英語を読みなおすのは辛いので日本語でメモしておく。

`Writing your first Django app, part 1 | Django documentation | Django <https://docs.djangoproject.com/en/1.5/intro/tutorial01/>`_

part6まである。辛かった。part3くらいで諦めそうになった。

Django 1.6が開発中ですが、1.5です。

`Django 1.6 release notes - UNDER DEVELOPMENT | Django documentation | Django <https://docs.djangoproject.com/en/dev/releases/1.6/>`_

---------------------------------------

.. contents:: 目次

---------------------------------------

環境
----

* Python 3.3.2
* Django 1.5.2
* pythonz

pythonのバージョン管理には、pythonbrewとかpythonzとかpyenvとか色々あるが、

自分はデフォルト環境のPythonのpipにvirtualenv & virtualenvwrapperを入れて、pythonzで色んなバージョンを入れることで管理している。

.. code-block:: bash

  % mkvirtualenv -p /path/to/pythonz/pythons/CPython-2.7.5/bin/python2.7 Django
  (Django)% pip install django

プロジェクト作成 & データベース設定
------------------------------------

.. code-block:: bash

  % django-admin startproject mysite
  % cd mysite

データベースの設定をするために、mysite/setting.pyを編集する。

DATABASESでSQliteを使用する設定をする。

.. code-block:: python

  DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3', # Add 'postgresql_psycopg2', 'mysql', 'sqlite3' or 'oracle'.
        'NAME': 'sqlite3.db',                      # Or path to database file if using sqlite3.
        # The following settings are not used with sqlite3:
        'USER': '',
        'PASSWORD': '',
        'HOST': '',                      # Empty for localhost through domain sockets or '127.0.0.1' for localhost through TCP.
        'PORT': '',                      # Set to empty string for default.
     }
  }

テーブル作成。

.. code-block:: bash

  % python manage.py syncdb

データベース関連を編集した際にはこのコマンドを実行する。

Admin画面を作る
---------------

* settings.py : 1箇所
* urls.py : 3箇所

のコメントアウトを解除するだけ。

**settings.py**

.. code-block:: python

    INSTALLED_APPS = (
        'django.contrib.auth',
        'django.contrib.contenttypes',
        'django.contrib.sessions',
        'django.contrib.sites',
        'django.contrib.messages',
        'django.contrib.staticfiles',
        # Uncomment the next line to enable the admin:
        'django.contrib.admin',
        # Uncomment the next line to enable admin documentation:
        # 'django.contrib.admindocs',
    )

**urls.py**

.. code-block:: python

    # Uncomment the next two lines to enable the admin:
    from django.contrib import admin
    admin.autodiscover()

    urlpatterns = patterns('',
        # Examples:
        # url(r'^$', 'mysite.views.home', name='home'),
        # url(r'^mysite/', include('mysite.foo.urls')),

        # Uncomment the admin/doc line below to enable admin documentation:
        # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

        # Uncomment the next line to enable the admin:
        url(r'^admin/', include(admin.site.urls)),
    )

コメントアウトしたら以下のコマンドを実行して、http://127.0.0.1:8000/admin/で確認。

.. code-block:: bash

  % python manage.py syncdb
  % python manage.py runserver

HOSTとPORTの変更
^^^^^^^^^^^^^^^^

.. code-block:: bash

  % python manage.py runserver XXX.XXX.XXX.XXX:XXXX

http://XXX.XXX.XXX.XXX:XXXX/で確認。

アプリケーション作成
--------------------

pollsアプリケーション(投票アプリ)を作る。

.. code-block:: bash

  % python manage.py startapp polls

モデル作成
^^^^^^^^^^

polls以下にあるmodels.py。

.. code-block:: python

  import datetime
  from django.utils import timezone
  from django.db import models

  class Poll(models.Model):
      question = models.CharField(max_length=200)
      pub_date = models.DateTimeField('date published')

      #def __unicode__(self):
      def __str__(self):
          return self.question
      
      def was_published_recently(self):
          now = timezone.now()
          return now - datetime.timedelta(days=1) <= self.pub_date <  now

  class Choice(models.Model):
      poll = models.ForeignKey(Poll)
      choice_text = models.CharField(max_length=200)
      votes = models.IntegerField(default=0)

      #def __unicode__(self):
      def __str__(self):
          return self.choice_text

python3系を使う場合は__unicode__でなく__str__を使わないと正常に動かなかった。詳しいことはわからないのでわかる方がいれば是非。

モデル操作
''''''''''

manage.py shellを使って操作してみる。

.. code-block:: bash

  $ python manage.py shell
  >>> from polls.models import Poll, Choice
  >>> Poll.objects.all()
  >>> Poll.objects.filter(id=1)
  >>> Poll.objects.filter(question__startswith='SearchWord')
  >>> Poll.objects.get(pub_date__year=current_year)
  >>> p = Poll.objects.get(pk=1) # Primary_Key
  >>> c = p.choice_set.create(choice_text='Just hacking again', votes=0)
  >>> c.delete()

Django ORMの詳細はドキュメントを読もう。ここでは扱わない。

`Models and databases | Django documentation | Django <https://docs.djangoproject.com/en/1.5/topics/db/>`_

admin画面でモデル操作
''''''''''''''''''''''

admin画面からもモデルを操作できる。

作成したアプリケーションのフォルダ(pollsフォルダ)にadmin.pyを作成する。

django.contribパッケージにあるadminを使用して、adminサイトにモデルを追加する。(admin.site.register)

.. code-block:: python

  from django.contrib import admin
  from polls.models import Poll, Choice
  
  #class PollAdmin(admin.ModelAdmin):
      #fields = ['pub_date', 'question']
  
  class PollAdmin(admin.ModelAdmin):
      fieldsets = [
              (None, {'fields': ['question']}),
              ('Date information', {'fields': ['pub_date']}),
      ]

  #class PollAdmin(admin.ModelAdmin):
      #fieldsets = [
              #(None,               {'fields': ['question']}),
              #('Date information', {'fields': ['pub_date'], 'classes': ['collapse']}),
      #]
  
  admin.site.register(Poll, PollAdmin)
  admin.site.register(Choice)

表示する項目はadmin.ModelAdminを継承したクラスを作成し、fieldsまたはfieldsetsに設定する。

リレーションのあるモデルはインラインで表示できる方が見やすい。そんな書き方もできる。

.. code-block:: python

  from django.contrib import admin
  from polls.models import Choice, Poll
  
  class ChoiceInline(admin.StackedInline):
      model = Choice
      extra = 3 # インライン時のデフォルト表示数
  
  class PollAdmin(admin.ModelAdmin):
      fieldsets = [
          (None,               {'fields': ['question']}),
          ('Date information', {'fields': ['pub_date'], 'classes': ['collapse']}),
      ]
      inlines = [ChoiceInline]
  
  admin.site.register(Poll, PollAdmin)

admin.StackedInlineを継承したクラスを作成し、リレーションのある対象のクラスのinlinesに指定すればいい。

inlinesはListなので複数指定する事が可能。

StackedInlineの代わりにTabularInlineを使うとテーブル形式で表示できる。(ちょっとスッキリする)

adminモジュールがあるcontribパッケージについてはドキュメントを参照。

`contrib packages | Django documentation | Django <https://docs.djangoproject.com/en/1.5/ref/contrib/>`_

admin画面のカスタム
'''''''''''''''''''

先ほどadmin.pyに作成した表示内容を指定するクラス(PollAdmin)に表示する項目を追加することでカスタマイズ出来る。

list_display = (Tuple)を追加することでchangeの表示項目を変更できる。

.. code-block:: python

    class PollAdmin(admin/.ModelAdmin):
        # ...(同じ)
        list_display = ('question', 'pub_date', 'was_published_recently')

list_displayにはメソッドも追加することができる。

表示内容を変更することも可能。表示内容の変更はmodels.pyで行う。

.. code-block:: python

  class Poll(models.Model):
      # ...(同じ)
      def was_published_recently(self):
          return self.pub_date >= timezone.now() - datetime.timedelta(days=1)
      was_published_recently.admin_order_field = 'pub_date'
      was_published_recently.boolean = True
      was_published_recently.short_description = 'Published recently?'

指定している項目の説明

* admin_order_field : 並べ替え指定
* boolean : boolean型指定
* short_description : 表示される説明。指定しないと'was_published_recently'になる。

フィルター、検索、階層ナビゲーションなども追加できる。便利。

list_filter, search_fields, date_hierarchyなどを追加することでこれらの項目を追加できる。

.. code-block:: python

    class PollAdmin(admin/.ModelAdmin):
        # ...(同じ)
        list_filter = ['pub_date']      # フィルタの追加
        search_fields = ['question']    # 検索の追加
        date_hierarchy = 'pub_date'     # 日付ナビの追加

View作成
^^^^^^^^

DjangoでいうViewは、MVCフレームワークで言うControllerに相当する。(DjangoはMVT[Model-View-Template]。 `FAQ: 全般 — Django v1.0 documentation <http://www.djangoproject.jp/doc/ja/1.0/faq/general.html#django-mvc-controller-view-view-template>`_ )

polls/views.pyにviewの処理を書いていく。以下は一番シンプルな例。

.. code-block:: python

  from django.http import HttpResponse

  def index(request):
      return HttpResponse('Hello! You are at the poll index')

次にurlpatternsを書いていく。urls.pyに記述する。

polls/urls.py

.. code-block:: python

  from django.conf.urls import patterns, url
  
  from polls import views
  
  urlpatterns = patterns('',
      url(r'^$', views.index, name='index')
  )

mysite.urls.pyのurlpatternsにも以下を追加する。

.. code-block:: python

  url(r'^polls/', include('polls.urls')),

これで、http://localhost:8000/polls/で'Hello! You are at the poll index'と表示される。

url関数の引数は先頭から

1. ルーティング(正規表現)
2. viewの関数
3. テンプレートから見える名前

ざっくりの説明なので詳細は -> `URL dispatcher | Django documentation | Django <https://docs.djangoproject.com/en/1.5/topics/http/urls/#naming-url-patterns>`_

テンプレートの使用
'''''''''''''''''''

polls/templates/polls/を作成して、index.html、detail.htmlを作成します。

polls/index.html

.. code-block:: html

  {% if latest_poll_list %}
  	<ul>
  		{% for poll in latest_poll_list %}
  		<li>
  			<a href="{% url 'polls:detail' poll.id %}">{{ poll.question }}</a>
  		</li>
  		{% endfor %}
  	</ul>
  {% else %}
  	<p>No polls are available.</p>
  {% endif %}

polls/detail.html

.. code-block:: html

  <h1>{{ poll.question }}</h1>
  <ul>
  {% for choice in poll.choice_set.all %}
  	<li>{{ choice.choice_text }}</li>
  {% endfor %}
  </ul>

.. note:: Jinja2がいいかも?

  記法はJinja2とよく似ている。Jinja2を使用したことのある人であれば違和感なく使えそう。
  
  しかし、Jinja2のほうが優れた機能が多いのでDjangoテンプレートなんて使ってられないッ！という方が多いかと思います。
  
  そのような場合は、django-jinjaというパッケージがあるのでそちらを。( `django-jinja — django-jinja 0.19 documentation <https://django-jinja.readthedocs.org/en/latest/>`_ )

このままでは作成したテンプレートを表示できないので、viewを変更します。

テンプレートを使用するview
'''''''''''''''''''''''''''

チュートリアルでは、django.shortcutsを使わない方法も紹介しているのですがコードが冗長になるので紹介しません。

polls/views.py

.. code-block:: python
  
  from django.shortcuts import render, get_object_or_404
  
  from polls.models import Poll
  
  def index(request):
      latest_poll_list = Poll.objects.order_by('-pub_date')[:5]
      context = {'latest_poll_list' : latest_poll_list}
      return render(request, 'polls/index.html', context)
  
  def detail(request, poll_id):
      poll = get_object_or_404(Poll, pk = poll_id)
      return render(request, 'polls/detail.html', {'poll' : poll})

render関数でテンプレートを指定する。

上記のコードでcontextで表される辞書型の引数にはテンプレートで使用可能な変数を指定します。

.. note:: shortcutsモジュール

  ここには便利関数が定義してあります。どのくらい便利かというと

  例) ここで使っているget_object_or_404を使わないで書こうとすると、Poll.object.get(pk=poll_id)をtry-exceptしてHttp404を返すコードを書かないといけない。最低でも5行かかる。get_object_or_404を使えばそれが1行でできる。

  知ってたら積極的に使っていく感じです。

  `Django shortcut functions | Django documentation | Django <https://docs.djangoproject.com/en/1.5/topics/http/shortcuts/>`_

form処理
^^^^^^^^

いよいよ投票出来るようにします。先ほどのdetail.htmlにformをつけます。

polls/detail.html

.. code-block:: html

  <h1>{{ poll.question }}</h1>
  
  {% if error_message %}<p><strong>{{ error_message }}</strong></p>{% endif %}
  
  <form action="{% url 'polls:vote' poll.id %}" method="post">
  {% csrf_token %}
  {% for choice in poll.choice_set.all %}
      <input type="radio" name="choice" id="choice{{ forloop.counter }}" value="{{ choice.id }}" />
      <label for="choice{{ forloop.counter }}">{{ choice.choice_text }}</label><br />
  {% endfor %}
  <input type="submit" value="Vote" />
  </form>

.. note:: forloop - django template -

  djangoテンプレートのfor文ではforloopが使える。

  counter, recounter, first, last, parentloopといったforループ中で便利な機能がある。

  `Built-in template tags and filters | Django documentation | Django <https://docs.djangoproject.com/en/1.5/ref/templates/builtins/#std:templatetag-for>`_  

.. note:: csrf_token

  Cross Site Request Forgery対策のためform要素に付ける。

  場所はformタグのすぐあと。

  `Cross Site Request Forgery protection | Django documentation | Django <https://docs.djangoproject.com/en/1.5/ref/contrib/csrf/>`_
  
データがpostされる先はpolls.voteと指定してあるので、viewにあるvote関数を実装する。

polls/views.py

.. code-block:: python

  from django.http import HttpResponse, HttpResponseRedirect
  from django.core.urlresolvers import reverse

  # ...

  def vote(request, poll_id):
      p = get_object_or_404(Poll, pk=poll_id)
      try:
          selected_choice = p.choice_set.get(pk=request.POST['choice'])
      except (KeyError, Choice.DoesNotExist):
          return render(request, 'polls/detial.html', {
              'poll' : p,
              'error_message' : "You didn't select a choice.",
              })
      else:
          selected_choice.votes += 1
          selected_choice.save()
          return HttpResponseRedirect(reverse('polls:results', args=(p.id,)))

これであとは、polls/urls.pyに

.. code-block:: python

  url(r'^(?P<poll_id>\d+)/vote/$', views.vote, name='vote'),

と書いてあれば投票出来る。

.. note:: shortcuts.redirectを使う

  HttpResponseRedirect(reverse(...), args=...)は冗長なのでshortcuts.redirectを使いましょう。

  使い方は簡単。

  return redirect('polls:results', poll_id=p.id)

  わかりやすい！

このままで投票はできたけど結果がわからないので、resultsも実装する。

polls/templates/polls/results.html

.. code-block:: html

  <h1>{{ poll.question }}</h1>
  
  <ul>
  {% for choice in poll.choice_set.all %}
      <li>{{ choice.choice_text }} -- {{ choice.votes }} vote{{ choice.votes|pluralize }}</li>
  {% endfor %}
  </ul>
  
  <a href="{% url 'polls:detail' poll.id %}">Vote again?</a>

polls/views.py

.. code-block:: python

  def results(request, poll_id):
      poll = get_object_or_404(Poll, pk=poll_id)
      return render(request, 'polls/results.html', {'poll': poll})

viewの改善 - generic views -
''''''''''''''''''''''''''''

Djangoにはgeneric viewsというviewをサポートするモジュールがあり、これを使うことでviewsをシンプルに記述することができます。

genericをインポートし抽象クラスが用意されているのでそれらを継承して使います。

polls/urls.pyとpolls/views.pyを修正し以下のようにします。

.. code-block:: python

  from django.conf.urls import patterns, url
  
  from polls import views
  
  urlpatterns = patterns('',
      url(r'^$', views.IndexView.as_view(), name='index'),
      url(r'^(?P<pk>\d+)/$', views.DetailView.as_view(), name='detail'),
      url(r'^(?P<pk>\d+)/results/$', views.ResultsView.as_view(), name='results'),
      url(r'^(?P<poll_id>\d+)/vote/$', views.vote, name='vote'),
  )

viewsの関数の指定を<class>.as_view()にし、ルーティングはpoll_idをpkに変更します。

.. code-block:: python

  # ...

  from django.views import generic
  
  class IndexView(generic.ListView):
      template_name = 'polls/index.html'
      context_object_name = 'latest_poll_list'
  
      def get_queryset(self):
          """Return the last five published polls."""
          return Poll.objects.order_by('-pub_date')[:5]
  
  
  class DetailView(generic.DetailView):
      model = Poll
      template_name = 'polls/detail.html'
  
  
  class ResultsView(generic.DetailView):
      model = Poll
      template_name = 'polls/results.html'

  # ...

indexとdetailとresultsをgeneric.ListView又はgeneric.DetailViewを継承したクラスに変更します。

ListViewとDetailView共通の部分はテンプレートの指定です。template_nameで指定できますが、指定しないこともできます。

指定しない場合は<app name>/<model name>_list.html or <app name>/<model name>_detail.htmlとなります。

ListViewでは常に指定した同じデータを返します。言い換えると返すデータをコードで指定できるということです。

DetailViewではmodelに指定したオブジェクトから、与えられたprimary key(pk)をもとにデータを自動的に取得してくれます。

なので、polls/urls.pyでpoll_idからpkに変更したということです。

チュートリアルではこのくらいの説明しかありませんが、もっと詳しく知ったほうがいいでしょう。

`Class-based views | Django documentation | Django <https://docs.djangoproject.com/en/1.5/topics/class-based-views/>`_

Djangoのテスト
--------------

Djangoにはテストに関する機能も含まれています。優秀ですね。

実はこのPollアプリケーションは未来のデータ(発表されていないデータ)に関してバグを抱えています。

このバグを修正しつつテストコードを書いていきます。

modelのテスト
^^^^^^^^^^^^^

modelのPollにあるwas_published_recentlyは未来のデータがあった場合、それもヒットしてしまうバグを抱えています。

このことを検証するテストコードを書いてみます。

テストコードはtest.pyに記述します。test.pyの場所はそれぞれのアプリケーションフォルダ、つまりpolls以下に配置します。

.. code-block:: python

  import datetime
  
  from django.utils import timezone
  from django.test import TestCase
  
  from polls.models import Choice, Poll
  
  class PollMethodTests(TestCase):
  
      def test_was_published_recently_with_future_poll(self):
          """
          was_published_recently() should return False for polls whose
          pub_date is in the future
          """
          future_poll = Poll(pub_date=timezone.now() + datetime.timedelta(days=30))
          self.assertEqual(future_poll.was_published_recently(), False)

実行はコマンドラインで。

.. code-block:: bash

  $ python manage.py test polls
  Creating test database for alias 'default'...
  F
  ======================================================================
  FAIL: test_was_published_recently_with_future_poll (polls.tests.PollMethodTests)
  ----------------------------------------------------------------------
  Traceback (most recent call last):
    File "/path/to/mysite/polls/tests.py", line 16, in test_was_published_recently_with_future_poll
      self.assertEqual(future_poll.was_published_recently(), False)
  AssertionError: True != False
  
  ----------------------------------------------------------------------
  Ran 1 test in 0.001s
  
  FAILED (failures=1)
  Destroying test database for alias 'default'...

現在の時間を基準に検索をする必要があります。修正したコードが以下になります。

.. code-block:: python

    def was_published_recently(self):
        now = timezone.now()
        return now - datetime.timedelta(days=1) <= self.pub_date < now

これでテストが通るようになるはずです。

viewのテスト
^^^^^^^^^^^^

DjangoはViewをユーザーをシミュレートしたテストクライアント機能を備えています。それを利用してViewのテストをすることができます。

その仕組はコマンドラインでテストした結果を見るとわかりやすいので、ズラズラを書いてみます。

.. code-block:: python

  >>> from django.test.utils import setup_test_environment
  >>> setup_test_environment()
  >>> from django.test.client import Client
  >>> # create an instance of the client for our use
  >>> client = Client()
  >>> # get a response from '/'
  >>> response = client.get('/')
  >>> # we should expect a 404 from that address
  >>> response.status_code
  404
  >>> # on the other hand we should expect to find something at '/polls/'
  >>> # we'll use 'reverse()' rather than a harcoded URL
  >>> from django.core.urlresolvers import reverse
  >>> response = client.get(reverse('polls:index'))
  >>> response.status_code
  200
  >>> response.content
  '\n\n\n    <p>No polls are available.</p>\n\n'
  >>> # note - you might get unexpected results if your ``TIME_ZONE``
  >>> # in ``settings.py`` is not correct. If you need to change it,
  >>> # you will also need to restart your shell session
  >>> from polls.models import Poll
  >>> from django.utils import timezone
  >>> # create a Poll and save it
  >>> p = Poll(question="Who is your favorite Beatle?", pub_date=timezone.now())
  >>> p.save()
  >>> # check the response once again
  >>> response = client.get('/polls/')
  >>> response.content
  '\n\n\n    <ul>\n    \n        <li><a href="/polls/1/">Who is your favorite Beatle?</a></li>\n    \n    </ul>\n\n'
  >>> response.context['latest_poll_list']
  [<Poll: Who is your favorite Beatle?>]

はじめの5行はTestCaseが用意してくれているので、test.pyを書く際にはあまり気にしないが知っておいたほうがいい。

client.getは直接URLをハードコーディングするのは良くないのでreverseを使う。

毎回コマンドを実行するわけにはいかないので、test.pyにテストを書いていく。

ViewIndexとDetailIndexのテスト

.. code-block:: python

  def create_poll(question, days):
      """
      Creates a poll with the given `question` published the given number of
      `days` offset to now (negative for polls published in the past,
      positive for polls that have yet to be published).
      """
      return Poll.objects.create(question=question,
          pub_date=timezone.now() + datetime.timedelta(days=days))
  
  class PollViewTests(TestCase):
      def test_index_view_with_no_polls(self):
          """
          If no polls exist, an appropriate message should be displayed.
          """
          response = self.client.get(reverse('polls:index'))
          self.assertEqual(response.status_code, 200)
          self.assertContains(response, "No polls are available.")
          self.assertQuerysetEqual(response.context['latest_poll_list'], [])
  
      def test_index_view_with_a_past_poll(self):
          """
          Polls with a pub_date in the past should be displayed on the index page.
          """
          create_poll(question="Past poll.", days=-30)
          response = self.client.get(reverse('polls:index'))
          self.assertQuerysetEqual(
              response.context['latest_poll_list'],
              ['<Poll: Past poll.>']
          )
  
      def test_index_view_with_a_future_poll(self):
          """
          Polls with a pub_date in the future should not be displayed on the
          index page.
          """
          create_poll(question="Future poll.", days=30)
          response = self.client.get(reverse('polls:index'))
          self.assertContains(response, "No polls are available.", status_code=200)
          self.assertQuerysetEqual(response.context['latest_poll_list'], [])
  
      def test_index_view_with_future_poll_and_past_poll(self):
          """
          Even if both past and future polls exist, only past polls should be
          displayed.
          """
          create_poll(question="Past poll.", days=-30)
          create_poll(question="Future poll.", days=30)
          response = self.client.get(reverse('polls:index'))
          self.assertQuerysetEqual(
              response.context['latest_poll_list'],
              ['<Poll: Past poll.>']
          )
  
      def test_index_view_with_two_past_polls(self):
          """
          The polls index page may display multiple polls.
          """
          create_poll(question="Past poll 1.", days=-30)
          create_poll(question="Past poll 2.", days=-5)
          response = self.client.get(reverse('polls:index'))
          self.assertQuerysetEqual(
              response.context['latest_poll_list'],
               ['<Poll: Past poll 2.>', '<Poll: Past poll 1.>']
          )


  class PollIndexDetailTests(TestCase):
      def test_detail_view_with_a_future_poll(self):
          """
          The detail view of a poll with a pub_date in the future should
          return a 404 not found.
          """
          future_poll = create_poll(question='Future poll.', days=5)
          response = self.client.get(reverse('polls:detail', args=(future_poll.id,)))
          self.assertEqual(response.status_code, 404)
  
      def test_detail_view_with_a_past_poll(self):
          """
          The detail view of a poll with a pub_date in the past should display
          the poll's question.
          """
          past_poll = create_poll(question='Past Poll.', days=-5)
          response = self.client.get(reverse('polls:detail', args=(past_poll.id,)))
          self.assertContains(response, past_poll.question, status_code=200)

日付に関するテストを書いたが、このままでは未来のデータが入る部分でテストが失敗するのでViewを書き直す。

.. code-block:: python

  from django.utils import timezone

  class IndexView(generic.ListView):
      template_name = 'polls/index.html'
      context_object_name = 'latest_poll_list'
  
      def get_queryset(self):
          return Poll.objects.filter(
                  pub_date__lte=timezone.now()
                  ).order_by('-pub_date')[:5]
  
  
  class DetailView(generic.DetailView):
      model = Poll
      template_name = 'polls/detail.html'
  
      def get_queryset(self):
          return Poll.objects.filter(pub_date__lte=timezone.now())

これでテストが通るはず。

テストについて
^^^^^^^^^^^^^^

もし他のViewに対してテストを行う場合、多分大体同じようなテストコードを書くことになるだろうけど、そんなのは別にいいらしい。

確かに美しさとは離れているかもしれないが、一旦書いたテストのことは忘れて新機能を追加していこう。(一旦書いたテストは自分のコードが正しいことを証明してくれる。)

今回書いたテストはChoiceがあるPollには対応していないので、Choiceがある場合多くのテストが失敗する。まぁ。それは直せということだ。だって自分のコードが正しくないのだから。

そんなこんなで冗長なテストコードになってしまうかもしれないが、テストコードが冗長なのは悪いことではない。それよりも意識したほうがいいこともある。

1. 1つのModelやViewごとにテストクラスを生成する
2. テストする条件ごとに別々にテストメソッドを作成する
3. テストメソッド名はそのテストの内容を説明している

ここで紹介しているテスト技法は基本的なものだけである。他の優れたツールを使うことでもっと多くのことができる。

Selenium
''''''''

`Selenium - Web Browser Automation <http://docs.seleniumhq.org/>`_

Seleniumを使ってフロントエンド(html, javascript)のテストをする。

LiveServerTestCaseと組み合わせると連携が便利になる。

`Testing Django applications | Django documentation | Django <https://docs.djangoproject.com/en/1.5/topics/testing/overview/#django.test.LiveServerTestCase>`_

coverage.py
'''''''''''

`Ned Batchelder: coverage.py <http://nedbatchelder.com/code/coverage/>`_

コードカバレッジツールのcoverage.pyを使用する。ドキュメントにも使用方法について説明してある。

`Advanced testing topics | Django documentation | Django <https://docs.djangoproject.com/en/1.5/topics/testing/advanced/#topics-testing-code-coverage>`_

Look and Feel
-------------

cssや画像、javascriptを使って見た目を改善してみる。

作成する場所はpolls/static/polls。CSSファイル(style.css)を追加する。

polls/static/polls/style.css

.. code-block:: css

  li a {
    color: green;
  }

cssファイルの読み込みをindex.htmlでやってみると、

.. code-block:: html

  {% load staticfiles %}

  <link rel="stylesheet" type="text/css" href="{% static 'polls/style.css' %}" />

画像の読み込みもしてみたいかもしれない。

.. code-block:: css

  body {
    background: white url("images/background.gif") no-repeat right bottom;
  }

画像はpolls/static/polls/imagesに配置する。

cssファイルでもurl関数を使用して対象のファイルを指定することが出来る。

チュートリアルにはないTips
--------------------------

MySQLを使う
^^^^^^^^^^^

settings.pyを書き換える。

.. code-block:: python

  DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql', # Add 'postgresql_psycopg2', 'mysql', 'sqlite3' or 'oracle'.
        'NAME': 'XXXXX',                      # Or path to database file if using sqlite3.
        # The following settings are not used with sqlite3:
        'USER': 'root',
        'PASSWORD': 'password',
        'HOST': 'localhost',                      # Empty for localhost through domain sockets or '127.0.0.1' for localhost through TCP.
        'PORT': '',                      # Set to empty string for default.
     }
  }

テーブル作成 & MySQL-Pythonのインストール。

.. code-block:: bash

  % pip install mysql-python
  % mysql -u root -p password
  mysql> create database XXXXX;
  mysql> exit;
  % python manage.py syncdb



Django Suit
^^^^^^^^^^^

誰でもかっこつけたい。Admin画面もきっとそう。

`Django Suit documentation — Django Suit 0.2.2 documentation <http://django-suit.readthedocs.org/en/develop/>`_

.. code-block:: bash

  $ workon Django
  (Django)$ pip install django-suit

settings.pyに以下を追加

.. code-block:: python

  INSTALLED_APPS = (
      ...
      'suit',
      'django.contrib.admin',
  )

  from django.conf.global_settings import TEMPLATE_CONTEXT_PROCESSORS as TCP

  TEMPLATE_CONTEXT_PROCESSORS = TCP + (
      'django.core.context_processors.request',
  )

`Django Suit - Modern theme for Django admin interface <http://djangosuit.com/>`_


.. author:: default
.. categories:: none
.. tags:: python, Django
.. comments::
