"""Conan package manager config file. https://docs.conan.io/en/latest/"""
from conans import ConanFile, CMake

        
class Project(ConanFile):
    """Conan package file."""
    settings = "os", "compiler", "build_type", "arch"
    requires = ["doctest/2.3.7"]

    default_options = {
        "gtest:shared": False
    }

    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto",
        "submodule": "recursive"
    }
    
    generators = "cmake"

    def imports(self):
        self.copy("*.dll", "", "bin")
        self.copy("*.dylib", "", "lib")

    def build(self):
        cmake = CMake(self, generator="Ninja")
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        cmake.configure()
        cmake.build()

