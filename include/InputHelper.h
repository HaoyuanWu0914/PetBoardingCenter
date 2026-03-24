#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <string>

namespace boarding {
namespace input {

// InputHelper 模块负责处理控制台输入校验。
// 把输入逻辑集中起来后，主流程就会更清晰。

// resetInputState 用于清除 cin 的错误状态和缓冲区残留内容。
void resetInputState();

// readInt 的重载版本分别用于“只读整数”和“读取区间内整数”。
int readInt(const std::string& promptMessage);
int readInt(const std::string& promptMessage, int minValue, int maxValue);

// readDouble 读取不小于给定下限的实数。
double readDouble(const std::string& promptMessage, double minValue = 0.0);

// readBoolChoice 使用 1 和 0 读取布尔选择，更适合控制台交互。
bool readBoolChoice(const std::string& promptMessage);

// readLine 用于读取整行文本，适合名字和地址等可含空格内容。
std::string readLine(const std::string& promptMessage);

}  // namespace input
}  // namespace boarding

#endif
