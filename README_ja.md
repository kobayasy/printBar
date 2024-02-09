[インストール](#インストール)
|
[使い方](#使い方)

***
[![macOS](https://github.com/kobayasy/printBar/workflows/macOS/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/build-macos.yml)
[![Linux](https://github.com/kobayasy/printBar/workflows/Linux/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/build-linux.yml)
*|*
[![SAST](https://github.com/kobayasy/printBar/workflows/SAST/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/codeql-analysis.yml)

[printBar] はコンソール出力をバーグラフ表示するコマンドです。

## 動作環境
POSIX準拠のOSならば動作すると思います。

## インストール
1. 下記コマンドでビルドとインストールを実行します。
```
curl -LOJs https://github.com/kobayasy/printBar/releases/download/1.1/printBar-1.1.tar.gz
tar xzf printBar-1.1.tar.gz
cd printBar-1.1
./configure --prefix=$HOME
make install

```

2. PATH に ~/bin が含まれていない場合は追加してください。

## 使い方
1. 下記コマンドで使い方が表示されます。
```
printbar --help

```

実行例↓
<img src="printBar.png" alt="printBar"/>

[printBar]: https://github.com/kobayasy/printBar
