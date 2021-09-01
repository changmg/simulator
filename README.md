# Logic Simulator

## Requirements
- gcc
- g++
- make
- libreadline
- cmake

## Getting Started
### Download

```shell
git clone git@github.com:changmg/simulator.git --recursive
```

### Build & run
```shell
cd simulator/
mkdir build
cd build
cmake ..
make -j16
cd ..
```
It will generate `simulator.out` in the project root directory.

Use `./simulator.out -h` to get help.

Example:
```shell
./simulator.out -i circuit/signed-multiplier-16x16.blif
```
