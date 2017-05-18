/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef APERMAKE_PROJECT_H
#define APERMAKE_PROJECT_H

#include "apermake.h"
#include <apercommon/system/filesystem/filesystem.h>
#include <optional.hpp>

#define STRING std::string

namespace apermake
{
    enum ProjectType
    {
        ROOT,
        LIBRARY,
        EXECUTABLE,
        UNKNOWN = -1
    };

    const STRING defaultReadmeFile = "README.md";

    extern ProjectType APERMAKE_API convertStrToProjectType(STRING type);

    extern STRING APERMAKE_API convertProjectTypeToStr(ProjectType type);

    class Project
    {
    private:
        apercommon::filesystem::Path _path;
        STRING _name;
        STRING _description;
        STRING _version;
        std::vector<STRING> _authors;
        ProjectType _type;
        STRING _lang;
        STRING _license;
        STRING _repository;
        STRING _readme;

    public:
        APERMAKE_API Project(apercommon::filesystem::Path path, STRING name, STRING description, STRING version,
                             std::vector<STRING> authors, ProjectType type, STRING lang, STRING license = "",
                             STRING repository = "",
                             STRING readme = defaultReadmeFile);

        /**
         * Gets the path of the project.
         * @return The path of the project.
         */
        inline apercommon::filesystem::Path APERMAKE_API getPath() const
        {
            return _path;
        }

        /**
         * Gets the name of the project.
         * @return The name of the project.
         */
        inline STRING APERMAKE_API getName() const
        {
            return _name;
        }

        /**
         * Gets the description of the project.
         * @return The description of the project.
         */
        inline STRING APERMAKE_API getDescription() const
        {
            return _description;
        }

        /**
         * Gets the version of the project.
         * @return The version of the project.
         */
        inline STRING APERMAKE_API getVersion() const
        {
            return _version;
        }

        /**
         * Gets the authors of the project.
         * @return The authors of the project.
         */
        inline std::vector<STRING> const APERMAKE_API &getAuthors() const
        {
            return _authors;
        }

        /**
         * Gets the lang of the project.
         * @return The lang of the project.
         */
        inline STRING APERMAKE_API getLang() const
        {
            return _lang;
        }

        /**
         * Gets the license of the project.
         * @return The license of the project.
         */
        inline STRING APERMAKE_API getLicense() const
        {
            return _license;
        }

        /**
         * Gets the repository of the project.
         * @return The repository of the project.
         */
        inline STRING APERMAKE_API getRepository() const
        {
            return _repository;
        }

        /**
         * Gets the readme of the project.
         * @return The readme of the project.
         */
        inline STRING APERMAKE_API getReadme() const
        {
            return _readme;
        }
    };

    extern std::experimental::optional<Project> APERMAKE_API loadProject(apercommon::filesystem::Path path);
}

#undef STRING
#endif //APERMAKE_PROJECT_H
