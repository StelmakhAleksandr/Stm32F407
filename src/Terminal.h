#pragma once

#include <string>

class Terminal
{
public:
    void sendMessage(const std::string &msg);
    static Terminal *instance();

private:
    Terminal();
};