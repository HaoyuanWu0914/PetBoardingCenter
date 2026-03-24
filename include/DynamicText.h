#ifndef DYNAMIC_TEXT_H
#define DYNAMIC_TEXT_H

#include <cstddef>

namespace boarding {

// DynamicText 专门演示动态内存、深拷贝和析构释放。
class DynamicText {
private:
    // textBuffer 指向动态分配的字符数组，保存真正的文本内容。
    char* textBuffer;
    // textLength 记录当前文本长度，避免每次都重复计算。
    std::size_t textLength;

    // copyFrom 负责按照深拷贝方式复制外部字符串内容。
    void copyFrom(const char* sourceText);

public:
    // 默认构造函数创建一个空字符串对象。
    DynamicText();
    // 带参构造函数允许在创建对象时直接写入文本。
    explicit DynamicText(const char* sourceText);
    // 拷贝构造函数用于演示对象复制时的深拷贝行为。
    DynamicText(const DynamicText& other);
    // 析构函数负责释放 textBuffer 指向的堆内存。
    ~DynamicText();

    // 赋值运算符同样需要遵守深拷贝语义。
    DynamicText& operator=(const DynamicText& other);

    // setText 用于替换当前对象保存的文本内容。
    void setText(const char* sourceText);
    // c_str 返回底层字符数组，方便与 C 风格接口交互。
    const char* c_str() const;
    // length 返回文本长度。
    std::size_t length() const;
    // empty 用来快速判断当前对象是否为空字符串。
    bool empty() const;
};

}  // namespace boarding

#endif
