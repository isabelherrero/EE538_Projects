load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "CPPLib",
    srcs = ["q.cc"],
    hdrs = ["q.h"],
    copts = ["--std=c++17"],
    alwayslink = True,
    visibility = ["//visibility:private"],
)

cc_test(
    name = "student_test",
    srcs = ["student_test.cc"],
    copts = ["--std=c++17"],
    deps = [
        ":CPPLib",
        "@googletest//:gtest_main",
    ],
)
