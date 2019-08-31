= 探索

== アルゴリズムってなんだろう

では、早速アルゴリズムを学んでいきましょう！
そもそも、「アルゴリズム」とはなんでしょうか？

「アルゴリズム」というのは、「コンピューターで計算を行うときの計算方法」だったり
「タスクを遂行するための命令の集まり」を指します。

ですが、大学のコンピュータ・サイエンスで教わるような「アルゴリズム」は
もう少し狭い範囲・問題を扱っていると自分は考えています。

具体的には、次の通りの問題です。

  * いかに少ない回数で、効率的に行える手順か？(計算量)
  * 手順によって、いかに解決が難しい問題に解を出すか？(組み合わせ最適化など)

この2つのポイントを大学で、教えることが多いと思います。

実際に何かソフトウェアを作る際にも、この2つが問題になることが多いと思います。
この問題を考えるのが「アルゴリズム」だと思います。

今回の上記の2つの中の1つ目である「効率的に行えるか」の中でも
一番、シンプルな「探索」について学びたいと思います。

== 探索とは
まず、最も基礎である「探索」を学びます！

探索はアルゴリズムとしては、初歩の初歩ですが、特に後で説明する「二分探索」はアルゴリズムの問題や競プロでもよく出てくる
シンプルながらも奥が深いアルゴリズムです！

探索とは、「何か複数のものから特定のものを選び出す」ことです。

たとえば「数字当てゲーム」を考えてみましょう。
数字当てゲームは次のようなルールです。

=== 数字当てゲーム
 
 1. Aさんは特定の数字を1-100の中から選ぶ。
 2. Bさんは、Aさんが考えた数字を想像して、Aさんに告げる。
 3. Aさんは、Bさんが述べた数字に対して、「HIGH or LOW」と答える。答えた数字が低ければLOW、答えた数字が高ければHIGHと答える。
 4. 数字を当てるまで1,~3.を繰り返す。

具体的な例を次のイラストで示します。

//image[number_game_explain][数字当てゲームの説明]{
//}

探索のアルゴリズムは、この数字当ての「Bさん側の当てる戦略」に関係します。

探索とは、「なにかの集合から一つのものを探し出す！」ことです。


=== 線形探索

線形探索は、Bさんが「1から100まで一つづつ上げて」当てていく戦略です。

具体的には、次の通りです。

=== 二分探索

1から100まで一つづつ上げていくのは、もちろん効率が悪いですよね？
答えが100だった場合、100回かかってしまいます。

これだとくたびれてしまいますよね。

そこで、もう少し効率的な戦略にします。
二分探索は、Bさんが「必ず想定される範囲の真ん中の値を当てる」戦略です。

具体的には、次の通りです。

== それぞれの計算量を考えてみよう



== 作るアプリ