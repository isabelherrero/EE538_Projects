load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "CCLib",
    hdrs = ["non_coding_q.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "non_coding_q",
    srcs = [
        "non_coding_q.cc",
    ],
    deps = [
        ":CCLib",
    ],
)
