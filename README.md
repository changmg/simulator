# Logic Simulator

## Requirements
To compile [ABC](https://github.com/berkeley-abc/abc), you need:
- gcc
- make
- libreadline

To compile the whole project, you also need:
- libboost
- ctags

## Getting Started
### Clone & Build ABC
Clone `ABC` into `abc/`.
```
git clone git@github.com:berkeley-abc/abc.git
```

Build a static library `libabc.a`.
```
cd abc/
make libabc.a
```

### Build Logic Simulator
Generate a executable program:
```
make
```
It will generate a program named `main`.

Use `./main -h` to get help.

Example:
```
./main -i circuit/rca12.blif
```

The demo verifies a 12-bit ripple carry adder.
