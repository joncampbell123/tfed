
#ifndef TF_TRACKGROUPSLICETRACK_H
#define TF_TRACKGROUPSLICETRACK_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"
#include "tf_trackgroupslicetrackslice.h"

class TFTrackGroupSliceTrackList;

class TFTrackGroupSliceTrack {
public:
                                                TFTrackGroupSliceTrack(const std::string &_name) : name(_name) { };
    virtual                                     ~TFTrackGroupSliceTrack() { };
public:
    std::string                                 name;
public:
    TFTrackGroupSliceTrackSliceList             slices;
public:
    friend class                                TFTrackGroupSliceTrackList;
};

using TFTrackGroupSliceTrackListBaseClass = TFMapWithRules< std::string , TFTrackGroupSliceTrack >;

class TFTrackGroupSliceTrackList : public TFTrackGroupSliceTrackListBaseClass {
public:
                                                TFTrackGroupSliceTrackList() : TFTrackGroupSliceTrackListBaseClass() { };
    virtual                                     ~TFTrackGroupSliceTrackList() { };
public:
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_TRACKGROUPSLICETRACK_H

