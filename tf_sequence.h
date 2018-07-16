
#ifndef TF_SEQUENCE_H
#define TF_SEQUENCE_H

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

using TFSequenceListBaseType = std::map<std::string, TFSequence*>;

class TFSequenceList : protected TFSequenceListBaseType {
public:
    using ListIterator =                        TFSequenceListBaseType::iterator;
public:
                                                TFSequenceList();
    virtual                                     ~TFSequenceList();
public:
    void                                        clear(void);
    TFSequence&                                 create(const std::string &name);
    TFSequence&                                 operator[](const std::string &name);
    void                                        erase(ListIterator const &i);
    void                                        erase(const std::string &name);
    void                                        rename(const std::string &oldname,const std::string &newname);
public:
    ListIterator                                find(const std::string &name);
    ListIterator                                begin(void);
    ListIterator                                end(void);
protected: /* the base class is protected */
};

#endif //TF_SEQUENCE_H

