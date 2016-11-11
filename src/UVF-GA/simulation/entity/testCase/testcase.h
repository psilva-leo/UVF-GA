#ifndef TESTCASE_H
#define TESTCASE_H

#include <UVF-GA/simulation/entity/entity.hh>
#include <UVF-GA/simulation/entity/player/player.h>
#include <UVF-GA/utils/utils.h>
#include <3rdparty/sslworld/sslworld.h>

class TestCase : public Entity {
public:
    TestCase();
    ~TestCase();

private:
    SSLWorld *_world;
    Player *_player;
    Timer *_timer;

    void initialization();
    void loop();
    void finalization();
};

#endif // TESTCASE_H
