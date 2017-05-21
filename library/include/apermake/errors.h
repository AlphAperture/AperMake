/*
 * Copyright © 2017 Clément "wAperClem" Wagner
 *
 * This file is part of AperMake.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef APERMAKE_ERRORS_H
#define APERMAKE_ERRORS_H

namespace apermake
{
    class InvalidProjectException : public std::exception
    {
    private:
        std::string msg;
    public:
        InvalidProjectException(std::string msg) : msg(msg)
        {}

        const char *what() const noexcept override
        {
            return msg.c_str();
        }
    };

    class NewProjectException : public std::exception
    {
    private:
        std::string msg;
    public:
        NewProjectException(std::string msg) : msg(msg)
        {}

        const char *what() const noexcept override
        {
            return msg.c_str();
        }
    };
}

#endif //APERMAKE_ERRORS_H
