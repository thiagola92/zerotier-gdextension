# godtier-extension
This repository is used to generate Godtier GDExtension.  
Godtier is an extension to use ZeroTier in Godot.  

### Compile Debug
```bash
scons
```

### Compile Release
```bash
scons target=template_release
```

# Submodules
- `godot-cpp` submodule to generate the GDExtension.
- `libzt` submodule to compile ZeroTier lib.

### Update submodules
```bash
git submodule update --remote # Pull changes from repository
```

Still need to commit this repository with the changes (`git add`, `git commit`).  

# references
- https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/what_is_gdextension.html
- https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html
- https://docs.godotengine.org/en/stable/contributing/development/core_and_modules/custom_modules_in_cpp.html#doc-custom-modules-in-cpp
- https://github.com/gilzoide/hello-gdextension/tree/main/1.hello-c