# Unwordler

Unwordler is an application written in C++ using the wxWidgets GUI library to solve the popular word puzzle game : Wordle

## Build

From project root:

```bash
mkdir build

cd build

cmake ..

cmake --build .

```
## Others options

```bash
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug // Generate ninja build files and use debug build

cmake --build . --target format // Run clang-format to auto indent the code

cmake --build . --target lint // Run clang-tidy and report linter warnings and errors
```

## Demo

![Unwordler Demo](https://github.com/sooriravindra/Unwordler/raw/master/res/Unwordler.gif "Unwordler Demo")
