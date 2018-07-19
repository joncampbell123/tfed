
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
    friend class                                TFTrackGroupSliceTrackSliceList;
};

using TFTrackGroupSliceTrackSliceListBaseClass = TFMapWithRules< long double , TFTrackGroupSliceTrackSlice >;

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
    long double set_start(ListIterator i,long double x) {
        if (i == end()) throw std::runtime_error("set_start on end item");
        if (i->first != x) {
            ListIterator j = find(x);
            do {
                if (j != end()) { x += 1e-100; j = find(x); }

                long double tx = x;

                if (j != end()) { x += 1e-99; j = find(x); }
                if (j != end()) { x += 1e-97; j = find(x); }
                if (j != end()) { x += 1e-81; j = find(x); }
                if (j != end()) { x += 1e-56; j = find(x); }
                if (j != end()) { x += 1e-33; j = find(x); }
                if (j != end()) { x += 1e-15; j = find(x); }
                if (j != end()) { x += 1e-8; j = find(x); }
                if (j != end()) { x += 1e-3; j = find(x); }

                if (j != end())
                    x = tx;
                else
                    break;
            } while (1);

            i->second->set_start(x);
            rename(i->first, x);
        }

        return x;
    }
};

#endif //TF_TRACKGROUPSLICETRACKSLICE_H

