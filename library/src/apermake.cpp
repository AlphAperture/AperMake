/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/apermake/apermake.h"

using namespace std;

namespace apermake
{
    string getVersion()
    {
        return to_string(APERMAKE_VERSION_MAJOR) + "." + to_string(APERMAKE_VERSION_MINOR) + "." +
               to_string(APERMAKE_VERSION_BUILD);
    }
}