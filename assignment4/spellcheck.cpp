#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  // 1. Identify all iterators to space characters
  auto is_space = [&](char c) { return std::isspace(c); };
  auto space_iterators = find_all(source.begin(), source.end(), is_space);
  // std::cout << space_iterators.size() << " spaces found" << std::endl;
  // 2. Generate tokens between consecutive space characters
  std::set<Token> tokens;
  auto inserter = std::inserter(tokens, tokens.end());
  auto token_binary_op = [&](auto it1, auto it2) {
    return Token(source, it1, it2);
  };

  std::transform(space_iterators.begin(), std::prev(space_iterators.end()),
                 std::next(space_iterators.begin()), inserter, token_binary_op);
  // 3. Get rid of empty tokens
  auto empty_token_pred = [](const Token& t) { return t.content.empty(); };
  std::erase_if(tokens, empty_token_pred);

  Corpus result;
  std::copy(tokens.begin(), tokens.end(), std::inserter(result, result.end()));
  return result;
}

std::set<Misspelling> spellcheck(const Corpus& source,
                                 const Dictionary& dictionary) {
  // 1. Skip words that are already correctly spelled.
  namespace rv = std::ranges::views;
  auto is_not_correct = [&](const Token& t) {
    return !dictionary.contains(t.content);
  };
  // 2. Find one-edit-away words in the dictionary using Damerau-Levenshtein
  auto is_one_edit_away = [&](const Token& t) {
    auto is_suggestion = [&](const std::string& s) {
      return levenshtein(t.content, s) == 1;
    };
    auto suggestions_set = dictionary | rv::filter(is_suggestion);
    std::set<std::string> suggestions(suggestions_set.begin(),
                                      suggestions_set.end());
    return Misspelling{t, suggestions};
  };
  auto misspelling_view =
      source | rv::filter(is_not_correct) | rv::transform(is_one_edit_away);
  // 3. Drop misspelled with no suggestions
  auto has_suggestions = [&](const Misspelling& m) {
    return !m.suggestions.empty();
  };

  auto misspellings_with_suggestions =
      misspelling_view | rv::filter(has_suggestions);
  std::set<Misspelling> misspellings(misspellings_with_suggestions.begin(),
                                     misspellings_with_suggestions.end());
  return misspellings;
};

/* Helper methods */

#include "utils.cpp"
