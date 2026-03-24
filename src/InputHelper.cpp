#include "../include/InputHelper.h"

#include <iostream>
#include <limits>

namespace boarding {
namespace input {

// resetInputState 的作用是恢复输入流状态。
// 当用户输入了非法字符后，cin 会进入失败状态。
// 如果不调用 clear 和 ignore，后续读取会持续失败。
void resetInputState() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// readInt 会持续循环，直到读取到一个合法整数。
// promptMessage 是外部传入的提示语，便于多个场景复用。
int readInt(const std::string& promptMessage) {
    // inputNumber 保存本次读取到的整数值。
    int inputNumber = 0;

    while (true) {
        // 先输出提示，再尝试读取。
        std::cout << promptMessage;
        std::cin >> inputNumber;

        if (!std::cin.fail()) {
            // 输入成功后清理缓冲区中的换行残留。
            resetInputState();
            return inputNumber;
        }

        // 输入失败通常意味着用户输入了字母或其他非法字符。
        std::cout << "输入无效，请输入整数。" << std::endl;
        resetInputState();
    }
}

// 这个重载版本在读取整数后继续检查数值范围。
// minValue 和 maxValue 分别表示允许输入的最小值和最大值。
int readInt(const std::string& promptMessage, int minValue, int maxValue) {
    while (true) {
        // 先复用基础版 readInt 读取整数。
        const int inputNumber = readInt(promptMessage);

        if (inputNumber >= minValue && inputNumber <= maxValue) {
            return inputNumber;
        }

        // 数值越界时继续提示用户重新输入。
        std::cout << "请输入范围在 " << minValue << " 到 " << maxValue << " 之间的整数。" << std::endl;
    }
}

// readDouble 用于读取浮点数，并限制最小值。
// 这个函数保留在工具模块中，便于后续扩展更多输入场景。
double readDouble(const std::string& promptMessage, double minValue) {
    // inputNumber 保存读取到的实数。
    double inputNumber = 0.0;

    while (true) {
        std::cout << promptMessage;
        std::cin >> inputNumber;

        if (!std::cin.fail() && inputNumber >= minValue) {
            // 成功后同样清除缓冲区残留。
            resetInputState();
            return inputNumber;
        }

        // 如果输入失败或数值太小，则继续循环。
        std::cout << "请输入不小于 " << minValue << " 的数字。" << std::endl;
        resetInputState();
    }
}

// readBoolChoice 通过 1 和 0 的形式读取布尔值。
// 这样比直接让用户输入 true / false 更适合控制台操作。
bool readBoolChoice(const std::string& promptMessage) {
    while (true) {
        // 这里复用整数读取函数，保证输入校验逻辑统一。
        const int choice = readInt(promptMessage + " (1=是, 0=否): ");

        if (choice == 1) {
            return true;
        }

        if (choice == 0) {
            return false;
        }

        // 只有 1 和 0 才是合法输入。
        std::cout << "请输入 1 或 0。" << std::endl;
    }
}

// readLine 读取一整行字符串。
// 它适合名字、地址、备注等可能带空格的文本内容。
std::string readLine(const std::string& promptMessage) {
    // inputText 保存用户输入的整行文本。
    std::string inputText;
    std::cout << promptMessage;
    std::getline(std::cin, inputText);
    return inputText;
}

}  // namespace input
}  // namespace boarding
