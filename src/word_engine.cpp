#include <random>

#include "app.h"

WordEngine::WordEngine() {
  wordBag_ = {"Hello", "World", "These", "Paper", "Nancy", "Still",
              "Layer", "piper", "smile", "nouns", "blind"};
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
