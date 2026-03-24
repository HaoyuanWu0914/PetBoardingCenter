#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include <string>

namespace boarding {

class PetCenter;

// FileStorage 封装文件保存和文件加载功能。
// 业务层只需要调用静态函数，不需要关心底层文件细节。
class FileStorage {
public:
    // saveCenter 把当前寄养中心的所有记录保存到指定文件。
    static bool saveCenter(const PetCenter& petCenter, const std::string& filePath);
    // loadCenter 从指定文件加载全部记录，并统计本次加载成功条数。
    static bool loadCenter(PetCenter& petCenter, const std::string& filePath, int& loadedCount);
};

}  // namespace boarding

#endif
