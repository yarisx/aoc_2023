#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <tuple>

typedef std::pair<std::string, std::string> lr_t;

typedef std::map<std::string, lr_t> map_t;

int main(int argc, char **argv)
{
    std::string s, is;
    std::string idx;
    std::ifstream in(argv[1]);
    map_t       smap;
    int c = 0;

    std::getline(in, is); // This is LR line

    std::getline(in, s); // empty line-separator
    std::getline(in, s);
    while (! s.empty())
    {
        std::string tag, left, right;

        tag = s.substr(0, 3);
        left = s.substr(7, 3);
        right = s.substr(12, 3);
        smap.insert({tag, lr_t(left, right)});
        std::getline(in, s);
    }
    auto next = smap["AAA"];
    for (std::string::size_type j = 0; idx != "ZZZ"; j++)
    {
        auto ri = j % is.size();

        if (is[ri] == 'L')
            idx = next.first;
        else
            idx = next.second;
        c++;
        next = smap[idx];
    }
    std::cout<<c<<" steps AAA to ZZZ"<<std::endl;

    return 0;
}
