---
layout: default
title: Architecture
---

# CppKaiLanguage Architecture

## Language pipeline

Rho source transpiles to Pi; Pi is what the Executor (in CppKaiCore)
actually evaluates. Rho exists because most people, including Christian,
find infix syntax easier to write — Pi alone is genuinely usable directly
too, RPN-style, for anyone comfortable with a stack.

```mermaid
flowchart LR
    RhoSrc[Rho source<br/>infix] -- transpile --> PiSrc[Pi source<br/>postfix / RPN]
    PiSrc --> Eval[Executor<br/>CppKaiCore]
```

## Module dependency graph

`PiLang` and `RhoLang` are the two CMake targets this repo defines. Rho
depends on Pi (it lowers to it); both depend on CppKaiCore's `Core`,
`Executor`, and `CommonLang` targets, either as an existing target in a
parent build or via `add_subdirectory(KAI_CORE_DIR)` in a standalone build.

```mermaid
flowchart BT
    Core[Core] --> Executor[Executor]
    Core --> CommonLang[CommonLang]
    Executor --> PiLang[PiLang]
    CommonLang --> PiLang
    PiLang --> RhoLang[RhoLang]
    CommonLang --> RhoLang
    Executor --> RhoLang
```

## Build modes

```mermaid
flowchart TB
    subgraph Standalone
        A[cmake -DKAI_CORE_DIR=...] --> B[add_subdirectory KAI_CORE_DIR]
        B --> C[PiLang / RhoLang targets]
    end
    subgraph "Parent project (e.g. CppKAI)"
        D[add_subdirectory CppKaiLanguage] --> E["Core target already exists"]
        E --> F[PiLang / RhoLang targets]
    end
```
