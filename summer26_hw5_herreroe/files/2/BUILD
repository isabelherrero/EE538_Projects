load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "CPPLib",
    srcs = ["q.cc"],
    hdrs = ["q.h"],
    copts = ["--std=c++17"],
    alwayslink = True,
    visibility = ["//visibility:public"],
)

cc_test(
    name = "student_test",
    srcs = glob(["student_test.cc"], allow_empty = True),
    copts = ["--std=c++17"],
    deps = [
        ":CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)
