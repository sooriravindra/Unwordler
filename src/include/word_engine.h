#pragma once

#include <list>
#include <string>
#include <vector>

class WordEngine {
 public:
  WordEngine();
  void Reset();
  std::string GetWord(const std::vector<char> &,
                      const std::vector<std::pair<char, uint32_t>> &,
                      const std::vector<std::pair<char, uint32_t>> &);
  std::list<std::string>::iterator GetRandWordIterator();
  std::list<std::string>::iterator GetLikelyWordIterator();
  static int GetRandom(uint32_t size);
  void RemoveWord(std::list<std::string>::iterator it);

 private:
  static std::list<std::string> ReadWordBagFromFile(std::string);
  std::list<std::string> wordBag_;
  std::list<std::string> possibleWords_;
};
