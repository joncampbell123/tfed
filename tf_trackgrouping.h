
#ifndef TF_TRACKGROUPING_H
#define TF_TRACKGROUPING_H

#include "tf_mapwithrules.h"

using TFTrackGrouping = std::vector<std::string>;

class TFTrackGroupingList : public TFMapWithRules< std::string, TFTrackGrouping > {
public:
                                                TFTrackGroupingList();
    virtual                                     ~TFTrackGroupingList();
};

#endif //TF_TRACKGROUPING_H

