#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <queue>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

namespace {

struct Patient {
  std::string name;
  int severity;
  long long arrival_order;
};

struct ComparePatients {
  bool operator()(const Patient& a, const Patient& b) const {
    if (a.severity != b.severity) {
      return a.severity < b.severity;
    }
    return a.arrival_order > b.arrival_order;
  }
};

using PatientQueue =
    std::priority_queue<Patient, std::vector<Patient>, ComparePatients>;
std::vector<std::string> ExtractWaitingOrder(PatientQueue queue) {
  std::vector<std::string> waiting;
  while (!queue.empty()) {
    waiting.push_back(queue.top().name);
    queue.pop();
  }
  return waiting;
}

}

std::vector<std::string> ProcessTriageEvents(const std::vector<Event>& events) {
  std::vector<std::string> result;
  PatientQueue queue;
  long long arrival_order = 0;

  for (const Event& event : events) {
    if (event.type == EventType::ARRIVE) {
      queue.push(Patient{event.name, event.severity, arrival_order++});
    } else {
      if (!queue.empty()) {
        result.push_back(queue.top().name);
        queue.pop();
      }
    }
  }

  return result;
}

std::vector<TriageFrame> BuildTriageFrames(const std::vector<Event>& events) {
  std::vector<TriageFrame> frames;
  frames.push_back(TriageFrame{"start", {}, {}});

  PatientQueue queue;
  std::vector<std::string> treated;
  long long arrival_order = 0;

  for (const Event& event : events) {
    std::string label;

    if (event.type == EventType::ARRIVE) {
      queue.push(Patient{event.name, event.severity, arrival_order++});
      label = "arrive(" + event.name +
              ", severity=" + std::to_string(event.severity) + ")";
    } else {
      if (!queue.empty()) {
        std::string treated_name = queue.top().name;
        queue.pop();
        treated.push_back(treated_name);
        label = "treat(" + treated_name + ")";
      } else {
        label = "treat() [empty]";
      }
    }

    TriageFrame frame;
    frame.label = label;
    frame.waiting = ExtractWaitingOrder(queue);
    frame.treated = treated;
    frames.push_back(frame);
  }

  return frames;
}