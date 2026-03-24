#include "../include/Dog.h"

#include <iostream>
#include <sstream>

#include "../include/Utility.h"

namespace boarding {

// Dog 表示宠物寄养中心中的狗狗类型。
Dog::Dog(int petIdValue,
         const std::string& petNameValue,
         int petAgeValue,
         const OwnerInfo& ownerInfoValue,
         const StayPlan& stayPlanValue,
         const char* careNoteText,
         bool needsOutdoorWalkValue,
         const std::string& favoriteToyValue)
    : Pet(PetKind::Dog, petIdValue, petNameValue, petAgeValue, ownerInfoValue, stayPlanValue, careNoteText),
      needsOutdoorWalk(needsOutdoorWalkValue),
      favoriteToy(favoriteToyValue) {
    // 构造函数体留空，因为初始化工作已经在初始化列表完成。
}

Dog::Dog(const Dog& other)
    : Pet(other),
      needsOutdoorWalk(other.needsOutdoorWalk),
      favoriteToy(other.favoriteToy) {
    // 拷贝构造交给基类和成员对象分别完成自己的复制。
}

Dog::~Dog() {
    // 当前类没有额外堆资源，但保留析构函数便于教学展示。
}

Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        // 先复制基类部分，再复制派生类自己的成员。
        Pet::operator=(other);
        needsOutdoorWalk = other.needsOutdoorWalk;
        favoriteToy = other.favoriteToy;
    }

    return *this;
}

void Dog::displayProfile(std::ostream& output, bool detailed) const {
    // 先打印基类共有信息，再补充狗狗特有字段。
    Pet::displayProfile(output, detailed);
    output << "狗狗特征: 需要遛弯 " << util::yesNo(needsOutdoorWalk)
           << "，最喜欢的玩具: " << favoriteToy << '\n';
    output << "每日费用: " << calculateDailyFee() << " 元" << '\n';
}

void Dog::makeSound() const {
    // 狗狗对象的多态叫声实现。
    std::cout << petName << " 说: 汪汪汪!" << std::endl;
}

double Dog::calculateDailyFee() const {
    // 狗狗收费以基础费用为起点，再叠加个性化服务费用。
    double baseFee = 58.0;

    if (needsOutdoorWalk) {
        // 额外遛弯会增加人工成本。
        baseFee += 12.0;
    }

    if (stayPlan.needsMedicine) {
        // 药物护理属于附加服务，需要追加收费。
        baseFee += 6.0;
    }

    return baseFee;
}

Pet* Dog::clone() const {
    // clone 返回一个堆上的新对象，供 PetCenter 深拷贝使用。
    return new Dog(*this);
}

std::string Dog::serializeData() const {
    // 派生类在基类公共数据后，再拼接自己的专属字段。
    std::ostringstream output;
    output << petKindToString(getPetKind()) << '|'
           << buildCommonData() << '|'
           << needsOutdoorWalk << '|'
           << util::escapeField(favoriteToy);
    return output.str();
}

}  // namespace boarding
