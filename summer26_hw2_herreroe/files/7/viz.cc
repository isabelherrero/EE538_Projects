// HW2 - Q7: Dynamic Array Visualizer (cpptui front-end).
//
// This file is PROVIDED. It turns the frames produced by BuildFrames() into an
// interactive flip-book:
//
//   left / right : step backward / forward through the operations
//   q            : quit
//
// You do not need to edit this file to pass the grader; it only depends on the
// BuildFrames() function you implement in q.cc. Run it with:
//
//   bazel run //sol/7:viz
//
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

// A small demo script that exercises every operation, including the no-op
// (out-of-range / empty) cases.
std::vector<Command> DemoScript() {
  return {
      {"push_back", 12, 0}, {"push_back", 7, 0},  {"push_back", 19, 0},
      {"insert", 99, 1},    {"insert", 5, 0},     {"erase", 0, 2},
      {"pop_back", 0, 0},   {"erase", 0, 9},      {"insert", 42, 50},
      {"pop_back", 0, 0},   {"pop_back", 0, 0},   {"pop_back", 0, 0},
      {"pop_back", 0, 0},
  };
}

class FlipBookView : public cpptui::Widget {
 public:
  FlipBookView() : frames_(BuildFrames(DemoScript())), current_(0) {
    focusable = true;
    tab_stop = true;
  }

  void render(cpptui::Buffer& buffer) override {
    DrawBox(buffer, 2, 1, std::min(width - 4, 88), std::min(height - 3, 24),
            AccentBlue());
    PutText(buffer, 5, 1, " 07: Dynamic array flip-book ", AccentBlue(), true);

    PutText(buffer, 5, 3,
            "left/right to step through the operations, q to quit.",
            MutedText());

    const Frame& frame = frames_[current_];

    PutText(buffer, 5, 5,
            "step " + std::to_string(current_) + " / " +
                std::to_string(frames_.size() - 1),
            AccentGreen(), true);
    PutText(buffer, 20, 5, "size = " + std::to_string(frame.values.size()),
            AccentGreen(), true);

    PutText(buffer, 5, 7, "operation: " + frame.label, AccentOrange(), true);

    // Draw each element as a boxed cell, with its index underneath.
    const int start_x = 7;
    const int cell_y = 10;
    const int cell_w = 8;
    for (int i = 0; i < static_cast<int>(frame.values.size()); ++i) {
      const int x = start_x + i * cell_w;
      DrawBox(buffer, x, cell_y, cell_w - 1, 5, AccentBlue());
      PutText(buffer, x + 2, cell_y + 2, std::to_string(frame.values[i]),
              AccentBlue(), true);
      PutText(buffer, x + 1, cell_y + 6, "[" + std::to_string(i) + "]",
              MutedText());
    }
    if (frame.values.empty()) {
      PutText(buffer, start_x, cell_y + 2, "(empty array)", MutedText());
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
  std::vector<Frame> frames_;
  int current_;
};

}  // namespace

int main() {
  cpptui::Theme::set_theme(cpptui::Theme::TokyoNight());
  cpptui::App app;
  app.register_exit_key('q');
  app.run(std::make_shared<FlipBookView>());
  return 0;
}
