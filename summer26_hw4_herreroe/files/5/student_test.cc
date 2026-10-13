#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(ProcessTriageEventsTest, SpecExample) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "Alice", 3), Event(EventType::TREAT),
      Event(EventType::ARRIVE, "Bob", 10),  Event(EventType::ARRIVE, "Chris", 5),
      Event(EventType::TREAT),              Event(EventType::TREAT)};
  std::vector<std::string> expected = {"Alice", "Bob", "Chris"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(ProcessTriageEventsTest, EmptyEventListReturnsEmpty) {
  std::vector<Event> events = {};
  EXPECT_EQ(ProcessTriageEvents(events), std::vector<std::string>{});
}

TEST(ProcessTriageEventsTest, TreatWithNoOneWaitingIsIgnored) {
  std::vector<Event> events = {Event(EventType::TREAT)};
  EXPECT_EQ(ProcessTriageEvents(events), std::vector<std::string>{});
}

TEST(ProcessTriageEventsTest, ExtraTreatsBeyondAvailablePatientsAreIgnored) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "A", 1),
      Event(EventType::TREAT),
      Event(EventType::TREAT),
      Event(EventType::TREAT)
  };
  std::vector<std::string> expected = {"A"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(ProcessTriageEventsTest, OnlyArrivalsNoTreatments) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "A", 1),
                                Event(EventType::ARRIVE, "B", 2)};
  EXPECT_EQ(ProcessTriageEvents(events), std::vector<std::string>{});
}

TEST(ProcessTriageEventsTest, TieSeverityTreatsEarlierArrivalFirst) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "First", 5),
      Event(EventType::ARRIVE, "Second", 5),
      Event(EventType::ARRIVE, "Third", 5),
      Event(EventType::TREAT), Event(EventType::TREAT),
      Event(EventType::TREAT)};
  std::vector<std::string> expected = {"First", "Second", "Third"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(ProcessTriageEventsTest, MixedTiesAndDistinctSeverities) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "A", 5), Event(EventType::ARRIVE, "B", 9),
      Event(EventType::ARRIVE, "C", 5), Event(EventType::ARRIVE, "D", 9),
      Event(EventType::TREAT),
      Event(EventType::TREAT),
      Event(EventType::TREAT),
      Event(EventType::TREAT)
  };
  std::vector<std::string> expected = {"B", "D", "A", "C"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(ProcessTriageEventsTest, PatientsArrivingLaterDoNotAffectEarlierTreats) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "Alice", 3), Event(EventType::TREAT),
      Event(EventType::ARRIVE, "MoreUrgent", 100)};
  std::vector<std::string> expected = {"Alice"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(ProcessTriageEventsTest, ZeroAndNegativeSeveritiesAreValid) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "Zero", 0), Event(EventType::ARRIVE, "Neg", -5),
      Event(EventType::TREAT), Event(EventType::TREAT)};
  std::vector<std::string> expected = {"Zero", "Neg"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(ProcessTriageEventsTest, SinglePatientArriveAndTreat) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "Solo", 7),
                                Event(EventType::TREAT)};
  std::vector<std::string> expected = {"Solo"};
  EXPECT_EQ(ProcessTriageEvents(events), expected);
}

TEST(BuildTriageFramesTest, EmptyEventListProducesOnlyStartFrame) {
  std::vector<Event> events = {};
  auto frames = BuildTriageFrames(events);
  ASSERT_EQ(frames.size(), 1u);
  EXPECT_EQ(frames[0].label, "start");
  EXPECT_TRUE(frames[0].waiting.empty());
  EXPECT_TRUE(frames[0].treated.empty());
}

TEST(BuildTriageFramesTest, TreatWithNoOneWaitingProducesEmptyTreatLabel) {
  std::vector<Event> events = {Event(EventType::TREAT)};
  auto frames = BuildTriageFrames(events);
  ASSERT_EQ(frames.size(), 2u);
  EXPECT_EQ(frames[1].label, "treat() [empty]");
  EXPECT_TRUE(frames[1].waiting.empty());
  EXPECT_TRUE(frames[1].treated.empty());
}

TEST(BuildTriageFramesTest, OneFramePerEventPlusStart) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "A", 1),
                                Event(EventType::ARRIVE, "B", 2),
                                Event(EventType::TREAT)};
  auto frames = BuildTriageFrames(events);
  EXPECT_EQ(frames.size(), events.size() + 1);
}

