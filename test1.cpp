
#include <stdio.h>

#include "tf_project.h"
#include "tf_sequence.h"

#include <iostream>

int main() {
    TFProject proj("testing");

    {
        TFSequence &x = proj.sequences.create("seq1");
        TFSequence &y = proj.sequences.create("seq2");
    }

    {
        TFSequence &x = proj.sequences["seq1"];
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
    }
 
    return 0;
}

