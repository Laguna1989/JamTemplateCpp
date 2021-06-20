#ifndef GUARD_JAMTEMPLATE_CSPLITSTRING_H_INCLUDED
#define GUARD_JAMTEMPLATE_CSPLITSTRING_H_INCLUDED

#include <string>
#include <vector>

namespace jt {

class SplitString : public std::string {
    std::vector<std::string> flds;

public:
    explicit SplitString(char* s)
        : std::string(s) {};
    explicit SplitString(std::string s)
        : std::string(s) {};

    std::vector<std::string>& split(char delim)
    {
        if (!flds.empty())
            flds.clear(); // empty vector if necessary
        std::string work = data();
        std::string buf = "";
        unsigned int i = 0;
        while (i < work.length()) {
            if (work[i] != delim)
                buf += work[i];
            else if (buf.length() > 0) {
                flds.push_back(buf);
                buf = "";
            }
            i++;
        }
        if (!buf.empty())
            flds.push_back(buf);
        return flds;
    }
};
} // namespace jt
#endif
