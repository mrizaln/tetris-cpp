# tetris-cpp

Tetris written in C++

## Dependencies

Build tools

- Python 3
- CMake 2.23+
- Conan 2

Library dependencies

> dependencies are managed using Conan

- fmt

## Building

If it was your first time building this project, you need to add `--install-deps` flags to install all the dependencies. This step is required for each build type (debug and release).

The `debug` flag can be replaced by `release` if you plan on building a release version of the project.

```sh
python build.py --install-deps debug
```
