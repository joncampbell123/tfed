
#ifndef TF_TRACKGROUP_H
#define TF_TRACKGROUP_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"
#include "tf_trackgroupslice.h"

class TFTrackGroupList;

class TFTrackGroup {
public:
    enum GroupType {
        NO_GROUP=0,
        AUDIO_GROUP,
        VIDEO_GROUP,
        EVENT_GROUP
    };
    enum EventType {
        NO_EVENT=0,
        CAPTION_EVENT,
        SUBTITLE_EVENT,
        MIDI_EVENT,
        TRIGGER_EVENT
    };
public:
                                                TFTrackGroup(const std::string &_name = std::string()) : name(_name) { };
    virtual                                     ~TFTrackGroup() { };
public:
    std::string                                 name;
    GroupType                                   type = NO_GROUP;
    EventType                                   eventType = NO_EVENT;
    TFFloatRational                             rate; // video: field/frame  audio: sample rate  event: tick rate
    VideoDescription                            video;
    AudioDescription                            audio;
protected:
    friend class                                TFTrackGroupList;
};

using TFTrackGroupListBaseClass = TFMapWithRules< std::string, TFTrackGroup >;

class TFTrackGroupList : public TFTrackGroupListBaseClass {
public:
                                                TFTrackGroupList() : TFTrackGroupListBaseClass() { };
    virtual                                     ~TFTrackGroupList() { };
public:
    virtual void check_key_valid(const KeyType &name) {
        /* default. override if needed */
        if (name.empty()) throw std::runtime_error("empty key name");
    }
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_TRACKGROUP_H

