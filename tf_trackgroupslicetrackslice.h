
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
    virtual void check_overlap_validity(void) {
        /* overlap rule:
         *
         * slices are only allowed to overlap one item to the right (later).
         * the overlap cannot extend past the end of the next item.
         * cross-transition code in this project is written around start-end
         * derived from the overlap of two slices that follow these rules. */
        for (auto i=begin();i!=end();i++) {
            do {
                auto j = i; j++;
                if (j == end()) break;

                /* i = current
                 * j = next */

                /* assume (due to std::map)
                 * - i->first != j->first (cannot occupy the same start)
                 * - i->first <  j->first (next item must have later start time) */

                /* current end cannot extend past the next end */
                /* i: +--------------------------+
                 * j:    +-----------------+ */
                if (i->second->end > j->second->end) {
                    std::cerr << "check_overlap_validity: curitem start=" << i->first <<
                        " nextitem start=" << j->first <<
                        " current end " << i->second->end <<
                        " > next end " << j->second->end << ", trimming current item end to " << j->second->end << std::endl;
                    i->second->end = j->second->end;

                    /* becomes */
                    /* i: +--------------------+
                     * j:    +-----------------+ */

                    /* and then go back and start again */
                    i = begin();
                    continue;
                }

                /* assume by this point:
                 * - i->second->end <= j->second->end */

                /* advance */
                j++;
                if (j != end()) {
                    /* i = current
                     * j = next of next */

                    /* current end cannot extend past the next, next start */
                    /*      i: +-----------------------+
                     * (next):     +-------------------+   (was clipped by code above)
                     *      j:                 +---------------+ */
                    if (i->second->end > j->first) {
                        std::cerr << "check_overlap_validity: curitem start=" << i->first <<
                            " nextnextitem start=" << j->first <<
                            " current end " << i->second->end <<
                            " > nextnext end " << j->second->end << ", trimming current item end to " << j->first << std::endl;
                        i->second->end = j->first;

                        /* and then go back and start again */
                        i = begin();
                        continue;
                    }
                }

                /* done */
                break;
            } while (1);
        }
    }
};

#endif //TF_TRACKGROUPSLICETRACKSLICE_H

