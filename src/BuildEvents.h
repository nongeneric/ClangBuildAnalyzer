// Clang Build Analyzer https://github.com/aras-p/ClangBuildAnalyzer
// SPDX-License-Identifier: Unlicense
#pragma once

#include <boost/bimap.hpp>

#include <stdint.h>
#include <string>
#include <vector>
#include <utility>

enum class BuildEventType
{
    kUnknown,
    kCompiler,
    kFrontend,
    kBackend,
    kParseFile,
    kParseTemplate,
    kParseClass,
    kInstantiateClass,
    kInstantiateFunction,
    kOptModule,
    kOptFunction,
};

struct DetailIndex
{
    int idx;
    explicit DetailIndex(int d = 0) : idx(d) {}
    bool operator==(DetailIndex rhs) const { return idx == rhs.idx; }
    bool operator!=(DetailIndex rhs) const { return idx != rhs.idx; }
    bool operator<(DetailIndex rhs) const { return idx < rhs.idx; }
    bool operator>(DetailIndex rhs) const { return idx > rhs.idx; }
    bool operator<=(DetailIndex rhs) const { return idx <= rhs.idx; }
    bool operator>=(DetailIndex rhs) const { return idx >= rhs.idx; }
};

struct EventIndex
{
    int idx;
    explicit EventIndex(int e = -1) : idx(e) {}
    bool operator==(EventIndex rhs) const { return idx == rhs.idx; }
    bool operator!=(EventIndex rhs) const { return idx != rhs.idx; }
    bool operator<(EventIndex rhs) const { return idx < rhs.idx; }
    bool operator>(EventIndex rhs) const { return idx > rhs.idx; }
    bool operator<=(EventIndex rhs) const { return idx <= rhs.idx; }
    bool operator>=(EventIndex rhs) const { return idx >= rhs.idx; }
};

namespace std
{
    template <> struct hash<DetailIndex>
    {
        size_t operator()(DetailIndex x) const
        {
            return hash<int>()(x.idx);
        }
    };
    template <> struct hash<EventIndex>
    {
        size_t operator()(EventIndex x) const
        {
            return hash<int>()(x.idx);
        }
    };
}

struct BuildEvent
{
    BuildEventType type = BuildEventType::kUnknown;
    int64_t ts = 0;
    int64_t dur = 0;
    DetailIndex detailIndex;
    EventIndex parent{ -1 };
    std::vector<EventIndex> children;
};

template <typename T, typename Idx>
struct IndexedVector : std::vector<T>
{
    using std::vector<T>::vector;
    typename std::vector<T>::reference       operator[](Idx pos) { return this->begin()[pos.idx]; }
    typename std::vector<T>::const_reference operator[](Idx pos) const { return this->begin()[pos.idx]; }
};
typedef boost::bimap<std::string, DetailIndex> BuildNames;
typedef IndexedVector<BuildEvent, EventIndex> BuildEvents;

void ParseBuildEvents(const std::string& fileName, std::string& jsonText, BuildEvents& outEvents, BuildNames& outNames);
