# SimpleLogo [![Ubuntu](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/Ubuntu.yml/badge.svg)](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/Ubuntu.yml) [![macOS](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/macOS.yml/badge.svg)](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/macOS.yml) [![Windows](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/Windows.yml/badge.svg)](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/Windows.yml)

A simple Logo implementation in C++

## Downloading the source and preparing for compilation

```sh
git clone https://github.com/DarkoGNU/SimpleLogo
mkdir SimpleLogo/build
cd SimpleLogo/build
```

## Dependencies

- png++

Installation on Windows:
```cmd
conan install ..
```
Refer to [docs.conan.io](https://docs.conan.io/en/latest/installation.html) for Conan installation guide

Installation on macOS:
```sh
brew install png++
```
Refer to [brew.sh](https://brew.sh/) for Homebrew installation guide

Installation on Arch Linux:
```sh
sudo pacman -Syu
sudo pacman -S png++
```

Installation on Debian/Ubuntu:
```sh
sudo apt update
sudo apt install libpng++-dev
```

## Compilation

```sh
cmake ..
cmake --build .
```

The binary is named SimpleLogo and will be placed in build/bin

## Usage

Check the folder Examples for examples of SimpleLogo's scripting language

## Copyright

Please put the following copyright disclaimer where it's appropriate:

Copyright 2021 The SimpleLogo Authors.
Licensed under GPL-3.0-or-later

## Contributions and bug reports

All contributions and bug reports are welcome!
