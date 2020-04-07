#pragma once
#include "StMgr.cpp"

int main()
{
    auto Program = StMgr<User,std::string>::getStMgr();

    Program->Run();
};