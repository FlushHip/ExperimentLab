#include <iostream>
#include <iomanip>
#include <memory>
#include <future>
#include <chrono>
#include <functional>

template <class CharT, class Traits, class Rep, class Period>
std::basic_ostream<CharT, Traits>&
operator <<(
    std::basic_ostream<CharT, Traits>& os, std::chrono::duration<Rep, Period> d)
{
    typedef std::chrono::duration<long long, std::ratio<86400> > days;
    typedef std::chrono::duration<long long, std::centi> centiseconds;

    centiseconds cs = std::chrono::duration_cast<centiseconds>(d);
    if (d - cs > std::chrono::milliseconds(5)
        || (d - cs == std::chrono::milliseconds(5) && cs.count() & 1))
        ++cs;
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(cs);
    cs -= s;
    std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(s);
    s -= m;
    std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(m);
    m -= h;
    days dy = std::chrono::duration_cast<days>(h);
    h -= dy;

    // print d/hh:mm:ss.cc
    os << dy.count() << '/' << std::setfill('0')
        << std::setw(2) << h.count() << ':'
        << std::setw(2) << m.count() << ':'
        << std::setw(2) << s.count() << ':'
        << std::setw(2) << cs.count();
    return os;
}


int main(int argc, char **argv)
{
    using namespace std::chrono;
    using namespace std::literals;

    auto stamp = system_clock::now();
    auto do_work = [stamp] () -> void
    {
        std::cout << std::this_thread::get_id() << " do" << std::endl;
        std::this_thread::sleep_for(5s);
        std::cout << std::this_thread::get_id() << " : " << system_clock::now() - stamp << std::endl;
    };

    std::cout << std::this_thread::get_id() << " main" << std::endl;

    auto fuA = std::async(std::launch::deferred, do_work);

    std::cout << __LINE__ << " : " << system_clock::now() - stamp << std::endl;
    fuA.get();
    std::cout << __LINE__ << " : " << system_clock::now() - stamp << std::endl;

    auto fuB = std::async(std::launch::async, do_work);
    std::cout << __LINE__ << " : " << system_clock::now() - stamp << std::endl;
    //fuB.get();
    std::this_thread::sleep_for(5s);
    std::cout << __LINE__ << " : " << system_clock::now() - stamp << std::endl;

    return 0;
}
