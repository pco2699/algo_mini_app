= 環境構築

アルゴリズムの説明に入る前に、今回作成するWebアプリの基本構成および環境構築の方法について説明します。

== 今回の構成

今回は以下の構成でWebアプリを作ります。

//image[architecture][今回の構成]{
//}

それぞれの要素について説明します。

=== Firebase

今回は、Firebaseと呼ばれるWebサイトのホスティングやDBをサクッと作れるBaaS(Backend as a service)上にWebサービスを作ります。
Firebaseを利用することで、難しかったインフラ構築やサーバーデプロイなどの作業が不要になるため、一人でWebサービスをサクッとプロトタイピングするのに向いています。

また、複雑な要件や大量のアクセス、大人数に利用される利用要件が無ければ @<b>{ほぼ無料} で使えるのが素晴らしいポイントです。
ほぼ無料と書きましたが、今回のアプリを作る分には、お金はかからないと思います。

サクッと一人で、コストも抑えてWebアプリを作るため、Firebaseを今回は採用することにしました。

=== Firebase Hosting

Firebase HostingはFirebaseのサービスの一つで、HTMLやCSS、JSなどの静的ファイルをホスティングするためのサービスです。
PHPやJava, Pythonなどはもちろん動きませんが、後述する「静的サイトジェネレーター」を組み合わせることで、フロントエンドフレームワークで作成された
ファイルをデプロイすることができます。

=== Cloud Firestore

データの永続化を行うDBです。Webサービスだと @<tt>{MySQL}や@<tt>{PostgreSQL}などのRDB(リレーショナル・データベース)が使われることが多いですが
今回は実装の容易性などからNoSQL型のデータベースであり、Firebaseで標準的に使われている@<tt>{Cloud Firestore} を利用してデータの永続化を行います。

NoSQLでスキーマレスなので、データベースのスキーマ定義などがなかったり、途中でデータ追加したい！となっても、データを追加したりできるのが便利な点です。

今回の探索編では、@<tt>{Cloud Firestore}は利用しませんが、今後の編では利用する予定のため、ついでにセットアップしておきます。

=== Nuxt.js
Nuxt.jsと呼ばれるフロントエンドフレームワークを用いて、Webサービスを作成します。Nuxt.jsはVue.jsと呼ばれるフレームワークがベースになっており
HTML/CSSが理解できていれば、非常に理解しやすく扱いやすいフロントエンドフレームワークです。

Nuxt.jsには「静的サイトジェネレーター」の機能もあり、これを用いて、生成されたHTML/CSSなどを Firebase Hostingにデプロイすることで
今回のWebアプリを作っていきます。

== 環境をつくろう

=== Firebaseへのサインアップ

まずは何より、Firebaseへサインアップを行いましょう。
Firebaseは以下のページからサインアップできます。

