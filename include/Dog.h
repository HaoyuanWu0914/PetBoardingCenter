#ifndef DOG_H
#define DOG_H

#include <string>

#include "Pet.h"

namespace boarding {

class Dog : public Pet {
private:
    // needsOutdoorWalk 记录狗狗是否需要额外遛弯服务。
    bool needsOutdoorWalk;
    // favoriteToy 保存狗狗最喜欢的玩具名称。
    std::string favoriteToy;

public:
    // 构造函数在初始化基类部分后，再补充狗狗专属属性。
    Dog(int petIdValue,
        const std::string& petNameValue,
        int petAgeValue,
        const OwnerInfo& ownerInfoValue,
        const StayPlan& stayPlanValue,
        const char* careNoteText,
        bool needsOutdoorWalkValue,
        const std::string& favoriteToyValue);

    // 拷贝构造和赋值运算符体现派生类对象的复制过程。
    Dog(const Dog& other);
    ~Dog() override;

    Dog& operator=(const Dog& other);

    // 以下虚函数全部重写为狗狗自己的业务行为。
    void displayProfile(std::ostream& output, bool detailed = true) const override;
    void makeSound() const override;
    double calculateDailyFee() const override;
    Pet* clone() const override;
    std::string serializeData() const override;
};

}  // namespace boarding

#endif
