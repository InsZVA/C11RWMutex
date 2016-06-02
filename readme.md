# C++11 RWMutex

## Introduction

A RWMutex implement for C++ 11 cross platform, all reader are starve writers.

## Usage

Include and use it like:
```
    RWMutex m;
    m.rLock();
    m.wLock();
    m.wUnlock();
    m.rUnlock();
```