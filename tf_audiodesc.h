
#ifndef TF_AUDIODESC_H
#define TF_AUDIODESC_H

class AudioDescription {
public:/*sample rate is in parent object "rate"*/
    unsigned int                            channel_count = 2;
    double                                  volume = 1.0;
};

#endif //TF_AUDIODESC_H

