# Windows solutions
Every error and solution while compiling in windows.  

**Note**: Many errors will require you to clean created files, because they are used as cache.  

## Error 1
```
CMake Error at CMakeLists.txt:2 (project):
  Generator

    Visual Studio 16 2019

  could not find any instance of Visual Studio.
```

**Solution**:  

Script try to execute Visual Studio from 2019 but you probably has some newer version.  

Replace every `Visual Studio 16 2019` in *build.ps1* file, for you Visual Studio information (example: `Visual Studio 17 2022`).

## Error 2
```
error C1083: Cannot open include file: 'nlohmann/json.hpp': No such file or directory
```

**Solution**:  

As mentioned by [@jbatnozic](https://github.com/zerotier/libzt/issues/263):  
> certain headers from ZeroTierOne will try to `#include <nlohmann/json.hpp>` and won't be able to find it so the build will fail. I'm surprised that it even builds without this on other platforms (system package maybe?).

Add `include_directories(${ZTO_SRC_DIR}/ext)` in *CMakeList.txt* file, under the line `# ZeroTier (ext)`.  

## Error 3
Many times mentioning not being able to link to `__imp_*`.  
```
zerotier.windows.template_release.x86_64.obj : error LNK2019: unresolved external symbol __imp_zts_init_from_storage referenced in function "public: int __cdecl godot::ZeroTier::init_from_storage(class godot::String)" (?init_from_storage@ZeroTier@godot@@QEAAHVString@2@@Z)
```

**Solution**:  

As mentioned by [Suma](https://stackoverflow.com/a/5159395/3210187)  
> The `__imp__` prefix appears whenever you are linking to a DLL.  

In *ZeroTierSockets.h* file, macros for dynamic library (`.dll`) are always being used: `__declspec(dllexport)` and `__declspec(dllimport)`.  
Even when you are building for static library (`.lib`).  

In *ZeroTierSockets.h* file, edit the code under the section `ZeroTier Service and Network Controls`.  

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
Complaining that you are trying to use a library build for debug and another library build for release.  

**Solution**:  

Build both libraries for release/debug.  

For example:
  - `. .\build.ps1; Build-Host -BuildType "Release" -Arch "x64"`
  - `python3 -m SCons target=template_release`  

## Error 5
```
Searching libraries
    Searching godot-cpp\bin\libgodot-cpp.windows.template_release.x86_64.lib:
    Searching lib\zt.lib:
zt.lib(Controls.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MD_DynamicRelease' doesn't match value 'MT_StaticRelease' in register_types.windows.template_release.x86_64.obj
```

**Explanation**:  
Project *godot-cpp* build a static library and expect that *libzt* also build a static library, but *libzt* is building as dynamic library.  

**Solution**:  
Replace `__declspec(dllexport)` and `__declspec(dllimport)` for nothing in all *libzt* project and compile it.

# References
- https://github.com/zerotier/libzt/issues/270
- https://github.com/zerotier/libzt/issues/263
- https://stackoverflow.com/questions/2728649/error-lnk2005-xxx-already-defined-in-msvcrt-libmsvcr100-dllc-something-libc
- https://stackoverflow.com/questions/3007312/resolving-lnk4098-defaultlib-msvcrt-conflicts-with
- https://stackoverflow.com/questions/64360872/libcpmt-lib-error-lnk2038-mismatch-detected-for-runtimelibrary-value-mt-sta
