#ifndef PET_H
#define PET_H

#include <iosfwd>
#include <string>

#include "CommonTypes.h"
#include "DynamicText.h"

namespace boarding {

// 抽象基类统一所有宠物的公共接口，并为多态提供入口。
class Pet {
protected:
    // petKind 记录宠物属于哪一种派生类型。
    PetKind petKind;
    // petId 是系统内唯一编号，用来查询和防止重复录入。
    int petId;
    // petName 保存宠物名字，用于界面展示和搜索结果提示。
    std::string petName;
    // petAge 表示宠物年龄，统计平均年龄时会用到。
    int petAge;
    // ownerInfo 封装主人姓名、电话、地址等登记信息。
    OwnerInfo ownerInfo;
    // stayPlan 描述这次寄养计划的时长和护理要求。
    StayPlan stayPlan;
    // careNote 保存额外护理说明，演示动态文本成员对象。
    DynamicText careNote;

    // buildCommonData 把各派生类共有的数据拼成一段可保存文本。
    std::string buildCommonData() const;

public:
    // totalPetCount 是静态成员，用来统计当前活跃 Pet 对象数量。
    static int totalPetCount;

    // 构造函数负责初始化所有公共数据成员。
    Pet(PetKind petKindValue,
        int petIdValue,
        const std::string& petNameValue,
        int petAgeValue,
        const OwnerInfo& ownerInfoValue,
        const StayPlan& stayPlanValue,
        const char* careNoteText);

    // 拷贝构造函数用于复制宠物对象时维持一致的数据状态。
    Pet(const Pet& other);

    // 虚析构函数保证通过基类指针删除对象时能正确析构派生类。
    virtual ~Pet();

    // 赋值运算符实现公共成员的逐项复制。
    Pet& operator=(const Pet& other);

    // 一组 getter 函数提供只读访问接口，保护封装性。
    PetKind getPetKind() const;
    int getPetId() const;
    const std::string& getPetName() const;
    int getPetAge() const;
    const OwnerInfo& getOwnerInfo() const;
    const StayPlan& getStayPlan() const;
    const DynamicText& getCareNote() const;

    // setter 只暴露少量允许修改的业务字段。
    void setStayDays(int newStayDays);
    void setCareNote(const char* newCareNote);

    // displayProfile 带有默认参数，允许选择显示简略信息或详细信息。
    virtual void displayProfile(std::ostream& output, bool detailed = true) const;

    // 纯虚函数要求每个派生类都提供自己的叫声实现。
    virtual void makeSound() const = 0;

    // 纯虚函数要求每个派生类自行决定每日费用计算规则。
    virtual double calculateDailyFee() const = 0;

    // clone 为深拷贝容器提供多态复制接口。
    virtual Pet* clone() const = 0;

    // serializeData 负责把对象转换成文件保存时的一行文本。
    virtual std::string serializeData() const = 0;

    // 友元输出运算符使 cout << pet 的写法更自然。
    friend std::ostream& operator<<(std::ostream& output, const Pet& pet);
};

}  // namespace boarding

#endif
