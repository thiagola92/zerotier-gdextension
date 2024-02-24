# Windows solutions
Every error and solution while compiling in windows.  

## Error
(after running `. .\build.ps1; Build-Host -BuildType "Release" -Arch "x64"`)  

```
CMake Error at CMakeLists.txt:2 (project):
  Generator

    Visual Studio 16 2019

  could not find any instance of Visual Studio.
```

## Solution
Replace every `Visual Studio 16 2019` in **build.ps1** file, for you Visual Studio information (example: `Visual Studio 17 2022`).

## Error
(after running `. .\build.ps1; Build-Host -BuildType "Release" -Arch "x64"`)  

Many times mentioning missing nlohmann/json.hpp.  
```
C:\Users\thiag\Downloads\libzt\ext\ZeroTierOne\osdep\OSUtils.hpp(46,10): error C1083: Cannot open include file: 'nlohmann/json.hpp': No such file or directory [C:\Users\thiag\Downloads\libzt\cache\win-x64-host-release\
zto_obj.vcxproj]
  (compiling source file '../../ext/ZeroTierOne/node/Bond.cpp')
```

## Solution
Add `include_directories(${ZTO_SRC_DIR}/ext)` in **CMakeList.txt** file, under the line `# ZeroTier (ext)`.  

## Error
(after running `python3 -m SCons`)  

Many times mentioning not being able to link to "\_\_imp\_\*".  
```
zerotier.windows.template_release.x86_64.obj : error LNK2019: unresolved external symbol __imp_zts_init_from_storage referenced in function "public: int __cdecl godot::ZeroTier::init_from_storage(class godot::String)" (?init_from_storage@ZeroTier@godot@@QEAAHVString@2@@Z)
```

## Solution
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

**Note**: Remember to delete files created by previous attempt.  

# References
- https://github.com/zerotier/libzt/issues/270
- https://github.com/zerotier/libzt/issues/263
