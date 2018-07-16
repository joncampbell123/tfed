
#include <stdio.h>

#include <map>
#include <vector>

class TFSequence {
public:
                                                TFSequence();
    virtual                                     ~TFSequence();
protected:
    std::string                                 name;
};

using TFSequenceListBaseType = std::map<std::string, TFSequence*>;

class TFSequenceList : protected TFSequenceListBaseType {
public:
                                                TFSequenceList();
    virtual                                     ~TFSequenceList();
public:
    TFSequence&                                 new_sequence(const std::string &name);
    TFSequence&                                 get_sequence(const std::string &name);
    bool                                        delete_sequence(const std::string &name);
    bool                                        sequence_exists(const std::string &name) const;
    bool                                        rename_sequence(const std::string &oldname,const std::string &newname);
protected: /* the base class is protected */
};

class TFProject {
public:
                                                TFProject();
    virtual                                     ~TFProject();
public:
    TFSequenceList                              sequences;
};

int main() {
    return 0;
}

