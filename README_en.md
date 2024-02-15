[Installation](#installation)
|
[Usage](#usage)
*|*
[Japanase(日本語)](README_ja.md)

***
[![macOS](https://github.com/kobayasy/printBar/workflows/macOS/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/build-macos.yml)
[![Linux](https://github.com/kobayasy/printBar/workflows/Linux/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/build-linux.yml)
*|*
[![SAST](https://github.com/kobayasy/printBar/workflows/SAST/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/codeql-analysis.yml)

[printBar] overlays a bar chart on the console output.
It works on any POSIX OS that has Terminfo.

## Installation
1. Build and installation with the following.
```
curl -LOJs https://github.com/kobayasy/printBar/releases/download/1.1/printBar-1.1.tar.gz
tar xzf printBar-1.1.tar.gz
cd printBar-1.1
./configure --prefix=$HOME
make install

```

2. Add ~/bin in the PATH if not included.

## Usage
1. Do the following to show usage.
```
printbar --help

```

Execution examples:
<img src="printBar.png" alt="printBar"/>

[printBar]: https://github.com/kobayasy/printBar
