load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "CPPLib",
    srcs = ["q.cc"],
    hdrs = ["q.h"],
    alwayslink = True,
    visibility = ["//visibility:public"],
)

cc_test(
    name = "student_test",
    srcs = glob(["student_test.cc"], allow_empty = True),
    deps = [
        ":CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "viz",
    srcs = ["viz.cc"],
    tags = ["manual"],
    deps = [
        ":CPPLib",
        "//third_party/cpptui:cpptui",
    ],
)
