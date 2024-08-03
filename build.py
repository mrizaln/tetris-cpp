#!/usr/bin/env python3

from subprocess import run
from argparse import ArgumentParser

INSTALL_DEPS = "conan install . -of build/{}/ --build missing -s build_type={}"
GENERATE = "cmake --preset conan-{}"
BUILD = "cmake --build --preset conan-{}"


def main():
    parser = ArgumentParser(description="build script")

    parser.add_argument("build_type", choices=["debug", "release"], default="debug", nargs='?')
    parser.add_argument("--install-deps", action="store_true")

    args = parser.parse_args()

    if args.install_deps:
        install = INSTALL_DEPS.format(args.build_type, args.build_type.capitalize())
        run(install.split())

    generate = GENERATE.format(args.build_type)
    build = BUILD.format(args.build_type)

    run(generate.split())
    run(build.split())


if __name__ == "__main__":
    main()
