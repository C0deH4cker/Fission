//
//  DynamicComponent.cpp
//  Fission
//
//  Created by C0deH4cker on 2/24/14.
//  Copyright (c) 2014 C0deH4cker. All rights reserved.
//

#include "DynamicComponent.h"

using namespace fsn;


DynamicComponent::DynamicComponent(char type, Grid& grid)
: Component(type), grid(grid) {}

DynamicComponent::~DynamicComponent() {}

