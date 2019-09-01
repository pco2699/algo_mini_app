= 探索のアプリを作ろう

では、この「探索」を用いてアプリを作っていきましょう。

== 「チケット検索アプリ」を作ろう

今回は「チケット検索アプリ」を作ってみましょう。

画面は次のような形です。

//image[app_image][チケット検索アプリ]{
//}

「チケット数」と「探したいチケット番号」、「探索の方法」を選択して
「検索」すると、チケットがあるかどうか、チケットを探すのにかかった計算量を出してくれます。

なお、チケットはチケット数の分だけ、チケット番号が振られていて
その中から探索を行います。

//image[app_abstract][チケット検索アプリの概要]{
//}

== 今回のアプリの構成
今回のアプリの構成・メインでいじっていくところを説明します。
まず、ディレクトリ
//list[?][Nuxtのディレクトリ]{
.
├── firebase.json
├── firestore.indexes.json
├── firestore.rules
├── jest.config.js
├── nuxt.config.js
├── pages // 今回メインで開発を行う場所・Webのページ
├── modules // アルゴリズムのロジックを書いておく場所
（...省略）
├── plugins
├── static
└── store
//}

今回は@<tt>{pages}の中でWebアプリのコードを記述していきます。
@<tt>{pages}の中には、デフォルトでファイルが入っていると思いますが、必要無いので、すべて削除してください。

//terminal[][pageの中身を削除する]{
$ rm -r pages/*
//}

@<tt>{modules}配下で、今回のアルゴリズムのロジックを記述していきます。これは、デフォルトでは作成されていないので
作成しましょう。また、今後、探索以外のロジックも実装していくことが予想されるため、@<tt>{modules}の下に@<tt>{search}というディレクトリも切りましょう。

//terminal[][modulesを作成する]{
$ mkdir -p modules/search
//}

== 探索のコードを書こう

まずは、探索のロジックを@<tt>{modules/search}配下に記載していきましょう。
@<tt>{modules/search}配下では、探索のロジックに加えて、以下のロジックを書いていきます。

 1. チケットを自動生成するロジック
 2. 線形探索を行うロジック
 3. 二分探索を行うロジック

それぞれのロジックは次のファイルに記述していきます。

//list[?][modules/search配下のファイル]{
modules/search
├── search_util.js // 1.のチケット自動生成ロジック
├── search_util.test.js // 1.のテストコード
├── searcher.js // 2.3.の探索ロジック
└── searcher.test.js　// 2.3.のテストコード
//}

それぞれのファイル・ロジックについて実際に作成していきましょう。
まずは@<tt>{search_util.js}からです。

=== search_util.js

//list[?][search_util.js][javascript]{
const contents = [
  'ジャニーズコンサート 2019/08/07',
  'サカナクション NF in MIDNIGHT SONIC 2019/08/16',
  '山下達郎 全国ツアー 2019/08/07',
  '宇多田ヒカル Laughter in the dark 2018/11/07',
  '椎名林檎 （生）林檎博 2018/11/25'
]

const ticketGenerator = (num) => {
  return Array(num)
    .fill(null)
    .map((_, i) => ({
      id: i + 1,
      content: contents[Math.floor(Math.random() * contents.length)]
    }))
}

export default ticketGenerator
//}

@<tt>{search_util.js}では、@<tt>{ticketGenerator}という、チケットを指定された数ぶんチケットの配列を自動で作成するロジックを書いています。
チケットの配列は次のような構造になっています。

//list[?][チケットの配列の構造]{
const tickets = [
    {
        id: 1, // チケット番号(1から始まる)
        contents: '宇多田ヒカル Laughter in the dark 2018/11/07'
    },
    {
        id: 2,
        contents: '椎名林檎 （生）林檎博 2018/11/25'
    }
    // ...以下、チケットの数だけ繰り返し
]
//}

配列の生成は、@<code>{Array()}と@<code>{fill()}と@<code>{map()}という関数を3つ 組み合わせています。
@<code>{Array(num)}で@<tt>{num}分の配列の作成、@<code>{fill(null)}は配列生成のおまじない、@<code>{map(fn)}で実際に、配列の内容の構成を指定しています。

配列の内容を構成する際に@<code>{id: i + 1}と指定しているのは、配列は0から付番されるのを1から始まるようにするためです。

@<code>{contents}は、お遊び要素で、上部の指定されている@<tt>{contents}からチケットの内容をランダムで埋め込みます。@<fn>{ticket_contents}

@<code>{export default ticketGenerator}で@<tt>{ticketGenerator}がこのファイル以外の外のモジュールからも利用出来るようになります。

//footnote[ticket_contents][ちなみに、コンテンツの内容自体は著者の最近行った or 行きたかったコンサート or 適当なコンサート名です。]

動作確認のため、簡単なテストコードも書いておきましょう。ファイル名は@<tt>{search_util.test.js}です。

//list[?][search_util.test.js][javascript]{
import ticketGenerator from './search_util.js'

test('test ticketGenerator', () => {
  // ticketGeneratorを実際に動かして結果をresに入れる
  const res = ticketGenerator(10)

  // 想定されるチケットの配列を記載する
  // contentsはランダムなので、検証を省略する
  const expected = [
    {
      id: 1,
      contents: ''
    },
    // (...以降、10回繰り返す)
  ]

  // さきほど作った想定チケットの配列とidが一致するか比較する
  res.forEach((r, i) => {
    expect(r.id).toEqual(expected[i].id)
  })
  // 結果の配列の長さが同じか検証する
  expect(res.length).toEqual(10)
})
//}

テストは@<tt>{Jest}というテストフレームワークを使ってかかれています。このように非常にシンプルに書くことができるのが特徴です。
@<code>{test(fn)}でテストケースを定義します。 そして@<code>{expected}というチケットの想定配列を手でガリガリ書いて、
@<code>{ticketGenerator}を動かした結果を比較しています。


=== 





== 画面を作ろう

== 動かしてみよう