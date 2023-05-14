#include "client_http.hpp"
#include <iostream>
#include <cpr/cpr.h>

int ClientHTTP::post(const Header & headers, const std::string & body, const std::string & url, std::string & response) {
    cpr::Response r = cpr::Post(cpr::Url{url},
                                cpr::Header{headers},
                                cpr::Body{body});
    std::string answer = r.text;
    std::cout << answer << std::endl;
    return 200;
}
