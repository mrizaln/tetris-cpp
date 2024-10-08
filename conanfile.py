from conan import ConanFile
from conan.tools.cmake import cmake_layout


class Recipe(ConanFile):
    settings = ["os", "compiler", "build_type", "arch"]
    generators = ["CMakeToolchain", "CMakeDeps", "MSBuildDeps"]
    requires = [
        "asio/1.29.0",
        "sfml/2.6.1",
        "spdlog/1.14.1",
        "tl-expected/1.1.0",
        "magic_enum/0.9.6",
    ]

    def layout(self):
        cmake_layout(self)
