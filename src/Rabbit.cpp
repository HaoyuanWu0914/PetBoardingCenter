#include "../include/Rabbit.h"

#include <iostream>
#include <sstream>

#include "../include/Utility.h"

namespace boarding {

// Rabbit 表示寄养中心中的兔兔类型。
Rabbit::Rabbit(int petIdValue,
               const std::string& petNameValue,
               int petAgeValue,
               const OwnerInfo& ownerInfoValue,
               const StayPlan& stayPlanValue,
               const char* careNoteText,
               int carrotCountPerDayValue,
               bool likesTunnelValue)
    : Pet(PetKind::Rabbit, petIdValue, petNameValue, petAgeValue, ownerInfoValue, stayPlanValue, careNoteText),
      carrotCountPerDay(carrotCountPerDayValue),
      likesTunnel(likesTunnelValue) {
    // 数据成员在初始化列表中完成初始化。
}

Rabbit::Rabbit(const Rabbit& other)
    : Pet(other),
      carrotCountPerDay(other.carrotCountPerDay),
      likesTunnel(other.likesTunnel) {
    // 拷贝构造便于多态容器执行深拷贝。
}

Rabbit::~Rabbit() {
    // 显式保留析构函数，便于展示继承结构中的析构链。
}

Rabbit& Rabbit::operator=(const Rabbit& other) {
    if (this != &other) {
        // 赋值遵循“先基类、后派生类”的顺序。
        Pet::operator=(other);
        carrotCountPerDay = other.carrotCountPerDay;
        likesTunnel = other.likesTunnel;
    }

    return *this;
}

void Rabbit::displayProfile(std::ostream& output, bool detailed) const {
    // 先复用基类输出，再追加兔兔专属资料。
    Pet::displayProfile(output, detailed);
    output << "兔兔特征: 每日胡萝卜 " << carrotCountPerDay
           << " 根，喜欢隧道 " << util::yesNo(likesTunnel) << '\n';
    output << "每日费用: " << calculateDailyFee() << " 元" << '\n';
}

void Rabbit::makeSound() const {
    // 兔兔对象的叫声实现。
    std::cout << petName << " 说: 呜噜..." << std::endl;
}

double Rabbit::calculateDailyFee() const {
    // 兔兔费用与饮食消耗、隧道玩具和药物护理有关。
    double baseFee = 35.0 + carrotCountPerDay * 2.5;

    if (likesTunnel) {
        // 隧道玩具需要额外设施成本。
        baseFee += 3.0;
    }

    if (stayPlan.needsMedicine) {
        // 药物护理依然属于附加服务。
        baseFee += 5.0;
    }

    return baseFee;
}

Pet* Rabbit::clone() const {
    // clone 返回新的堆对象，供外部接管所有权。
    return new Rabbit(*this);
}

std::string Rabbit::serializeData() const {
    // 派生类把自己的饮食和偏好信息接在公共数据后面。
    std::ostringstream output;
    output << petKindToString(getPetKind()) << '|'
           << buildCommonData() << '|'
           << carrotCountPerDay << '|'
           << likesTunnel;
    return output.str();
}

}  // namespace boarding
