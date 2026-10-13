// Agentic C++ Lab 1 - Hash map visualizer.
//
// Run:
//
//   bazel run --cxxopt="-std=c++17" //files/4:viz
//
// left / right : step backward / forward
// q            : quit
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "cpptui.hpp"
#include "q.h"

namespace {

cpptui::Color AccentBlue() { return cpptui::Color{80, 150, 255}; }
cpptui::Color AccentGreen() { return cpptui::Color{80, 210, 130}; }
cpptui::Color AccentOrange() { return cpptui::Color{245, 170, 80}; }
cpptui::Color MutedText() { return cpptui::Color{170, 180, 190}; }

cpptui::Cell MakeCell(const std::string& content, cpptui::Color fg, bool bold) {
  cpptui::Cell cell;
  cell.content = content;
  cell.fg_color = fg;
  cell.bold = bold;
  return cell;
}

void PutText(cpptui::Buffer& buffer, int x, int y, const std::string& text,
             cpptui::Color fg = MutedText(), bool bold = false) {
  for (int i = 0; i < static_cast<int>(text.size()); ++i) {
    buffer.set(x + i, y, MakeCell(text.substr(i, 1), fg, bold));
  }
}

void DrawBox(cpptui::Buffer& buffer, int x, int y, int w, int h,
             cpptui::Color color) {
  if (w < 2 || h < 2) return;
  for (int dx = 1; dx < w - 1; ++dx) {
    buffer.set(x + dx, y, MakeCell("-", color, true));
    buffer.set(x + dx, y + h - 1, MakeCell("-", color, true));
  }
  for (int dy = 1; dy < h - 1; ++dy) {
    buffer.set(x, y + dy, MakeCell("|", color, true));
    buffer.set(x + w - 1, y + dy, MakeCell("|", color, true));
  }
  buffer.set(x, y, MakeCell("+", color, true));
  buffer.set(x + w - 1, y, MakeCell("+", color, true));
  buffer.set(x, y + h - 1, MakeCell("+", color, true));
  buffer.set(x + w - 1, y + h - 1, MakeCell("+", color, true));
}

std::vector<HashCommand> DemoScript() {
  // clang-format off
  return {
      {"insert", "alpha", 1, 0},
      {"insert", "beta", 2, 0},
      {"insert", "gamma", 3, 0},
      {"insert", "alpha", 9, 0},
      {"erase", "beta", 0, 0},
      {"erase", "missing", 0, 0},
      {"rehash", "", 0, 8},
      {"insert", "delta", 4, 0},
      {"rehash", "", 0, 0},
  };
  // clang-format on
}

std::vector<HashMapFrame> DemoFrames() {
  std::vector<HashMapFrame> frames = BuildHashMapFrames(DemoScript(), 4);
  if (!frames.empty()) {
    return frames;
  }

  HashMapFrame fallback;
  fallback.label = "no frames yet; implement BuildHashMapFrames";
  fallback.buckets.resize(1);
  fallback.size = 0;
  return {fallback};
}

std::string NextOperationLabel(const std::vector<HashMapFrame>& frames,
                               int current) {
  if (current + 1 >= static_cast<int>(frames.size())) {
    return "(done)";
  }
  return frames[current + 1].label;
}

class HashMapView : public cpptui::Widget {
 public:
  HashMapView() : frames_(DemoFrames()), current_(0) {
    focusable = true;
    tab_stop = true;
  }

  void render(cpptui::Buffer& buffer) override {
    DrawBox(buffer, 2, 1, std::min(width - 4, 96), std::min(height - 3, 30),
            AccentBlue());
    PutText(buffer, 5, 1, " Agentic Lab 1: vector-bucket hash map ",
            AccentBlue(), true);
    PutText(buffer, 5, 3, "left/right to step through operations, q to quit.",
            MutedText());

    const HashMapFrame& frame = frames_[current_];
    PutText(buffer, 5, 5,
            "step " + std::to_string(current_) + " / " +
                std::to_string(frames_.size() - 1),
            AccentGreen(), true);
    PutText(buffer, 20, 5, "size = " + std::to_string(frame.size),
            AccentGreen(), true);
    PutText(buffer, 34, 5, "buckets = " + std::to_string(frame.buckets.size()),
            AccentGreen(), true);
    PutText(buffer, 5, 7, "current operation: " + frame.label, AccentOrange(),
            true);
    PutText(buffer, 5, 8, "next operation: " +
                             NextOperationLabel(frames_, current_),
            MutedText(), true);

    const int start_x = 5;
    const int start_y = 11;
    const int bucket_h = 3;
    const int bucket_gap = 1;
    for (int i = 0; i < static_cast<int>(frame.buckets.size()); ++i) {
      const int y = start_y + i * (bucket_h + bucket_gap);
      if (y + bucket_h >= height - 1) break;

      DrawBox(buffer, start_x, y, 12, bucket_h, AccentBlue());
      PutText(buffer, start_x + 2, y + 1, "bucket " + std::to_string(i),
              AccentBlue(), true);

      int x = start_x + 15;
      for (const auto& entry : frame.buckets[i]) {
        const std::string text =
            "[" + entry.key + ":" + std::to_string(entry.value) + "]";
        PutText(buffer, x, y + 1, text, AccentOrange(), true);
        x += static_cast<int>(text.size()) + 2;
      }
      if (frame.buckets[i].empty()) {
        PutText(buffer, x, y + 1, "(empty)", MutedText());
      }
    }
  }

  bool on_event(const cpptui::Event& event) override {
    if (!event.is_key_event()) return false;
    if (event.is_nav_left() && current_ > 0) {
      --current_;
      return true;
    }
    if (event.is_nav_right() &&
        current_ + 1 < static_cast<int>(frames_.size())) {
      ++current_;
      return true;
    }
    return false;
  }

 private:
  std::vector<HashMapFrame> frames_;
  int current_;
};

}  // namespace

int main() {
  cpptui::Theme::set_theme(cpptui::Theme::TokyoNight());
  cpptui::App app;
  app.register_exit_key('q');
  app.run(std::make_shared<HashMapView>());
  return 0;
}
