#include <cpr/cpr.h>
#include <cpr/util.h>
#include <fstream>

#include "client_http.hpp"

int ClientHTTP::post(Header & headers, const std::string & body, const std::string & url, std::string & response) {
    std::string str_headers;
    for (const auto& [header, value] : headers) {
        str_headers += header + ": " + value + "\r\n";
    }
    str_headers += "\r\n";
    cpr::Response res = cpr::Post(cpr::Url(url),
                                  cpr::util::parseHeader(str_headers),
                                  cpr::Body(body));
    response = res.text;
    return res.status_code;
}

std::string Get(const std::string & u) {
    cpr::Response res = cpr::Get(cpr::Url(u));
    return res.text;
}

std::string UrlEncode(const std::string & text) {
    return cpr::util::urlEncode(text);
}
