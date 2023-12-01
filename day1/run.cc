#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    std::ifstream in("input2.txt");
    std::string s;
    std::getline(in, s);
    bool forward = true;

    if (argc > 1 && ! std::strcmp(argv[1], "-f")) forward = true;
    else forward = false;

    while(! s.empty())
    {
        bool next = false;
        if (! forward) reverse(s.begin(), s.end());
        for (std::string::size_type i = 0; i < s.size() && !next; i++)
        {
            switch(s[i])
            {
                case 'e': {
                    if (forward) {
                        if (s.substr(i, 5) == "eight")
                        {
                            std::cout<<"8"<<std::endl;
                            next = true;
                        }
                    } else {
                        if (s.substr(i, 3) == "eno")
                        {
                            std::cout<<"1"<<std::endl;
                            next = true;
                        }
                        if (s.substr(i, 4) == "enin")
                        {
                            std::cout<<"9"<<std::endl;
                            next = true;
                        }
                        if (s.substr(i, 4) == "evif")
                        {
                            std::cout<<"5"<<std::endl;
                            next = true;
                        }
                        if (s.substr(i, 5) == "eerht")
                        {
                            std::cout<<"3"<<std::endl;
                            next = true;
                        }
                    }
                }
                break;
                case 'f': {
                    if (forward) {
                        if (s.substr(i, 4) == "five")
                        {
                            std::cout<<"5"<<std::endl;
                            next = true;
                        }
                        if (s.substr(i, 4) == "four")
                        {
                            std::cout<<"4"<<std::endl;
                            next = true;
                        }
                    }
                }
                break;
                case 'n': {
                    if (forward) {
                        if (s.substr(i, 4) == "nine")
                        {
                            std::cout<<"9"<<std::endl;
                            next = true;
                        }
                    } else {
                        if (s.substr(i, 5) == "neves")
                        {
                            std::cout<<"7"<<std::endl;
                            next = true;
                        }
                    }
                }
                break;
                case 'o': {
                    if (forward) {
                        if (s.substr(i, 3) == "one")
                        {
                            std::cout<<"1"<<std::endl;
                            next = true;
                        }
                    } else {
                        if (s.substr(i, 4) == "orez")
                        {
                            std::cout<<"0"<<std::endl;
                            next = true;
                        }
                        if (s.substr(i, 3) == "owt")
                        {
                            std::cout<<"2"<<std::endl;
                            next = true;
                        }
                    }
                }
                break;
                case 'r': {
                    if (! forward) {
                        if (s.substr(i, 4) == "ruof")
                        {
                            std::cout<<"4"<<std::endl;
                            next = true;
                        }
                    }
                }
                case 's': {
                    if (s.substr(i, 3) == "six")
                    {
                        std::cout<<"6"<<std::endl;
                        next = true;
                    }
                    if (s.substr(i, 5) == "seven")
                    {
                        std::cout<<"7"<<std::endl;
                        next = true;
                    }
                }
                break;
                case 't': {
                    if (forward) {
                        if (s.substr(i, 3) == "two")
                        {
                            std::cout<<"2"<<std::endl;
                            next = true;
                        }
                        if (s.substr(i, 5) == "three")
                        {
                            std::cout<<"3"<<std::endl;
                            next = true;
                        }
                    } else {
                        if (s.substr(i, 5) == "thgie")
                        {
                            std::cout<<"8"<<std::endl;
                            next = true;
                        }
                    }
                }
                break;
                case 'x': {
                    if (! forward) {
                        if (s.substr(i, 3) == "xis")
                        {
                            std::cout<<"6"<<std::endl;
                            next = true;
                        }
                    }
                }
                case 'z': {
                    if (s.substr(i, 4) == "zero")
                    {
                        std::cout<<"0"<<std::endl;
                        next = true;
                    }
                }
                break;
                default: {
                    if (s[i] >= '0' && s[i] <= '9')
                    {
                        std::cout<<s[i]<<std::endl;
                        next = true;
                    }
                }
            }
        }
        std::getline(in, s);
    }
}
