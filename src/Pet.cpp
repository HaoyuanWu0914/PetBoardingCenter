#include "../include/Pet.h"

#include <sstream>

#include "../include/Utility.h"

namespace boarding {

// totalPetCount 用于统计当前内存中一共存在多少个 Pet 对象。
int Pet::totalPetCount = 0;

// 这个函数把枚举类型转成人类可读文本。
std::string petKindToString(PetKind petKind) {
    switch (petKind) {
    case PetKind::Dog:
        return "Dog";
    case PetKind::Cat:
        return "Cat";
    case PetKind::Rabbit:
        return "Rabbit";
    default:
        return "Unknown";
    }
}

// 运算符重载让 OwnerInfo 能够直接被输出流打印。
std::ostream& operator<<(std::ostream& output, const OwnerInfo& ownerInfo) {
    output << "主人: " << ownerInfo.ownerName
           << "，电话: " << ownerInfo.phoneNumber
           << "，地址: " << ownerInfo.address;
    return output;
}

Pet::Pet(PetKind petKindValue,
         int petIdValue,
         const std::string& petNameValue,
         int petAgeValue,
         const OwnerInfo& ownerInfoValue,
         const StayPlan& stayPlanValue,
         const char* careNoteText)
    : petKind(petKindValue),
      petId(petIdValue),
      petName(petNameValue),
      petAge(petAgeValue),
      ownerInfo(ownerInfoValue),
      stayPlan(stayPlanValue),
      careNote(careNoteText) {
    // 每创建一个对象，静态计数器加一。
    ++totalPetCount;
}

Pet::Pet(const Pet& other)
    : petKind(other.petKind),
      petId(other.petId),
      petName(other.petName),
      petAge(other.petAge),
      ownerInfo(other.ownerInfo),
      stayPlan(other.stayPlan),
      careNote(other.careNote) {
    // 拷贝出来的新对象同样应该计入总数量。
    ++totalPetCount;
}

Pet::~Pet() {
    // 对象销毁时把计数器减回去。
    --totalPetCount;
}

Pet& Pet::operator=(const Pet& other) {
    if (this != &other) {
        // 赋值只复制数据，不应该影响对象数量统计。
        petKind = other.petKind;
        petId = other.petId;
        petName = other.petName;
        petAge = other.petAge;
        ownerInfo = other.ownerInfo;
        stayPlan = other.stayPlan;
        careNote = other.careNote;
    }

    return *this;
}

PetKind Pet::getPetKind() const {
    // 返回宠物类型枚举值。
    return petKind;
}

int Pet::getPetId() const {
    // 返回宠物唯一编号。
    return petId;
}

const std::string& Pet::getPetName() const {
    // 返回宠物名字的常量引用，避免额外拷贝。
    return petName;
}

int Pet::getPetAge() const {
    // 返回宠物年龄。
    return petAge;
}

const OwnerInfo& Pet::getOwnerInfo() const {
    // 返回主人信息结构体的只读引用。
    return ownerInfo;
}

const StayPlan& Pet::getStayPlan() const {
    // 返回寄养计划结构体的只读引用。
    return stayPlan;
}

const DynamicText& Pet::getCareNote() const {
    // 返回护理说明对象的只读引用。
    return careNote;
}

void Pet::setStayDays(int newStayDays) {
    // 允许外部按需调整计划寄养天数。
    stayPlan.stayDays = newStayDays;
}

void Pet::setCareNote(const char* newCareNote) {
    // 把新的护理说明交给 DynamicText 自己管理。
    careNote.setText(newCareNote);
}

void Pet::displayProfile(std::ostream& output, bool detailed) const {
    // 第一行输出所有宠物共有的基础资料。
    output << "类型: " << petKindToString(petKind)
           << " | 编号: " << petId
           << " | 名字: " << petName
           << " | 年龄: " << petAge << '\n';

    if (detailed) {
        // 详细模式下继续输出主人信息、寄养计划和护理说明。
        output << ownerInfo << '\n';
        output << "寄养天数: " << stayPlan.stayDays
               << "，每日喂食次数: " << stayPlan.mealCountPerDay
               << "，是否需要药物护理: " << util::yesNo(stayPlan.needsMedicine) << '\n';
        output << "特殊护理说明: " << (careNote.empty() ? "无" : careNote.c_str()) << '\n';
    }
}

std::string Pet::buildCommonData() const {
    // 序列化时，基类负责输出所有派生类共享字段。
    std::ostringstream output;

    output << petId << '|'
           << util::escapeField(petName) << '|'
           << petAge << '|'
           << util::escapeField(ownerInfo.ownerName) << '|'
           << util::escapeField(ownerInfo.phoneNumber) << '|'
           << util::escapeField(ownerInfo.address) << '|'
           << stayPlan.stayDays << '|'
           << stayPlan.needsMedicine << '|'
           << stayPlan.mealCountPerDay << '|'
           << util::escapeField(careNote.c_str());

    return output.str();
}

std::ostream& operator<<(std::ostream& output, const Pet& pet) {
    // 统一复用 displayProfile，避免两处格式不一致。
    pet.displayProfile(output, true);
    return output;
}

}  // namespace boarding
