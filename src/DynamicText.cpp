#include "../include/DynamicText.h"

#include <cstring>

namespace boarding {

// copyFrom 统一处理字符串复制，避免构造和赋值里重复写同一套逻辑。
void DynamicText::copyFrom(const char* sourceText) {
    // safeSource 保证即使传入空指针，也能安全退化成空字符串。
    const char* safeSource = sourceText == 0 ? "" : sourceText;
    // 先计算长度，再按“字符数 + 结束符”申请堆内存。
    textLength = std::strlen(safeSource);
    textBuffer = new char[textLength + 1];
    // strcpy 负责把文本内容完整复制到新缓冲区中。
    std::strcpy(textBuffer, safeSource);
}

DynamicText::DynamicText() : textBuffer(0), textLength(0) {
    // 默认对象保存空文本，便于其他类把它当作普通成员直接使用。
    copyFrom("");
}

DynamicText::DynamicText(const char* sourceText) : textBuffer(0), textLength(0) {
    // 带参构造直接把外部文本深拷贝进来。
    copyFrom(sourceText);
}

DynamicText::DynamicText(const DynamicText& other) : textBuffer(0), textLength(0) {
    // 拷贝构造必须重新申请内存，而不是共享同一个字符数组。
    copyFrom(other.textBuffer);
}

DynamicText::~DynamicText() {
    // 对应 new[] 的资源必须使用 delete[] 释放。
    delete[] textBuffer;
    textBuffer = 0;
    textLength = 0;
}

DynamicText& DynamicText::operator=(const DynamicText& other) {
    if (this != &other) {
        // 赋值前先释放旧内存，避免发生内存泄漏。
        delete[] textBuffer;
        textBuffer = 0;
        textLength = 0;
        // 然后再按深拷贝方式复制右侧对象。
        copyFrom(other.textBuffer);
    }

    return *this;
}

void DynamicText::setText(const char* sourceText) {
    // 修改内容的流程与赋值类似：先释放，再重新复制。
    delete[] textBuffer;
    textBuffer = 0;
    textLength = 0;
    copyFrom(sourceText);
}

const char* DynamicText::c_str() const {
    // 返回底层字符指针，便于和输出流或 C 风格 API 配合。
    return textBuffer;
}

std::size_t DynamicText::length() const {
    // 直接返回缓存的长度值，避免重复调用 strlen。
    return textLength;
}

bool DynamicText::empty() const {
    // 长度为 0 时表示当前对象保存的是空文本。
    return textLength == 0;
}

}  // namespace boarding
