#ifndef PROGRAMMING_PEARLS_COMMAND_H
#define PROGRAMMING_PEARLS_COMMAND_H

#include "basic.h"

class Command {
public:
    virtual void Execute(Request& req) = 0;
};

class LoginCommand : public Command {
public:
    LoginCommand(UserManager* pUserMan) {
        pUserMan_ = pUserMan;
    }

    void Execute(Request& req) {
        pUserMan_->CheckPasswd(req);
    }

private:
    UserManager* pUserMan_;
};

class ListCommand : public Command {
public:
    ListCommand(BBS *pBbs) {
        pBbs_ = pBbs;
    }

    void Execute(Request& req) {
        pBbs_->DisplayList(req);
    }

private:
    BBS *pBbs_;
};

class ReadCommand : public Command {
public:
    ReadCommand(BBS *pBbs) {
        pBbs_ = pBbs;
    }

    void Execute(Request& req) {
        pBbs_->DisplayItem(req);
    }

private:
    BBS *pBbs_;
};

#endif //PROGRAMMING_PEARLS_COMMAND_H
