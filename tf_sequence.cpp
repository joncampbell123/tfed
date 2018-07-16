
#include <stdio.h>

#include "tf_sequence.h"

TFSequenceList::TFSequenceList() : TFSequenceListBaseType() {
}

TFSequenceList::~TFSequenceList() {
    TFSequenceList::clear();
}

void TFSequenceList::clear(void) {
    do {
        auto i = TFSequenceList::begin();
        if (i == TFSequenceList::end()) break;
        TFSequenceList::erase(i);
    } while (1);
}

TFSequence& TFSequenceList::create(const std::string &name) {
    if (name.empty()) throw std::runtime_error("create: empty name");

    auto i = TFSequenceList::find(name);
    if (i != TFSequenceList::end()) throw std::runtime_error("create: sequence already exists");

    auto &ptr = TFSequenceListBaseType::operator[](name); /* poof */
    ptr = new TFSequence(name);/* will throw exception on failure */

    return *ptr;
}

TFSequence& TFSequenceList::operator[](const std::string &name) {
    if (name.empty()) throw std::runtime_error("[]: empty name");

    auto i = TFSequenceListBaseType::find(name);
    if (i == TFSequenceListBaseType::end()) throw std::runtime_error("[]: sequence does not exist");

    auto &ptr = i->second;
    if (ptr == NULL) throw std::runtime_error("[]: sequence does exist but ptr is null");

    return *ptr;
}

TFSequenceListIterator TFSequenceList::begin(void) {
    return TFSequenceListBaseType::begin();
}

TFSequenceListIterator TFSequenceList::end(void) {
    return TFSequenceListBaseType::end();
}

TFSequenceListIterator TFSequenceList::find(const std::string &name) {
    if (name.empty()) throw std::runtime_error("find: empty name");

    return TFSequenceListBaseType::find(name);
}

void TFSequenceList::erase(const std::string &name) {
    if (name.empty()) throw std::runtime_error("erase: empty name");

    auto i = TFSequenceListBaseType::find(name);
    if (i == TFSequenceListBaseType::end()) throw std::runtime_error("erase: sequence does not exist");

    TFSequenceList::erase(i);
}

void TFSequenceList::erase(TFSequenceListIterator const &i) {
    auto &ptr = i->second;
    if (ptr == NULL) throw std::runtime_error("erase: sequence does exist but ptr is null");
    delete ptr;

    TFSequenceListBaseType::erase(i);
}

void TFSequenceList::rename(const std::string &oldname,const std::string &newname) {
    if (oldname.empty() || newname.empty()) throw std::runtime_error("rename_sequence: empty name(s)");

    if (oldname != newname) {
        auto old_i = TFSequenceListBaseType::find(oldname);
        if (old_i == TFSequenceListBaseType::end()) throw std::runtime_error("rename_sequence: old name does not exist");

        auto &old_p = old_i->second;
        if (old_p == NULL) throw std::runtime_error("rename_sequence: old name does exist but is null");

        auto new_i = TFSequenceListBaseType::find(newname);
        if (new_i != TFSequenceListBaseType::end()) throw std::runtime_error("rename_sequence: new name already exists");

        auto &new_p = TFSequenceListBaseType::operator[](newname);

        new_p = old_p;
        new_p->name = newname;

        TFSequenceListBaseType::erase(old_i);
    }
}

/*--------------------*/

TFSequence::TFSequence(const std::string &_name) : name(_name) {
}

TFSequence::~TFSequence() {
}

