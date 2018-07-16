
#include <map>
#include <string>
#include <vector>
#include <iostream>

using TFTrackGrouping = std::vector<std::string>;

using TFTrackGroupingListBaseType = std::map<std::string, TFTrackGrouping>;

using TFTrackGroupingListIterator = TFTrackGroupingListBaseType::iterator;

class TFTrackGroupingList : protected TFTrackGroupingListBaseType {
public:
                                            TFTrackGroupingList();
    virtual                                 ~TFTrackGroupingList();
public:
    void                                    clear(void);
    TFTrackGrouping&                        create(const std::string &name);
    TFTrackGrouping&                        operator[](const std::string &name);
    void                                    erase(TFTrackGroupingListIterator const &i);
    void                                    rename(const std::string &oldname,const std::string &newname);
    void                                    erase(const std::string &name);
    TFTrackGroupingListIterator             find(const std::string &name);
    TFTrackGroupingListIterator             begin(void);
    TFTrackGroupingListIterator             end(void);
protected:/* base class */
};

