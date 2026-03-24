#include "../include/Utility.h"

#include <cstring>
#include <sstream>

namespace boarding {
namespace util {

// copyText 把 std::string 安全复制到固定长度字符数组中。
void copyText(char* destination, std::size_t destinationSize, const std::string& sourceText) {
    // 目标为空或容量非法时直接返回，避免越界访问。
    if (destination == 0 || destinationSize == 0) {
        return;
    }

    // strncpy 最多复制指定长度，最后一位手动补 '\0' 更稳妥。
    std::strncpy(destination, sourceText.c_str(), destinationSize - 1);
    destination[destinationSize - 1] = '\0';
}

std::string yesNo(bool condition) {
    // 统一把 bool 转为中文文本，避免各处重复写三目表达式。
    return condition ? "是" : "否";
}

std::string trim(const std::string& sourceText) {
    // begin 和 end 分别向中间收缩，找到真正有效的文本区间。
    std::size_t begin = 0;
    std::size_t end = sourceText.length();

    // 跳过左侧空格、制表符和回车。
    while (begin < end && (sourceText[begin] == ' ' || sourceText[begin] == '\t' || sourceText[begin] == '\r')) {
        ++begin;
    }

    // 跳过右侧空格、制表符和回车。
    while (end > begin && (sourceText[end - 1] == ' ' || sourceText[end - 1] == '\t' || sourceText[end - 1] == '\r')) {
        --end;
    }

    // substr 截取中间真正需要保留的部分。
    return sourceText.substr(begin, end - begin);
}

std::string escapeField(const std::string& sourceText) {
    // 保存文件时，分隔符和反斜杠都需要转义，避免破坏数据格式。
    std::ostringstream escapedText;

    for (std::size_t index = 0; index < sourceText.length(); ++index) {
        const char currentCharacter = sourceText[index];

        // 先对特殊字符补一个转义前缀。
        if (currentCharacter == '\\' || currentCharacter == '|') {
            escapedText << '\\';
        }

        // 换行单独编码为两个字符，便于单行保存。
        if (currentCharacter == '\n') {
            escapedText << "\\n";
        } else {
            escapedText << currentCharacter;
        }
    }

    return escapedText.str();
}

std::string unescapeField(const std::string& sourceText) {
    // 读取文件时，需要把转义后的文本恢复成原始内容。
    std::ostringstream plainText;
    bool isEscaping = false;

    for (std::size_t index = 0; index < sourceText.length(); ++index) {
        const char currentCharacter = sourceText[index];

        if (isEscaping) {
            // 如果前一个字符是反斜杠，就按照转义规则解释当前字符。
            if (currentCharacter == 'n') {
                plainText << '\n';
            } else {
                plainText << currentCharacter;
            }

            isEscaping = false;
        } else if (currentCharacter == '\\') {
            isEscaping = true;
        } else {
            plainText << currentCharacter;
        }
    }

    return plainText.str();
}

std::vector<std::string> splitEscaped(const std::string& textLine, char separator) {
    // 这个函数的任务是在“识别转义”的前提下做安全分割。
    std::vector<std::string> fields;
    std::ostringstream currentField;
    bool isEscaping = false;

    for (std::size_t index = 0; index < textLine.length(); ++index) {
        const char currentCharacter = textLine[index];

        if (isEscaping) {
            // 被转义的字符先原样写回临时字段，稍后统一反转义。
            currentField << '\\' << currentCharacter;
            isEscaping = false;
            continue;
        }

        if (currentCharacter == '\\') {
            // 记录“下一个字符被转义”这一状态。
            isEscaping = true;
            continue;
        }

        if (currentCharacter == separator) {
            // 遇到真正的分隔符时，当前字段结束并压入结果数组。
            fields.push_back(unescapeField(currentField.str()));
            currentField.str("");
            currentField.clear();
        } else {
            currentField << currentCharacter;
        }
    }

    if (isEscaping) {
        // 如果最后一个字符恰好是反斜杠，也保留回字段中。
        currentField << '\\';
    }

    // 别忘记把最后一个字段也加入结果。
    fields.push_back(unescapeField(currentField.str()));
    return fields;
}

}  // namespace util
}  // namespace boarding
