#include "phone_validator.hpp"
#include <regex>
#include <string>
#include <iostream>
#include <unordered_map>

namespace
{
    std::unordered_map<std::string, std::string> countryRules = {
        // 中国：+86 或自动补全 +86
        {"86", "^861[3-9]\\d{9}$"},
        // 美国：+1
        {"1", "^1\\d{10}$"}};

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

    // length & format
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

// main function
bool validatePhone(const std::string &phone)
{
    if (valierror(phone))
        return false;
    return isValidPhoneNumber(phone);
}
