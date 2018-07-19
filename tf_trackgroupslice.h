
#ifndef TF_TRACKGROUPSLICE_H
#define TF_TRACKGROUPSLICE_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"
#include "tf_trackgroupslicetrack.h"

class TFTrackGroupSliceList;

class TFTrackGroupSlice {
public:
                                                TFTrackGroupSlice(const size_t &_index) : index(_index) { };
    virtual                                     ~TFTrackGroupSlice() { };
public:
    size_t                                      index;
    unsigned long long                          length = 0;/*in ticks at rate*/
public:
    /* start-end in SECONDS. The slice covers start <= t < end. */
    long double                                 start = 0;/*start time, recomputed as needed from overall slice list and ticks*/
    long double                                 end = 0;/*end time, recomputed as needed from start + ticks*/
public:
    TFTrackGroupSliceTrackList                  tracks;
public:
    TFULongRational                             rate;/*recomputed from get_rate, ticks per second*/
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
    void set_rate(const TFULongRational &r) {
        if (r.num == 0 || r.den == 0) throw std::runtime_error("invalid rate");
        rate = r;
        update_end_time();
        update_track_rates();
    }
    void set_length(const unsigned long long &l) {
        if (length != l) {
            length = l;
            update_end_time();
        }
    }
    void set_start(const long double s) {
        if (start != s) {
            start = s;
            update_end_time();
        }
    }
    void update_end_time(void) {
        end = start + duration();
    }
    long double duration(void) const {
        return ((long double)length * rate.den) / rate.num;
    }
    long double ticks2seconds(const long double &x) const {
        return ((long double)x * rate.den) / rate.num;
    }
    long double seconds2ticks(const long double &x) const {
        return ((long double)x * rate.num) / rate.den;
    }
    void update_track_rates(void) {
        for (auto &i : tracks)
            i.second->set_rate(rate);
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

