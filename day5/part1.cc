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

typedef std::pair<long, long> range_t;
typedef std::vector<range_t> rnglist_t;

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

struct {
    bool operator()(const map_entry_t& l, const map_entry_t &r)
    {
        return l.s_start < r.s_start;
    }
} map_less_op;

int update_rngs2(const pmap_t m, const rnglist_t *irng, rnglist_t *org)
{
    rnglist_t tmp;
    bool processed = false;

    tmp = *irng;

    auto r = tmp.begin();
    while (r != tmp.end())
    {
        range_t rtmp(r->first, r->second);
        processed = false;
        tmp.erase(r);

        //std::cout<<"Checking range ["<<rtmp.first<<".."<<rtmp.second<<")"<<std::endl;
        for (auto mv : m->map)
        {
            if (rtmp.first < mv.s_start)
            {
                if (rtmp.second <= mv.s_start)
                {
                    // if the range is completely to the left of the current map
                    // then it is to the left of any subsequent map also
                    // so if it was not taken by the previous map - it is not mapped at all
                    //std::cout<<"Maps ["<<mv.s_start<<".."<<mv.s_start + mv.len<<") to ["<<mv.d_start<<".."<<mv.d_start + mv.len<<")"<<" : ";
                    //std::cout<<"Res ["<<rtmp.first<<".."<<rtmp.second<<")"<<std::endl;
                    processed = true;
                    org->push_back(rtmp);
                    break;
                }
                tmp.push_back(range_t(rtmp.first, mv.s_start));
                rtmp.first = mv.s_start;
            }
            if (rtmp.second > mv.s_start + mv.len)
            {
                if (rtmp.first >= mv.s_start + mv.len)
                {
                    continue;
                }
                tmp.push_back(range_t(mv.s_start + mv.len, rtmp.second));
                rtmp.second = mv.s_start + mv.len;
            }
            if (rtmp.second > mv.s_start)
            {
                long nfirst = (mv.d_start - mv.s_start) + rtmp.first;
                long nsecond = (mv.d_start - mv.s_start) + rtmp.second;
                org->push_back(range_t(nfirst, nsecond));
                //std::cout<<"Maps ["<<mv.s_start<<".."<<mv.s_start + mv.len<<") to ["<<mv.d_start<<".."<<mv.d_start + mv.len<<")"<<" : ";
                //std::cout<<"Res "<<nfirst<<"..."<<nsecond<<std::endl;
                processed = true;
                break;
            }
        }
        if (! processed) // it is to the right of any map
        {
            //std::cout<<"Unmapped : ";
            //std::cout<<"Res ["<<rtmp.first<<".."<<rtmp.second<<")"<<std::endl;
            org->push_back(rtmp);
        }
        r = tmp.begin();
    }
    return 0;
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
        else
        {
            std::sort(alm[aidx]->map.begin(), alm[aidx]->map.end(),
                      map_less_op);
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

int parse_seeds2(rnglist_t &rngs, std::string fname)
{
    std::ifstream in(fname);
    std::string s;

    std::getline(in, s, ' '); // skip 'seeds: '

    do
    {
        long s = 0, l = 0;
        in>>s>>l;
        if (s != 0 && l != 0)
        {
            rngs.push_back(range_t(s, s + l)); // range [s; s+l)
        }
    }
    while (! in.eof() && !in.fail());
    return 0;
}

int main(int argc, char **argv)
{
    almanac_t alm;
    std::vector<long> vseeds, res;
    rnglist_t onerng, tworng, *c_rngs, *p_rngs, nextrng, *tmprng;

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
    std::cout<<"Minsta första: "<<res[0]<<std::endl;

    parse_seeds2(onerng, argv[2]);

    p_rngs = &onerng;
    c_rngs = &tworng;

    for (auto m : alm)
    {
        c_rngs->clear();
        // Update ranges, each potentially can be split
        update_rngs2(m, p_rngs, c_rngs);
        tmprng = p_rngs;
        p_rngs = c_rngs;
        c_rngs = tmprng;
    }
    std::sort(p_rngs->begin(), p_rngs->end());
    std::cout<<"Minsta andra: "<<p_rngs->begin()->first<<std::endl;

    return 0;
}
