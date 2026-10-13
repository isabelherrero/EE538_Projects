#ifndef EMERGENCY_ROOM_TRIAGE_H
#define EMERGENCY_ROOM_TRIAGE_H

#include <string>
#include <vector>
using namespace std;

/**
 * An emergency room receives a sequence of events.
 *
 * ARRIVE event:
 * A patient enters the waiting room with a name and severity score. Higher
 * severity means the patient should be treated sooner.
 *
 * TREAT event:
 * Treat exactly one patient from the current waiting room. The treated patient
 * should be the patient with the highest severity. If two waiting patients have
 * the same severity, treat the one who arrived earlier.
 *
 * Implement both functions below:
 *
 * 1. ProcessTriageEvents:
 *    Return the names of the patients in the order they are treated. If a
 *    TREAT event happens when no patient is waiting, ignore that event.
 *
 * 2. BuildTriageFrames:
 *    Build visualization frames that show how the waiting room and treated
 *    patient list change after each event.
 *    The provided viz.cc target uses this function to show an interactive
 *    visualization after you implement it.
 *
 * Use a priority queue ADT to solve this problem. Process the events in order:
 * insert patients when they arrive, check the most urgent waiting patient when
 * treatment happens, and remove that patient from the queue.
 *
 * Do not sort the full input list. Patients who arrive later must not affect
 * earlier TREAT events.
 *
 * Example:
 *
 * events = {
 *   Event(EventType::ARRIVE, "Alice", 3),
 *   Event(EventType::TREAT),
 *   Event(EventType::ARRIVE, "Bob", 10),
 *   Event(EventType::ARRIVE, "Chris", 5),
 *   Event(EventType::TREAT),
 *   Event(EventType::TREAT)
 * }
 *
 * Output: {"Alice", "Bob", "Chris"}
 *
 * Alice is treated first because Bob and Chris have not arrived yet when the
 * first TREAT event occurs.
 *
 * Hint:
 * A priority queue stores one type of object. You may find it helpful to create
 * a small helper struct that stores a patient's name, severity, and arrival
 * order. You may also need a custom comparator so the priority queue knows
 * which patient has the highest priority.
 * For ARRIVE events, push a patient into the priority queue. For TREAT events,
 * read and remove the current highest-priority patient if one exists.
 *
 * For BuildTriageFrames:
 * - The first frame is always the initial state:
 *   label = "start", waiting = {}, treated = {}.
 * - After every event, add one frame.
 * - waiting should show the current waiting room in treatment-priority order.
 * - treated should show patients already treated, in treatment order.
 *
 * Frame labels must match this format:
 * - start
 * - arrive(<name>, severity=<severity>)
 * - treat(<name>)
 * - treat() [empty]
 *
 * After implementing the functions, run the visualization target for this
 * question with Bazel to step through the frames.
 */
enum class EventType { ARRIVE, TREAT };

class Event {
 public:
  Event(EventType type, std::string name = "", int severity = 0)
      : type(type), name(name), severity(severity) {}

  EventType type;
  std::string name;
  int severity;
};

struct TriageFrame {
  std::string label;
  std::vector<std::string> waiting;
  std::vector<std::string> treated;
};

std::vector<std::string> ProcessTriageEvents(const std::vector<Event>& events);

std::vector<TriageFrame> BuildTriageFrames(const std::vector<Event>& events);

#endif  // EMERGENCY_ROOM_TRIAGE_H
