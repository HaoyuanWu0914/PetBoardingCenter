#ifndef CAT_H
#define CAT_H

#include "Pet.h"

namespace boarding {

class Cat : public Pet {
private:
    // likesClimbingFrame 表示猫咪是否喜欢猫爬架。
    bool likesClimbingFrame;
    // jumpLevel 表示猫咪的敏捷程度，用于模拟个性化收费。
    int jumpLevel;

public:
    // 构造函数负责同时初始化公共信息和猫咪专属信息。
    Cat(int petIdValue,
        const std::string& petNameValue,
        int petAgeValue,
        const OwnerInfo& ownerInfoValue,
        const StayPlan& stayPlanValue,
        const char* careNoteText,
        bool likesClimbingFrameValue,
        int jumpLevelValue);

    // 复制相关函数保证派生类对象复制完整。
    Cat(const Cat& other);
    ~Cat() override;

    Cat& operator=(const Cat& other);

    // 这些接口通过 override 体现运行期多态。
    void displayProfile(std::ostream& output, bool detailed = true) const override;
    void makeSound() const override;
    double calculateDailyFee() const override;
    Pet* clone() const override;
    std::string serializeData() const override;
};

}  // namespace boarding

#endif
