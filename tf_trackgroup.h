
#ifndef TF_TRACKGROUP_H
#define TF_TRACKGROUP_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"

class TFTrackGroupList;

class TFTrackGroup {
public:
                                                TFTrackGroup(const std::string &_name = std::string()) : name(_name) { };
    virtual                                     ~TFTrackGroup() { };
public:
    std::string                                 name;
protected:
    friend class                                TFTrackGroupList;
};

using TFTrackGroupListBaseClass = TFMapWithRules< std::string, TFTrackGroup >;

class TFTrackGroupList : public TFTrackGroupListBaseClass {
public:
                                                TFTrackGroupList() : TFTrackGroupListBaseClass() { };
    virtual                                     ~TFTrackGroupList() { };
public:
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_TRACKGROUP_H

