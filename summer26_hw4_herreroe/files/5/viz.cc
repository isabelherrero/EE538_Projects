// Q5: Emergency Room Triage Visualizer (cpptui front-end).
//
// This file turns the frames produced by BuildTriageFrames() into an
// interactive flip-book:
//
//   left / right : step backward / forward through the events
//   q            : quit
//
// Run it from the solution tree with:
//
//   bazel run //sol/5:viz
//
// In the generated student files, run it with:
//
//   bazel run //files/5:viz
//
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "cpptui.hpp"
#include "q.h"

namespace {

cpptui::Color AccentBlue() { return cpptui::Color{80, 150, 255}; }
cpptui::Color AccentGreen() { return cpptui::Color{80, 210, 130}; }
cpptui::Color AccentOrange() { return cpptui::Color{245, 170, 80}; }
cpptui::Color AccentRed() { return cpptui::Color{245, 100, 100}; }
cpptui::Color MutedText() { return cpptui::Color{170, 180, 190}; }
cpptui::Color PanelText() { return cpptui::Color{220, 225, 235}; }

cpptui::Cell MakeCell(const std::string& content, cpptui::Color fg,
                      bool bold = false) {
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

std::map<std::string, int> SeverityByName(const std::vector<Event>& events) {
  std::map<std::string, int> severity_by_name;
  for (const Event& event : events) {
    if (event.type == EventType::ARRIVE) {
      severity_by_name[event.name] = event.severity;
    }
  }
  return severity_by_name;
}

std::string FormatName(const std::string& name,
                       const std::map<std::string, int>& severity_by_name) {
  auto it = severity_by_name.find(name);
  if (it == severity_by_name.end()) return name;
  return name + " (" + std::to_string(it->second) + ")";
}

std::string JoinNames(const std::vector<std::string>& names,
                      const std::map<std::string, int>& severity_by_name) {
  if (names.empty()) return "(empty)";

  std::string result;
  for (int i = 0; i < static_cast<int>(names.size()); ++i) {
    if (i > 0) result += " -> ";
    result += FormatName(names[i], severity_by_name);
  }
  return result;
}

std::vector<Event> DemoScript() {
  return {
      Event(EventType::ARRIVE, "Alice", 3),
      Event(EventType::TREAT),
      Event(EventType::ARRIVE, "Bob", 10),
      Event(EventType::ARRIVE, "Chris", 5),
      Event(EventType::ARRIVE, "Dana", 10),
      Event(EventType::TREAT),
      Event(EventType::ARRIVE, "Eli", 7),
      Event(EventType::TREAT),
      Event(EventType::TREAT),
      Event(EventType::TREAT),
      Event(EventType::TREAT),
  };
}

std::string FormatEvent(const Event& event) {
  if (event.type == EventType::ARRIVE) {
    return "arrive(" + event.name +
           ", severity=" + std::to_string(event.severity) + ")";
  }
  return "treat()";
}

std::string CurrentEventLabel(const std::vector<Event>& events,
                              int frame_index) {
  if (frame_index == 0) return "(start state)";
  return FormatEvent(events[frame_index - 1]);
}

std::string NextEventLabel(const std::vector<Event>& events, int frame_index) {
  if (frame_index >= static_cast<int>(events.size())) return "(none)";
  return FormatEvent(events[frame_index]);
}

void DrawNameList(cpptui::Buffer& buffer, const std::vector<std::string>& names,
                  const std::map<std::string, int>& severity_by_name, int x,
                  int y, int w, int h, cpptui::Color color) {
  if (names.empty()) {
    PutText(buffer, x + 2, y + 2, "(empty)", MutedText());
    return;
  }

  const int row_limit = std::max(0, h - 3);
  for (int i = 0; i < static_cast<int>(names.size()) && i < row_limit; ++i) {
    std::string prefix = i == 0 ? "#1 " : "   ";
    std::string line = prefix + FormatName(names[i], severity_by_name);
    if (static_cast<int>(line.size()) > w - 4) {
      line = line.substr(0, std::max(0, w - 7)) + "...";
    }
    PutText(buffer, x + 2, y + 2 + i, line, i == 0 ? color : PanelText(),
            i == 0);
  }

  if (static_cast<int>(names.size()) > row_limit) {
    PutText(buffer, x + 2, y + h - 2,
            "+" + std::to_string(names.size() - row_limit) + " more",
            MutedText());
  }
}

class TriageView : public cpptui::Widget {
 public:
  TriageView()
      : events_(DemoScript()),
        severity_by_name_(SeverityByName(events_)),
        frames_(BuildTriageFrames(events_)),
        current_(0) {
    focusable = true;
    tab_stop = true;
  }

  void render(cpptui::Buffer& buffer) override {
    const int frame_w = std::min(width - 4, 96);
    const int frame_h = std::min(height - 3, 28);
    DrawBox(buffer, 2, 1, frame_w, frame_h, AccentBlue());
    PutText(buffer, 5, 1, " Q5: Emergency room triage ", AccentBlue(), true);

    PutText(buffer, 5, 3, "left/right to step through events, q to quit.",
            MutedText());

    const TriageFrame& frame = frames_[current_];
    PutText(buffer, 5, 5,
            "step " + std::to_string(current_) + " / " +
                std::to_string(frames_.size() - 1),
            AccentGreen(), true);
    PutText(buffer, 21, 5, "frame: " + frame.label, AccentOrange(), true);
    PutText(buffer, 5, 6,
            "current event: " + CurrentEventLabel(events_, current_),
            AccentOrange(), true);
    PutText(buffer, 5, 7, "next event: " + NextEventLabel(events_, current_),
            AccentGreen(), true);

    const int panel_y = 10;
    const int panel_h = std::min(12, frame_h - 13);
    const int panel_w = std::max(24, (frame_w - 12) / 2);
    const int waiting_x = 5;
    const int treated_x = waiting_x + panel_w + 4;

    DrawBox(buffer, waiting_x, panel_y, panel_w, panel_h, AccentOrange());
    PutText(buffer, waiting_x + 2, panel_y, " Waiting room ", AccentOrange(),
            true);
    DrawNameList(buffer, frame.waiting, severity_by_name_, waiting_x, panel_y,
                 panel_w, panel_h, AccentOrange());

    DrawBox(buffer, treated_x, panel_y, panel_w, panel_h, AccentGreen());
    PutText(buffer, treated_x + 2, panel_y, " Treated ", AccentGreen(), true);
    DrawNameList(buffer, frame.treated, severity_by_name_, treated_x, panel_y,
                 panel_w, panel_h, AccentGreen());

    const int summary_y = panel_y + panel_h + 2;
    PutText(buffer, 5, summary_y,
            "priority queue top: " +
                (frame.waiting.empty()
                     ? std::string("(none)")
                     : FormatName(frame.waiting.front(), severity_by_name_)),
            frame.waiting.empty() ? MutedText() : AccentRed(), true);
    PutText(buffer, 5, summary_y + 2,
            "waiting: " + JoinNames(frame.waiting, severity_by_name_),
            MutedText());
    PutText(buffer, 5, summary_y + 3,
            "treated: " + JoinNames(frame.treated, severity_by_name_),
            MutedText());
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
  std::vector<Event> events_;
  std::map<std::string, int> severity_by_name_;
  std::vector<TriageFrame> frames_;
  int current_;
};

}  // namespace

int main() {
  cpptui::Theme::set_theme(cpptui::Theme::TokyoNight());
  cpptui::App app;
  app.register_exit_key('q');
  app.run(std::make_shared<TriageView>());
  return 0;
}
