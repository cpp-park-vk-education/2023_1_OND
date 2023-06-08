#pragma once
#include <string>
#include <boost/serialization/map.hpp>
#include <map>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>
#include <iostream>


struct Package {

  std::string text;
  std::string voice;
  std::map <std::string, std::string> param;
  bool finish;


  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar & text;
    ar & voice;
    ar & finish;
    ar & param;
  }
};
