/* constを使う１ マクロの欠点 */
// この使い方をするとコンパイラからはASPECT_RATIOは見えない
// 1.653という数字になってる
// デバックするときに困るかもしれない
#define ASPECT_RATIO 1.653

// マクロを定数に置き換えることで解決
const double AspectRatio = 1.653;

// 利点
// * マクロを使うと、ASPECT_RATIOが出てくるたびに機械的にそれを1.653に置き換える(コピーが大量発生)
// * 一方、AspectRatioは常に１つしか存在しない


/* constを使う２ 定数ポインタ */
// char*を使った定数文字列
// constが２回必要(charとポインタの２回)
const char* const authorName = "Nanashino Gonbe";
// 一般にはchar*よりstringを使ったほうが良い
const std::string authorName("Nanashino Gonbe");


/* constを使う３ クラスの持つ定数 */
// クラスで使う変数のスコープを限定するために、その定数をクラスのメンバにすることがある
// #defineでは再現不可能
// その定数が実際に１つだけ存在するようにstaticにする必要がある
class GamePlayer
{
	private:
		static const int NumTurns = 5;
		int scores[NumTurns];
};
// 問題
// * staticな整数型定数メンバであっても宣言時に初期化できない(昔のコンパイラを使っているならば)
class CostEstimate
{
	private:
		static const double FudgeFactor;	// ヘッダーファイルに書かれる
};
const double CostEstimate::FudgeFactor = 1.35;	// ソースダイルに書かれる
// 更に問題
// * GamePlayerのようにコンパイル時に「クラスの定数」が必要になった時、コンパイルエラーが出る。


/* enumハック */
// 上記の更に問題を解決する手法
class GamePlayer
{
	private:
		enum { NumTurns=5 };	// [enumハック] => NumTurnsを５として使える
								// constよりdefineに近い
								// enumハックは色々なところで利用されているので覚えておく価値有り！
		int score[NumTurns];	// 問題なし
};

/* マクロの問題点 */
#define CALL_WITH_MAX(a,b) f((a) > (b) ? (a) : (b))
// このマクロの悲惨さ
// * 仮引数を括弧で囲う必要がある
// * int a=5, b=0;
// * CALL_WITH_MAX(++a, b);		// aが２回インクリメント
// * CALL_WITH_MAX(++a, b+10);	// aが１回インクリメント
// * 運悪く引数によって挙動が変わる事がある
//
// こんなマクロを作るくらいならインライン関数のテンプレートを作る！
template<typename T>
inline void callWithMax(const T& a, const T& b)
{
	f(a > b ? a : b)
}

