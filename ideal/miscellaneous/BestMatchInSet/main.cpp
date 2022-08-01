#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <forward_list>

#include "best_match_in_set.hpp"

// 默认参数自动进行推导，自动导航到偏特化
template<typename Iterator
    , typename Tag = BestMatchInSet_t<
        typename std::iterator_traits<Iterator>::iterator_category
        , std::input_iterator_tag
        , std::output_iterator_tag
        , std::forward_iterator_tag
        , std::bidirectional_iterator_tag
        , std::random_access_iterator_tag>>
class AdvanceIterator;

template<typename Iterator>
class AdvanceIterator<Iterator, std::input_iterator_tag> {
public:
    void operator()() const {
        std::cout << "input_iterator_tag\n";
    }
};

template<typename Iterator>
class AdvanceIterator<Iterator, std::output_iterator_tag> {
public:
    void operator()() const {
        std::cout << "output_iterator_tag\n";
    }
};

template<typename Iterator>
class AdvanceIterator<Iterator, std::forward_iterator_tag> {
public:
    void operator()() const {
        std::cout << "forward_iterator_tag\n";
    }
};

template<typename Iterator>
class AdvanceIterator<Iterator, std::bidirectional_iterator_tag> {
public:
    void operator()() const {
        std::cout << "bidirectional_iterator_tag\n";
    }
};

template<typename Iterator>
class AdvanceIterator<Iterator, std::random_access_iterator_tag> {
public:
    void operator()() const {
        std::cout << "random_access_iterator_tag\n";
    }
};

int main(int argc, char* argv[]) {
    AdvanceIterator<std::string::iterator>{}();
    AdvanceIterator<std::vector<int>::iterator>{}();
    AdvanceIterator<std::list<int>::iterator>{}();
    AdvanceIterator<std::map<int, int>::iterator>{}();
    AdvanceIterator<std::forward_list<int>::iterator>{}();
    AdvanceIterator<std::ostream_iterator<int>>{}();
    AdvanceIterator<std::istream_iterator<int>>{}();
    return 0;
}
