#include <optional>
#include <regex>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include "doctest/doctest.h"
#include "utility.hpp"

// parser url
// https://developer.mozilla.org/en-US/docs/Learn/Common_questions/What_is_a_URL
auto parse_url(std::string&& raw_url) {
  struct url_t {
    std::string scheme;
    std::string domain;
    std::optional<unsigned int> port;
    std::optional<std::string> resource;
    // std::optional<std::pair<std::string, std::string>> parameters;
    std::optional<std::string> parameters;
    std::optional<std::string> tag;
  };

  url_t url;
  const std::regex pattern(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?(\/([\w\/\.-]+))?(\?([\w=&-]*))?(#(\w+))?$)");
  std::smatch matches;
  if (std::regex_search(raw_url, matches, pattern)) {
    url.scheme = matches[1].str();
    url.domain = matches[2].str();

    if (matches[4].matched) {
      url.port = std::make_optional(std::stoi(matches[4].str()));
    }

    if (matches[6].matched) {
      url.resource = std::make_optional(matches[6].str());
    }

    if (matches[8].matched) {
      url.parameters = std::make_optional(matches[8].str());
    }

    if (matches[10].matched) {
      url.tag = std::make_optional(matches[10].str());
    }
  }
  return url;
}

TEST_CASE(util::problem_name().data()) {
  {
    const auto url = parse_url("http://www.example.com:80/path/to/file.html?key1=value1&key2=value2#tag");

    CHECK(url.scheme == "http");
    CHECK(url.domain == "www.example.com");
    CHECK(url.port == 80);
    CHECK(url.resource == "path/to/file.html");
    CHECK(url.parameters == "key1=value1&key2=value2");
    CHECK(url.tag == "tag");
  }

  {
    const auto url = parse_url("http://www.example.com/path/to/file.html?key1=value1&key2=value2#tag");

    CHECK(url.scheme == "http");
    CHECK(url.domain == "www.example.com");
    CHECK(!url.port);
    CHECK(url.resource == "path/to/file.html");
    CHECK(url.parameters == "key1=value1&key2=value2");
    CHECK(url.tag == "tag");
  }

  {
    const auto url = parse_url("http://www.example.com/path/to/file.html?key1=value1&key2=value2");

    CHECK(url.scheme == "http");
    CHECK(url.domain == "www.example.com");
    CHECK(!url.port);
    CHECK(url.resource == "path/to/file.html");
    CHECK(url.parameters == "key1=value1&key2=value2");
    CHECK(!url.tag);
  }

  {
    const auto url = parse_url("http://www.example.com/path/to/file.html");

    CHECK(url.scheme == "http");
    CHECK(url.domain == "www.example.com");
    CHECK(!url.port);
    CHECK(url.resource == "path/to/file.html");
    CHECK(!url.parameters);
    CHECK(!url.tag);
  }

  {
    const auto url = parse_url("http://www.example.com");

    CHECK(url.scheme == "http");
    CHECK(url.domain == "www.example.com");
    CHECK(!url.port);
    CHECK(!url.resource);
    CHECK(!url.parameters);
    CHECK(!url.tag);
  }
}