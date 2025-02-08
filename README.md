# Logic Simulator

An efficient logic simulator for logic circuits.

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

## Workflow of Logic Simulator
The working flow of the logic simulation is generally like this:

1. main.cc#L91: load circuit. The circuit is stored using a "NetMan" class, which is a wrapper class of the open-source LS tool ABC.
2. main.cc#L98: create a "Simulator" class, which is built upon the "NetMan" class.
3. main.cc#L102: randomly generate primary input patterns. Each node is associated with a simulation pattern. As shown in  https://github.com/changmg/simulator/blob/master/simulator/src/simulator.h#L12 , in the Simulator class, dat[id] represents the simulation pattern of the id-th node. Note that dat[id] has the type of "boost::dynamic_bitset <unsigned long long>", which is a bit vector.
4. main.cc#L103: logic simulation. Traverse the nodes in topological order and update the simulation patterns for all nodes.
5. main.cc#L110~#L117: print the signal probabilities.
