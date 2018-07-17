
#ifndef TF_TRACKGROUP_H
#define TF_TRACKGROUP_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"

// TODO
enum FieldOrder {
    PROGRESSIVE_ORDER=0,
    INTERLACED_TOP_FIRST,
    INTERLACED_BOTTOM_FIRST
};

class VideoDescription {
public:
    FieldOrder                              field_order = PROGRESSIVE_ORDER;
    unsigned int                            field_duration = 1;             /* video "ticks" per field/frame */
    TFULongRational                         display_aspect_ratio = { 16, 9 };
    TFULongRational                         pixel_aspect_ratio = { 1, 1 };
    unsigned int                            width = 1280, height = 720;
public:
    inline bool is_interlaced(void) const {
        return field_order != PROGRESSIVE_ORDER;
    }
    inline unsigned int fields_per_frame(void) const {
        return is_interlaced() ? 2u : 1u;
    }
    inline unsigned int frame_duration(void) const {
        return field_duration * fields_per_frame();
    }
    void set_display_aspect_ratio(const TFULongRational &r) {
        display_aspect_ratio = r;
        update_pixel_aspect_ratio();
    }
    void set_pixel_aspect_ratio(const TFULongRational &r) {
        pixel_aspect_ratio = r;

        display_aspect_ratio.num = (pixel_aspect_ratio.num * width);
        display_aspect_ratio.den = (pixel_aspect_ratio.den * height);

        display_aspect_ratio.reduce();
    }
    void setDimensions(unsigned int nwidth,unsigned int nheight) {
        if (nwidth == 0 || nwidth > 10000 || nheight == 0 || nheight > 10000)
            throw std::runtime_error("setDimensions invalid values");

        width = nwidth;
        height = nheight;
        update_pixel_aspect_ratio();
    }
    void update_pixel_aspect_ratio(void) {
        pixel_aspect_ratio.num = (display_aspect_ratio.num * height);
        pixel_aspect_ratio.den = (display_aspect_ratio.den * width);

        pixel_aspect_ratio.reduce();
    }
};
// END TODO

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
protected:
    friend class                                TFTrackGroupList;
};

using TFTrackGroupListBaseClass = TFMapWithRules< std::string, TFTrackGroup >;

class TFTrackGroupList : public TFTrackGroupListBaseClass {
public:
                                                TFTrackGroupList() : TFTrackGroupListBaseClass() { };
    virtual                                     ~TFTrackGroupList() { };
public:
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_TRACKGROUP_H

