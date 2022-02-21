#pragma once

#include <list>
#include <string>
#include <vector>

class WordEngine {
 public:
  WordEngine();
  void Reset();
  std::string GetWord(std::vector<char> &,
                      std::vector<std::pair<char, uint32_t>> &,
                      std::vector<std::pair<char, uint32_t>> &);
  std::list<std::string>::iterator GetRandWordIterator();
  std::list<std::string>::iterator GetLikelyWordIterator();
  int GetRandom(uint32_t size);
  void RemoveWord(std::list<std::string>::iterator it, std::string);

 private:
  std::list<std::string> ReadWordBagFromFile(std::string);
  std::list<std::string> wordBag_;
  std::list<std::string> possibleWords_;
};
