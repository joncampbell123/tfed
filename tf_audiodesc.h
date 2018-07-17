
#ifndef TF_AUDIODESC_H
#define TF_AUDIODESC_H

class AudioDescription {
public:/*sample rate is in parent object "rate"*/
    unsigned int                            channel_count = 2;
    double                                  volume = 1.0;
};

class AudioDescriptionOverride {
public:/*sample rate is in parent object "rate"*/
    unsigned int                            channel_count = 0;
public:
    AudioDescription apply(AudioDescription parent) {
        if (channel_count > 0) parent.channel_count = channel_count;
        return parent;
    }
};

#endif //TF_AUDIODESC_H

