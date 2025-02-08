# Logic Simulator

## Requirements
- Reference environment, **Ubuntu 20.04 LTS** with the following tools and libraries:

  - Tools: gcc 10.3.0 & g++ 10.3.0 & [cmake](https://cmake.org/) 3.16.3

    You can install these tools with the following command:

    ```shell
    sudo apt install gcc-10
    sudo apt install g++-10
    sudo apt install cmake
    ```

    You also need to check whether the default versions of gcc and g++ are 10.3.0:

    ```shell
    gcc --version
    g++ --version
    ```

    If the default versions of gcc and g++ are not 10.3.0, please change them to 10.3.0.

  - Libraries: [libboost](https://www.boost.org/) 1.74.0, libreadline 8.0-4, libgmp, libmpfr, libmpc

    You can install these libraries with the following command:

    ```shell
    sudo apt install libboost1.74-all-dev
    sudo apt install libreadline-dev
    sudo apt install libgmp-dev
    sudo apt-get install libmpfr-dev
    sudo apt-get install libmpc-dev

## Getting Started
### Download

```shell
git clone --recursive git@github.com:changmg/simulator.git
```

### Build & run
Run the following commands in the project root directory.
```shell
mkdir build
cd build
cmake ..
make -j16
cd ..
```
It will generate `simulator.out` in the project root directory.

Example:
```shell
./simulator.out
```
