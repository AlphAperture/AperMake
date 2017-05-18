/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../../library/include/apermake/project.h"
#include <iostream>

using namespace apercommon;
using namespace apermake;
using namespace std;

void printVector(vector<string> vector1)
{
    cout << "{";
    string final;
    for (auto str : vector1)
        final += (str + ", ");
    final = final.substr(0, final.size() - 2);
    cout << final << "}\n";
}

int main(int argc, char **argv)
{
    auto proj = loadProject(filesystem::Path{"."});

    if (!proj)
    {
        cout << "Not a project...\n";
        return -1;
    }

    auto project = *proj;
    cout << "Project in `" << project.getPath().toString() << "`:\n";
    cout << "Name: " << project.getName() << endl;
    cout << "Description: " << project.getDescription() << endl;
    cout << "Version: " << project.getVersion() << endl;
    cout << "Authors: ";
    printVector(project.getAuthors());
    cout << "Lang: " << project.getLang() << endl;
    cout << "License: " << project.getLicense() << endl;
    cout << "Repository: " << project.getRepository() << endl;
    cout << "README: " << project.getReadme() << endl;

    return 0;
}

