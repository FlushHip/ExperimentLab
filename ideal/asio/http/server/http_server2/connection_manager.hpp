#pragma once

#include <set>

#include <boost/noncopyable.hpp>

#include "connection.hpp"

namespace http {
namespace server {

class ConnectionManager : public boost::noncopyable
{
public:
    void start(ConnectionPtr con);
    void stop(ConnectionPtr con);
    void stop_all();
private:
    std::set<ConnectionPtr> connections_;
};

}
}
