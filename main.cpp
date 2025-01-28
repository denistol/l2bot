#include <fmt/core.h>
#include <fmt/chrono.h>

int main() {
  auto now = std::chrono::system_clock::now();
  fmt::print("Date and ti2me: {}\n", now);
  fmt::print("Time: {:%H:%M}\n", now);
}