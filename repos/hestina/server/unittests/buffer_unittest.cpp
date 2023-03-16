#include <doctest/doctest.h>

#include <hestina/net/buffer.h>
#include <hestina/util/funs.h>

#include <fstream>
#include <ios>

#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>

TEST_CASE("buffer interface") {
    SUBCASE("init default") {
        hestina::buffer buff;
        CHECK(buff.data().length() == hestina::buffer::init_length);
        CHECK(buff.readable_bytes() == 0);
        CHECK(buff.writeable_bytes() == hestina::buffer::init_length);
    }

    SUBCASE("init with 2048") {
        int init_length = 2048;
        hestina::buffer buff(init_length);
        CHECK(buff.data().length() == init_length);
        CHECK(buff.readable_bytes() == 0);
        CHECK(buff.writeable_bytes() == init_length);
    }

    SUBCASE("peek*") {
        using namespace std::string_view_literals;
        hestina::buffer buff;
        std::string_view line = "flushhip";
        buff.append(line);
        CHECK(buff.writeable_bytes() == buff.data().length() - line.size());
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek() == line);
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek(1) == "f"sv);
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek(2) == "fl"sv);
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek_int8() == 'f');
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek_int16() ==
            ntohs(*reinterpret_cast<const uint16_t*>(line.data())));
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek_int32() ==
            ntohl(*reinterpret_cast<const uint32_t*>(line.data())));
        CHECK(buff.readable_bytes() == line.size());

        CHECK(buff.peek_int64() ==
            hestina::util::ntoh64(
                *reinterpret_cast<const uint64_t*>(line.data())));
        CHECK(buff.readable_bytes() == line.size());
    }

    SUBCASE("read") {
        hestina::buffer buff;
        std::string_view line = "flushhip";
        buff.append(line);
        CHECK(buff.writeable_bytes() == buff.data().length() - line.size());

        CHECK(buff.read() == line);
        CHECK(buff.readable_bytes() == 0);
    }

    SUBCASE("read_int8") {
        hestina::buffer buff;
        std::string_view line = "flushhip";
        buff.append(line);
        CHECK(buff.writeable_bytes() == buff.data().length() - line.size());

        CHECK(buff.read_int8() == 'f');
        CHECK(buff.readable_bytes() == line.size() - 1);
    }

    SUBCASE("read_int16") {
        hestina::buffer buff;
        std::string_view line = "flushhip";
        buff.append(line);
        CHECK(buff.writeable_bytes() == buff.data().length() - line.size());

        CHECK(buff.read_int16() ==
            ntohs(*reinterpret_cast<const uint16_t*>(line.data())));
        CHECK(buff.readable_bytes() == line.size() - 2);
    }

    SUBCASE("read_int32") {
        hestina::buffer buff;
        std::string_view line = "flushhip";
        buff.append(line);
        CHECK(buff.writeable_bytes() == buff.data().length() - line.size());

        CHECK(buff.read_int32() ==
            ntohl(*reinterpret_cast<const uint32_t*>(line.data())));
        CHECK(buff.readable_bytes() == line.size() - 4);
    }

    SUBCASE("read_int64") {
        hestina::buffer buff;
        std::string_view line = "flushhip";
        buff.append(line);
        CHECK(buff.writeable_bytes() == buff.data().length() - line.size());

        CHECK(buff.read_int64() ==
            hestina::util::ntoh64(
                *reinterpret_cast<const uint64_t*>(line.data())));
        CHECK(buff.readable_bytes() == line.size() - 8);
    }
}

TEST_CASE("buffer read_fd") {
    hestina::buffer buff;

    std::string_view file_name = "dummy.txt";
    int value = 39535;
    {
        std::ofstream fout(file_name.data(), std::ios_base::binary);
        auto i_8 = static_cast<uint8_t>(value);
        auto i_16 = htons(value);
        auto i_32 = htonl(value);
        auto i_64 = hestina::util::hton64(value);
        fout.write(reinterpret_cast<char*>(&i_8), 1);
        fout.write(reinterpret_cast<char*>(&i_16), 2);
        fout.write(reinterpret_cast<char*>(&i_32), 4);
        fout.write(reinterpret_cast<char*>(&i_64), 8);
    }

    int fd = ::open(file_name.data(), O_RDONLY);
    REQUIRE(fd != -1);

    int err = 0;
    int n = buff.read_fd(fd, err);
    CHECK(n > 0);
    CHECK(err == 0);

    CHECK(buff.read_int8() == static_cast<uint8_t>(value));
    CHECK(buff.read_int16() == value);
    CHECK(buff.read_int32() == value);
    CHECK(buff.read_int64() == value);

    ::close(fd);
}

TEST_CASE("buffer grow length") {
    hestina::buffer buff;
    buff.append(std::string(hestina::buffer::init_length * 2, 'h'));
    CHECK(buff.peek_int8() == 'h');

    buff.append(std::string(hestina::buffer::init_length * 2, 'y'));
    buff.retrieve(hestina::buffer::init_length * 2);
    CHECK(buff.peek_int8() == 'y');

    buff.retrieve_all();
    CHECK(buff.readable_bytes() == 0);
    CHECK(buff.writeable_bytes() == hestina::buffer::init_length);
}
