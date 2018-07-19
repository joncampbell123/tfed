
#include <stdio.h>

#include "tf_project.h"
#include "tf_sequence.h"

#include <iostream>

int main() {
    TFProject proj("testing");

    {
        TFSequence &x = proj.sequences.create("seq1");
        TFSequence &y = proj.sequences.create("seq2");
        (void)x;
        (void)y;
    }

    {
        TFSequence &x = proj.sequences["seq1"];
        (void)x;
    }

    {
        proj.sequences.rename("seq1","seq3");
    }

    {
        for (auto &i : proj.sequences) {
            std::cout << "Sequence: " << i.first << std::endl;
            std::cout << "    name: " << i.second->name << std::endl;
        }

        auto j = proj.sequences.find("seq2");
        if (j != proj.sequences.end())
            std::cout << "Found: " << j->first << std::endl;

        proj.sequences.erase("seq2");

        for (auto &i : proj.sequences)
            std::cout << "Sequence: " << i.first << std::endl;
    }

    {
        TFSequence &x = proj.sequences["seq3"];
        TFTrackGrouping &l = x.groupings.create("x1");
        l.push_back("video1");
        l.push_back("audio1");
    }
    {
        TFSequence &x = proj.sequences["seq3"];
        TFTrackGroup &g = x.groups.create("video1");
        g.type = TFTrackGroup::VIDEO_GROUP;
        g.rate = { 30000, 1001 };
    }
    {
        TFSequence &x = proj.sequences["seq3"];
        TFTrackGroup &g = x.groups.create("audio1");
        g.type = TFTrackGroup::AUDIO_GROUP;
        g.rate = 48000;
    }
    {
        std::cout << "TrackGroup video1 rate " << proj.sequences["seq3"].groups["video1"].rate << std::endl;
        std::cout << "TrackGroup video1 rate " << proj.sequences["seq3"].groups["video1"].rate.value() << std::endl;
    }
    {
        for (auto &i : proj.sequences["seq3"].groups) {
            std::cout << "group: " << i.first << std::endl;
            std::cout << " name: " << i.second->name << std::endl;
            std::cout << " rate: " << i.second->rate << std::endl;
        }
    }
    {
        for (auto &i : proj.sequences["seq3"].groupings) {
            std::cout << "grouping: " << i.first << std::endl;
            for (auto &j : (*i.second))
                std::cout << "  " << j << std::endl;
        }
    }
    {
        TFFloatRational x;
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFFloatRational x(2);
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFFloatRational x(3.14159);
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFFloatRational x(5,2);
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFFloatRational x(7,3);
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFULongRational x(2,1);
        x.reduce();
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFULongRational x(4,2);
        x.reduce();
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFULongRational x(15,3);
        x.reduce();
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFULongRational x(123123,123);
        x.reduce();
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
    {
        TFSequence &x = proj.sequences["seq3"];
        TFTrackGroup &g = x.groups["video1"];

        std::cout << g.rate.value() << " [" << g.rate << "] " << g.video.width << "x" << g.video.height << " PAR " << g.video.pixel_aspect_ratio << " DAR " << g.video.display_aspect_ratio << std::endl;

        g.video.setDimensions(1920,480);/*should result in DAR 4:1 */
        std::cout << g.rate.value() << " [" << g.rate << "] " << g.video.width << "x" << g.video.height << " PAR " << g.video.pixel_aspect_ratio << " DAR " << g.video.display_aspect_ratio << std::endl;

        g.video.set_display_aspect_ratio({4,3});/*should result in DAR 4:3 PAR 1:3 */
        std::cout << g.rate.value() << " [" << g.rate << "] " << g.video.width << "x" << g.video.height << " PAR " << g.video.pixel_aspect_ratio << " DAR " << g.video.display_aspect_ratio << std::endl;

        g.video.set_pixel_aspect_ratio({1,1});/*should result in DAR 4:1 PAR 1:1 */
        std::cout << g.rate.value() << " [" << g.rate << "] " << g.video.width << "x" << g.video.height << " PAR " << g.video.pixel_aspect_ratio << " DAR " << g.video.display_aspect_ratio << std::endl;

        g.video.setDimensions(1920,1080);/*should result in DAR 16:9 PAR 1:1 */
        std::cout << g.rate.value() << " [" << g.rate << "] " << g.video.width << "x" << g.video.height << " PAR " << g.video.pixel_aspect_ratio << " DAR " << g.video.display_aspect_ratio << std::endl;

        g.video.set_pixel_aspect_ratio({2,1});/*should result in DAR 8:1 PAR 2:1 */
        std::cout << g.rate.value() << " [" << g.rate << "] " << g.video.width << "x" << g.video.height << " PAR " << g.video.pixel_aspect_ratio << " DAR " << g.video.display_aspect_ratio << std::endl;
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];
        TFTrackGroupSlice &s = x.slices.create(0);
        (void)x;
        (void)s;
    }
    {
        TFTrackGroupSlice &s = proj.sequences["seq3"].groups["video1"].slices[0];
        (void)s;
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];
        TFTrackGroupSlice &s = x.slices[0];
        TFULongRational nrate = s.get_rate(x.rate);

        std::cout << "Slice: From " << x.rate << " to " << nrate << std::endl;

        s.o_rate = { 25, 1 };
        nrate = s.get_rate(x.rate);

        std::cout << "Slice: From " << x.rate << " to " << nrate << std::endl;
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];
        TFTrackGroupSlice &s = x.slices[0];
        s.set_rate(s.get_rate(x.rate));
        s.set_start(5);
        s.set_length(1000);

        std::cout << "Slice: " << s.rate << " length " << s.length << " start " << s.start << " end " << s.end << std::endl;

        s.o_rate = { 0 };
        s.set_rate(s.get_rate(x.rate));

        std::cout << "Slice: " << s.rate << " length " << s.length << " start " << s.start << " end " << s.end << std::endl;
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];
        TFTrackGroupSlice &s = x.slices.create(1);
        (void)x;
        (void)s;
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];
        TFTrackGroupSlice &s = x.slices[1];
        s.set_rate(s.get_rate(x.rate));
        s.set_start(10);
        s.set_length(1000);

        std::cout << "Slice: " << s.rate << " length " << s.length << " start " << s.start << " end " << s.end << std::endl;
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];

        std::cout << "layout..." << std::endl;
        x.slice_layout();

        for (auto &s : x.slices) {
            std::cout << "Slice: " << s.second->rate << " length " <<
                s.second->length << " start " << s.second->start << " end " <<
                s.second->end << std::endl;
        }
    }
    {
        TFTrackGroup &x = proj.sequences["seq3"].groups["video1"];

        std::cout << "layout..." << std::endl;
        x.slice_layout_zero();

        for (auto &s : x.slices) {
            std::cout << "Slice: " << s.second->rate << " length " <<
                s.second->length << " start " << s.second->start << " end " <<
                s.second->end << std::endl;
        }
    }
    {
        TFTrackGroupSlice &s = proj.sequences["seq3"].groups["video1"].slices[0];
        TFTrackGroupSliceTrack &t = s.tracks.create("track1");

        {
            TFTrackGroupSliceTrackSlice &s2 = t.slices.create(0/*ticks*/);
            s2.set_duration(8);

            std::cout << "seq3.video1.track1: start " << s2.start << " end " << s2.end << " duration " << s2.duration << std::endl;

            s2.set_end(10);

            std::cout << "seq3.video1.track1: start " << s2.start << " end " << s2.end << " duration " << s2.duration << std::endl;
        }

        {
            TFTrackGroupSliceTrackSlice &s2 = t.slices.create(4/*ticks*/);
            s2.set_duration(12);

            std::cout << "seq3.video1.track1: start " << s2.start << " end " << s2.end << " duration " << s2.duration << std::endl;

            s2.set_end(20);

            std::cout << "seq3.video1.track1: start " << s2.start << " end " << s2.end << " duration " << s2.duration << std::endl;

            t.slices.set_start(t.slices.find(4), 8);
        }

        {
            t.slices.set_start(t.slices.find(0), 4);
            t.slices.set_start(t.slices.find(4), 5);
            TFTrackGroupSliceTrackSlice &s2 = t.slices[5];

            std::cout << "seq3.video1.track1: start " << s2.start << " end " << s2.end << " duration " << s2.duration << std::endl;
        }
    }
    {
        TFTrackGroupSliceTrack &t = proj.sequences["seq3"].groups["video1"].slices[0].tracks["track1"];

        std::cout << "seq3.video1.slice0.track1 slices" << std::endl;
        for (auto &i : t.slices) {
            std::cout << " slice " << i.first << " start " <<
                i.second->start << " end " << i.second->end <<
                " duration " << i.second->duration << std::endl;
        }
    }
    {
        TFTrackGroupSliceTrack &t = proj.sequences["seq3"].groups["video1"].slices[0].tracks["track1"];
        for (unsigned long long c = 0;c < 30;c++) {
            auto i = t.slices.rounddown_bound(c);
            if (i != t.slices.end()) {
                std::cout << "slice rounddown_bound(" << c << ") " << i->first << " start " <<
                    i->second->start << " end " << i->second->end <<
                    " duration " << i->second->duration << std::endl;
            }
            else {
                std::cout << "slice rounddown_bound(" << c << ") end" << std::endl;
            }
        }
    }
 
    return 0;
}

