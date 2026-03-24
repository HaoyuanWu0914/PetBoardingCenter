#include "../include/PetFactory.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/Cat.h"
#include "../include/Dog.h"
#include "../include/InputHelper.h"
#include "../include/PetCenter.h"
#include "../include/Rabbit.h"
#include "../include/Utility.h"

namespace boarding {

// ------------------------------------------------------------------
// PetFactory.cpp 负责“创建对象”这一件事。
// main 函数不直接 new Dog / Cat / Rabbit，
// 而是把创建逻辑交给工厂类统一处理。
// 这样可以让主流程更短、更清晰，也便于后续扩展。
// ------------------------------------------------------------------

// readOwnerInfo 统一读取主人姓名、电话和地址。
// 这些信息会被封装进 OwnerInfo 结构体后整体返回。
OwnerInfo PetFactory::readOwnerInfo() {
    OwnerInfo ownerInfo = {};

    // ownerName 表示宠物主人的姓名。
    ownerInfo.ownerName = input::readLine("请输入主人姓名: ");

    // phoneNumber 使用字符数组保存，因此通过 copyText 写入。
    util::copyText(ownerInfo.phoneNumber, MAX_PHONE_LENGTH, input::readLine("请输入联系电话: "));

    // address 保存联系地址。
    ownerInfo.address = input::readLine("请输入联系地址: ");

    return ownerInfo;
}

// readStayPlan 负责读取寄养计划中的公共业务字段。
// stayDays、needsMedicine、mealCountPerDay 都属于所有宠物共有信息。
StayPlan PetFactory::readStayPlan() {
    StayPlan stayPlan = {};

    // stayDays 表示计划寄养总天数。
    stayPlan.stayDays = input::readInt("请输入寄养天数: ", 1, 365);

    // needsMedicine 表示是否需要额外药物护理。
    stayPlan.needsMedicine = input::readBoolChoice("是否需要药物护理");

    // mealCountPerDay 表示每天喂食次数。
    stayPlan.mealCountPerDay = input::readInt("请输入每日喂食次数: ", 1, 10);

    return stayPlan;
}

// createFromConsole 根据用户输入动态创建不同派生类对象。
// 这个函数返回 Pet*，从而体现“基类指针指向派生类对象”的多态思想。
Pet* PetFactory::createFromConsole(const PetCenter& petCenter) {
    // 第一步：先选择宠物类型。
    std::cout << "\n请选择宠物类型:" << std::endl;
    std::cout << "1. 狗狗" << std::endl;
    std::cout << "2. 猫咪" << std::endl;
    std::cout << "3. 兔兔" << std::endl;

    const int petKindNumber = input::readInt("请输入类型编号: ", 1, 3);
    const int petId = input::readInt("请输入宠物编号: ", 1, 999999);

    // 如果编号重复，会影响查询唯一性，因此直接拒绝创建。
    if (petCenter.containsPetId(petId)) {
        std::cout << "该编号已经存在，请使用新的编号。" << std::endl;
        return 0;
    }

    // 第二步：读取所有宠物共有字段。
    const std::string petName = input::readLine("请输入宠物名字: ");
    const int petAge = input::readInt("请输入宠物年龄: ", 0, 50);
    const OwnerInfo ownerInfo = readOwnerInfo();
    const StayPlan stayPlan = readStayPlan();
    const std::string careNoteText = input::readLine("请输入特殊护理说明(可留空): ");

    // 第三步：根据宠物种类补充专属字段，并创建对应派生类对象。
    if (petKindNumber == static_cast<int>(PetKind::Dog)) {
        // 狗狗特有属性：是否需要额外遛弯、最喜欢的玩具。
        const bool needsOutdoorWalk = input::readBoolChoice("是否需要额外遛弯");
        const std::string favoriteToy = input::readLine("请输入最喜欢的玩具: ");
        return new Dog(petId, petName, petAge, ownerInfo, stayPlan, careNoteText.c_str(), needsOutdoorWalk, favoriteToy);
    }

    if (petKindNumber == static_cast<int>(PetKind::Cat)) {
        // 猫咪特有属性：是否喜欢猫爬架、敏捷等级。
        const bool likesClimbingFrame = input::readBoolChoice("是否喜欢猫爬架");
        const int jumpLevel = input::readInt("请输入敏捷等级(1-10): ", 1, 10);
        return new Cat(petId, petName, petAge, ownerInfo, stayPlan, careNoteText.c_str(), likesClimbingFrame, jumpLevel);
    }

    // 剩余情况默认创建 Rabbit 对象。
    // 兔兔特有属性：每日胡萝卜数量、是否喜欢隧道玩具。
    const int carrotCountPerDay = input::readInt("请输入每日胡萝卜数量: ", 1, 20);
    const bool likesTunnel = input::readBoolChoice("是否喜欢隧道玩具");
    return new Rabbit(petId, petName, petAge, ownerInfo, stayPlan, careNoteText.c_str(), carrotCountPerDay, likesTunnel);
}

// createFromSavedLine 根据文件中的一行文本恢复出一个对象。
// 它是 createFromConsole 的“文件版入口”，用于数据加载场景。
Pet* PetFactory::createFromSavedLine(const std::string& textLine) {
    // 先去掉首尾空白，避免空格干扰判断。
    const std::string trimmedLine = util::trim(textLine);

    // 空行或注释行不参与反序列化。
    if (trimmedLine.empty() || trimmedLine[0] == '#') {
        return 0;
    }

    // 按转义规则切分出每个字段。
    const std::vector<std::string> fields = util::splitEscaped(trimmedLine);

    // 字段数量不足说明这一行格式不完整。
    if (fields.size() < 13) {
        return 0;
    }

    // 先准备公共数据结构。
    OwnerInfo ownerInfo = {};
    StayPlan stayPlan = {};

    // 前几列是所有宠物共同拥有的字段。
    const std::string petKindText = fields[0];
    const int petId = std::atoi(fields[1].c_str());
    const std::string petName = fields[2];
    const int petAge = std::atoi(fields[3].c_str());
    ownerInfo.ownerName = fields[4];
    util::copyText(ownerInfo.phoneNumber, MAX_PHONE_LENGTH, fields[5]);
    ownerInfo.address = fields[6];
    stayPlan.stayDays = std::atoi(fields[7].c_str());
    stayPlan.needsMedicine = std::atoi(fields[8].c_str()) != 0;
    stayPlan.mealCountPerDay = std::atoi(fields[9].c_str());
    const std::string careNoteText = fields[10];

    // 最后根据第一列类型标记恢复对应派生类对象。
    if (petKindText == "Dog") {
        // 第 11 和第 12 列分别对应狗狗专属字段。
        const bool needsOutdoorWalk = std::atoi(fields[11].c_str()) != 0;
        const std::string favoriteToy = fields[12];
        return new Dog(petId, petName, petAge, ownerInfo, stayPlan, careNoteText.c_str(), needsOutdoorWalk, favoriteToy);
    }

    if (petKindText == "Cat") {
        // 猫咪对象恢复时需要读取喜好和敏捷等级。
        const bool likesClimbingFrame = std::atoi(fields[11].c_str()) != 0;
        const int jumpLevel = std::atoi(fields[12].c_str());
        return new Cat(petId, petName, petAge, ownerInfo, stayPlan, careNoteText.c_str(), likesClimbingFrame, jumpLevel);
    }

    if (petKindText == "Rabbit") {
        // 兔兔对象恢复时需要读取胡萝卜数量和隧道偏好。
        const int carrotCountPerDay = std::atoi(fields[11].c_str());
        const bool likesTunnel = std::atoi(fields[12].c_str()) != 0;
        return new Rabbit(petId, petName, petAge, ownerInfo, stayPlan, careNoteText.c_str(), carrotCountPerDay, likesTunnel);
    }

    // 任何未知类型都返回空指针，交给调用方忽略。
    return 0;
}

}  // namespace boarding
