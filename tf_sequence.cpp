
#include <stdio.h>

#include "tf_sequence.h"

TFSequenceList::TFSequenceList() : TFMapWithRules< std::string, TFSequence >() {
}

TFSequenceList::~TFSequenceList() {
    TFSequenceList::clear();
}

/*--------------------*/

TFSequence::TFSequence(const std::string &_name) : name(_name) {
}

TFSequence::~TFSequence() {
}

