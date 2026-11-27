# Managed by lilim — rewritten by `lilim add`, `lilim remove` and `lilim sync`.
# Installed automatically when CMake configures (cmake/conan_provider.cmake).
from conan import ConanFile

class BadAppleTerminalRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeConfigDeps"

    def requirements(self):
        pass
