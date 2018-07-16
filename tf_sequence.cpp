
#include <stdio.h>

#include "tf_sequence.h"

TFSequenceList::TFSequenceList() : TFSequenceListBaseClass() {
}

TFSequenceList::~TFSequenceList() {
}

/*--------------------*/

TFSequence::TFSequence(const std::string &_name) : name(_name) {
}

TFSequence::~TFSequence() {
}

