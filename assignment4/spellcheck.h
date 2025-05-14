#pragma once

#include <set>
#include <string>
#include <unordered_set>

struct Token {
  /*
   * for example, the string "Hello, world!" would be split into:
   *   "Hello" -> src_offset = 0
   *   ","     -> src_offset = 5
   *  "world" -> src_offset = 7
   *  "!"     -> src_offset = 12
   */
  std::string content;  // split string
  size_t src_offset;    // offset in the source string

  template <typename It>
  Token(std::string& source, It begin, It end)
      : src_offset{static_cast<std::size_t>(
            std::distance(source.begin(), begin))},
        content{std::string(begin, end)} {
    clean(source);
  }

 private:
  void clean(const std::string& source);
};

struct Misspelling {
  Token token;
  std::set<std::string> suggestions;
};

using Corpus = std::set<Token>;
using Dictionary = std::unordered_set<std::string>;

Corpus tokenize(std::string& input);
std::set<Misspelling> spellcheck(const Corpus& source,
                                 const Dictionary& dictionary);

/* Helper methods */

size_t levenshtein(const std::string&, const std::string&);
bool operator<(const Token&, const Token&);
bool operator<(const Misspelling&, const Misspelling&);
