= 探索アルゴリズム

本章では、まず探索アルゴリズムの内容説明をします。
そのあと、アルゴリズムの重要な要素である@<kw>{計算量}について、説明します。

== アルゴリズムってなんだろう

@<b>{アルゴリズム}とはなんでしょうか。
@<b>{アルゴリズム}というのは、@<b>{コンピューターで計算を行うときの計算方法}だったり
@<b>{タスクを遂行するための命令の集まり}を指します。
しかし、大学のコンピュータ・サイエンスで教わるような@<b>{アルゴリズム}は
もう少し狭い範囲・問題を扱っていると自分は考えています。

具体的には、次の通りの問題です。

  * いかに少ない回数で、効率的に行える手順か？(計算量)
  * 手順によって、いかに解決が難しい問題に解を出すか？(組み合わせ最適化など)

この2つのポイントを大学で、教えることが多いです。
この問題を考えるのが@<kw>{アルゴリズム}です。

2つの中の1つ目である@<kw>{効率的に行えるか}について、中でもシンプルな@<kw>{探索} を通して学びます。

== 探索ってなんだろう

探索は初歩で学ぶものですが、特に「二分探索」は競プロなどでもよく出てくる
シンプルながらも奥が深いアルゴリズムです。@<fn>{search}

探索とは、「何か複数のものから特定のものを選び出す」ことです。

たとえば「数字当てゲーム」を考えてみましょう。
数字当てゲームは次のようなルールです。

//footnote[search][正確にいうと今回学ぶ探索は「リスト探索」といいます。もう1つ探索として対象がグラフの「グラフ探索」がありますが、これは続刊に説明を譲ります。]

=== 数字当てゲーム
 
 1. Aさんは特定の数字を1-100の中から選ぶ。
 2. Bさんは、Aさんが考えた数字を想像して、Aさんに告げる。
 3. Aさんは、Bさんが述べた数字に対して、「HIGH or LOW」と答える。答えた数字が低ければLOW、答えた数字が高ければHIGHと答える。
 4. 数字を当てるまで1.~3.を繰り返す。

具体的な例を@<img>{number_game_explain}で示します。

//image[number_game_explain][数字当てゲームの説明][scale=0.6]{
//}

探索のアルゴリズムは、この数字当ての「Bさん側の数字を言っていく戦略」にあたります。

=== 線形探索

線形探索は、Bさんが「1から100まで1つづつ数字を上げて」言っていく戦略です。
具体的にBさんは次の戦略を取ります。(@<img>{number_game_linear})

  1. 必ず最初は1を言う
  2. 外れたら、言った数字に1を足して言う(1だったら、2。15だったら16と言った感じ)
  3. それを100まで繰り返す。

//image[number_game_linear][数字当てゲームを線形探索で解く。][scale=0.6]{
//}

線形探索は、非常にわかりやすい戦略です。
ただ、すこし効率が悪い戦略です。
答えが100だった場合、100回かかってしまいます。

これだとくたびれてしまいます。

=== 二分探索

そこで、もう少し効率的な戦略にします。
二分探索の登場です。二分探索は、Bさんが「必ず想定される範囲の真ん中の値を言っていく」戦略です。(@<img>{number_game_binary})

 1. 考えられる値の幅の真ん中を言う(1~100だったら50, 1~1000だったら500と言った感じ)
 2. 相手がHIGHと答えた場合は、幅を答えた値より上の幅に設定する。(51～100といった形)
 3. 相手がLOWと答えた場合は、幅を答えた値より下の幅に設定する。(1～49といった形)
 4. 設定した幅に応じて1.と同じく幅の真ん中の値を言う(51~100だったら75)。1.~3.を繰り返す

//image[number_game_binary][数字当てゲームを二分探索で解く。][scale=0.6]{
//}

これだと、毎回Aさんが「HIGH」か「LOW」という度に、数字の候補が半分になります。
そのため、 線形探索と比べて効率的です。

探索を行うライブラリは二分探索で実装されているのが、一般的です。@<fn>{citation_needed}
例えば、Go言語の探索は二分探索で実装されています。@<fn>{go_search}

//footnote[citation_needed][著者のイメージであり、実際に、統計・裏付けは取っていません。]
//footnote[go_search][@<href>{https://golang.org/src/sort/search.go}]

==== 二分探索の注意点
二分探索において、1つ注意点があります。
それは、@<b>{探索を行う対象が整列されていること。}です。

数当てゲームの場合も、「HIGH」「LOW」を頼りに、探索範囲の絞り込みを行いましたが
このHIGHやLOWも「1-100」で1が小さくて100が大きいという前提があり、かつそれがソートされているから範囲の絞り込みを行うことができます。
トランプの色を当てるゲームの場合でも、それぞれの色の間で順番をつけない限り、同じ戦略で当てることは出来ないですよね。
つまり@<b>{探索を行う対象が順番があり、ソートされていること}が二分探索では必要です。気をつけてください。(@<img>{binary_note})

//image[binary_note][二分探索の注意点][scale=0.7]{
//}

== それぞれの計算量を考えてみよう

アルゴリズムを考える上で@<b>{いかにそのアルゴリズムが効率的か？}を測るものさしとして@<kw>{計算量}というものがあります。
@<kw>{計算量}とは、@<b>{そのタスクを、作業を完了するのに最大どれくらいの作業量が必要か？}を示したものです。

