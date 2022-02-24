#include "word_engine.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

#include "word_bag.h"

std::list<std::string> WordEngine::ReadWordBagFromFile(std::string file_name) {
  std::list<std::string> s;
  std::ifstream wordsFile(file_name);
  std::string line;
  if (wordsFile.is_open()) {
    while (getline(wordsFile, line)) {
      s.push_back(line);
    }
  } else {
    std::cout << "Failed to open words file" << std::endl;
  }
  return s;
}
WordEngine::WordEngine() {
  /* wordBag_ = WordEngine::ReadWordBagFromFile("../res/words.txt");
   */
  wordBag_ = gWordList;
  possibleWords_ = wordBag_;
}

void WordEngine::Reset() { possibleWords_ = wordBag_; }

bool PruneUsingGreyLettters(
    const std::string &s, const std::vector<char> &grey_letters,
    const std::vector<std::pair<char, uint32_t>> &amber_letters,
    const std::vector<std::pair<char, uint32_t>> &green_letters) {
  for (auto c : grey_letters) {
    auto lambda = [&c](std::pair<char, uint32_t> p) { return p.first == c; };

    if ((std::find_if(amber_letters.begin(), amber_letters.end(), lambda) !=
         amber_letters.end()) ||
        std::find_if(green_letters.begin(), green_letters.end(), lambda) !=
            green_letters.end()) {
      continue;
    }
    if (std::count(s.begin(), s.end(), c) != 0) {
      return true;
    }
  }
  return false;
}

bool PruneUsingAmberLetters(
    const std::string &s,
    const std::vector<std::pair<char, uint32_t>> &amber_letters) {
  return std::any_of(amber_letters.begin(), amber_letters.end(), [&s](auto c) {
    return ((s.at(c.second) == c.first) ||
            (std::count(s.begin(), s.end(), c.first) == 0));
  });
}

bool PruneUsingGreenLetters(
    const std::string &s,
    const std::vector<std::pair<char, uint32_t>> &green_letters) {
  return std::any_of(green_letters.begin(), green_letters.end(),
                     [&s](auto c) { return (s.at(c.second) != c.first); });
}

std::string WordEngine::GetWord(
    const std::vector<char> &grey_letters,
    const std::vector<std::pair<char, uint32_t>> &amber_letters,
    const std::vector<std::pair<char, uint32_t>> &green_letters) {
  std::string s;
  auto it = possibleWords_.begin();
  while (true) {
    /* it = GetRandWordIterator(); */
    it = GetLikelyWordIterator();
    if (it == possibleWords_.end()) {
      return "";
    }
    s = *it;
    if (PruneUsingGreyLettters(s, grey_letters, amber_letters, green_letters)) {
      RemoveWord(it);
      continue;
    }

    if (PruneUsingAmberLetters(s, amber_letters)) {
      RemoveWord(it);
      continue;
    }

    if (PruneUsingGreenLetters(s, green_letters)) {
      RemoveWord(it);
      continue;
    }
    break;
  }
  RemoveWord(it);
  return s;
}

void WordEngine::RemoveWord(std::list<std::string>::iterator it) {
  possibleWords_.erase(it);
}

int WordEngine::GetRandom(uint32_t size) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distrib(0, size - 1);
  return distrib(rng);
}

std::list<std::string>::iterator WordEngine::GetRandWordIterator() {
  auto it = possibleWords_.begin();
  auto sz = possibleWords_.size();
  if (sz == 0) {
    std::cout << "Out of words!!" << std::endl;
    return possibleWords_.end();
  }
  std::advance(it, GetRandom(possibleWords_.size()));
  return it;
}

std::list<std::string>::iterator WordEngine::GetLikelyWordIterator() {
  if (possibleWords_.empty()) {
    std::cout << "Out of words!!" << std::endl;
    return possibleWords_.end();
  }
  return possibleWords_.begin();
}
