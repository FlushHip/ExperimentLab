#include <hestina/log/logger.h>
#include <hestina/net/http_common.h>
#include <hestina/net/http_request.h>
#include <hestina/net/http_response.h>
#include <hestina/net/http_server.h>

#include <string>
#include <thread>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace, true);

    hestina::http_server server("127.0.0.1", 12347);
    server.register_handler("/test",
        [](const hestina::http_request& request,
            hestina::http_response& response) {
            static int scnt = 1;
            response.set_content_type(hestina::content_type_t::ktext_html);
            response.set_body(R"(<!DOCTYPE html>
<html>
<head>
<title>Page Title</title>
</head>
<body>

<h1>This is a Heading</h1>
<p>This is a paragraph.</p>

<p> cnt : <b>)" +
                std::to_string(scnt++) +
                R"(</b></p>

</body>
</html>)");
        });
    server.register_handler("/test2",
        [](const hestina::http_request& request,
            hestina::http_response& response) {
            static int scnt = 1;
            response.set_content_type(hestina::content_type_t::ktext_plain);
            response.set_body("flushhip");
        });
    server.register_handler("/test3",
        [](const hestina::http_request& request,
            hestina::http_response& response) {
            static int scnt = 1;
            response.set_content_type(
                hestina::content_type_t::kapplication_json);
            response.set_body(
                R"({
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
})");
        });
    server.start();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1h);
    return 0;
}
