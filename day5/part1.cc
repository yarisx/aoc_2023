#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef struct {
    long s_start, d_start, len;
} map_entry_t;

typedef std::vector<map_entry_t> map_value_t;
typedef struct {
    std::string name;
    map_value_t map;
} map_t;
typedef map_t *pmap_t;
typedef std::vector<pmap_t> almanac_t;

long find_dest(const pmap_t l, long s)
{
    for (auto m : l->map)
    {
        if (s >= m.s_start && s < (m.s_start + m.len))
        {
            return m.d_start + (s - m.s_start);
        }
    }
    return s;
}

int parse_maps(almanac_t& alm, std::string fname)
{
    std::ifstream in(fname);
    std::string s;
    almanac_t::size_type aidx = 0;

    std::getline(in, s);
    for ( ; ! in.eof(); std::getline(in, s))
    {
        if (s.find("map:") != std::string::npos)
        {
            pmap_t p = new map_t;
            p->name = s;
            alm.push_back(p);
            aidx = alm.size() - 1;
        }
        else if (! s.empty())
        {
            std::istringstream ins(s);
            map_entry_t me;

            ins>>me.d_start>>me.s_start>>me.len;
            alm[aidx]->map.push_back(me);
        }
    }
    return 0;
}

int parse_seeds(std::vector<long> &vseeds, std::string fname)
{
    std::ifstream in(fname);
    std::string s;

    std::getline(in, s, ' '); // skip 'seeds: '

    while (!in.eof())
    {
        long v;
        in>>v;
        vseeds.push_back(v);
    }
    return 0;
}

int main(int argc, char **argv)
{
    almanac_t alm;
    std::vector<long> vseeds, res;

    if (argc < 3) return -1;

    parse_maps(alm, argv[1]);

    parse_seeds(vseeds, argv[2]);

    for (auto s : vseeds)
    {
        auto next = s;
        for (auto m : alm)
        {
            next = find_dest(m, next);
        }
        res.push_back(next);
    }
    std::sort(res.begin(), res.end());
    std::cout<<"Minsta plats: "<<res[0]<<std::endl;

    return 0;
}
