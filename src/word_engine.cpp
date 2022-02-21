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
  /* wordBag_ = std::move(WordEngine::ReadWordBagFromFile("../res/words.txt"));
   */
  wordBag_ = gWordList;
  possibleWords_ = wordBag_;
}

void WordEngine::Reset() { possibleWords_ = wordBag_; }

std::string WordEngine::GetWord(
    std::vector<char> &grey_letters,
    std::vector<std::pair<char, uint32_t>> &amber_letters,
    std::vector<std::pair<char, uint32_t>> &green_letters) {
  bool found = false;
  std::string s;
  auto it = possibleWords_.begin();
  while (!found) {
    found = true;
    /* it = GetRandWordIterator(); */
    it = GetLikelyWordIterator();
    if (it == possibleWords_.end()) {
      return "";
    }
    s = *it;
    for (auto c : grey_letters) {
      auto lambda = [&c](std::pair<char, uint32_t> p) { return p.first == c; };
      if ((std::find_if(amber_letters.begin(), amber_letters.end(), lambda) !=
           amber_letters.end()) ||
          std::find_if(green_letters.begin(), green_letters.end(), lambda) !=
              green_letters.end()) {
        continue;
      }
      if (std::count(s.begin(), s.end(), c) != 0) {
        std::string msg = "Grey letters";
        msg += c;
        RemoveWord(it, msg);
        found = false;
        break;
      }
    }
    if (!found) {
      continue;
    }

    for (auto c : amber_letters) {
      if (std::count(s.begin(), s.end(), c.first) == 0) {
        RemoveWord(it, "Amber letters");
        found = false;
        break;
      }
      if (s.at(c.second) == c.first) {
        RemoveWord(it, "Amber letters position");
        found = false;
        break;
      }
    }
    if (!found) {
      continue;
    }

    for (auto c : green_letters) {
      if (s.at(c.second) != c.first) {
        RemoveWord(it, "Green letters");
        found = false;
        break;
      }
    }
  }
  RemoveWord(it, "Chosen word");
  return s;
}

void WordEngine::RemoveWord(std::list<std::string>::iterator it,
                            std::string reason) {
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
