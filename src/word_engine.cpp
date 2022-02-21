#include <fstream>
#include <random>
#include <stdexcept>

#include "app.h"

std::set<std::string> WordEngine::InitWordBag() {
  std::set<std::string> s;
  std::ifstream wordsFile("../res/words.txt");
  std::string line;
  if (wordsFile.is_open()) {
    while (getline(wordsFile, line)) {
      s.insert(line);
    }
  } else {
    std::cout << "Failed to open words file" << std::endl;
  }
  return s;
}
WordEngine::WordEngine() {
  wordBag_ = std::move(WordEngine::InitWordBag());
  possibleWords_ = wordBag_;
}

void WordEngine::Reset() { possibleWords_ = wordBag_; }

std::string WordEngine::GetWord(
    std::vector<char> &grey_letters, std::vector<char> &amber_letters,
    std::vector<std::pair<char, uint32_t>> &green_letters) {
  bool found = false;
  std::string s;
  while (!found) {
    found = true;
    auto it = GetRandWordIterator();
    s = *it;
    for (auto c : grey_letters) {
      if (std::count(s.begin(),s.end(),c) != 0) {
          possibleWords_.erase(it);
          found = false;
          break;
      }
    }
    if (!found) continue;

    for (auto c: amber_letters) {
        if(std::count(s.begin(),s.end(),c) == 0) {
            possibleWords_.erase(it);
            found = false;
            break;
        }
    }
    if (!found) continue;

    for (auto c: green_letters) {
        if(s.at(c.second) != c.first) {
            possibleWords_.erase(it);
            found = false;
            break;
        }
    }
    if (!found) continue;

    possibleWords_.erase(it);
  }
  return s;
}

int WordEngine::GetRandom(uint32_t size) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distrib(0, size - 1);
  return distrib(rng);
}

std::set<std::string>::iterator WordEngine::GetRandWordIterator() {
  auto it = possibleWords_.begin();
  auto sz = possibleWords_.size();
  if (sz ==0)
  {
      std::cout << "possibleWords_ empty" << std::endl;
      exit(11);
  }
  std::advance(it, GetRandom(possibleWords_.size()));
  return it;
}
