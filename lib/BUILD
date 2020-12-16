cc_library(
    name = "crowd_safety",
    hdrs = ["crowd_safety.hpp"],
    srcs = ['crowd_safety.cpp'],
    deps = [
	"@fcpp//lib:data",
        "//lib:logic_samples",
    ],
    visibility = [
        '//visibility:public',
    ],
)

cc_library(
    name = "drones_recognition",
    hdrs = ["drones_recognition.hpp"],
    srcs = ['drones_recognition.cpp'],
    deps = [
	"@fcpp//lib:data",
        "//lib:logic_samples",
    ],
    visibility = [
        '//visibility:public',
    ],
)

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

cc_library(
    name = "smart_home",
    hdrs = ["smart_home.hpp"],
    srcs = ['smart_home.cpp'],
    deps = [
	"@fcpp//lib:data",
        "//lib:logic_samples",
    ],
    visibility = [
        '//visibility:public',
    ],
)
