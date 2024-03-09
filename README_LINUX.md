# Linux solutions
Every error and solution while compiling in linux.  


## Error 1
```
error: ‘invalid_argument’ is not a member of ‘std’
    throw std::invalid_argument("Family name already exists with different type");
```
```
note: ‘std::invalid_argument’ is defined in header ‘<stdexcept>’; did you forget to ‘#include <stdexcept>’?
```

**Solution**:  

Add `#include <stdexcept>` to files:  
- `libzt/ext/ZeroTierOne/ext/prometheus-cpp-lite-1.0/core/include/prometheus/family.h`  
- `libzt/ext/ZeroTierOne/ext/prometheus-cpp-lite-1.0/core/include/prometheus/registry.h`  