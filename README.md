# SimpleLogo [![CMake](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/cmake.yml/badge.svg)](https://github.com/DarkoGNU/SimpleLogo/actions/workflows/cmake.yml)

A simple Logo implementation in C++

## Dependencies

- png++

Installation on Arch Linux:

```bash
sudo pacman -Syu
sudo pacman -S png++
```

Installation on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install libpng++-dev
```

## Usage

Check the folder Examples for examples of SimpleLogo's scripting language

## Compilation

```bash
git clone https://github.com/DarkoGNU/SimpleLogo
cd SimpleLogo/
cmake -B build && make -j -C build
```

The binary is named SimpleLogo and will be placed in build/bin

## Contributions and bug reports

All contributions and bug reports are welcome!
