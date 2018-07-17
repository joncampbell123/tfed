
#ifndef TF_TRACKGROUPING_H
#define TF_TRACKGROUPING_H

#include "tf_mapwithrules.h"

#include <vector>

using TFTrackGrouping = std::vector<std::string>;

using TFTrackGroupingBaseClass = TFMapWithRules< std::string, TFTrackGrouping >;

class TFTrackGroupingList : public TFTrackGroupingBaseClass {
public:
                                                TFTrackGroupingList() : TFTrackGroupingBaseClass() { };
    virtual                                     ~TFTrackGroupingList() { };
public:
    virtual ValType *new_value(const KeyType &name) {
        (void)name;
        return new ValType();
    }
};

#endif //TF_TRACKGROUPING_H

