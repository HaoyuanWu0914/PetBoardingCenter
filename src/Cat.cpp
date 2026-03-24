#include "../include/Cat.h"

#include <iostream>
#include <sstream>

#include "../include/Utility.h"

namespace boarding {

// Cat 表示寄养中心中的猫咪类型。
Cat::Cat(int petIdValue,
         const std::string& petNameValue,
         int petAgeValue,
         const OwnerInfo& ownerInfoValue,
         const StayPlan& stayPlanValue,
         const char* careNoteText,
         bool likesClimbingFrameValue,
         int jumpLevelValue)
    : Pet(PetKind::Cat, petIdValue, petNameValue, petAgeValue, ownerInfoValue, stayPlanValue, careNoteText),
      likesClimbingFrame(likesClimbingFrameValue),
      jumpLevel(jumpLevelValue) {
    // 初始化列表已经完成全部初始化工作。
}

Cat::Cat(const Cat& other)
    : Pet(other),
      likesClimbingFrame(other.likesClimbingFrame),
      jumpLevel(other.jumpLevel) {
    // 拷贝构造保证猫咪对象被完整复制。
}

Cat::~Cat() {
    // 这里没有额外资源，但显式析构函数能更清晰体现继承结构。
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        // 复制时先处理共同基类，再处理本类字段。
        Pet::operator=(other);
        likesClimbingFrame = other.likesClimbingFrame;
        jumpLevel = other.jumpLevel;
    }

    return *this;
}

void Cat::displayProfile(std::ostream& output, bool detailed) const {
    // 先显示通用资料，再补充猫咪特色资料。
    Pet::displayProfile(output, detailed);
    output << "猫咪特征: 喜欢猫爬架 " << util::yesNo(likesClimbingFrame)
           << "，敏捷等级: " << jumpLevel << '\n';
    output << "每日费用: " << calculateDailyFee() << " 元" << '\n';
}

void Cat::makeSound() const {
    // 猫咪对象的叫声实现。
    std::cout << petName << " 说: 喵喵喵!" << std::endl;
}

double Cat::calculateDailyFee() const {
    // 猫咪收费会受敏捷等级、猫爬架偏好和药物护理影响。
    double baseFee = 50.0 + jumpLevel * 1.5;

    if (likesClimbingFrame) {
        // 喜欢爬架意味着需要更多活动设施。
        baseFee += 5.0;
    }

    if (stayPlan.needsMedicine) {
        // 药物护理增加额外服务费用。
        baseFee += 4.0;
    }

    return baseFee;
}

Pet* Cat::clone() const {
    // 返回当前对象的一个深拷贝副本。
    return new Cat(*this);
}

std::string Cat::serializeData() const {
    // 保存时追加猫咪特有的两个字段。
    std::ostringstream output;
    output << petKindToString(getPetKind()) << '|'
           << buildCommonData() << '|'
           << likesClimbingFrame << '|'
           << jumpLevel;
    return output.str();
}

}  // namespace boarding
