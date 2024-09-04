#!/usr/bin/env python3

from subprocess import run
from argparse import ArgumentParser
from platform import system
from pathlib import Path
from contextlib import chdir

INSTALL_DEPS = "conan install . --build missing -s build_type={}"
GENERATE = "cmake --preset conan-{}"
BUILD = "cmake --build --preset conan-{}"


def main() -> int:
    parser = ArgumentParser(description="build script")

    a = parser.add_argument
    a("build_type", choices=["debug", "release"], default="debug", nargs="?")
    a("--refresh", action="store_true")
    a("--run", action="store_true")

    args = parser.parse_args()

    build_type = args.build_type
    refresh = args.refresh

    if args.run:
        bin_path = Path("build", build_type.capitalize(), "main")
        run(bin_path).check_returncode()
        return 0

    def is_windows():
        return system() == "Windows"

    def cmake_cache_exist():
        if is_windows():
            return Path("build", "CMakeCache.txt").exists()
        else:
            return Path("build", build_type.capitalize(), "CMakeCache.txt").exists()

    if refresh or not cmake_cache_exist():
        install = INSTALL_DEPS.format(build_type.capitalize())
        run(install.split()).check_returncode()

        name = "default" if is_windows() else build_type
        generate = GENERATE.format(name)
        run(generate.split()).check_returncode()

    build = BUILD.format(build_type)
    run(build.split()).check_returncode()

    return 0


if __name__ == "__main__":
    with chdir(Path(__file__).absolute().parent):
        ret = main()
        exit(ret)