TEST(BuildTriageFramesTest, ArriveFrameLabelFormat) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "Alice", 3)};
  auto frames = BuildTriageFrames(events);
  ASSERT_EQ(frames.size(), 2u);
  EXPECT_EQ(frames[1].label, "arrive(Alice, severity=3)");
  EXPECT_EQ(frames[1].waiting, (std::vector<std::string>{"Alice"}));
  EXPECT_TRUE(frames[1].treated.empty());
}

TEST(BuildTriageFramesTest, TreatFrameLabelIncludesPatientName) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "Alice", 3),
                                Event(EventType::TREAT)};
  auto frames = BuildTriageFrames(events);
  ASSERT_EQ(frames.size(), 3u);
  EXPECT_EQ(frames[2].label, "treat(Alice)");
  EXPECT_TRUE(frames[2].waiting.empty());
  EXPECT_EQ(frames[2].treated, (std::vector<std::string>{"Alice"}));
}

TEST(BuildTriageFramesTest, FullSpecExampleFrameBySFrame) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "Alice", 3), Event(EventType::TREAT),
      Event(EventType::ARRIVE, "Bob", 10),  Event(EventType::ARRIVE, "Chris", 5),
      Event(EventType::TREAT),              Event(EventType::TREAT)};
  auto frames = BuildTriageFrames(events);
  ASSERT_EQ(frames.size(), 7u);

  EXPECT_EQ(frames[0].label, "start");
  EXPECT_TRUE(frames[0].waiting.empty());
  EXPECT_TRUE(frames[0].treated.empty());

  EXPECT_EQ(frames[1].label, "arrive(Alice, severity=3)");
  EXPECT_EQ(frames[1].waiting, (std::vector<std::string>{"Alice"}));
  EXPECT_TRUE(frames[1].treated.empty());

  EXPECT_EQ(frames[2].label, "treat(Alice)");
  EXPECT_TRUE(frames[2].waiting.empty());
  EXPECT_EQ(frames[2].treated, (std::vector<std::string>{"Alice"}));

  EXPECT_EQ(frames[3].label, "arrive(Bob, severity=10)");
  EXPECT_EQ(frames[3].waiting, (std::vector<std::string>{"Bob"}));

  EXPECT_EQ(frames[4].label, "arrive(Chris, severity=5)");
  EXPECT_EQ(frames[4].waiting, (std::vector<std::string>{"Bob", "Chris"}));

  EXPECT_EQ(frames[5].label, "treat(Bob)");
  EXPECT_EQ(frames[5].waiting, (std::vector<std::string>{"Chris"}));
  EXPECT_EQ(frames[5].treated, (std::vector<std::string>{"Alice", "Bob"}));

  EXPECT_EQ(frames[6].label, "treat(Chris)");
  EXPECT_TRUE(frames[6].waiting.empty());
  EXPECT_EQ(frames[6].treated,
            (std::vector<std::string>{"Alice", "Bob", "Chris"}));
}

TEST(BuildTriageFramesTest, WaitingRoomIsInTreatmentPriorityOrder) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "Low", 1),
                                Event(EventType::ARRIVE, "High", 9),
                                Event(EventType::ARRIVE, "Mid", 5)};
  auto frames = BuildTriageFrames(events);
  EXPECT_EQ(frames.back().waiting,
            (std::vector<std::string>{"High", "Mid", "Low"}));
}

TEST(BuildTriageFramesTest, WaitingRoomTieBreaksByEarlierArrival) {
  std::vector<Event> events = {Event(EventType::ARRIVE, "First", 5),
                                Event(EventType::ARRIVE, "Second", 5)};
  auto frames = BuildTriageFrames(events);
  EXPECT_EQ(frames.back().waiting,
            (std::vector<std::string>{"First", "Second"}));
}

TEST(BuildTriageFramesTest, TreatedListGrowsInTreatmentOrderNotArrivalOrder) {
  std::vector<Event> events = {
      Event(EventType::ARRIVE, "Low", 1), Event(EventType::ARRIVE, "High", 9),
      Event(EventType::TREAT),            Event(EventType::TREAT)};
  auto frames = BuildTriageFrames(events);
  EXPECT_EQ(frames.back().treated,
            (std::vector<std::string>{"High", "Low"}));
}