#include "serve_mux.hpp"

ServeMux::ServeMux(): m_(std::map<std::string, std::unique_ptr<Handler>>()) {}
void ServeMux::serve(WriterSPtr w, ReaderSPtr r) {
    std::string target;
    r->read(target);
    if (m_.find(target) == m_.end()) {
         w->write("target not found");
    } else {
        m_[target]->serve(w, r);
    }
}

void ServeMux::addHandle(const std::string & url, std::unique_ptr <Handler> handle) {
    m_.insert({url, std::move(handle)});
}
