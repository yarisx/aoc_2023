#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <set>
#include <map>

typedef std::set<int> cardside_t;
typedef std::pair<cardside_t, cardside_t> card_t;
typedef std::pair<card_t, int> cardentry_t;
typedef std::multimap<int, cardentry_t> map_t;

unsigned int winning_card(const card_t& c)
{
    unsigned int num = 0;
    auto l = c.first, r = c.second;
    auto lit = l.begin(), rit = r.begin();
    while (lit != l.end() && rit != r.end())
    {
        if (*lit < *rit)
            ++lit;
        else
        {
            if (!(*rit < *lit))
            {
                num++;
                lit++;
            }
            ++rit;
        }
    }
    return num;
}

int main(int argc, char **argv)
{
    std::string cs;
    int card_num = 0, num;
    map_t   deck;
    std::ifstream in(argv[1]);

    std::getline(in, cs);
    while (! cs.empty())
    {
        std::istringstream is(cs);
        cardside_t  left, right;

        is.ignore(cs.size(), ' '); // Skip 'Card ...' part
        is>>card_num;
        is.ignore(1, ':');
        while (! is.fail())
        {
            is>>num;
            left.insert(num);
        }
        is.clear();
        is.ignore(cs.size(), '|');
        while (! is.eof())
        {
            is>>num;
            right.insert(num);
        }
        deck.insert({card_num, cardentry_t(card_t(left, right), 1)});
        std::getline(in, cs);
    }
    auto one_card = deck.begin();
    while (one_card != deck.end())
    {
        // each card adds 'wins' card numbers, each  - N times,
        // where N == number of "current number" cards in deck
        unsigned int wins = winning_card(one_card->second.first);

        int i = 0;
        for (auto tmp = deck.upper_bound(one_card->first);
                  i < wins && tmp != deck.end(); i++)
        {
            tmp->second.second += one_card->second.second;
            tmp = deck.upper_bound(tmp->first);
        }
        one_card = deck.upper_bound(one_card->first); // next key
    }
    num = 0;
    for (auto c : deck)
    {
        num += c.second.second;
    }
    std::cout<<"Total "<<num<<" cards"<<std::endl;

    return 0;
}
