
#ifndef TF_TRACKGROUPSLICE_H
#define TF_TRACKGROUPSLICE_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"

class TFTrackGroupSliceList;

class TFTrackGroupSlice {
public:
                                                TFTrackGroupSlice(const size_t &_index) : index(_index) { };
    virtual                                     ~TFTrackGroupSlice() { };
public:
    size_t                                      index;
    double                                      start = 0;/*start time, recomputed as needed from overall slice list and ticks*/
    double                                      end = 0;/*end time, recomputed as needed from start + ticks*/
    unsigned long long                          length = 0;/*in ticks at rate*/
    TFULongRational                             rate;/*recomputed from get_rate*/
    /* overrides */
    TFULongRational                             o_rate = { 0 };
    VideoDescriptionOverride                    o_video;
    AudioDescriptionOverride                    o_audio;
    /* final computed... */
    TFULongRational get_rate(TFULongRational parent) {
        if (o_rate.num > 0) parent = o_rate;
        return parent;
    }
    VideoDescription get_video(VideoDescription parent) {
        o_video.apply(parent);
        return parent;
    }
    AudioDescription get_audio(AudioDescription parent) {
        o_audio.apply(parent);
        return parent;
    }
protected:
    friend class                                TFTrackGroupSliceList;
};

using TFTrackGroupSliceListBaseClass = TFMapWithRules< size_t, TFTrackGroupSlice >;

class TFTrackGroupSliceList : public TFTrackGroupSliceListBaseClass {
public:
                                                TFTrackGroupSliceList() : TFTrackGroupSliceListBaseClass() { };
    virtual                                     ~TFTrackGroupSliceList() { };
public:
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.index = newname;
    }
};

#endif //TF_TRACKGROUPSLICE_H

