
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

    auto &ptr = TFTrackGroupingListBaseType::operator[](name); /* poof */
    ptr = new TFTrackGrouping();/* will throw exception on failure */

    return *ptr;
}

TFTrackGrouping& TFTrackGroupingList::operator[](const std::string &name) {
    if (name.empty()) throw std::runtime_error("[]: empty name");

    auto i = TFTrackGroupingListBaseType::find(name);
    if (i == TFTrackGroupingListBaseType::end()) throw std::runtime_error("[]: sequence does not exist");

    auto &ptr = i->second;
    if (ptr == NULL) throw std::runtime_error("[]: sequence does exist but ptr is null");

    return *ptr;
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
    auto &ptr = i->second;
    if (ptr == NULL) throw std::runtime_error("erase: sequence does exist but ptr is null");
    delete ptr;

    TFTrackGroupingListBaseType::erase(i);
}

void TFTrackGroupingList::rename(const std::string &oldname,const std::string &newname) {
    if (oldname.empty() || newname.empty()) throw std::runtime_error("rename_sequence: empty name(s)");

    if (oldname != newname) {
        auto old_i = TFTrackGroupingListBaseType::find(oldname);
        if (old_i == TFTrackGroupingListBaseType::end()) throw std::runtime_error("rename_sequence: old name does not exist");

        auto &old_p = old_i->second;
        if (old_p == NULL) throw std::runtime_error("rename_sequence: old name does exist but is null");

        auto new_i = TFTrackGroupingListBaseType::find(newname);
        if (new_i != TFTrackGroupingListBaseType::end()) throw std::runtime_error("rename_sequence: new name already exists");

        auto &new_p = TFTrackGroupingListBaseType::operator[](newname);

        new_p = old_p;

        TFTrackGroupingListBaseType::erase(old_i);
    }
}

