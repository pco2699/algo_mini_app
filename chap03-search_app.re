= 探索のアプリを作ろう

では、この「探索」を用いてアプリを作っていきましょう。
今回のアプリは @<href>{https://algo-mini-app.web.app/}にデプロイされているので確認してみてください。

ソースコードは@<href>{https://github.com/pco2699/algo-mini-sample-app}にあります。

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

@<code>{expect(実際の値).toEqual(期待値)}という形で、実際の値と期待値を比較して同じであること確認します。

テストを動かすのは極めて簡単で、次のコマンドをプロジェクト配下のどこかで打つだけです。
//cmd{
$ jest
//}

以下のように、PASSと出たらテストが通ったということです。おめでとうございます。
もし通ってなかったらFAILという文字とともに差分がでると思うので、差分をもとに原因を特定して修正しましょう。
//cmd{
$ jest
 PASS  modules/search/search_util.test.js
//}

=== searcher.js(線形探索)

@<tt>{searcher.js}は@<tt>{Searcher}というクラスに線形探索、二分探索のロジックをそれぞれ分けて書いています。
クラスにまとめているのは、@<tt>{export}のときに取り扱いやすくするためだけなので、それぞれ別の関数にして、それぞれを@<tt>{export}してしまっても問題ないです。

線形探索、二分探索でそれぞれ分けて説明していきましょう。
まずは、線形探索からです。

//list[?][searcher.js(線形探索)][javascript]{
export default class Searcher {
  static linearSearch(tickets, target) {
    const result = { count: 1, ticket: null }
    for (const ticket of tickets) {
      if (ticket.id === target) {
        result.ticket = ticket
        return result
      }
      result.count++
    }
    return null
  }
}
//}

@<tt>{linearSearch}は、@<tt>{tickets}と@<tt>{target}の２つの引数を取ります。
@<tt>{tickets}は、さきほど作ったチケットの配列、@<tt>{target}は対象のチケットの番号です。

まず、最初に、次の構造の結果を返す用のオブジェクトを作成しています。
//list[?][結果を返すresultの構造][javascript]{
  const result = {
    count: 1 // 探すのにかかった回数(計算量)
    ticket: null // 探し当てた対象のチケットの内容を格納
  }
//}

次に、@<tt>{for of}で、チケットをすべて調べていきます。
（線形探索は対象のチケットをすべて1から調べていくやり方でしたね。）

@<tt>{for文}の中では、それぞれチケットが探している対象のものか一個ずつ番号/IDを比較しています。
もし見つかったら、対象のチケットを@<tt>{result}に格納し、それを返します。もし見つからなければ@<tt>{null}を返すようにしています。

ちなみに、計算量を返す必要がなく、純粋な線形探索を実装したい場合は、次のように、よりシンプルに書くことが出来ます。
これは、@<tt>{find}という関数を使っています。

//list[?][よりシンプルな線形探索][javascript]{
static linearSearch(tickets, target) {
  return tickets.find((ticket) => {
    return ticket.id === target
  })
}
//}


同じようにこのロジックを軽く検証するテストコードを書いてみましょう。ファイル名は@<tt>{searcher.test.js}です。
//list[?][線形探索のロジックを検証するテストコード][javascript]{
import Searcher from './searcher.js'
import ticketGenerator from './search_util'

test('test linear search', () => {
  const tickets = ticketGenerator(10)
  const res = Searcher.linearSearch(tickets, 5)
  expect(res).toEqual(expect.anything())
  expect(res.ticket.id).toEqual(5)
  expect(res.count).toEqual(5)
})
//}
@<tt>{import}で線形探索のロジックを組み込んだ@<tt>{Searcher}と@<tt>{ticketGenerator}を呼んできます。
@<tt>{ticketGenerator}の使い方は前に説明した通りです。@<code>{Searcher.linearSearch()}で、さきほど作った線形探索のロジックを呼び出すことができます。
今回はチケット数 10で、チケット番号 5を探します。

これで、さきほど説明したとおり、計算量と対象のチケットが格納されてくるはずです。なければ、@<tt>{null}が返ってくるはずです。
そのため、とりあえず、見つかる=@<tt>{null}以外が返ってくる想定のため@<code>{expect.anything()}で@<tt>{null}以外のなにかを期待値として検証します。

その後、IDと計算量を比較して、想定と同じかどうかを確認しています。

=== searcher.js(二分探索)

次は、二分探索を実装しましょう。

//list[?][searcher.js(二分探索)][javascript]{
export default class Searcher {
  // 線形探索の後に追記しましょう
  static binarySearch(tickets, target) {
    if (tickets.length === 0) {
      return null
    }
    const result = { count: 1, ticket: null }

    let left = 0
    let right = tickets.length - 1
    while (left <= right) {
      const mid = Math.floor((left + right) / 2)

      if (tickets[mid].id === target) {
        result.ticket = tickets[mid]
        return result
      } else if (tickets[mid].id < target) {
        left = mid + 1
      } else {
        right = mid - 1
      }
      result.count++
    }
    return null
  }

//}

引数などは線形探索と同じです。

まず、最初に@<code>{tickets.length}が1以上かどうかを確認しています。0の場合、後で出てくる@<code>{let right = tickets.length - 1}で
マイナスの値になってしまい、誤動作してしまうため、ここでチェックしています。

次に@<tt>{left}と@<tt>{right}という２つの変数を定義しています。二分探索において、非常に重要な変数です。
これは探索を行う範囲を決めるもので@<tt>{left}が範囲の左端、@<tt>{right}が範囲の右端を示します。

次のようなイメージです。
//image[binary_search_code_image][二分探索のコードイメージ][scale=1.0]{
//}

この@<tt>{left}と@<tt>{right}を使って、探索を繰り返していきます。

繰り返す条件は@<code>{left <= right}である間です。@<tt>{=}は入っているので、@<tt>{left}と@<tt>{right}が同じの場合でも探索を行います。

繰り返しの中ではまず、@<code>{const mid = Math.floor((left + right) / 2)}を計算しています。
これは、左端と右端を足し合わせて2で割ることにより、範囲の真ん中を値を計算しています。
@<code>{Math.floor()}をしている理由は、割り切れない場合、小数となってしまい、配列にアクセスすることが出来ないからです。
@<code>{Math.floor()}で、小数を整数に切り下げを行うことができます。


その後、@<tt>{mid}の値で、配列にアクセスしにいきます。@<code>{tickets[mid].id}で@<tt>{mid}に対応するIDを取得することができるので
それが@<tt>{target}の値と一致するかどうかを確認します。
もし、一致していたら@<kw>{目的の値が見つかった}ということなので、@<code>{result}に入れて関数を抜けます。

見つからなかった場合、は@<tt>{tickets[mid].id}と@<tt>{target}の値を比較して、探索の範囲を決めます。
探索の範囲の決め方は次の図の通りです。

//image[binary_search_code_image2][二分探索のコードイメージ]{
//}

このようにして、@<tt>{left}、@<tt>{right}の値を更新し、これを繰り返していくことで二分探索を実装することができます。

次にこの二分探索のコードをテストしてみましょう。
@<tt>{searcher.test.js}に次の内容を追記しましょう。




== 画面を作ろう
画面のロジックが完成したので、次は画面を作っていきましょう。アルゴリズムとはあまり関係ないWEBよりの内容ではありますが
もりもり画面ができていくのは楽しいですよ。

=== Vuetifyの基本
今回は、@<tt>{Vuetify} @<fn>{vuetify}というVue用のUIコンポーネントフレームワークを利用して、画面を作っていきます。
UIコンポーネントフレームワークとは、使えそうなUIの部品を詰め込んだフレームワークで、それを呼び出すだけでキレイな画面を作ることができます。

他の有名なUIコンポーネントフレームワークとしては、@<tt>{Bootstrap} @<fn>{bootstrap} などがあります。@<tt>{Bootstrap}は、皆さん一度使ったことあるのではないでしょうか。

//footnote[vuetify][https://vuetifyjs.com/]
//footnote[bootstrap][https://getbootstrap.com/]

例えば@<img>{simple_button}を作る際には、@<list>{simple_button_code}のコードを書くだけでボタンを作ることができます。

//image[simple_button][Vuetifyのシンプルなボタン]{
//}

//list[simple_button_code][シンプルなボタンのコード]{
<template>
  <div class="text-center">
    <v-btn>Button</v-btn>
  </div>
</template>
//}

他にも、さまざまなコンポーネントがあるので、ぜひ@<href>{https://vuetifyjs.com/ja/components/api-explorer, 公式のドキュメント} @<fn>{vuetify_doc}を参照してみてください。

//footnote[vuetify_doc][https://vuetifyjs.com/ja/components/api-explorer]

=== 今回の画面構成
今回のアプリの画面構成について、説明します。非常にシンプルです。

 1. ホーム画面
 2. 探索を行う画面

==== 1. ホーム画面

//image[homepage_of_app][ホーム画面]{
//}
簡易的なホーム画面を作ります。右にメニューがあり、「探索」を選択すると2.の「探索を行う画面」に移動することができます。
この画面と全体のレイアウトについては、ソースコードの説明は省略しますので、気になる方はソースコードを見てみてください。


==== 2. 探索を行う画面

//image[search_screen_app][探索を行う画面]{
//}

探索を行うための項目を入力する画面です。今回はこの画面を作る方法をメインで解説していきます。

=== 今回のディレクトリ構成

実際に画面を作り始める前に、ディレクトリ構成・ファイル構成を説明します。

//list[?][今回のファイル構成]{
./
├── pages
│   ├── index.vue // 1. ホーム画面
│   └── search.vue // 2. 探索を行う画面
//}

ホーム画面と探索を行う画面それぞれで@<tt>{.vue}ファイルを作ります。
@<tt>{index.vue}については、前述の通り説明を割愛しますので、ソースコードを参照してみてください。

Vue/Nuxt.jsはホントは、様々なUIコンポーネントを分割して自作することができるのが特徴ですが、今回はそこに拘わらず、シンプルに一つのファイルで画面を作っていきます。

== 探索画面を実際に作ってみよう
では、実際に探索を行う画面を作っていきましょう。


まずは@<tt>{vue}ファイルをつくるところからです。
とりあえず空のファイルを作ります。
//cmd{
$ cd pages
$ touch search.vue
//}

次にエディタで次の通り@<tt>{vue}ファイルの下地をつくります。

//list[?][vueファイルの下地][]{
<template>
/* ここにHTMLを記載します。 */
</template>
<script>
// ここに処理をJavaScriptで記載します。
</script>
<style>
/* ここにCSSでスタイルを記述します。(ただし今回はほぼ使わないので省略) */
</style>
}

これでファイルができたので、それぞれの@<tt>{HTML}と@<tt>{JavaScript}について記載していきましょう。

=== HTML部をつくろう
まずは、@<tt>{HTML}部を作りましょう。さきほども言ったとおり、今回は@<tt>{Vuetify}を用いて作成します。
@<img>{search_screen_app_explained})のイメージを頭に入れてHTMLを作っていきましょう。

//image[search_screen_app_explained][探索画面の構成]{
//}

==== 全体
まずは全体を@<tt>{div}で包みます。
Vueのルールとして@<kw>{templateの下は必ず一つのタグ}がルールなので、このdivタグで包んであげます。
他に、classとして@<kw>{text--center}、@<kw>{ms-10}を設定します。両方ともVuetifyで設定されているクラス属性です。

@<kw>{text--center}はテキスト中央揃え、@<kw>{ms-10}は左右両方(side)に10のmarginを設けることを示しています。

//list[?][HTML部 - 全体][html]{
<template>
  <div class="text--center ms-10">
  </div>
</template>
//}

==== フォーム
入力する部分=フォームを作っていきます。
まずは全体を@<tt>{v-form}で囲います。ここらへんはHTMLで@<tt>{form}タグで囲うのと全く同じ要領です。
今回は実際には、POSTなどは行わないため、この@<tt>{v-form}タグは実は省略しても構いません。

//list[?][HTML部 - 全体][html]{
<template>
  <div class="text--center ms-10">
    <v-form>
    </v-form>
  </div>
</template>
//}

==== テキストフィールド（チケット番号）
チケット番号を入力するテキストフィールドを定義します。
@<tt>{v-text-field}でテキストフィールドを定義することができます。

@<tt>{v-model}で後述するJavaScriptで利用するモデルと紐付けを行います。
@<tt>{ticketNumber}とモデルと紐付けを行います。

また@<tt>{label}で実際に表示されるlabel名を指定します。

//list[?][テキストフィールド][html]{
<template>
  // 今まで記載したものは省略
  <v-form>
    <v-text-field v-model="ticketNumber" label="チケット番号" />
  </v-form>
</template>
//}

==== スライダー(チケット数)
チケット数を入力するスライダーを定義します。
@<tt>{v-slider}でスライダーを定義することができます。

@<tt>{thumb-label}の設定値に応じて、水玉のようなラベルを表示するか決めることができます。
@<tt>{always}で常にラベルを表示、何も指定しない(=@<tt>{thumb-label}のみ)だとクリックやタッチした際にだけ
ラベルを表示します。

@<tt>{min}, @<tt>{max}, @<tt>{step}は、それぞれ数値の範囲を決めています。
今回は、大きめの数字(1万)ぐらいまで見てみたいので、@<tt>{max}は1万に設定して@<tt>{step}も大きめに1000と設定しておきます。

//list[?][スライダー][html]{
<v-text-field />(詳しい内容は前述の通り)
<v-slider
  v-model="ticketAmount"
  class="mt-7"
  thumb-size="32"
  thumb-label="always"
  min="10"
  max="10000"
  step="1000"
  label="チケット数"
/>
//}

==== ラジオボタン(探索方法)
探索方法を指定するラジオボタンを定義します。
@<tt>{v-radio-group}でラジオボタンの集合を示すタグです。@<tt>{v-radio}はラジオボタンのそれぞれの項目に対応しています。

@<tt>{v-radio-group}の@<tt>{row}属性は、ラジオボタンの並び方を決めます。@<tt>{row}ならば横並びです。

@<tt>{v-radio}の@<tt>{value}は選択された際に@<tt>{v-model}に格納される値を記載します。

//list[?][ラジオボタン][html]{
<v-radio-group v-model="searchMethod" label="探索方法" row>
  <v-radio label="線形探索" value="linear" />
  <v-radio label="二分探索" value="binary" />
</v-radio-group>
//}

==== エラー表示 & 検索ボタン
さきほどの画面構成には含まれていませんでしたが、入力した数値がバリデーションにひっかかった場合にエラーを表示する場所も作っておきましょう。
合わせて、検索ボタンも作ります。

@<tt>{v-input}は、汎用的なインプットを作るためのコンポーネントですが今回はエラーメッセージを表示するために使っています。
@<tt>{errors}というモデルと紐付けて使います。具体的な処理は、後述します。

ボタンは@<tt>{v-btn}を使います。classに@<tt>{primary}と記載することで@<hd>{chap01-install|vuetify_theme}で設定した色を付与することができます。
クリック時の動作は、@<tt>{@click}で付与することができます。この処理の内容はあとで説明します。

//list[?][エラー表示 & 検索ボタン][html]{
<v-input :error-count="errors.length" :error-messages="errors" />
<v-btn class="primary" @click="checkForm() && execSearch()">
  検索
</v-btn>
//}

==== 結果表示






== 動かしてみよう