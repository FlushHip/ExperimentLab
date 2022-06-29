#pragma once

#include <boost/logic/tribool.hpp>

#include "request.hpp"

namespace http {
namespace server {

class RequestParser
{
public:
    RequestParser();

    template<typename InputIterator>
    std::tuple<boost::tribool, InputIterator>
        parse(Request &request, InputIterator begin, InputIterator end)
    {
        return {true, begin};
    }
};

}
}
