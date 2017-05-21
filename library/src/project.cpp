/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/apermake/project.h"
#include "../include/apermake/errors.h"
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

        if (path.isFile() && aperstring::equals(path.getFileName(), PROJECT_FILE_NAME))
        {
            manifest = path;
            path = path.getParent();
        }
        else if (path.isDirectory())
            manifest = path / PROJECT_FILE_NAME;
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
                           package->get_as<string>("readme").value_or(DEFAULT_README_FILE));
        }
        catch (cpptoml::parse_exception e)
        {
            return empty;
        }
    }

    Project APERMAKE_API newProject(filesystem::Path path, string name, ProjectType type, string lang)
    {
        if (!aperstring::equalsIgnoreCase(path.getFileName(), name))
            path = path / name;
        auto manifest = path / PROJECT_FILE_NAME;
        if (manifest.exists())
            throw NewProjectException("Project already exists!");
        if (!path.exists())
            if (!path.mkdir())
                throw NewProjectException("Cannot create directory.");
        if (type != ROOT && lang.empty())
            throw InvalidProjectException("The type isn't ROOT, please specify a language!");

        auto toml = cpptoml::make_table();

        auto package = cpptoml::make_table();
        package->insert("project", name);
        package->insert("description", "");
        package->insert("version", "0.0.1");
        auto authors = cpptoml::make_array();
        authors->push_back("Someone <someone@email.com>");
        package->insert("authors", authors);
        package->insert("type", convertProjectTypeToStr(type));
        if (type != ROOT)
            package->insert("lang", lang);
        package->insert("license", "Unknown");

        toml->insert("package", package);

        ofstream out(manifest.toString());
        out << (*toml);
        out.close();

        auto loaded = loadProject(path);
        if (!loaded)
            throw NewProjectException(
                    "Cannot create project! (Cannot read " + PROJECT_FILE_NAME + " at path " + path.toString() + ")");

        return *loaded;
    }
}