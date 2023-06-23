#include "serve_mux.hpp"
#include <iostream>

ServeMux::ServeMux(): m_(std::map<std::string, std::unique_ptr<Handler>>()) {}
void ServeMux::serve(WriterSPtr w, ReaderSPtr r) {
    m_["ask"]->serve(w, r);
}

void ServeMux::addHandle(const std::string & target, std::unique_ptr <Handler> handle) {
    m_.insert({target, std::move(handle)});
}
