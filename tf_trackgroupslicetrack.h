
#ifndef TF_TRACKGROUPSLICETRACK_H
#define TF_TRACKGROUPSLICETRACK_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"

class TFTrackGroupSliceTrackList;

class TFTrackGroupSliceTrack {
public:
                                                TFTrackGroupSliceTrack(const long double &_start) : start(_start) { };
    virtual                                     ~TFTrackGroupSliceTrack() { };
public:
    /* start-end in SECONDS. The slice covers start <= t < end. */
    long double                                 start = 0;/*start time, in ticks*/
    long double                                 end = 0;/*end time, in ticks*/
    long double                                 duration = 0;/*duration, in ticks*/
public:
    long double get_duration(void) const {
        return end - start;
    }
private:/*this requires cooperation with the list object*/
    void set_start(const long double &x) {
        start = x;
        end = start + duration;
    }
public:
    void set_end(const long double &x) {
        end = x;
        if (end < (start + min_duration)) end = (start + min_duration);
        duration = end - start;
    }
    void set_duration(const long double &x) {
        duration = std::max(x,min_duration); /* x cannot be less than min_duration */
        end = start + duration;
    }
public:
    const long double min_duration =            1e-3;
public:
    friend class                                TFTrackGroupSliceTrackList;
};

using TFTrackGroupSliceTrackListBaseClass = TFMapWithRules< long double , TFTrackGroupSliceTrack >;

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
        value.start = newname;
    }
};

#endif //TF_TRACKGROUPSLICETRACK_H

