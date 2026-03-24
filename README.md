# 宠物寄养中心课程项目

这是一个完整的 C++ 控制台项目，主题是“宠物寄养中心管理系统”。
项目采用多文件组织方式，源文件和头文件已经拆分，不是单文件拼接。

## 目录结构

```text
PetBoardingCenter
├─ include
│  ├─ CommonTypes.h
│  ├─ DynamicText.h
│  ├─ Utility.h
│  ├─ LimitedList.h
│  ├─ Pet.h
│  ├─ Dog.h
│  ├─ Cat.h
│  ├─ Rabbit.h
│  ├─ InputHelper.h
│  ├─ PetCenter.h
│  ├─ PetFactory.h
│  ├─ FileStorage.h
│  └─ ReportPrinter.h
├─ src
│  ├─ main.cpp
│  ├─ DynamicText.cpp
│  ├─ Utility.cpp
│  ├─ Pet.cpp
│  ├─ Dog.cpp
│  ├─ Cat.cpp
│  ├─ Rabbit.cpp
│  ├─ InputHelper.cpp
│  ├─ PetCenter.cpp
│  ├─ PetFactory.cpp
│  ├─ FileStorage.cpp
│  └─ ReportPrinter.cpp
├─ data
│  └─ pet_records.txt
└─ CMakeLists.txt
```

## 功能说明

1. 手动录入狗、猫、兔三类宠物
2. 显示全部宠物档案
3. 让全部宠物统一发声
4. 按编号查询宠物
5. 统计数量、平均年龄、总费用、预计收入
6. 按编号、名字、年龄、每日费用排序
7. 保存数据到文件
8. 从文件加载数据
9. 查看最近操作历史

## 对应知识点

本项目尽量覆盖《C++ Primer Plus》的核心内容：

- 变量、常量、输入输出、表达式、基础数据处理
- 结构体、字符串、字符数组、枚举、复合类型
- 循环、条件判断、关系表达式、`switch`
- 函数拆分与模块化
- 函数重载、默认参数、引用、内联函数、函数模板
- 命名空间、静态成员、动态内存、头文件管理
- 类与对象
- 友元与运算符重载
- 构造函数、析构函数、拷贝构造、赋值运算符、深拷贝
- 继承、虚函数、虚析构、多态
- 类模板与代码复用

## 重点体现位置

- 指针：`Pet*`、`Pet**`
- 函数指针：`PetAction`
- 动态内存：`DynamicText`
- 深拷贝：`DynamicText`、`PetCenter`
- 继承和多态：`Pet`、`Dog`、`Cat`、`Rabbit`
- 模板：`Utility.h`、`LimitedList.h`
- 文件读写：`FileStorage.cpp`

## 编译方式

如果你的环境里有 `g++`，可以直接执行：

```bash
g++ -std=c++11 -Iinclude src/*.cpp -o build/PetBoardingCenter.exe
```

然后运行：

```bash
./build/PetBoardingCenter.exe
```

## 说明

- 项目支持你自己输入数据并查看结果
- 默认数据文件为 `data/pet_records.txt`
- 代码中已经加入了较多注释，适合课程设计和作业展示
