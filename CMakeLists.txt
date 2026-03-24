cmake_minimum_required(VERSION 3.10)
project(PetBoardingCenter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-fexec-charset=GBK>")

add_executable(PetBoardingCenter
    src/main.cpp
    src/DynamicText.cpp
    src/FileStorage.cpp
    src/InputHelper.cpp
    src/Pet.cpp
    src/PetCenter.cpp
    src/PetFactory.cpp
    src/ReportPrinter.cpp
    src/Utility.cpp
    src/Dog.cpp
    src/Cat.cpp
    src/Rabbit.cpp
)
# 告诉 GCC 编译器在生成可执行文件时，将执行字符集设置为 GBK

target_compile_definitions(PetBoardingCenter PRIVATE BOARDING_SEPARATE_BUILD)