@<href>{https://firebase.google.com/?hl=ja}

//image[firebase_signup][Firebaseのトップページ][scale=0.8]{
//}

「使ってみよう」ボタンを押しましょう。

//image[google_login][Googleのログイン][scale=0.8]{
//}

Googleのログインが求められると思うので自分のGoogleアカウントでログインしましょう。

//image[firebase_project][Firebaseのプロジェクト作成][scale=0.8]{
//}

「プロジェクトを追加」でプロジェクトを追加しましょう。

//image[firebase_project_start][Firebaseのプロジェクトの名前][scale=0.8]{
//}

「プロジェクトの名前」を聞かれるので適当に「algo-mini-app」と入力しましょう。

//image[firebase_project_start2][Firebaseのアナリティクスの利用有無][scale=0.8]{
//}

アナリティクスの利用有無を聞かれるので「なし」と答えましょう。

//image[firebase_completed][Firebaseのプロジェクト作成完了][scale=0.8]{
//}

@<img>{firebase_completed} が出ればfirebaseのプロジェクト作成が完了です！

あとで、Nuxt.jsとも連携していきます！

=== Nuxt.jsの導入

==== 本書でのバージョン

本書では、次のバージョンでNuxt.jsを動かします。

//table[nuxt_ver][Nuxtのバージョン]{
プロダクト名	バージョン
-----------------------
Nuxt.js	2.8.1
Node.js	10.14
Vuetify	2.0.5
//}

==== Nuxt.jsの初期プロジェクト作成

Nuxt.jsを動かすには、Node.jsの動作環境が必要です。
本書では、Node.jsの環境構築の手順は省略しますのでネットで検索して、Node.jsの環境構築をお願いします。

Nuxtの初期プロジェクトは @<tt>{create-nuxt-app} というコマンドを利用して構築すると簡単です。
Node.jsのバージョンが10系であれば、 @<tt>{npx}というコマンドが使えるのでそれを組み合わせて
コンソールで次の内容を入力しましょう。

//cmd{
$ npx create-nuxt-app
//}

ダイアログで色々聞かれると思うので、次のとおり回答しましょう。

//cmd{
npx: 341個のパッケージを34.576秒でインストールしました。

create-nuxt-app v2.9.2
✨  Generating Nuxt.js project in .
? Project name algo-mini-app // プロジェクト名を指定します。
? Project description Sample Project for Algo Mini App // プロジェクト名の説明を指定します。
? Author name pco2699 // 開発者の名前(あなたです！)を入れてください。
? Choose the package manager Npm // 今回利用するパッケージマネージャを指定します。今回はnpmというものを利用します。
? Choose UI framework Vuetify.js // 利用するUIフレームワークを指定します。今回はVuetifyを利用します。
? Choose custom server framework None (Recommended) // 利用するサーバサイドのフレームワークを指定します。今回は利用しないので何も指定しません。
? Choose Nuxt.js modules Progressive Web App (PWA) Support // axios(HTTPで通信を行うためのもの)、PWA(Webにアプリのような挙動をさせる技術)を選べますが、今回はPWAのみ指定します。
? Choose linting tools ESLint, Prettier // Lint(文法チェックや静的解析)を行うかどうかを指定します。私は指定してますが、指定しなくても開発できます。
? Choose test framework Jest // 利用するテストフレームワークとしてJestを指定します。
? Choose rendering mode Universal (SSR) // レンダリングの方式を指定します。今回はUniversalを指定します。
//}

これで Nuxt.jsのプロジェクトができました。

あとは、個人的な好みで細かいカスタマイズを入れておきます。

==== Nuxtのプロジェクトのカスタマイズ

===== nuxt-propety-decolatorの追加

パッケージとして追加で @<href>{https://github.com/nuxt-community/nuxt-property-decorator, nuxt-property-decolator}@<fn>{prop_deco}を入れます。これは、Nuxt.jsのコンポーネントのスタイルをclass構文と呼ばれる書き方に変えるための
パッケージです。

次の通り、クラス構文を使ってVueのコンポーネントを組み立てることができるようになります。

//list[before_prop][nuxt-property-decolatorを入れる前][javascript]{
export const MyComponent = Vue.extend({
  props: {
    propA: Number
  },
  data () {
    return {
      foo: 'foo',
      baz: 'bar'
    }
  }
})
//}

//list[after_prop][nuxt-property-decolatorを入れた後][javascript]{
import { Component, Prop, Provide } from 'nuxt-property-decorator'
@Component()
export class MyComponent extends Vue {

  @Prop()
  propA!: number

  @Provide() foo = 'foo'
  @Provide('bar') baz = 'bar'
 
}
//}

@<tt>{nuxt-property-decorator}は次のコマンドで追加してください。

//terminal[][nuxt-property-decoraterのインストール]{
$ pwd # プロジェクトの直下にいることを確認
$ npm install nuxt-property-decorator
//}

//footnote[prop_deco][https://github.com/nuxt-community/nuxt-property-decorator]


===== babelの設定の追加

@<tt>{nuxt-propety-decorator}を動かすためにbabelというコンパイラのエラーの抑制するための設定の追加が必要になります。
@<tt>{nuxt.config.js}に次の内容を追記しましょう。

//list[?][nuxt.config.jsに設定を追記][javascript]{
  build: {
    babel: {
      plugins: [
        ["@babel/plugin-proposal-decorators", { legacy: true }],
        ["@babel/plugin-proposal-class-properties", { loose: true }]
      ]
    }
  }
//}

====={vuetify_theme} Vuetifyのテーマ色の設定

今回、VuetifyというUIフレームワークを利用して、画面を作っていきます。
まず、基本色を設定してしまいましょう。基本色は@<tt>{nuxt.config.js}で設定できます。

次のように設定していますが、好きな色に設定してみてください。
@<href>{https://theme-generator.vuetifyjs.com/, Vuetify Theme Generator} @<fn>{vuetify_theme}というサイトで、実際に色を見ながら、テーマ色を設定することも出来ます。

//list[?][nuxt.config.jsにVuetifyのテーマを設定][javascript]{
  vuetify: {
    customVariables: ['~/assets/style/variables.scss'],
    theme: {
      light: true,
      themes: {
        light: {
          primary: '#2196f3',
          secondary: '#03a9f4',
          accent: '#e91e63',
          error: '#ff5722',
          warning: '#ff9800',
          info: '#009688',
          success: '#00bcd4'
        }
      }
    }
  },
//}

//footnote[vuetify_theme][https://theme-generator.vuetifyjs.com/]

=== Nuxt.jsとFirebaseの連携設定

さきほど作ったNuxt.jsのプロジェクトとFirebaseを連携させる設定を行いましょう。

==== Firebase CLIのインストール

Firebaseを連携させるには、まずコマンドラインのツールを導入しましょう。
次のコマンドを打つことで、Firebaseのコマンドラインツールを導入できます。

//cmd{
$ npm install -g firebase-tools
//}

次に実際にFirebaseにログインしましょう。
コンソールで次のコマンドを打ってください。

//cmd{
$ firebase login
//}

ブラウザが立ち上がり、Googleのログインを促されるのでログインすれば
ログインが完了です。

==== Firebaseの設定

NuxtプロジェクトにFirebaseを設定します。
さきほどNuxtのプロジェクトで次のコマンドを打ちます。

//cmd{
$ cd {Nuxtのプロジェクトを作ったディレクトリ}
$ firebase init
//}

かっこいいFirebaseのロゴとともにプロンプトが立ち上がりますので答えていきましょう。
まずは「Are you ready to proceed?(次に進んでもいいですか？)」と聞かれるので
問題なければ、「Y」と押しましょう。

//cmd{

     ######## #### ########  ######## ########     ###     ######  ########
     ##        ##  ##     ## ##       ##     ##  ##   ##  ##       ##
     ######    ##  ########  ######   ########  #########  ######  ######
     ##        ##  ##    ##  ##       ##     ## ##     ##       ## ##
     ##       #### ##     ## ######## ########  ##     ##  ######  ########

You're about to initialize a Firebase project in this directory:

  {Nuxtのディレクトリ}

Before we get started, keep in mind:

  * You are currently outside your home directory

? Are you ready to proceed? (Y/n) Y
//}

次に、どのFirebaseのサービスを利用するか聞かれるので
今回は@<tt>{Firestore}と@<tt>{Hosting}を選択しましょう。

//cmd{
? Which Firebase CLI features do you want to setup for this folder? Press Space to select features, then Enter to confirm your choices.
 ( ) Database: Deploy Firebase Realtime Database Rules
 (*) Firestore: Deploy rules and create indexes for Firestore
 ( ) Functions: Configure and deploy Cloud Functions
>(*) Hosting: Configure and deploy Firebase Hosting sites
 ( ) Storage: Deploy Cloud Storage security rules
//}

次にどのプロジェクトと紐付けるかを聞かれるので、さきほど作ったFirebaseのプロジェクトと紐付けましょう。

//cmd{
First, let's associate this project directory with a Firebase project.
You can create multiple project aliases by running firebase use --add,
but for now we'll just set up a default project.

? Select a default Firebase project for this directory: (Use arrow keys)
 [don't setup a default project]
>  algo-mini-app (algo-mini-app)
   VueWedding (vuewedding-c05d9)
(Move up and down to reveal more choices)
//}

次にFirestoreのセットアップを行います。
まずは、Firestoreのセキュリティルールの設定ファイルなどの名称について聞かれるので
すべてなにも押さずにデフォルトのものにしておきましょう。

//cmd{
=== Firestore Setup

Firestore Security Rules allow you to define how and when to allow
requests. You can keep these rules in your project directory
and publish them with firebase deploy.

? What file should be used for Firestore Rules? (firestore.rules)

Firestore indexes allow you to perform complex queries while
maintaining performance that scales with the size of the result
set. You can keep index definitions in your project directory
and publish them with firebase deploy.

? What file should be used for Firestore indexes? (firestore.indexes.json)
//}

最後はFirebase Hostingの設定です。
後章でも説明しますが、Nuxt.jsの生成される静的ファイルをデプロイしたいため
@<tt>{dist}というディレクトリ名を必ず指定してください。

//cmd{
=== Hosting Setup

Your public directory is the folder (relative to your project directory) that
will contain Hosting assets to be uploaded with firebase deploy. If you
have a build process for your assets, use your build's output directory.

? What do you want to use as your public directory? dist
? Configure as a single-page app (rewrite all urls to /index.html)? No
//}

これで環境構築が完了しました。
