```
git submodule add -b release/v9.2 https://github.com/lvgl/lvgl lvgl
```

```
mkdir build
cd build
emcmake cmake ..
make -j8
```


build-with-emscripten.sh : 

```
#!/usr/bin/env sh

# prerequisite: put in .bashrc following line: source ~/emsdk/emsdk_env.sh

# execute from cmd.exe: wsl -d Ubuntu-20.04 -e bash -lic "~/build-with-emscripten.sh ~/lvgl/v9-with-flow-no-eez-framework/"

cd $1
mkdir -p build
cd build
emcmake cmake ..
make -j8
```