
#ifndef TF_TRACKGROUPSLICETRACKSLICE_H
#define TF_TRACKGROUPSLICETRACKSLICE_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"

class TFTrackGroupSliceTrackSliceList;

class TFTrackGroupSliceTrackSlice {
public:
                                                TFTrackGroupSliceTrackSlice(const long double &_start) : start(_start) { };
    virtual                                     ~TFTrackGroupSliceTrackSlice() { };
public:
    /* start-end in ticks. The slice covers start <= t < end. */
    unsigned long long                          start = 0;/*start time, in ticks*/
    unsigned long long                          end = 0;/*end time, in ticks*/
    unsigned long long                          duration = 0;/*duration, in ticks*/
public:
    unsigned long long get_duration(void) const {
        return end - start;
    }
private:/*this requires cooperation with the list object*/
    void set_start(const unsigned long long &x) {
        start = x;
        end = start + duration;
    }
public:
    void set_end(const unsigned long long &x) {
        end = x;
        if (end < (start + min_duration)) end = (start + min_duration);
        duration = end - start;
    }
    void set_duration(const unsigned long long &x) {
        duration = std::max(x,min_duration); /* x cannot be less than min_duration */
        end = start + duration;
    }
public:
    const unsigned long long min_duration =     1ull;
public:
    friend class                                TFTrackGroupSliceTrackSliceList;
};

using TFTrackGroupSliceTrackSliceListBaseClass = TFMapWithRules< unsigned long long , TFTrackGroupSliceTrackSlice >;

class TFTrackGroupSliceTrackSliceList : public TFTrackGroupSliceTrackSliceListBaseClass {
public:
                                                TFTrackGroupSliceTrackSliceList() : TFTrackGroupSliceTrackSliceListBaseClass() { };
    virtual                                     ~TFTrackGroupSliceTrackSliceList() { };
public:
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.start = newname;
    }
public:
    unsigned long long set_start(ListIterator i,unsigned long long x) {
        if (i == end()) throw std::runtime_error("set_start on end item");
        if (i->first != x) {
            i->second->set_start(x);
            rename(i->first, x);
        }

        return x;
    }
};

#endif //TF_TRACKGROUPSLICETRACKSLICE_H

