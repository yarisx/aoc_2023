#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

typedef std::vector<int> line_t;
typedef std::vector<line_t> lineset_t;

int get_forecast(line_t* inln)
{
    bool all_zero = false;
    line_t last_elems, diffs1 = *inln, diffs2;
    line_t *it1 = &diffs1, *it2 = &diffs2, *tmp;
    int psum = 0, sum = 0;

    do
    {
        last_elems.push_back(*(it1->rbegin()));
        line_t::iterator i1, i2;
        all_zero = true;
        it2->clear();

        for (i1 = it1->begin(), i2 = (it1->begin()) + 1; i2 != it1->end(); i1++, i2++)
        {
            int diff = *i2 - *i1;
            it2->push_back(diff);
            if (diff != 0) all_zero = false;
        }
        tmp = it2;
        it2 = it1;
        it1 = tmp;
    }
    while (! all_zero);
    for (auto l = last_elems.size(); l > 0; l--)
    {
        sum = last_elems[l - 1] + psum;
        psum = sum;
    }
    return sum;
}

int get_backecast(line_t* inln)
{
    bool all_zero = false;
    line_t first_elems, diffs1 = *inln, diffs2;
    line_t *it1 = &diffs1, *it2 = &diffs2, *tmp;
    int psum = 0, sum = 0;

    do
    {
        first_elems.push_back(*(it1->begin()));
        line_t::reverse_iterator i1, i2;
        all_zero = true;
        it2->clear();

        for (i1 = it1->rbegin(), i2 = (it1->rbegin()) + 1; i2 != it1->rend(); i1++, i2++)
        {
            int diff = *i1 - *i2;
            it2->insert(it2->begin(), diff);
            if (diff != 0) all_zero = false;
        }
        tmp = it2;
        it2 = it1;
        it1 = tmp;
    }
    while (! all_zero);
    for (auto l = first_elems.size(); l > 0; l--)
    {
        sum = first_elems[l - 1] - psum;
        psum = sum;
    }
    return sum;
}

int main(int argc, char **argv)
{
    std::string     s, is, idx;
    std::ifstream   in(argv[1]);
    lineset_t       lineset;
    bool            first = true;

    if (argc < 3) return -1;
    if (std::strcmp(argv[2], "1") != 0) first = false;

    std::getline(in, s);
    while (! s.empty())
    {
        std::istringstream ins(s);
        line_t  ln;
        int     v;

        do
        {
            ins>>v;
            ln.push_back(v);
        }
        while (! ins.eof());
        lineset.push_back(ln);
        std::getline(in, s);
    }

    int total = 0;
    for (int i = 0; i < lineset.size(); i++)
    {
        if (first)
            total += get_forecast(&lineset[i]);
        else
            total += get_backecast(&lineset[i]);
    }
    std::cout<<"Total "<<total<<std::endl;
}
