#ifndef UTILITY_H
#define UTILITY_H

#include <cstddef>
#include <string>
#include <vector>

namespace boarding {
namespace util {

// Utility.h 集中放置项目中的通用辅助函数和模板函数。
// 它们大多不属于某一个具体业务类，但会被多个模块复用。

// 内联函数适合这种短小且频繁调用的逻辑。
inline double calculateProjectedIncome(double dailyFee, int stayDays) {
    return dailyFee * stayDays;
}

// 函数模板让同一段逻辑可以作用于多种数据类型。
template <typename T>
T largerValue(const T& firstValue, const T& secondValue) {
    return firstValue > secondValue ? firstValue : secondValue;
}

template <typename T>
void swapValues(T& firstValue, T& secondValue) {
    T temporaryValue = firstValue;
    firstValue = secondValue;
    secondValue = temporaryValue;
}

// copyText 把 string 内容安全复制到字符数组中。
void copyText(char* destination, std::size_t destinationSize, const std::string& sourceText);

// yesNo 把布尔值转成更适合界面显示的“是/否”文本。
std::string yesNo(bool condition);

// trim 去掉字符串首尾空白字符，便于处理用户输入和文件数据。
std::string trim(const std::string& sourceText);

// escapeField 和 unescapeField 用于文件保存时的转义处理。
std::string escapeField(const std::string& sourceText);
std::string unescapeField(const std::string& sourceText);

// splitEscaped 会在保留转义规则的前提下按分隔符切分文本行。
std::vector<std::string> splitEscaped(const std::string& textLine, char separator = '|');

}  // namespace util
}  // namespace boarding

#endif
