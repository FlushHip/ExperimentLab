#include "connection_manager.hpp"

namespace http {
namespace server {

void ConnectionManager::start(ConnectionPtr con)
{
    connections_.insert(con);
    con->start();
}

void ConnectionManager::stop(ConnectionPtr con)
{
    connections_.erase(con);
    con->stop();
}

void ConnectionManager::stop_all()
{
    for (auto ptr : connections_) {
        ptr->stop();
    }
    connections_.clear();
}

}
}
