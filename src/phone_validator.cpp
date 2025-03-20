#include "phone_validator.hpp"

namespace
{
    /**
     * @brief 存储各个国家手机号码的正则表达式
     *
     */
    std::unordered_map<std::string, std::string> countryRules = {
        // 中国：+86 或自动补全 +86
        {"86", "^861[3-9]\\d{9}$"},
        // 美国：+1
        {"1", "^1\\d{10}$"}};

    /**
     * @brief 对手机号码的各个字符进行合法性检验
     *
     * @param phone 手机号码
     * @return true 合法
     * @return false 非法
     */
    inline bool valierror(const std::string &phone)
    {
        for (const auto &i : phone)
            if (!isdigit(i) && i != '+')
            {
                std::cout << "存在非法字符!\n";
                return true;
            }
        return false;
    }

    /**
     * @brief 清洗手机号码之间的空格，并对中国大陆手机号码加上 86 国家码
     *
     * @param phone 手机号码
     * @return const std::string 清洗并处理完之后的完整手机号码
     */
    inline const std::string cleanPhoneNumber(const std::string &phone)
    {
        std::string cleaned;
        for (const auto &i : phone)
            if (isdigit(i))
                cleaned += i;
        if (cleaned[0] == '1' && cleaned.length() == 11)
            cleaned = "86" + cleaned;
        return cleaned;
    }

    /**
     * @brief 检验手机号码合法性的主逻辑函数 进行私密处理
     *
     * @param phone 待检验手机号码
     * @return true 合法
     * @return false 非法
     */
    inline bool isValidPhoneNumber(const std::string &phone)
    {
        const std::string cleanedPhone = cleanPhoneNumber(phone);

        std::string nationCode;
        if (cleanedPhone.substr(0, 2) == "86" && cleanedPhone.length() == 13)
            nationCode = "86";
        else if (cleanedPhone.substr(0, 1) == "1" && cleanedPhone.length() == 11)
            nationCode = "1";

        auto tmp = countryRules.find(nationCode);
        if (tmp == countryRules.end())
        {
            std::cout << "错误的手机号码!\n";
            return false;
        }

        std::regex r(tmp->second);
        return std::regex_match(cleanedPhone, r);
    }
}

/**
 * @brief 对外的手机号码合法性检验接口
 *
 * @param phone 待检验手机号码
 * @return true 为合法手机号
 * @return false 为不合法手机号
 */
bool validatePhone(const std::string &phone)
{
    if (valierror(phone))
        return false;
    return isValidPhoneNumber(phone);
}
