#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

const int high = 0;
const int one_pair = 1;
const int two_pair = 2;
const int three = 3;
const int full_house = 4;
const int four = 5;
const int five = 6;

typedef std::tuple<int, std::string, long> draw_t;
typedef std::vector<draw_t>  game_t;

const size_t hand_len = 5;

int promote(int ret, int js);

struct {
    bool operator()(const draw_t &l, const draw_t &r) const
    {
        auto lkind = std::get<0>(l);
        auto rkind = std::get<0>(r);

        if (lkind < rkind)
        {
            return true;
        }
        else
        {
            if (lkind > rkind) return false;
            else
            {
                auto lhand = std::get<1>(l);
                auto rhand = std::get<1>(r);

                for (int i = 0; i < hand_len; i++)
                {
                    if (lhand[i] < rhand[i])
                    {
                        return true;
                    }
                    else
                    {
                        if (lhand[i] > rhand[i]) return false;
                    }
                }
            }
        }
        return false;
    }
} hand_sort;

int kind(std::string &h)
{
    std::string t(5, ' ');
    int c[13] = {0};
    bool three_f = false, two_f = false;

    for (std::string::size_type i = 0; i < h.size(); i++)
    {
        if (h[i] >= '2' && h[i] <= '9')
        {
            t[i] = h[i] - 50;
        }
        if (h[i] == 'T') t[i] = 8;
        if (h[i] == 'J') t[i] = 9;
        if (h[i] == 'Q') t[i] = 10;
        if (h[i] == 'K') t[i] = 11;
        if (h[i] == 'A') t[i] = 12;
        c[t[i]]++;
    }
    h = t;
    for (size_t i = 0; i < 13; i++)
    {
        if (c[i] == 5) return five;
        if (c[i] == 4) return four;
        if (c[i] == 3)
        {
            if (two_f) return full_house;
            else three_f = true;
        }
        if (c[i] == 2)
        {
            if (three_f) return full_house;
            else
            {
                if (two_f) return two_pair;
                else two_f = true;
            }
        }
    }
    if (three_f) return three;
    if (two_f) return one_pair;
    return high;
}

int kind2(std::string &h)
{
    std::string t(5, ' ');
    int c[13] = {0};
    int js = 0;
    bool three_f = false, two_f = false;
    int ret = high;

    for (std::string::size_type i = 0; i < h.size(); i++)
    {
        if (h[i] == 'J') { t[i] = 0; js++; continue; }
        if (h[i] >= '2' && h[i] <= '9')
        {
            t[i] = h[i] - 49;
        }
        if (h[i] == 'T') t[i] = 9;
        if (h[i] == 'Q') t[i] = 10;
        if (h[i] == 'K') t[i] = 11;
        if (h[i] == 'A') t[i] = 12;
        c[t[i]]++;
    }
    h = t;
    for (size_t i = 0; i < 13 && ret == high; i++)
    {
        if (c[i] == 5) { ret = five; continue; }
        if (c[i] == 4) { ret = four; continue; }
        if (c[i] == 3)
        {
            if (two_f) { ret = full_house; continue; }
            else { three_f = true; continue; }
        }
        if (c[i] == 2)
        {
            if (three_f) { ret = full_house; continue; }
            else
            {
                if (two_f) { ret = two_pair; continue; }
                else { two_f = true; continue; }
            }
        }
    }
    if (three_f && ret == high) ret = three;
    else if (two_f && ret == high) ret = one_pair;
    return promote(ret, js);
}

int promote(int ret, int js)
{
    if (js == 5) return five;
    switch (ret)
    {
        case four: if (js == 1) return five;
        case three:
            if (js == 2) return five;
            else if (js == 1) return four;
        case two_pair:
            if (js == 1) return full_house;
        case one_pair:
            if (js == 3) return five;
            else
            {
                if (js == 2) return four;
                else if (js == 1) return three;
            }
        case high:
            switch(js)
            {
                case 4: return five;
                case 3: return four;
                case 2: return three;
                case 1: return one_pair;
            }
    }
    return ret;
}

int main(int argc, char **argv)
{
    std::ifstream in(argv[1]);
    std::string s;
    game_t  game;
    long    total = 0;
    int     hkind, pn = std::stoi(argv[2]);

    std::getline(in, s);
    while (! s.empty())
    {
        auto space = s.find_first_of(" ");
        std::string hand = s.substr(0, space);
        if (pn == 1)
            hkind = kind(hand);
        else
            hkind = kind2(hand);
        long bid = std::strtol(s.substr(space, s.size()).c_str(), NULL, 10);
        game.push_back(draw_t(hkind, hand, bid));
        std::getline(in, s);
    }
    std::sort(game.begin(), game.end(), hand_sort);
    for (size_t i = 0; i < game.size(); i++)
    {
        long v = std::get<2>(game[i]);
        total += v * (i + 1);
    }
    std::cout<<"Total "<<total<<std::endl;

    return 0;
}
