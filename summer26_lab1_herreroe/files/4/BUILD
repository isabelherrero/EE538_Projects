load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "CPPLib",
    srcs = ["q.cc"],
    hdrs = ["q.h"],
    visibility = ["//visibility:private"],
)

cc_test(
    name = "student_test",
    srcs = ["student_test.cc"],
    deps = [
        ":CPPLib",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "viz",
    srcs = ["viz.cc"],
    copts = ["-std=c++17"],
    deps = [
        ":CPPLib",
        "//third_party/cpptui:cpptui",
    ],
)
