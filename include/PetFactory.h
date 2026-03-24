#ifndef PET_FACTORY_H
#define PET_FACTORY_H

#include <string>

#include "CommonTypes.h"

namespace boarding {

class Pet;
class PetCenter;

// PetFactory 负责根据输入来源创建具体派生类对象。
// 这样 main 函数就不用自己写很长的对象构造分支。
class PetFactory {
private:
    // 读取主人登记信息。
    static OwnerInfo readOwnerInfo();
    // 读取寄养计划信息。
    static StayPlan readStayPlan();

public:
    // createFromConsole 根据用户交互输入创建宠物对象。
    static Pet* createFromConsole(const PetCenter& petCenter);
    // createFromSavedLine 根据文件中的一行文本恢复宠物对象。
    static Pet* createFromSavedLine(const std::string& textLine);
};

}  // namespace boarding

#endif
