#include "id_validator.hpp"

using std::cout;

namespace
{
    /**
     * @brief 身份证各余数所对应的校验码
     *
     */
    static const std::map<int, char> CHECK_CODE = {
        {0, '1'}, {1, '0'}, {2, 'X'}, {3, '9'}, {4, '8'}, {5, '7'}, {6, '6'}, {7, '5'}, {8, '4'}, {9, '3'}, {10, '2'}};

    /**
     * @brief 权重因子
     *
     */
    static const int WEIGHT[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};

    /**
     * @brief 长度验证
     *
     * @param id 身份证字符串
     * @return true 合法长度
     * @return false 非法长度
     */
    inline bool valilength(const std::string &id)
    {
        if (id.length() != 18)
        {
            cout << "错误的身份证号码, 错误原因: 过长或过短的身份证号码\n";
            return false;
        }
        return true;
    }

    /**
     * @brief 判断是否为一个非数字字符
     *
     * @param now 需判断的字符
     * @return true 字符不是一个数字
     * @return false 字符是一个数字
     */
    inline bool IsNotNumber(const char now)
    {
        return !isdigit(now);
    }

    /**
     * @brief 对身份证的各字符进行验证是否合法
     *
     * @param id 身份证字符串
     * @return true 身份证合法
     * @return false 身份证不合法
     */
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

    /**
     * @brief 对身份证的行政区划号码合法性进行验证 (Not finished)
     *
     * @param code 身份证行政区划号码
     * @return true 合法
     * @return false 非法
     */
    inline bool validateRegion(const std::string &code)
    {
        return true;
    }

    /**
     * @brief 对身份证的日期合法性进行验证
     *
     * @param dateStr 身份证生日
     * @return true 合法
     * @return false 非法
     */
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

    /**
     * @brief 对身份证的校验码进行计算并检验合法性
     *
     * @param id 身份证字符串
     * @return true 合法
     * @return false 非法
     */
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

/**
 * @brief 为主验证函数（即对外暴露接口）
 *
 * @param _id 待检验身份证
 * @return true 合法身份证
 * @return false 不合法身份证
 */
bool validateId(std::string &_id)
{
    if (_id == "quit")
        return false;

    const std::string id = _id;

    // 私域验证
    return valilength(id) &&                     // 长度
           valichar(id) &&                       // 字符
           validateRegion(id.substr(0, 6)) &&    // 地区
           validateBirthDate(id.substr(6, 8)) && // 日期
           calculateCheckCode(id);               // 校验码
}
