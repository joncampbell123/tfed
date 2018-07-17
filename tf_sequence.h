
#ifndef TF_SEQUENCE_H
#define TF_SEQUENCE_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"

class TFSequenceList;

class TFSequence {
public:
                                                TFSequence(const std::string &_name = std::string()) : name(_name) { };
    virtual                                     ~TFSequence() { };
public:
    TFTrackGroupList                            groups;
    TFTrackGroupingList                         groupings;
    std::string                                 name;
protected:
    friend class                                TFSequenceList;
};

using TFSequenceListBaseClass = TFMapWithRules< std::string, TFSequence >;

class TFSequenceList : public TFSequenceListBaseClass {
public:
                                                TFSequenceList() : TFSequenceListBaseClass() { };
    virtual                                     ~TFSequenceList() { };
public:
    virtual void check_key_valid(const KeyType &name) {
        /* default. override if needed */
        if (name.empty()) throw std::runtime_error("empty key name");
    }
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_SEQUENCE_H

