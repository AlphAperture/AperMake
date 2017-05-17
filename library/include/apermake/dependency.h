/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef APERMAKE_DEPENDENCY_H
#define APERMAKE_DEPENDENCY_H

#include "apermake.h"

namespace apermake
{
    const std::string APERMAKE_API dependenciesGitDir = "dependencies";
    const std::string APERMAKE_API dependenciesDir = ".deps";

    enum DependencyType
    {
        DEFAULT,
        GIT,
        LOCAL
    };

    enum LinkType
    {
        SHARED,
        STATIC
    };

    class APERMAKE_API Dependency
    {
    protected:
        DependencyType _type;
        std::string _source;
        LinkType _linkType;

    public:
        /**
         * Gets the type of the dependency.
         * @return The dependency's type.
         */
        inline DependencyType getType()
        {
            return _type;
        }

        /**
         * Gets the source of the dependency.
         * If the type is `DEFAULT`, the source will be empty.
         * @return The dependency's source.
         */
        inline std::string getSource()
        {
            return _source;
        }

        /**
         * Gets the link type of the dependency, there are two possibilities: SHARED or STATIC.
         * Default value is SHARED.
         * @return The link type of the dependency.
         */
        inline LinkType getLinkType()
        {
            return _linkType;
        }
    };
}

#endif //APERMAKE_DEPENDENCY_H
