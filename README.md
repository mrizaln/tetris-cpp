# tetris-cpp

Tetris written in C++20

## Dependencies

Compiler

- Any compiler with C++20 support (concepts and coroutines)

Build tools

- Python 3 (required to use Conan)
- CMake 2.23+
- Conan 2

Library dependencies

> dependencies are managed using Conan (see [conanfile.py](conanfile.py) for exact versions of the dependencies)

- fmt
- SFML

## Building

I have created a handy build script and runner for this:

> If `python` executable is not found, it probably named something else like `python3` (in Fedora)

```sh
python build.py --release --run     # build and run the program at one go
```

If you want to invoke the command manually, then just do the following

> The exact commands may vary if you have different platform than mine (Fedora)

```sh
conan install . --build missing -s build_type=Release # or Debug
cmake --preset conan-release                          # use conan-default if you have a multi-config build system (Windows)
cmake --build --preset conan-release
./build/Debug/main                                    # run the program
```
