
#include <stdio.h>

#include <map>
#include <string>
#include <vector>
#include <iostream>

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
using TFSequenceListIterator = TFSequenceListBaseType::iterator;

class TFSequenceList : protected TFSequenceListBaseType {
public:
                                                TFSequenceList();
    virtual                                     ~TFSequenceList();
public:
    void                                        clear(void);
    TFSequence&                                 new_sequence(const std::string &name);
    TFSequence&                                 get_sequence(const std::string &name);
    TFSequenceListIterator                      find_sequence(const std::string &name);
    void                                        delete_sequence(const std::string &name);
    void                                        delete_sequence(TFSequenceListIterator const &i);
    bool                                        sequence_exists(const std::string &name) const;
    void                                        rename_sequence(const std::string &oldname,const std::string &newname);
    TFSequenceListIterator                      begin_sequence(void);
    TFSequenceListIterator                      end_sequence(void);
protected: /* the base class is protected */
};

TFSequenceList::TFSequenceList() : TFSequenceListBaseType() {
}

TFSequenceList::~TFSequenceList() {
    clear();
}

void TFSequenceList::clear(void) {
    do {
        auto i = begin();
        if (i == end()) break;
        delete_sequence(i);
    } while (1);
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

TFSequenceListIterator TFSequenceList::begin_sequence(void) {
    return begin();
}

TFSequenceListIterator TFSequenceList::end_sequence(void) {
    return end();
}

TFSequenceListIterator TFSequenceList::find_sequence(const std::string &name) {
    return find(name);
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

void TFSequenceList::delete_sequence(TFSequenceListIterator const &i) {
    if (i->second == NULL) throw std::runtime_error("delete_sequence: sequence with null ptr");
    delete i->second;

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
    TFProject proj("testing");

    {
        TFSequence &x = proj.sequences.new_sequence("seq1");
        TFSequence &y = proj.sequences.new_sequence("seq2");
    }

    {
        TFSequence &x = proj.sequences.get_sequence("seq1");
    }

    {
        proj.sequences.rename_sequence("seq1","seq3");
    }

    {
        for (auto i=proj.sequences.begin_sequence();i!=proj.sequences.end_sequence();i++) {
            std::cout << "Sequence: " << i->first << std::endl;
        }

        auto j=proj.sequences.find_sequence("seq2");
        if (j != proj.sequences.end_sequence())
            std::cout << "Found: " << j->first << std::endl;
    }

    return 0;
}

