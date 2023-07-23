from conans import ConanFile, CMake

class Example(ConanFile):
    name = "Example"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package"
    requires = [("boost/1.82.0"), ("glfw/3.3.8"), ("opengl/system"), ("qt/6.5.0"), ("glew/2.2.0"), ("glm/cci.20230113")]