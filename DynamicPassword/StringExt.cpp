#include <string>

std::wstring& trim(std::wstring& s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0, s.find_first_not_of(L' '));
    s.erase(s.find_last_not_of(L' ') + 1);
    return s;
}