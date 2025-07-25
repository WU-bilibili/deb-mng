//language: C++    name:dpkg_mng (dpkg 命令管理包)    system: Linux only    filename: command.hpp
//description: dpkg_mng 是一个 C++ 程序，用于管理 debian下的apt/dpkg 包。      
//2025-7-24         Wu-CYT
//本代码使用GPL-3.0许可证授权。    什么是GPL3.0?去往https://www.gnu.org/licenses/gpl-3.0.html查看
#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <iostream>
#include <cstdlib>
#include <string>
#include "toml.hpp"
using namespace std;
int run_command(std::string command)
{
    std::string _Command = command;
    //使用 system 函数执行 sudo 命令
    int result = std::system(_Command.c_str()); //将 std::string 转换为 const char*

    if (result == 0)
    {
        std::cout << "命令执行成功。" << std::endl;
    }
    else
    {
        std::cerr << "命令执行失败，返回码: " << result << std::endl;
        return 1;
    }
    return 0;
}

int readfile(string name, char * command = nullptr)
{
    auto data = toml::parse_file("config.toml");
    // 检查指针是否不为空，避免空指针解引用
    if (auto cmd_ptr = data[name].as_string()) {
        // 调用 get() 方法获取 std::string 对象
        const string& cmd_str = cmd_ptr->get();
        if (command != nullptr) {
            // 将字符串复制到字符数组中
            strncpy(command, cmd_str.c_str(), cmd_str.size());
            // 手动添加字符串结束符
            command[cmd_str.size()] = '\0';
        }
    } else {
        // 若键不存在或不是字符串类型，输出错误信息
        std::cerr << "Key " << name << " not found in config.toml or not a string." << std::endl;
        return 1;
    }
    return 0;
}
#endif 