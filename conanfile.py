from conan import ConanFile
from conan.tools.cmake import cmake_layout


class Recipe(ConanFile):
    settings = ["os", "compiler", "build_type", "arch"]
    generators = ["CMakeToolchain", "CMakeDeps", "MSBuildDeps"]
    requires = [
        "fmt/10.2.1",
        "sfml/2.6.1",
        "spdlog/1.14.1",
    ]

    def layout(self):
        cmake_layout(self)
