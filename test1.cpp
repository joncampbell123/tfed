
#include <stdio.h>

#include <map>
#include <vector>

class TFSequenceList;

class TFSequence {
public:
                                                TFSequence(const std::string &_name = std::string());
    virtual                                     ~TFSequence();
protected:
    std::string                                 name;
protected:
    friend class                                TFSequenceList;
};

TFSequence::TFSequence(const std::string &_name) : name(_name) {
}

TFSequence::~TFSequence() {
}

using TFSequenceListBaseType = std::map<std::string, TFSequence*>;

class TFSequenceList : protected TFSequenceListBaseType {
public:
                                                TFSequenceList();
    virtual                                     ~TFSequenceList();
public:
    TFSequence&                                 new_sequence(const std::string &name);
    TFSequence&                                 get_sequence(const std::string &name);
    void                                        delete_sequence(const std::string &name);
    bool                                        sequence_exists(const std::string &name) const;
    void                                        rename_sequence(const std::string &oldname,const std::string &newname);
protected: /* the base class is protected */
};

TFSequenceList::TFSequenceList() : TFSequenceListBaseType() {
}

TFSequenceList::~TFSequenceList() {
}

TFSequence& TFSequenceList::new_sequence(const std::string &name) {
    if (name.empty()) throw std::runtime_error("new_sequence: empty name");

    auto i = find(name);
    if (i != end()) throw std::runtime_error("new_sequence: sequence already exists");

    auto &ptr = operator[](name); /* poof */
    ptr = new TFSequence(name);/* will throw exception on failure */

    return *ptr;
}

TFSequence& TFSequenceList::get_sequence(const std::string &name) {
    if (name.empty()) throw std::runtime_error("get_sequence: empty name");

    auto i = find(name);
    if (i == end()) throw std::runtime_error("get_sequence: sequence does not exist");

    auto &ptr = i->second;
    if (ptr == NULL) throw std::runtime_error("get_sequence: sequence does exist but ptr is null");

    return *ptr;
}

void TFSequenceList::delete_sequence(const std::string &name) {
    if (name.empty()) throw std::runtime_error("delete_sequence: empty name");

    auto i = find(name);
    if (i == end()) throw std::runtime_error("delete_sequence: sequence does not exist");

    auto &ptr = i->second;
    if (ptr == NULL) throw std::runtime_error("delete_sequence: sequence does exist but ptr is null");
    delete ptr;

    erase(i);
}

bool TFSequenceList::sequence_exists(const std::string &name) const {
    if (name.empty()) throw std::runtime_error("sequence_exists: empty name");

    return find(name) != end();
}

void TFSequenceList::rename_sequence(const std::string &oldname,const std::string &newname) {
    if (oldname.empty() || newname.empty()) throw std::runtime_error("rename_sequence: empty name(s)");

    if (oldname != newname) {
        auto old_i = find(oldname);
        if (old_i == end()) throw std::runtime_error("rename_sequence: old name does not exist");

        auto &old_p = old_i->second;
        if (old_p == NULL) throw std::runtime_error("rename_sequence: old name does exist but is null");

        auto new_i = find(newname);
        if (new_i != end()) throw std::runtime_error("rename_sequence: new name already exists");

        auto &new_p = operator[](newname);

        new_p = old_p;
        new_p->name = newname;

        erase(old_i);
    }
}

class TFProject {
public:
                                                TFProject(const std::string &_name = std::string());
    virtual                                     ~TFProject();
public:
    TFSequenceList                              sequences;
    std::string                                 name;
};

TFProject::TFProject(const std::string &_name) : name(_name) {
}

TFProject::~TFProject() {
}

int main() {
    return 0;
}