具体的に、さきほど説明した探索のアルゴリズムを例に計算量を考えてみましょう。

=== 線形探索の計算量

線形探索は、最大で、探索対象の数の分だけ数え上げる必要があります。

例えば、数当てゲームで、「1-100」が対象だった場合、最大で100回数字を言っていく必要があります。
数字を増やして「1-10,000,000(1000万)」だった場合、どうでしょうか。
最大で10,000,000(1000万)かかります。

これを少し数学っぽく抽象化して、@<tt>{1 - n}まで数え上げる数当てゲームの場合、最大で@<tt>{n}回かかる必要がある、と言えます。
つまり、線形探索の計算量は、@<kw>{最大でn回} かかる、と一般化できます。

これを、アルゴリズムの用語に言い換えると @<m>{O(n)} と表記します。
この書き方を@<kw>{ビッグオー表記}と呼びます。

//note[ビッグオー表記]{
  ビッグオー表記は、アルゴリズムでは、欠かすことができない表記です。
  @<kw>{入力の個数がn個だった場合、nに対して、そのアルゴリズムが最大でどのぐらいの作業量が必要か}を表したものです。
//}

=== 二分探索の計算量

次に二分探索の計算量を求めてみましょう。二分探索の計算量は、線形探索よりもう少し複雑です。
さきほど説明したとおり、二分探索は、毎回、探索の対象を半分にしていきます。

具体的に、探索の対象数を100で考えてみましょう。
100の場合、次の図のとおり、半分ずつ対象数が減っていくことになります。

//image[binary_search_order][二分探索の計算量]{
//}

更に式にして考えてみましょう。

//image[binary_search_order2][二分探索の計算量をさらに分解...]{
//}

100をどんどん2で割っていって最終的に1まで絞っていきます。
つまり、@<m>{100 \div 2^6 \simeq 1}という数式になります。
@<m>{2^6}を右辺に持っていくと@<m>{100 \simeq 2^6}となります。
この右肩にのっているのが計算量です。

この右肩に乗っているのを外すのには@<m>{log}を使います。
@<m>{log}と聞いて懐かしい記憶が呼び覚まされた方もいるのではないでしょうか。
ここで、ついでに@<m>{log}についても復習しましょう。

//note[logの復習]{
@<m>{log}は@<kw>{x回 数字を掛け合わせると、その数になる}という@<tt>{x}にあてはまる数です。
たとえば@<m>{log_2^8}は@<kw>{x回 2を掛け合わせると、8になる}の@<tt>{x}です。2を3回掛け合わせると(@<m>{2^3})=8になるので
@<tt>{x}には3がはいります。
//}

本題に戻りまして、さきほどの数式の両辺に@<m>{log_2}をつけてみましょう。

//texequation{
log_2 100 \simeq log_2 2^6
//}

@<m>{log_2 2}は1ですね。（1回 2を掛け合わせると、2になるので）
そのため、次の式になります。

//texequation{
log_2 100 \simeq 6
//}

つまり、探索の対象数に@<m>{log_2}をつけてあげれば計算量になることがわかります。

これを探索の対象数が@<tt>{n}個の時、と考えてみて、一般化すると@<m>{log_2 n} が計算量になります。
さきほど説明したビッグオー記法を用いて、書くと次のようになります。

//texequation{
O(log_2 n)
//}

これで、線形探索と二分探索それぞれの計算量を求めることができました。

=== 線形探索と二分探索の計算量の違い

今までで、@<table>{each_order}の通りそれぞれの計算量を求めることができました。

//table[each_order][それぞれの計算量]{
探索方法	計算量
-----------------------
線形探索	@<m>{O(n)}
二分探索	@<m>{O(log_2 n)}
//}

実際、これらの計算量がどのくらいの違いを生むのでしょうか。
グラフにしてみましょう。グラフは@<href>{https://www.desmos.com/calculator, desmos} @<fn>{desmos}というWebサービスで簡単に数式をグラフにできます。(@<img>{desmos-graph1})

//image[desmos-graph1][計算量のグラフ][scale=0.8]{
//}

横軸は入力の数(@<tt>{n})、縦軸は、そのアルゴリズムの計算量を示します。
例えば、横軸が10であれば、入力の数が10、それに対応する縦軸の値が計算量になります。
線形探索の場合は10、二分探索の場合は、およそ3です。

表のスケールが0-10ぐらいまでなので、このぐらいだとあまり差はなさそうですね。
しかし、表のスケールを一気に大きくしてみましょう。(@<img>{desmos-graph2})

//image[desmos-graph2][計算量のグラフ(スケールを大きくしたもの)][scale=0.8]{
//}

横軸が1000をみてもらえると分かる通り、かなり差がついてますね。
1000で線形探索をすると、1000回の計算量です。二分探索だとなんと@<kw>{10}回で済みます。

=== アルゴリズムの力

これがアルゴリズムの面白いところであり、力です。@<br>{}
効率的なアルゴリズムだと、規模がスケールしても耐えられるのです。

エンジニアがアルゴリズムを学ぶ必要はここにあります。
とりあえず、動くものであれば誰でも作ることができますが
何万人が使うようなサービス、あるいは何万TBのデータを検索するような場合、こうしたアルゴリズムのバックグラウンドがあるかどうかによって差が出てきます。

//footnote[desmos][https://www.desmos.com/calculator]

