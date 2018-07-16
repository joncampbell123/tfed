
#ifndef TF_SEQUENCE_H
#define TF_SEQUENCE_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"

class TFSequenceList;

class TFSequence {
public:
                                                TFSequence(const std::string &_name = std::string());
    virtual                                     ~TFSequence();
public:
    TFTrackGroupingList                         groupings;
    std::string                                 name;
protected:
    friend class                                TFSequenceList;
};

class TFSequenceList : public TFMapWithRules< std::string, TFSequence > {
public:
                                                TFSequenceList();
    virtual                                     ~TFSequenceList();
public:
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_SEQUENCE_H

