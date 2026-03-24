#ifndef RABBIT_H
#define RABBIT_H

#include "Pet.h"

namespace boarding {

class Rabbit : public Pet {
private:
    // carrotCountPerDay 表示兔兔每天要吃多少根胡萝卜。
    int carrotCountPerDay;
    // likesTunnel 记录兔兔是否喜欢隧道类玩具。
    bool likesTunnel;

public:
    // 构造函数把兔兔的饮食和活动偏好一起写入对象。
    Rabbit(int petIdValue,
           const std::string& petNameValue,
           int petAgeValue,
           const OwnerInfo& ownerInfoValue,
           const StayPlan& stayPlanValue,
           const char* careNoteText,
           int carrotCountPerDayValue,
           bool likesTunnelValue);

    // 复制相关函数便于容器做深拷贝。
    Rabbit(const Rabbit& other);
    ~Rabbit() override;

    Rabbit& operator=(const Rabbit& other);

    // 这些成员函数是 Rabbit 对基类虚函数的具体实现。
    void displayProfile(std::ostream& output, bool detailed = true) const override;
    void makeSound() const override;
    double calculateDailyFee() const override;
    Pet* clone() const override;
    std::string serializeData() const override;
};

}  // namespace boarding

#endif
