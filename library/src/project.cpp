/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/apermake/project.h"
#include <apercommon/string.h>
#include <cpptoml.h>

using namespace apercommon;
using namespace std;

namespace apermake
{
    ProjectType convertStrToProjectType(string type)
    {
        if (aperstring::equalsIgnoreCase(type, "ROOT"))
            return ROOT;
        else if (aperstring::equalsIgnoreCase(type, "LIBRARY"))
            return LIBRARY;
        else if (aperstring::equalsIgnoreCase(type, "EXECUTABLE"))
            return EXECUTABLE;
        else
            return UNKNOWN;
    }

    string convertProjectTypeToStr(ProjectType type)
    {
        switch (type)
        {
            case ROOT:
                return "ROOT";
            case LIBRARY:
                return "LIBRARY";
            case EXECUTABLE:
                return "EXECUTABLE";
            case UNKNOWN:
                return "UNKNOWN";
            default:
                return "";
        }
    }

    Project::Project(filesystem::Path path, string name, string description, string version, vector<string> authors,
                     ProjectType type, string lang, string license, string repository, string readme) : _path(path),
                                                                                                        _name(name),
                                                                                                        _description(
                                                                                                                description),
                                                                                                        _version(
                                                                                                                version),
                                                                                                        _authors(
                                                                                                                authors),
                                                                                                        _type(type),
                                                                                                        _lang(lang),
                                                                                                        _license(
                                                                                                                license),
                                                                                                        _repository(
                                                                                                                repository),
                                                                                                        _readme(readme)
    {}

    experimental::optional<Project> APERMAKE_API loadProject(filesystem::Path path)
    {
        experimental::optional<Project> empty{};

        filesystem::Path manifest;

        if (path.isFile() && aperstring::equals(path.getFileName(), "project.amanifest"))
        {
            manifest = path;
            path = path.getParent();
        }
        else if (path.isDirectory())
            manifest = path / "project.amanifest";
        else
            return empty;

        if (!manifest.exists())
            return empty;

        try
        {
            auto toml = cpptoml::parse_file(manifest.toAbsolute().toString());
            auto package = toml->get_table("package");

            auto name = package->get_as<string>("project");
            if (!name)
                return empty;

            auto description = package->get_as<string>("description");
            if (!description)
                return empty;

            auto version = package->get_as<string>("version");
            if (!version)
                return empty;

            auto authors = package->get_array_of<string>("authors");
            if (!authors)
                return empty;

            auto _t = package->get_as<string>("type");
            if (!_t)
                return empty;
            auto type = convertStrToProjectType(*_t);

            auto lang = package->get_as<string>("lang");
            if (!lang && type != ROOT)
                return empty;

            return Project(path, *name, *description, *version, *authors, type, *lang,
                           package->get_as<string>("license").value_or(""),
                           package->get_as<string>("repository").value_or(""),
                           package->get_as<string>("readme").value_or(defaultReadmeFile));
        }
        catch (cpptoml::parse_exception e)
        {
            return empty;
        }
    }
}