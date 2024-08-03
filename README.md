# tetris-cpp

Tetris written in C++

## Dependencies

Build dependecies

- Python 3
- CMake
- Conan

Library dependencies

- fmt

## Building

If it was your first time building this project, you need to add `--install-deps` flags to install all the dependencies. This step is required for each build type (debug and release).

The `debug` flag can be replaced by `release` if you plan on building a release version of the project.

```sh
python build.py --install-deps debug
```
