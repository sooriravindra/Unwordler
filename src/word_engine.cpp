#include <random>

#include "app.h"

WordEngine::WordEngine() {
  wordBag_ = {"Hello", "World", "These", "Paper", "Nancy", "Still", "Layer"};
}
std::string WordEngine::GetWord(std::multiset<std::string>& amber_letters,
                                std::multiset<std::string>& green_letters) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distrib(
      0, wordBag_.size() - 1);
  auto index = distrib(rng);
  auto it = wordBag_.begin() + index;
  std::string x = *it;
  wordBag_.erase(it);
  return x;
}
