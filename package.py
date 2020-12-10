
from spack import *

class StackMachine(CMakePackage):
    depends_on("fmt")
    depends_on("cxxopts")

    def cmake_args(self):
        return []
