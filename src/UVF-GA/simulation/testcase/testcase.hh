#ifndef TESTCASE_H
#define TESTCASE_H

#include <UVF-GA/utils/entity/entity.hh>
#include <UVF-GA/simulation/player/player.hh>
#include <UVF-GA/utils/utils.hh>
#include <3rdparty/sslworld/sslworld.hh>

class TestCase : public Entity {
public:
    TestCase();
    ~TestCase();

    QString name();

private:
    SSLWorld *_world;
    Player *_player;
    Timer *_timer;

    void initialization();
    void loop();
    void finalization();
};

#endif // TESTCASE_H
