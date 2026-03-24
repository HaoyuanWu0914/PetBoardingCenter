#ifndef REPORT_PRINTER_H
#define REPORT_PRINTER_H

#include "CommonTypes.h"

namespace boarding {

class Pet;
class PetCenter;

namespace report {

// ReportPrinter 统一负责界面输出，避免打印语句散落在各处。

// printDivider 的重载版本可以打印默认分隔线或自定义分隔线。
void printDivider();
void printDivider(char symbol, int count = 60);

// printWelcomeMessage 输出程序欢迎信息。
void printWelcomeMessage();

// printMenu 输出主菜单。
void printMenu();

// printPetDetails 和 printPetVoice 用于配合函数指针遍历所有宠物。
void printPetDetails(const Pet& pet);
void printPetVoice(const Pet& pet);

// printStatistics 输出统计分析结果。
void printStatistics(const PetCenter& petCenter);

// printHistory 输出最近操作历史。
void printHistory(const PetCenter& petCenter);

}  // namespace report
}  // namespace boarding

#endif
