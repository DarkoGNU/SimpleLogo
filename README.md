# SimpleLogo [![](http://github-actions.40ants.com/DarkoGNU/SimpleLogo/matrix.svg)](https://github.com/DarkoGNU/SimpleLogo)

A simple Logo implementation in C++

## Dependencies

- png++

Installation on Windows:

```cmd
vcpkg install pngpp
```

Installation on macOS:

```sh
brew install png++
```

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

## Usage

Check the folder Examples for examples of SimpleLogo's scripting language

## Compilation

```sh
git clone https://github.com/DarkoGNU/SimpleLogo
cd SimpleLogo/

BUILD_TYPE=RelWithDebInfo
cmake -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build build --config $BUILD_TYPE
```

The binary is named SimpleLogo and will be placed in build/bin

## Contributions and bug reports

All contributions and bug reports are welcome!
