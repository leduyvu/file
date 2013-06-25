//
//  IOFile.h
//  demo4
//
//  Created by macbook_006 on 13/06/20.
//
//

#ifndef __IOFILE_H
#define __IOFILE_H
#include "cocos2d.h"
#include "string.h"
USING_NS_CC;
using namespace std;
//****** Player class ************//
class Player : public cocos2d::CCObject {
private:
    string name;
    int mark;
public:
    Player(string name , int mark);
    ~Player();
    void setName(string name);
    void setMark(int mark);
    string getName();
    int getMark();
};

//*********** IOfile class ***********//
class IOFile {
private:
    string filename;
public:
    ~IOFile();
    IOFile(string filename);
    CCArray* read();
    bool write(Player *player);
    void removeMin();
    inline void addPlayerToFile(Player * player);
    void writeDic(CCDictionary *c);
};
#endif
