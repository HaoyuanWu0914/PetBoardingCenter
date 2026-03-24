#include "../include/ReportPrinter.h"

#include <iostream>
#include <string>

#include "../include/LimitedList.h"
#include "../include/Pet.h"
#include "../include/PetCenter.h"

namespace boarding {
namespace report {

// --------------------------------------------------------------
// ReportPrinter.cpp 专门负责“界面输出”。
// 这样 main 函数不用堆满 cout 语句，
// 输出格式也能集中维护，更利于模块化展示。
// --------------------------------------------------------------

// 默认版本的 printDivider 使用 '=' 打印 60 个字符。
void printDivider() {
    printDivider('=', 60);
}

// 自定义版本允许外部指定分隔线字符和长度。
void printDivider(char symbol, int count) {
    // symbol 是打印用的字符，count 是重复次数。
    for (int index = 0; index < count; ++index) {
        std::cout << symbol;
    }

    std::cout << std::endl;
}

// printWelcomeMessage 在程序启动时展示项目主题和功能说明。
void printWelcomeMessage() {
    printDivider();
    std::cout << "欢迎使用宠物寄养中心课程项目" << std::endl;
    std::cout << "本项目支持你自己录入、查询、统计、排序以及文件保存/加载。" << std::endl;
    std::cout << "同时它还演示了指针、函数指针、类、继承、多态、动态内存和模板等知识点。" << std::endl;
    printDivider();
}

// printMenu 统一输出主菜单项，方便 main 函数保持简洁。
void printMenu() {
    std::cout << "\n请选择功能:" << std::endl;
    std::cout << "1. 录入新宠物" << std::endl;
    std::cout << "2. 显示全部宠物档案" << std::endl;
    std::cout << "3. 让全部宠物发声" << std::endl;
    std::cout << "4. 按编号查询宠物" << std::endl;
    std::cout << "5. 显示统计信息" << std::endl;
    std::cout << "6. 按字段排序" << std::endl;
    std::cout << "7. 保存到文件" << std::endl;
    std::cout << "8. 从文件加载" << std::endl;
    std::cout << "9. 查看最近操作历史" << std::endl;
    std::cout << "0. 退出程序" << std::endl;
}

// printPetDetails 会作为回调函数输出单只宠物的档案。
void printPetDetails(const Pet& pet) {
    // 先打印分隔线，再输出宠物对象。
    printDivider('-');
    std::cout << pet;
}

// printPetVoice 会作为回调函数触发宠物发声。
void printPetVoice(const Pet& pet) {
    // 具体发什么声音由派生类决定，这里只调用统一接口。
    pet.makeSound();
}

// printStatistics 负责展示数量、费用和平均值等统计结果。
void printStatistics(const PetCenter& petCenter) {
    // 统计结果集中展示，方便用户一眼看到整体情况。
    printDivider();
    std::cout << "当前宠物数量: " << petCenter.size() << std::endl;
    std::cout << "狗狗数量: " << petCenter.countByKind(PetKind::Dog) << std::endl;
    std::cout << "猫咪数量: " << petCenter.countByKind(PetKind::Cat) << std::endl;
    std::cout << "兔兔数量: " << petCenter.countByKind(PetKind::Rabbit) << std::endl;
    std::cout << "总对象数量(静态成员统计): " << Pet::totalPetCount << std::endl;
    std::cout << "平均年龄: " << petCenter.calculateAverageAge() << std::endl;
    std::cout << "单日总费用: " << petCenter.calculateTotalDailyFee() << " 元" << std::endl;
    std::cout << "预计总收入: " << petCenter.calculateTotalProjectedIncome() << " 元" << std::endl;
    std::cout << "最长寄养天数: " << petCenter.longestStayDays() << std::endl;
    printDivider();
}

// printHistory 用于显示最近记录的操作历史。
void printHistory(const PetCenter& petCenter) {
    printDivider();

    // operationHistory 引用最近保留的操作日志容器。
    const LimitedList<std::string, 20>& operationHistory = petCenter.getOperationHistory();

    // 如果没有历史记录，就直接提示后返回。
    if (operationHistory.size() == 0) {
        std::cout << "当前没有历史记录。" << std::endl;
        printDivider();
        return;
    }

    std::cout << "最近操作历史:" << std::endl;

    // index + 1 让显示序号从 1 开始，更符合阅读习惯。
    for (int index = 0; index < operationHistory.size(); ++index) {
        std::cout << index + 1 << ". " << operationHistory[index] << std::endl;
    }

    printDivider();
}

}  // namespace report
}  // namespace boarding
