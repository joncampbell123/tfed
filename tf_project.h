
#ifndef TF_PROJECT_H
#define TF_PROJECT_H

#include "tf_sequence.h"

#include <string>

class TFProject {
public:
                                                TFProject(const std::string &_name = std::string()) : name(_name) { };
    virtual                                     ~TFProject() { };
public:
    TFSequenceList                              sequences;
    std::string                                 name;
};

#endif //TF_PROJECT_H

