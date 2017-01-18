#include <gtest/gtest.h>
#include "basic.h"
#include "command.h"

class Command_Fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Command_Fixture() : Test() {

    }

    virtual ~Command_Fixture() {
    }
};

TEST_F(Command_Fixture, basic) {
    BBS _bbs;
    UserManager _userMan;
    RequestParser parser;
    Request req;

    string input = "cmd=login";
    parser.GetRequest(input, req);
    string cmd = req.GetValue(CMD_NAME);
    ASSERT_EQ("login", cmd);

    input = "cmd=bbslist";
    parser.GetRequest(input, req);
    cmd = req.GetValue(CMD_NAME);
    ASSERT_EQ("bbslist", cmd);

    input = "cmd=bbsread";
    parser.GetRequest(input, req);
    cmd = req.GetValue(CMD_NAME);
    ASSERT_EQ("bbsread", cmd);
}

TEST_F(Command_Fixture, hax2digit_test) {
    char a = 1;
    a <<= 4;
    ASSERT_EQ(16, a);

    RequestParser rp;
    char hex[3] = {'0', 'F'};
    ASSERT_EQ(15, rp.Hex2Digit(hex));

    char hex1[3] = {'1', '0'};
    ASSERT_EQ(16, rp.Hex2Digit(hex1));

    char hex2[3] = {'A', '0'};
    ASSERT_EQ(160, rp.Hex2Digit(hex2));

    char hex3[3] = {'A', 'A'};
    ASSERT_EQ(170, rp.Hex2Digit(hex3));

    char hex4[3] = {'F', 'F'};
    ASSERT_EQ(255, rp.Hex2Digit(hex4));
}

TEST_F(Command_Fixture, command_class_test) {
    BBS _bbs;
    UserManager _userMan;
    map<string, Command*> _req2Cmd;

    _req2Cmd[LOGIN_VAL] = new LoginCommand(& _userMan);
    _req2Cmd[BBSLIST_VAL] = new ListCommand(& _bbs);
    _req2Cmd[BBSREAD_VAL] = new ReadCommand(& _bbs);

    string input = "cmd=login";
    RequestParser parser;

    Request req;
    parser.GetRequest(input, req);
    string cmd = req.GetValue(CMD_NAME);
    Command* pCmd = _req2Cmd[cmd];

    if (pCmd != nullptr)
        pCmd->Execute(req);
}

