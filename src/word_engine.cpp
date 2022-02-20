#include <random>
#include <fstream>
#include "app.h"

std::vector<std::string> WordEngine::InitWordBag(){
    std::vector<std::string> v;
    std::ifstream wordsFile("../res/words.txt");
    std::string line;
    if (wordsFile.is_open()) {
       while(getline(wordsFile, line)) {
           v.push_back(line);
       }
    }
    else {
        std::cout << "Failed to open words file" << std::endl;
    }
    return v;
}
WordEngine::WordEngine() {
  wordBag_ = std::move(WordEngine::InitWordBag());
  possibleWords_ = wordBag_;
}

void WordEngine::Reset() { possibleWords_ = wordBag_; }

std::string WordEngine::GetWord(std::vector<char> &amber_letters,
                                std::vector<char> &green_letters) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distrib(
      0, possibleWords_.size() - 1);
  auto index = distrib(rng);
  auto it = possibleWords_.begin() + index;
  if (it >= possibleWords_.end()) return "";
  std::string x = *it;
  possibleWords_.erase(it);
  return x;
}
