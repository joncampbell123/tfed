
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
using TFSequenceListIterator = TFSequenceListBaseType::iterator;

class TFSequenceList : protected TFSequenceListBaseType {
public:
                                                TFSequenceList();
    virtual                                     ~TFSequenceList();
public:
    void                                        clear(void);
    TFSequence&                                 create(const std::string &name);
    TFSequence&                                 operator[](const std::string &name);
    void                                        erase(TFSequenceListIterator const &i);
    void                                        erase(const std::string &name);
    void                                        rename(const std::string &oldname,const std::string &newname);
public:
    TFSequenceListIterator                      find(const std::string &name);
    TFSequenceListIterator                      begin(void);
    TFSequenceListIterator                      end(void);
protected: /* the base class is protected */
};

#endif //TF_SEQUENCE_H

