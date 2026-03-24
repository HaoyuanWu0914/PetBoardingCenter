#include <iostream>
#include <string>

#include "../include/FileStorage.h"
#include "../include/InputHelper.h"
#include "../include/Pet.h"
#include "../include/PetCenter.h"
#include "../include/PetFactory.h"
#include "../include/ReportPrinter.h"

// -------------------------------------------------------------
// main.cpp 负责组织程序的整体运行流程。
// 它并不直接处理底层细节，而是：
// 1. 创建核心管理对象。
// 2. 循环显示菜单。
// 3. 接收用户选择。
// 4. 调用对应模块完成业务。
// 这种写法能让主程序保持清晰，符合模块化设计思路。
// -------------------------------------------------------------

// main 是整个宠物寄养中心管理系统的程序入口。
int main() {
    // petCenter 统一管理所有宠物对象及其生命周期。
    boarding::PetCenter petCenter;

    // dataFilePath 保存默认的数据文件路径。
    const std::string dataFilePath = "data/pet_records.txt";

    // shouldExitProgram 控制主菜单循环是否结束。
    bool shouldExitProgram = false;

    // 程序启动后先输出欢迎信息。
    boarding::report::printWelcomeMessage();

    // 主循环不断读取菜单指令并分发到对应功能模块。
    while (!shouldExitProgram) {
        boarding::report::printMenu();

        // menuNumber 是用户输入的原始数字菜单项。
        const int menuNumber = boarding::input::readInt("请输入菜单编号: ", 0, 9);

        // menuOption 把整数转换成枚举，后续 switch 更清晰。
        const boarding::MenuOption menuOption = static_cast<boarding::MenuOption>(menuNumber);

        switch (menuOption) {
        case boarding::MenuOption::AddPet: {
            // 使用工厂模块按输入创建具体的派生类对象。
            boarding::Pet* newPetPointer = boarding::PetFactory::createFromConsole(petCenter);

            if (newPetPointer != 0) {
                // addPet 成功后，petCenter 接管该对象的生命周期。
                if (petCenter.addPet(newPetPointer)) {
                    std::cout << "录入成功，当前共保存 " << petCenter.size() << " 条记录。" << std::endl;
                } else {
                    // 如果加入失败，就由 main 负责释放这块内存。
                    std::cout << "录入失败，可能是编号重复。" << std::endl;
                    delete newPetPointer;
                }
            }
            break;
        }
        case boarding::MenuOption::ListPets:
            // 显示全部宠物档案时，会遍历 petCenter 中保存的所有对象。
            if (petCenter.isEmpty()) {
                std::cout << "当前没有任何宠物记录。" << std::endl;
            } else {
                petCenter.forEachPet(boarding::report::printPetDetails);
            }
            break;
        case boarding::MenuOption::MakeAllPetsSpeak:
            // 这个分支再次体现函数指针和多态调用的组合。
            if (petCenter.isEmpty()) {
                std::cout << "当前没有任何宠物记录。" << std::endl;
            } else {
                petCenter.forEachPet(boarding::report::printPetVoice);
            }
            break;
        case boarding::MenuOption::SearchPet:
            // 查询功能根据用户输入的宠物编号定位单个对象。
            if (petCenter.isEmpty()) {
                std::cout << "当前没有任何宠物记录。" << std::endl;
            } else {
                const int targetPetId = boarding::input::readInt("请输入要查询的宠物编号: ", 1, 999999);
                boarding::Pet* foundPet = petCenter.findPetById(targetPetId);

                if (foundPet != 0) {
                    // 找到对象后输出该宠物的完整资料。
                    boarding::report::printDivider();
                    foundPet->displayProfile(std::cout, true);
                    boarding::report::printDivider();
                } else {
                    std::cout << "未找到对应编号的宠物。" << std::endl;
                }
            }
            break;
        case boarding::MenuOption::ShowStatistics:
            // 统计信息由 report 模块集中输出。
            if (petCenter.isEmpty()) {
                std::cout << "当前没有任何宠物记录。" << std::endl;
            } else {
                boarding::report::printStatistics(petCenter);
            }
            break;
        case boarding::MenuOption::SortPets:
            // 排序前先让用户选择排序字段。
            if (petCenter.isEmpty()) {
                std::cout << "当前没有任何宠物记录。" << std::endl;
            } else {
                // 这里的 4 个选项分别对应 SortField 枚举中的 4 个值。
                std::cout << "1. 按编号排序" << std::endl;
                std::cout << "2. 按名字排序" << std::endl;
                std::cout << "3. 按年龄排序" << std::endl;
                std::cout << "4. 按每日费用排序" << std::endl;

                const int sortNumber = boarding::input::readInt("请选择排序字段: ", 1, 4);

                // 把整数菜单项转换成排序字段枚举。
                petCenter.sortBy(static_cast<boarding::SortField>(sortNumber));
                std::cout << "排序完成。" << std::endl;
            }
            break;
        case boarding::MenuOption::SaveToFile:
            // 保存功能把当前所有数据写入默认文本文件。
            if (boarding::FileStorage::saveCenter(petCenter, dataFilePath)) {
                petCenter.recordOperation("已将数据保存到文件。");
                std::cout << "保存成功，文件路径: " << dataFilePath << std::endl;
            } else {
                std::cout << "保存失败，请检查文件路径或权限。" << std::endl;
            }
            break;
        case boarding::MenuOption::LoadFromFile: {
            // loadedCount 用于记录本次成功加载了多少条数据。
            int loadedCount = 0;

            // 成功时会整体替换当前内存中的数据。
            if (boarding::FileStorage::loadCenter(petCenter, dataFilePath, loadedCount)) {
                std::cout << "加载成功，本次读取到 " << loadedCount << " 条记录。" << std::endl;
            } else {
                std::cout << "加载失败，可能是文件不存在。" << std::endl;
            }
            break;
        }
        case boarding::MenuOption::ShowHistory:
            // 这个菜单项用于查看最近操作历史。
            boarding::report::printHistory(petCenter);
            break;
        case boarding::MenuOption::Exit:
            // 把控制变量设为 true 后，下一轮循环判断时程序会退出。
            shouldExitProgram = true;
            std::cout << "程序即将退出，感谢使用。" << std::endl;
            break;
        }
    }

    // 返回 0 表示程序正常结束。
    return 0;
}

// 如果 IDE 只单独编译 src/main.cpp，这组包含会把其他实现文件一起编进来。
// 正常的 CMake 或多文件构建会定义 BOARDING_SEPARATE_BUILD，从而避免重复定义。
#ifndef BOARDING_SEPARATE_BUILD
#include "DynamicText.cpp"
#include "Utility.cpp"
#include "Pet.cpp"
#include "Dog.cpp"
#include "Cat.cpp"
#include "Rabbit.cpp"
#include "InputHelper.cpp"
#include "PetCenter.cpp"
#include "PetFactory.cpp"
#include "FileStorage.cpp"
#include "ReportPrinter.cpp"
#endif
