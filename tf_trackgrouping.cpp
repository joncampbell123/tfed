
#include <stdio.h>

#include "tf_trackgrouping.h"

TFTrackGroupingList::TFTrackGroupingList() : TFTrackGroupingListBaseType() {
}

TFTrackGroupingList::~TFTrackGroupingList() {
    TFTrackGroupingList::clear();
}

void TFTrackGroupingList::clear(void) {
    do {
        auto i = TFTrackGroupingList::begin();
        if (i == TFTrackGroupingList::end()) break;
        TFTrackGroupingList::erase(i);
    } while (1);
}

TFTrackGrouping& TFTrackGroupingList::create(const std::string &name) {
    if (name.empty()) throw std::runtime_error("create: empty name");

    auto i = TFTrackGroupingList::find(name);
    if (i != TFTrackGroupingList::end()) throw std::runtime_error("create: sequence already exists");

    return TFTrackGroupingListBaseType::operator[](name); /* poof */
}

TFTrackGrouping& TFTrackGroupingList::operator[](const std::string &name) {
    if (name.empty()) throw std::runtime_error("[]: empty name");

    auto i = TFTrackGroupingListBaseType::find(name);
    if (i == TFTrackGroupingListBaseType::end()) throw std::runtime_error("[]: sequence does not exist");

    return i->second;
}

TFTrackGroupingListIterator TFTrackGroupingList::begin(void) {
    return TFTrackGroupingListBaseType::begin();
}

TFTrackGroupingListIterator TFTrackGroupingList::end(void) {
    return TFTrackGroupingListBaseType::end();
}

TFTrackGroupingListIterator TFTrackGroupingList::find(const std::string &name) {
    if (name.empty()) throw std::runtime_error("find: empty name");

    return TFTrackGroupingListBaseType::find(name);
}

void TFTrackGroupingList::erase(const std::string &name) {
    if (name.empty()) throw std::runtime_error("erase: empty name");

    auto i = TFTrackGroupingListBaseType::find(name);
    if (i == TFTrackGroupingListBaseType::end()) throw std::runtime_error("erase: sequence does not exist");

    TFTrackGroupingList::erase(i);
}

void TFTrackGroupingList::erase(TFTrackGroupingListIterator const &i) {
    TFTrackGroupingListBaseType::erase(i);
}

void TFTrackGroupingList::rename(const std::string &oldname,const std::string &newname) {
    if (oldname.empty() || newname.empty()) throw std::runtime_error("rename_sequence: empty name(s)");

    if (oldname != newname) {
        auto old_i = TFTrackGroupingListBaseType::find(oldname);
        if (old_i == TFTrackGroupingListBaseType::end()) throw std::runtime_error("rename_sequence: old name does not exist");

        auto new_i = TFTrackGroupingListBaseType::find(newname);
        if (new_i != TFTrackGroupingListBaseType::end()) throw std::runtime_error("rename_sequence: new name already exists");

        auto &new_p = TFTrackGroupingListBaseType::operator[](newname);

        new_p = old_i->second;

        TFTrackGroupingListBaseType::erase(old_i);
    }
}

