
#ifndef TF_TRACKGROUPING_H
#define TF_TRACKGROUPING_H

#include "tf_mapwithrules.h"

using TFTrackGrouping = std::vector<std::string>;

using TFTrackGroupingBaseClass = TFMapWithRules< std::string, TFTrackGrouping >;

class TFTrackGroupingList : public TFTrackGroupingBaseClass {
public:
                                                TFTrackGroupingList();
    virtual                                     ~TFTrackGroupingList();
};

#endif //TF_TRACKGROUPING_H

