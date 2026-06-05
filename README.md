# CppKaiLanguage

The KAI surface languages, extracted from
[CppKAI](https://github.com/cschladetsch/CppKAI) as a reusable module
(including for Android):

- **Pi** - a postfix / reverse-Polish language.
- **Rho** - an infix language built on top of Pi.

## Dependencies

Downstream of [CppKaiCore](https://github.com/cschladetsch/CppKaiCore)
(Core + Executor + CommonLang). When building standalone, point `KAI_CORE_DIR`
at a CppKaiCore checkout (and `KAI_MONOTONIC_INCLUDE_DIR` at CppMonotonic, which
CppKaiCore needs).

## Building

Standalone:

    cmake -B build \
      -DKAI_CORE_DIR=/path/to/CppKaiCore \
      -DKAI_MONOTONIC_INCLUDE_DIR=/path/to/CppMonotonic
    cmake --build build

Or consume it from a parent project with `add_subdirectory(CppKaiLanguage)`,
which defines the `PiLang` and `RhoLang` targets with public include
directories.
