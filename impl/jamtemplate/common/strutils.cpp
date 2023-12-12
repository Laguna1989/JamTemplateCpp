#include "strutils.hpp"

std::string strutil::to_lower(std::string_view const str)
{
    std::string result { str };
    std::transform(
        result.begin(), result.end(), result.begin(), [](unsigned char c) -> unsigned char {
            return static_cast<unsigned char>(std::tolower(c));
        });

    return result;
}

std::string strutil::to_upper(std::string_view const str)
{
    std::string result { str };
    std::transform(
        result.begin(), result.end(), result.begin(), [](unsigned char c) -> unsigned char {
            return static_cast<unsigned char>(std::toupper(c));
        });

    return result;
}

bool strutil::contains(std::string_view const str, std::string_view const substring) noexcept
{
    return str.find(substring) != std::string::npos;
}

bool strutil::contains(std::string_view const str, char const character)
{
    return contains(str, std::string(1, character));
}

bool strutil::compare_ignore_case(std::string_view const str1, std::string_view const str2)
{
    return to_lower(str1) == to_lower(str2);
}

void strutil::trim_left(std::string& str)
{
    str.erase(str.begin(),
        std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); }));
}

void strutil::trim_right(std::string& str)
{
    str.erase(
        std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(),
        str.end());
}

void strutil::trim(std::string& str)
{
    trim_left(str);
    trim_right(str);
}

std::string strutil::trim_left_copy(std::string str)
{
    trim_left(str);
    return str;
}

std::string strutil::trim_right_copy(std::string str)
{
    trim_right(str);
    return str;
}

std::string strutil::trim_copy(std::string str)
{
    trim(str);
    return str;
}

bool strutil::replace_first(
    std::string& str, std::string_view const target, std::string_view const replecament)
{
    auto const start_pos = str.find(target);
    if (start_pos == std::string::npos) {
        return false;
    }

    str.replace(start_pos, target.length(), replecament);
    return true;
}

bool strutil::replace_last(
    std::string& str, std::string_view const target, std::string_view const replecament)
{
    auto const start_pos = str.rfind(target);
    if (start_pos == std::string::npos) {
        return false;
    }

    str.replace(start_pos, target.length(), replecament);
    return true;
}

bool strutil::replace_all(
    std::string& str, std::string_view const target, std::string_view const replecament)
{
    if (target.empty()) {
        return false;
    }

    std::size_t start_pos = 0u;
    bool const found_substring = str.find(target, start_pos) != std::string::npos;

    while ((start_pos = str.find(target, start_pos)) != std::string::npos) {
        str.replace(start_pos, target.length(), replecament);
        start_pos += replecament.length();
    }

    return found_substring;
}

std::vector<std::string> strutil::split(std::string_view const str, char const delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss { std::string { str }, std::ios_base::in };

    std::string token {};
    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);
    }

    // Match semantics of split(str,str)
    if (str.size() == 0 || str.ends_with(delim)) {
        tokens.push_back("");
    }

    return tokens;
}

std::vector<std::string> strutil::split(std::string_view const str, std::string_view const delim)
{
    std::size_t pos_start { 0u };
    std::size_t pos_end { 0u };
    std::size_t const delim_len { delim.length() };
    std::string token {};
    std::vector<std::string> tokens;

    while ((pos_end = str.find(delim, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        tokens.push_back(token);
    }

    tokens.push_back(std::string { str.substr(pos_start) });
    return tokens;
}

std::vector<std::string> strutil::split_any(
    std::string_view const str, std::string_view const delims)
{
    std::string token;
    std::vector<std::string> tokens;

    size_t pos_start = 0;
    for (size_t pos_end = 0; pos_end < str.length(); ++pos_end) {
        if (contains(delims, str[pos_end])) {
            token = str.substr(pos_start, pos_end - pos_start);
            tokens.push_back(token);
            pos_start = pos_end + 1;
        }
    }

    tokens.push_back(std::string { str.substr(pos_start) });
    return tokens;
}

std::string strutil::repeat(std::string_view const str, unsigned n)
{
    std::string result {};

    for (unsigned i = 0; i < n; ++i) {
        result += str;
    }

    return result;
}

std::string strutil::repeat(char c, unsigned n) { return std::string(n, c); }

bool strutil::matches(std::string const& str, std::regex const& regex)
{
    return std::regex_match(str, regex);
}
