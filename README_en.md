<!--
README_en.md - Last modified: 08-Feb-2026 (kobayasy)
-->

[
	[Installation](#installation) |
	[Usage](#usage)
]
// [Japanase(日本語)](README_ja.md)

---

[![macOS](https://github.com/kobayasy/printBar/workflows/macOS/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/build-macos.yml)
[![Linux](https://github.com/kobayasy/printBar/workflows/Linux/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/build-linux.yml)
<sup>|</sup>
[![SAST](https://github.com/kobayasy/printBar/workflows/SAST/badge.svg)](https://github.com/kobayasy/printBar/actions/workflows/codeql-analysis.yml)

Overlays a bar chart on the console output.
It works on any POSIX OS that has Terminfo.

### Installation
1. Build and installation with the following.
```sh
curl -LOJs https://github.com/kobayasy/printBar/releases/download/1.2/printBar-1.2.tar.gz
tar xzf printBar-1.2.tar.gz
cd printBar-1.2
./configure --prefix=$HOME
make install
```

2. Add `~/bin` in the PATH if not included.

### Usage
1. Do the following to show usage.
```sh
printbar --help
```

Execution examples:
![printBar](printBar.png)
