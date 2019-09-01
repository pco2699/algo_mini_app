= まえがき

== 自己紹介

はじめまして、こんにちは、たかやま(@pco2699)と申します。
普段は、資産運用のスタートアップでJavaのバックエンドエンジニアとして働いています。
土日は、ハッカソンに出たり、このようなちょっとしたアプリをつくるような開発本を書いたり
プチ0->1を楽しむのが、日課です。

== Webエンジニアにアルゴリズム/データ構造の知識は必要か

よくはてブのホッテントリやTwitterでも話題に上がる、@<b>{Webエンジニアにアルゴリズム・データ構造などの知識は必要か？}論。
皆さんも目にしたことがあると思います。この論について、どのような意見をお持ちでしょうか？

私、個人としては、@<b>{無くても困らないけど、あると色々助かる、}ものだと思っています。
こういったCS(コンピュータ・サイエンス)と呼ばれる以下のような知識は、エンジニアにとっては@<b>{筋肉}のようなものだと思います。

 * アルゴリズム
 * データ構造
 * ネットワーク
 * オペレーティング・システム
 
 などなど...

筋肉ももちろん無くて困ることはありませんが、あるといろいろ便利です。

=== でも、アルゴリズムの勉強って何に使うの？？

Webエンジニアとして働いていると、もちろんアルゴリズムがそのまま出てくることなんて、そうそう無いです。
普通にWebページを作る、ということであれば、アルゴリズムの知識なんて全然使わないと思います。

しかも、町の本屋さんやAmazonで売っているいわゆる「アルゴリズム・データ構造」が載っている本は
ストイックにアルゴリズムやデータ構造が書いてあるので、まあ読む気が失せるわけです。

そこで、私はアルゴリズムをそのまま小さいWebアプリ = アルゴリズムミニアプリ として
実装することで、「アルゴリズムがWebアプリでどのように活かされるか」をわかりやすく理解できる本を書きたいと思いました。

#@# アルゴリズムをWebアプリで実装するとは？

それが本書「Nuxt.jsとPythonでつくるアルゴリズムミニアプリ」です。

=== アルゴリズムミニアプリってなに？

「アルゴリズムミニアプリってなんだろう」と思う方もいると思います。
アルゴリズムミニアプリは、以下の要素をもつWebアプリです。

 * Facebookの友達検索機能！など、Webサービスの一つの機能だけをアプリとして切り出したもの。
 * ゲーム好きの方なら「メイドインワリオ」のWebサービス 

=== わたしがアルゴリズムに興味をもったきっかけ

そもそも自分がアルゴリズムを勉強したタイミングは人生で2回あります。

 1. 大学(情報工学専攻でした)の授業
 2. Goo◯leなどの外資系のIT系を受けようと思った時

個人的に、影響が大きかったのが、2.の時です。
実際に外資系のITの会社だと、書類選考を通過すると、リクルーターから
@<b>{アルゴリズムとデータ構造を死ぬほど勉強しておけ！}と次のようなサイトや記事、本をやまほど、案内されます。

    * @<href>{https://www.coursera.org/learn/algorithms-part1, Couseraのアルゴリズム講座}
    * @<href>{https://www.amazon.co.jp/dp/B071GN3JN2/, Cracking the code interview}
    * @<href>{https://leetcode.com, LeetCode}
    * @<href>{https://www.hackerrank.com/, HackerRank}
    * @<href>{https://community.topcoder.com/, Topcoder}

結果的に、受けた会社自体は、すべて落ちてしまいました。
しかし、そこからアルゴリズムの面白さに目覚めて、今でも@<href>{https://leetcode.com, LeetCode}や@<href>{https://atcoder.jp/, AtCoder}をやったりします。

アルゴリズムの勉強をしてて思うのが@<b>{アルゴリズムとWebアプリの間に断絶がある}ということです。

アルゴリズムの勉強で作るのは、次のようなものです。（LeetCodeの問題を日本語に訳したもの）

//note[アルゴリズムの問題]{
i番目の配列がi日目の株の値段を表す配列があります。
最大で一回のトランザクション(例: 一個の株を買い、一個の株を売る)が許されている場合、最大の利益を探すアルゴリズムを設計しなさい。

株を買う前に売ることが出来ないことに気をつけること。
//}

このアルゴリズムの問題は非常に有名ですが、入力は配列で、出力は一つの値です。
実際に、コードを書いてみると以下のような出力になると思います。
つまりアルゴリズムの問題で出されたり書く、コードは
コマンドラインツールなどの入出力に近いものになります。

実際、ほとんどのアルゴリズムの本でも、こういった形式を取っています。
こうした本はもちろんとても良い教材ですし、大変、お世話になりました。

ただ、一つ思うのが、@<kw>{「アルゴリズムとWebアプリの間で断絶があるのでは無いか」}ということです。

===　アルゴリズムとWebアプリの間にある断絶

「アルゴリズムとWebアプリの間にある断絶」とは、アルゴリズムの勉強で書くコードや成果物が
Web系のエンジニアにとっては、実際のWeb開発とはかけ離れている、ということを指します。

そこで、私は、「アルゴリズムの入力、出力をWebアプリにして、その断絶を無くせないか？」と考えました。

アルゴリズムの教材で使われるC++やPythonは用いず、JavaScriptを用いて説明し
そのまま、それをWebアプリにしてしまうことで、今までに無いアルゴリズムの教材ができる、と考えています。

== 本書の特徴

=== 言語はJavaScriptのみを利用

アルゴリズムの本だとC++やC、Pythonが多いですが、本書ではWebエンジニアが最も書ける（と思われる）JavaScriptのみを利用して
アルゴリズムの構築、Webアプリの構築を行います。

=== WebアプリはNuxt.js/Firebaseを用いて構築

WebアプリはNuxt.jsとFirebaseを用いて作成します。
非常にモダンな技術スタックではありますが、環境構築などの手間が少なく作れて、経験の少ない初心者でも
苦労せずに作れるようにしました。


== 対象読者

本書の対象読者は以下のような方です。
特に1.の方を対象としています。

 1. アルゴリズムがよくわからないWeb系のエンジニア
 2. アルゴリズムがどのようにWebアプリに活用されるか知りたい人
 3. CS専攻で、モダンなWeb技術でのアプリの技術スタック、開発方法が知りたい人

言語はJavaScriptをメインで利用します。
JavaScriptを書いたことが無くても、C, C++, Java, Python, Ruby, PHPなどの言語をどれか一つで
簡単なWebシステムやツールを書いたことがある方なら理解できる内容となっていると思います。

逆に以下のような方は、本書を読んでも？？となってしまうかもしれません。

 1. プログラミングを全くしたことが無い方
 
== 本書の構成

本書は、各章で一つのアルゴリズムを取り上げます。
章の前半でアルゴリズムの解説、後半でWebアプリの説明、およびコード内容の説明を行います。

