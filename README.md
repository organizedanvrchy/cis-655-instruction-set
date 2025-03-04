# CIS655-instruction-set

>[!NOTE]
>**Project done in collaboration with [Dan](https://github.com/radioxeth), [Matthew](https://github.com/how2useGit), [Jacob Montpetit](https://github.com/vikingfacer), and [Chang](https://github.com/ahamburglar).** <br>

# Build
Requirements: cmake & build-generator (make, nmake, ninja, etc...)
_all instructions assume commands are ran in the root of the directory_

make a directory for the build
```
mkdir build
```

configure the build (vanilla)
```
cmake -S . -B build
```

configure the build (ninja flavored)
```
cmake -S . -B build -G Ninja
```

build the build
```
cd build
<build command: make, nmake, etc..>
```

build the build ninja style
```
ninja -C build
```

---

# Run
navigate to into build directory
```
cd build
```
run the emulator
```
./emulator/emulator
```
run the parser
```
./parser/parser
```
