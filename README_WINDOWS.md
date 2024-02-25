# Windows solutions
Every error and solution while compiling in windows.  

**Note**: Many errors will require you to clean created files, but they are used as cache (there is probably a way to make a clean rerun but I don't know).  

## Error 1
(after running `. .\build.ps1; Build-Host -BuildType "Release" -Arch "x64"`)  

```
CMake Error at CMakeLists.txt:2 (project):
  Generator

    Visual Studio 16 2019

  could not find any instance of Visual Studio.
```

### Explanation
Not much to explain, script try to execute Visual Studio from 2019.  

### Solution
Replace every `Visual Studio 16 2019` in **build.ps1** file, for you Visual Studio information (example: `Visual Studio 17 2022`).

## Error 2
(after running `. .\build.ps1; Build-Host -BuildType "Release" -Arch "x64"`)  

Many times mentioning missing nlohmann/json.hpp.  
```
C:\Users\thiag\Downloads\libzt\ext\ZeroTierOne\osdep\OSUtils.hpp(46,10): error C1083: Cannot open include file: 'nlohmann/json.hpp': No such file or directory [C:\Users\thiag\Downloads\libzt\cache\win-x64-host-release\
zto_obj.vcxproj]
  (compiling source file '../../ext/ZeroTierOne/node/Bond.cpp')
```

### Explanation
As mentioned by @jbatnozic:  
> certain headers from ZeroTierOne will try to `#include <nlohmann/json.hpp>` and won't be able to find it so the build will fail. I'm surprised that it even builds without this on other platforms (system package maybe?).

### Solution
Add `include_directories(${ZTO_SRC_DIR}/ext)` in **CMakeList.txt** file, under the line `# ZeroTier (ext)`.  

## Error 3
(after running `python3 -m SCons`)  

Many times mentioning not being able to link to "\_\_imp\_\*".  
```
zerotier.windows.template_release.x86_64.obj : error LNK2019: unresolved external symbol __imp_zts_init_from_storage referenced in function "public: int __cdecl godot::ZeroTier::init_from_storage(class godot::String)" (?init_from_storage@ZeroTier@godot@@QEAAHVString@2@@Z)
```

### Explanation
In **ZeroTierSockets.h** file, macros for dynamic library (`.dll`) are always being used: `__declspec(dllexport)` and `__declspec(dllimport)`.  
Even when you are building for static library (`.lib`).  

### Solution
In **ZeroTierSockets.h** file, edit the code under the section `ZeroTier Service and Network Controls`.  

```cpp
#if defined(_WIN32)
/*
#ifdef ADD_EXPORTS
#define ZTS_API __declspec(dllexport)
#else
#define ZTS_API __declspec(dllimport)
#endif
*/
#define ZTS_API
#define ZTCALL __cdecl
#else
#define ZTS_API
#define ZTCALL
#endif
```

## Error 4
(after running `python3 -m SCons`)  

> Don't remember how to reproduce and I'm not having this issue anymore, but here is the solution that I had.  

### Explanation
It will complain if you try to use a library build for debug and another library build for release.  

### Solution
Build both libraries for release/debug.  

Building for release: `python3 -m SCons target=template_release`  

# References
- https://github.com/zerotier/libzt/issues/270
- https://github.com/zerotier/libzt/issues/263
- https://stackoverflow.com/questions/2728649/error-lnk2005-xxx-already-defined-in-msvcrt-libmsvcr100-dllc-something-libc
