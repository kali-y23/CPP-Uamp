#pragma once

// #include "mediator.h"

class Mediator;

class Component
{
public:
    const Mediator *mediator;
    Component(const Mediator *mediator_);
};