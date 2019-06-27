#ifndef CSPLITSTRING_H_INCLUDED
#define CSPLITSTRING_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace JamTemplate {
class SplitString : public std::string {
    std::vector<std::string> flds;

public:
    explicit SplitString(char* s)
        : std::string(s) {};
    explicit SplitString(std::string s)
        : std::string(s) {};

    std::vector<std::string>& split(char delim, int rep = 0)
    {
        if (!flds.empty())
            flds.clear(); // empty vector if necessary
        std::string work = data();
        std::string buf = "";
        unsigned int i = 0;
        while (i < work.length()) {
            if (work[i] != delim)
                buf += work[i];
            else if (rep == 1) {
                flds.push_back(buf);
                buf = "";
            } else if (buf.length() > 0) {
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
}
#endif
