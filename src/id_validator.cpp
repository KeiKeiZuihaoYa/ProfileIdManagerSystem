#include "id_validator.hpp"
#include <string>
#include <map>
#include <ctime>
#include <cctype>
#include <iostream>
using std::cout;

// 双层命名空间， 私密具体实现逻辑
namespace
{
    // 校验码表
    static const std::map<int, char> CHECK_CODE = {
        {0, '1'}, {1, '0'}, {2, 'X'}, {3, '9'}, {4, '8'}, {5, '7'}, {6, '6'}, {7, '5'}, {8, '4'}, {9, '3'}, {10, '2'}};

    // 权重因子
    static const int WEIGHT[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};

    // 长度验证
    inline bool valilength(const std::string &id)
    {
        if (id.length() == 0 || id.length() > 18)
        {
            cout << "错误的身份证号码, 错误原因: 过长或过短的身份证号码\n";
            return false;
        }
        return true;
    }

    inline bool IsNotNumber(const char now)
    {
        return !isdigit(now);
    }

    // 字符验证
    inline bool valichar(const std::string &id)
    {
        bool flag = true;

        for (int i = 0; i < 17; i++)
            if (IsNotNumber(id[i]))
            {
                cout << "错误的身份证号码, 错误原因: 前17位中出现非数字字符\n";
                flag = false;
            }

        if (IsNotNumber(id[17]) && toupper(id[17]) != 'X')
        {
            cout << "错误的身份证号码, 错误原因: 校验码为非校验码字符\n";
            flag = false;
        }

        return flag;
    }

    // 行政区划验证
    inline bool validateRegion(const std::string &code)
    {
        return true;
    }

    // 日期验证
    inline bool validateBirthDate(const std::string &dateStr)
    {
        bool flag = true;

        const int year = stoi(dateStr.substr(0, 4));
        const int month = stoi(dateStr.substr(4, 2));
        const int day = stoi(dateStr.substr(6, 2));

        if (year < 1900 || year > 2025)
        {
            cout << "错误的身份证号码, 错误原因: 身份证年份错误\n";
            flag = false;
        }
        if (month < 1 || month > 12)
        {
            cout << "错误的身份证号码, 错误原因: 身份证月份错误\n";
            flag = false;
        }

        int maxDay = 31;
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            maxDay = 30;
        }
        else if (month == 2)
        {
            maxDay = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
        }

        if (day < 1 || day > maxDay)
        {
            cout << "错误的身份证号码, 错误原因: 身份证日份错误\n";
            flag = false;
        }

        return flag;
    }

    // 计算校验码
    inline bool calculateCheckCode(const std::string &id)
    {
        int sum = 0;
        for (int i = 0; i < 17; ++i)
        {
            sum += (id[i] - '0') * WEIGHT[i];
        }

        if (CHECK_CODE.at(sum % 11) != id[17])
        {
            cout << "错误的身份证号码, 错误原因: 身份证校验码错误\n";
            return false;
        }
        return true;
    }
}

// 为主验证函数（即对外暴露接口）
bool validateId(std::string &_id)
{
    if (_id.length() >= 18 && _id[17] == 'x')
        _id[17] = 'X';

    const std::string id = _id;

    // 私域验证
    return valilength(id) &&                     // 长度
           valichar(id) &&                       // 字符
           validateRegion(id.substr(0, 6)) &&    // 地区
           validateBirthDate(id.substr(6, 8)) && // 日期
           calculateCheckCode(id);               // 校验码
}
