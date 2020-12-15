cc_library(
    name = "logic_samples",
    hdrs = ["logic_samples.hpp"],
    srcs = ['logic_samples.cpp'],
    deps = [
        "//lib:past_ctl",
    ],
    visibility = [
        '//visibility:public',
    ],
)

cc_library(
    name = "past_ctl",
    hdrs = ["past_ctl.hpp"],
    srcs = ['past_ctl.cpp'],
    deps = [
        "@fcpp//lib:beautify",
        "@fcpp//lib/coordination:utils",
    ],
    visibility = [
        '//visibility:public',
    ],
)
