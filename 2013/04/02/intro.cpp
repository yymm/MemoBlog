/* 宣言 */
extern int x;
std::size_t numDigits(int number);
class Widget;
template<typename T>
class GraphNode;
// extern宣言
// * 外部の変数にアクセスできるキーワード

// size_t
// * 何かを数えるときに使う「符号なし整数」をtypedefしたもの


/* 定義 */
std::size_t numDigits(int number)
{
	std::size_t digitsSoFar = 1;
	while ((number /= 10) != 0)
		++digitsSoFar;
	return digitsSoFar;
}
template<typename T>
class GraphNode
{
	public:
		GraphNode();
		~GraphNode();
};


/* デフォルトコンストラクタ */
class A
{
	public:
		A();	// デフォルトコンストラクタ
};
class B
{
	public:
		explicit B(int x=0, bool b=true)	// デフォルトコンストラクタ
		{
		}
};
class C
{
	public:
		explicit C(int x);	// デフォルトコンストラクタではない
};


/* explicitキーワード */
void doSomething(B bObject)
{
	std::cout << "B型のオブジェクトを引数に取る関数";
}
B bObj1;
B bObj2(28);		// int値の28からB型のオブジェクトを生成
doSomething(28);	// エラー!: intからB型オブジェクトへの暗黙の型変換はされない
doSomething(B(28));	// 問題ない: B型のオブジェクトを使ってintをBに変換している
// explicit
// * 暗黙的な型変換を禁止するキーワード
// * explicitを付けないコンストラクタだと予想外の型変換を起こす可能性がある
// * 下記のコードもexplicitを付けないと暗黙的に型変換をしてしまいエラーにならず通ってしまう
// * 特に理由がなければ、暗黙的な型変換をしないようにコンストラクタはexplicit付きで宣言する

/* コピーコンストラクタ */
class Widget
{
	public:
		Widget();								// デフォルトコンストラクタ
		Widget(const Widget& rhs);				// コピーコンストラクタ
		Widget& operator=(const Widget& rhs);	// コピー代入演算子
		~Widget();
};
Widget w1;		// デフォルトコンストラクタが使われる
Widget w2(w1);	// コピーコンストラクタが使われる
w1 = w2;		// コピー代入演算子が使われる
Widget w3=w2;	// コピーコンストラクタが使われる！ => Widget w2(w1)とWidget w2=w1は同じ動作
bool hasAcceptableQuery(Widget w);
Widget aWidget;
if (hasAcceptableQuery(Widget w))	// コピーコンストラクタが実行
{
	// ユーザー定義型を値渡しするのは良くない。一般にはconst参照渡しが良い。
}
// コピーコンストラクタ
// * 同じ型の別のオブジェクトで初期化するときに使う
// コピー演算子
// * 同じ型の別のオブジェクトを代入するときに使う

/* 未定義な動作 */
int* p=0;				// pがヌルポインタ
std::cout << *p;		// ヌルポインタが示す場所を取り出そうとすると動作は未定義になる
char name[] = "Hoge";	// 要素数は6
char c = name[10];		// 無効な添字の要素にアクセスしようとすると動作は未定義になる
// undefined
// * C++ではこのような未定義な動作をかけてしまう(JavaやC#ではない)
// * C++では未定義な動作をするコードをできるだけ書かないようにする注意が必要


/* シグネチャ */
// * メソッドや関数の名前、戻り値、引数の型などの組み合わせのこと


/* インターフェース */
// * JavaやC#にあるInterface宣言とは違う使い方をしてます
// * 関数のシグネチャやクラスのアクセス可能な要素などを意味する
// * テンプレート型のパラメータを意味することもある


/* 命名法 */
// わかり易い名前を心がける
// * 略記について
const Rational operator*(const Rational& lhs, const Rational& rhs);	// left-hand sideとright-hand sideのこと
Widget* pw;	// ポインタ変数には接頭語に"p"をつける
class GameCharacter;
GameCharacter* pgc;
GameCharactor::move()
{
	mf = "hoge";	// メンバ変数のことをmfと書くこともある
}
