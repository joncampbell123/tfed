
#ifndef TF_VIDEODESC_H
#define TF_VIDEODESC_H

#include "tf_rational.h"

enum FieldOrder {
    NO_ORDER=-1,
    PROGRESSIVE_ORDER=0,
    INTERLACED_TOP_FIRST,
    INTERLACED_BOTTOM_FIRST
};

class VideoDescription {
public:/*field/frame rate is in parent object "rate" */
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
        update_par_from_dar();
    }
    void set_pixel_aspect_ratio(const TFULongRational &r) {
        pixel_aspect_ratio = r;
        update_dar_from_par();
    }
    void setDimensions(unsigned int nwidth,unsigned int nheight) {
        if (nwidth == 0 || nwidth > 10000 || nheight == 0 || nheight > 10000)
            throw std::runtime_error("setDimensions invalid values");

        width = nwidth;
        height = nheight;
        update_dar_from_par();
    }
    void update_dar_from_par(void) {
        display_aspect_ratio.num = (pixel_aspect_ratio.num * width);
        display_aspect_ratio.den = (pixel_aspect_ratio.den * height);

        display_aspect_ratio.reduce();
    }
    void update_par_from_dar(void) {
        pixel_aspect_ratio.num = (display_aspect_ratio.num * height);
        pixel_aspect_ratio.den = (display_aspect_ratio.den * width);

        pixel_aspect_ratio.reduce();
    }
};

class VideoDescriptionOverride {
public:
    FieldOrder                              field_order = NO_ORDER;
    unsigned int                            field_duration = 0;
    TFULongRational                         display_aspect_ratio = { 0 };
    TFULongRational                         pixel_aspect_ratio = { 0 };
    unsigned int                            width = 0, height = 0;
public:
    VideoDescription apply(VideoDescription parent) {
        if (field_order > NO_ORDER) parent.field_order = field_order;
        if (field_duration > 0) parent.field_duration = field_duration;
        if (display_aspect_ratio.num > 0) parent.display_aspect_ratio = display_aspect_ratio;
        if (pixel_aspect_ratio.num > 0) parent.pixel_aspect_ratio = pixel_aspect_ratio;
        if (width > 0) parent.width = width;
        if (height > 0) parent.height = height;
        return parent;
    }
};

#endif //TF_VIDEODESC_H

