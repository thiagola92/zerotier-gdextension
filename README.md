# zerotier-gdextension
This repository is used to generate ZeroTier GDExtension.  

# Requirements
- Linux
  - Install SCons
    - Ubuntu: `sudo apt install scons`
- Windows
  - Install Python
  - Install SCons: `pip install SCons`
  - Install Visual Studio 2022

# Build libzt
- `cd libzt`
- Fix bugs
  - Linux: https://github.com/zerotier/libzt/issues/269
  - Windows: https://github.com/zerotier/libzt/issues/270
- Build
  - Linux: `./build.sh host "release"`
  - Windows: `. .\build.ps1; Build-Host -BuildType "Release" -Arch "x64"`
- Copy lib
  - Linux example
    - `cp dist/linux-x64-host-release/lib/libzt.so ../lib/libzt.so`
  - Windows example (renaming at same time)
    - `cp dist/windows-x64-host-release/lib/libzt.dll ../lib/zt-shared.dll`
    - `cp dist/windows-x64-host-release/lib/libzt.lib ../lib/zt-shared.lib`
- `cd ..`

# Compile GDExtension
- Compile
  - Debug: `scons`
  - Release: `scons target=template_release`
- Copy lib to your project binary directory
  - Linux example
    - `cp lib/libzt.so test/bin/libzt.so`
  - Windows example
    - `cp lib/zt-shared.dll test/bin/zt-shared.dll`

# Submodules
- `godot-cpp` submodule to generate the GDExtension.
- `libzt` submodule to compile ZeroTier lib.

# References
- **GDExtension**
  - https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/what_is_gdextension.html
  - https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html
  - https://docs.godotengine.org/en/stable/contributing/development/core_and_modules/custom_modules_in_cpp.html#doc-custom-modules-in-cpp
  - https://github.com/gilzoide/hello-gdextension/tree/main/1.hello-c
- **libzt**
  - https://docs.zerotier.com/sockets/
