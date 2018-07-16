
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
        l.push_back("video2");
    }
    {
        for (auto &i : proj.sequences["seq3"].groupings) {
            std::cout << "grouping: " << i.first << std::endl;
            for (auto &j : (*i.second))
                std::cout << "  " << j << std::endl;
        }
    }
 
    return 0;
}

