
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
        TFULongRational x(7,3);
        std::cout << x.value() << " [" << x << "]" << std::endl;
    }
 
    return 0;
}

