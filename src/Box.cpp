#include "Box.h"

Box::Box() {
    this->value = -1;
    this->isDefault = false;
}

Box::Box(int v) {
    this->value = v;
    this->isDefault = true;
}

int Box::getValue() {
    return this->value;
}

void Box::setValue(int v) {
    this->value = v;
}

void Box::clear() {
    if(!this->isDefault)
        this->value = -1;
}

bool Box::isEmpty() {
    return this->value == -1;
}