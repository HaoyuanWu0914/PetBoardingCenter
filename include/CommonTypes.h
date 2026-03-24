#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <ostream>
#include <string>

namespace boarding {

// 这个头文件集中放置项目里多个模块都会用到的公共类型。
// 把这些基础定义抽出来后，其他头文件就不用重复声明同样的数据结构。
// 这样做也符合“先抽象公共概念，再组织业务模块”的工程写法。

// 使用具名常量代替魔法数字，便于维护和统一修改。
const int MAX_PHONE_LENGTH = 20;

// 枚举类比普通整数更安全，能避免菜单编号和宠物类型混用。
enum class PetKind {
    Dog = 1,
    Cat = 2,
    Rabbit = 3
};

enum class MenuOption {
    Exit = 0,
    AddPet = 1,
    ListPets = 2,
    MakeAllPetsSpeak = 3,
    SearchPet = 4,
    ShowStatistics = 5,
    SortPets = 6,
    SaveToFile = 7,
    LoadFromFile = 8,
    ShowHistory = 9
};

enum class SortField {
    ById = 1,
    ByName = 2,
    ByAge = 3,
    ByDailyFee = 4
};

// 结构体适合保存一组公开且相关的数据，便于教学展示。
struct OwnerInfo {
    // ownerName 表示宠物主人的姓名，查询档案时直接展示。
    std::string ownerName;
    // phoneNumber 使用字符数组保存，专门演示 C 风格字符串的用法。
    char phoneNumber[MAX_PHONE_LENGTH];
    // address 记录主人联系地址，便于模拟真实寄养中心登记流程。
    std::string address;
};

struct StayPlan {
    // stayDays 表示本次计划寄养的总天数。
    int stayDays;
    // needsMedicine 用于标记是否需要额外药物护理。
    bool needsMedicine;
    // mealCountPerDay 记录宠物每天需要喂食几次。
    int mealCountPerDay;
};

// 前置声明可以减少头文件之间的相互包含，提高编译效率。
class Pet;

// PetAction 是函数指针类型，表示“接收一只宠物并执行某种操作”的函数。
// 后续统一展示宠物信息、统一让宠物发声，都可以通过它来完成。
typedef void (*PetAction)(const Pet&);

// petKindToString 把枚举值转换成字符串，方便打印和保存到文件。
std::string petKindToString(PetKind petKind);

// 重载输出运算符后，可以直接使用 cout 输出主人信息结构体。
std::ostream& operator<<(std::ostream& output, const OwnerInfo& ownerInfo);

}  // namespace boarding

#endif
