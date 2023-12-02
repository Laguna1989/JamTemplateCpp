/**
******************************************************************************
*
*  strutil v1.0.1 - header-only string utility library documentation
*  https://github.com/Shot511/strutil
*
*  @copyright  Copyright (C) 2020 Tomasz Galaj (Shot511)
*  @file       strutil.h
*  @brief      Library public interface header
*
*  @subsection Thank you for your contributions:
*              - SomeRandomDev49
*              - flying-tiger
*
*
******************************************************************************
*/

#ifndef JAMTEMPLATE_STRUTILS_HPP
#define JAMTEMPLATE_STRUTILS_HPP

#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

//! The strutil namespace
namespace strutil {
/**
 * @brief Converts any datatype into std::string.
 *        Datatype must support << operator.
 * @tparam T
 * @param value - will be converted into std::string.
 * @return Converted value as std::string.
 */
template <typename T>
static inline std::string to_string(T value)
{
    std::stringstream ss;
    ss << value;

    return ss.str();
}

/**
 * @brief Converts std::string into any datatype.
 *        Datatype must support << operator.
 * @tparam T
 * @param str - std::string that will be converted into datatype T.
 * @return Variable of datatype T.
 */
template <typename T>
static inline T parse_string(std::string const& str)
{
    T result;
    std::istringstream(str) >> result;

    return result;
}

/**
 * @brief Converts std::string to lower case.
 * @param str - std::string that needs to be converted.
 * @return Lower case input std::string.
 */
std::string to_lower(std::string_view str);

/**
 * @brief Converts std::string to upper case.
 * @param str - std::string that needs to be converted.
 * @return Upper case input std::string.
 */
std::string to_upper(std::string_view str);

/**
 * @brief Checks if input std::string str contains specified substring.
 * @param str - std::string to be checked.
 * @param substring - searched substring.
 * @return True if substring was found in str, false otherwise.
 */
bool contains(std::string_view str, std::string_view substring) noexcept;

/**
 * @brief Checks if input std::string str contains specified character.
 * @param str - std::string to be checked.
 * @param character - searched character.
 * @return True if character was found in str, false otherwise.
 */
bool contains(std::string_view str, char character);

/**
 * @brief Compares two std::strings ignoring their case (lower/upper).
 * @param str1 - std::string to compare
 * @param str2 - std::string to compare
 * @return True if str1 and str2 are equal, false otherwise.
 */
bool compare_ignore_case(std::string_view str1, std::string_view str2);

/**
 * @brief Trims (in-place) white spaces from the left side of std::string.
 *        Taken from:
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 */
void trim_left(std::string& str);

/**
 * @brief Trims (in-place) white spaces from the right side of std::string.
 *        Taken from:
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 */
void trim_right(std::string& str);

/**
 * @brief Trims (in-place) white spaces from the both sides of std::string.
 *        Taken from:
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 */
void trim(std::string& str);

/**
 * @brief Trims white spaces from the left side of std::string.
 *        Taken from:
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 * @return Copy of input str with trimmed white spaces.
 */
std::string trim_left_copy(std::string str);

/**
 * @brief Trims white spaces from the right side of std::string.
 *        Taken from:
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 * @return Copy of input str with trimmed white spaces.
 */
std::string trim_right_copy(std::string str);

/**
 * @brief Trims white spaces from the both sides of std::string.
 *        Taken from:
 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 * @return Copy of input str with trimmed white spaces.
 */
std::string trim_copy(std::string str);

/**
 * @brief Replaces (in-place) the first occurance of target with replacement.
 *        Taken from:
 * http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
 * @param str - input std::string that will be modified.
 * @param target - substring that will be replaced with replacement.
 * @param replecament - substring that will replace target.
 * @return True if replacement was successfull, false otherwise.
 */
bool replace_first(std::string& str, std::string_view target, std::string_view replecament);

/**
 * @brief Replaces (in-place) last occurance of target with replacement.
 *        Taken from:
 * http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
 * @param str - input std::string that will be modified.
 * @param target - substring that will be replaced with replacement.
 * @param replecament - substring that will replace target.
 * @return True if replacement was successfull, false otherwise.
 */
bool replace_last(std::string& str, std::string_view target, std::string_view replecament);

/**
 * @brief Replaces (in-place) all occurances of target with replacement.
 *        Taken from:
 * http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
 * @param str - input std::string that will be modified.
 * @param target - substring that will be replaced with replacement.
 * @param replecament - substring that will replace target.
 * @return True if replacement was successfull, false otherwise.
 */
bool replace_all(std::string& str, std::string_view target, std::string_view replecament);

/**
 * @brief Splits input std::string str according to input delim.
 * @param str - std::string that will be splitted.
 * @param delim - the delimiter.
 * @return std::vector<std::string> that contains all splitted tokens.
 */
std::vector<std::string> split(std::string_view str, char delim);

/// Splits input std::string str according to input delim.
/// \tparam N number of tokens
/// \param str std::string that will be splitted.
/// \param delim delimiter
/// \return std::array<std::string, N> that contains all splitted tokens.
template <std::size_t N>
static std::array<std::string, N> split(std::string_view str, char const delim)
{
    std::array<std::string, N> tokens;
    std::stringstream ss { std::string { str }, std::ios_base::in };

    std::string token;
    auto index = 0u;
    while (std::getline(ss, token, delim)) {
        if (index >= N) {
            throw std::invalid_argument { "strutil::split Array size '" + std::to_string(N)
                + "' does not match number of Tokens '" + std::to_string(index) + "'" };
        }
        tokens.at(index) = token;
        index++;
    }

    return tokens;
}

/**
 * @brief Splits input std::string str according to input std::string delim.
 *        Taken from: https://stackoverflow.com/a/46931770/1892346.
 * @param str - std::string that will be split.
 * @param delim - the delimiter.
 * @return std::vector<std::string> that contains all splitted tokens.
 */
std::vector<std::string> split(std::string_view str, std::string_view delim);

/**
 * @brief Splits input string using any delimiter in the given set.
 * @param str - std::string that will be split.
 * @param delims - the set of delimiter characters.
 * @return vector of resulting tokens.
 */
std::vector<std::string> split_any(std::string_view str, std::string_view delims);

/**
 * @brief Joins all elements of std::vector tokens of arbitrary datatypes
 *        into one std::string with delimiter delim.
 * @tparam T - arbitrary datatype.
 * @param tokens - vector of tokens.
 * @param delim - the delimiter.
 * @return std::string with joined elements of vector tokens with delimiter delim.
 */
template <typename T>
static std::string join(std::vector<T> const& tokens, std::string_view const delim)
{
    std::ostringstream result;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it != tokens.begin()) {
            result << delim;
        }

        result << *it;
    }

    return result.str();
}

/**
 * @brief Creates new std::string with repeated n times substring str.
 * @param str - substring that needs to be repeated.
 * @param n - number of iterations.
 * @return std::string with repeated substring str.
 */
std::string repeat(std::string_view str, unsigned n);

/**
 * @brief Creates new std::string with repeated n times char c.
 * @param c - char that needs to be repeated.
 * @param n - number of iterations.
 * @return std::string with repeated char c.
 */
std::string repeat(char c, unsigned n);

/**
 * @brief Checks if input std::string str matches specified reular expression regex.
 * @param str - std::string to be checked.
 * @param regex - the std::regex regular expression.
 * @return True if regex matches str, false otherwise.
 */
bool matches(std::string const& str, std::regex const& regex);

} // namespace strutil

#endif
