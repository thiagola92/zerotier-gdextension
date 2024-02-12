# godtier-extension
This repository is used to generate the GDExtension


# Submodules
- `godot-cpp` submodule responsible to generate the GDExtension.
- `godtier` submodule responsible for testing the GDExtension.

### Update submodules 
```bash
git submodule update --remote # Pull changes from repository
```

### Compile Debug
```bash
scons
```

### Compile Release
```bash
scons target=template_release
```

# references
- https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/what_is_gdextension.html
- https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html
- https://docs.godotengine.org/en/stable/contributing/development/core_and_modules/custom_modules_in_cpp.html#doc-custom-modules-in-cpp
- https://github.com/gilzoide/hello-gdextension/tree/main/1.hello-c