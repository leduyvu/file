#include "IOFile.h"
#include "cocos2d.h"
#include "IOFile.h"
#include<iostream>
#include<fstream>
#include <string.h>
USING_NS_CC;
using namespace std;
IOFile::IOFile(string filename){
    this->filename = filename;
}
IOFile::~IOFile(){}
//read file
CCArray* IOFile::read()
{
    CCArray *players = new CCArray();
    CCArray *names= new CCArray();
    CCDictionary *pConfInfo;
    pConfInfo = CCDictionary::createWithContentsOfFile(this->filename.c_str());
    names = pConfInfo->allKeys();
    CCObject *i;
    CCARRAY_FOREACH(names, i)
    {
        int mark;
        CCString *s = (CCString*)i;
        string *str = &(s->m_sString);
        mark = pConfInfo->valueForKey(str->c_str())->intValue();
        Player * player = new Player(str->c_str(), mark);
        players->addObject(player);
    }
    return players;
}

//write file
bool IOFile::write(Player* player)
{
    bool check = false;
    CCDictionary *pConfInfo = CCDictionary::createWithContentsOfFile(this->filename.c_str());
    CCArray *names = pConfInfo->allKeys();
    CCObject *i;
    CCLOG(".count ..%d", names->count());
    if(names->count() >= 5)
    {
        CCARRAY_FOREACH(names, i)
        {
            CCString *j = (CCString *)i;
            if ((player->getName().compare(j->m_sString)==0) && (player->getMark() >= pConfInfo->valueForKey(player->getName())->intValue()))
            {
                pConfInfo->removeObjectForKey(player->getName());
                writeDic(pConfInfo);
                return check;
                
            }else if(player->getMark() >= pConfInfo->valueForKey(j->m_sString)->intValue())
            {
                check =true;
                removeMin();
                addPlayerToFile(player);
                return check;
            }
        }
    }
    else
    {
        CCARRAY_FOREACH(names, i){
            CCString *j = (CCString *)i;
            if (player->getName().compare(j->m_sString)==0)
            {
                pConfInfo->removeObjectForKey(player->getName());
                writeDic(pConfInfo);
                addPlayerToFile(player);
                return check;
            }else
            {
                addPlayerToFile(player);
                return check;
            }
        }
    }
    return check;
}

//add play to file
void IOFile::addPlayerToFile(Player * player)
{
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(this->filename.c_str());
    FILE * f;
    CCLOG("%s",path.c_str());
    f = fopen(path.c_str(), "r+");
    fseek(f,-17,SEEK_END);
    fprintf(f, "<key>%s</key>\n<integer>%i</integer>\n</dict>\n</plist>\n",
            player->getName().c_str(),player->getMark());
    fclose(f);
}

//write new file by CCDictonary
void IOFile::writeDic(CCDictionary *c)
{
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(this->filename.c_str());
    FILE * f;
    f = fopen(path.c_str(), "w");
    fseek(f,0,SEEK_SET);
    fprintf(f,"<?xml version='1.0' encoding='UTF-8'?>\n<!DOCTYPE plist PUBLIC '-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd'>\n<plist version='1.0'>\n<dict>\n");
    CCArray *player = new CCArray();
    player = c->allKeys();
    CCObject * i;
    CCARRAY_FOREACH(player, i)
    {
        CCString * str = (CCString*)i ;
        int mark = c->valueForKey(str->m_sString)->intValue();
        fprintf(f, "<key>%s</key>\n<integer>%i</integer>\n",str->m_sString.c_str(),mark);
    }
    fprintf(f, "</dict>\n</plist>\n");
    fclose(f);
}

//remove min value
void IOFile::removeMin()
{
    CCDictionary *pConfInfo = CCDictionary::createWithContentsOfFile(this->filename.c_str());
    CCArray *names = pConfInfo->allKeys();
    string smin = ((CCString*)names->objectAtIndex(0))->m_sString;
    int min = pConfInfo->valueForKey(((CCString*)names->objectAtIndex(0))->m_sString)->intValue();
    for (int i= 1 ; i<5; i++)
    {
        CCString *s1 = (CCString*)(names->objectAtIndex(i));
        int mark = pConfInfo->valueForKey(s1->m_sString)->intValue();
        if (mark <= min)
        {
            min = mark;
            smin = s1->m_sString;
        }
    }
    pConfInfo->removeObjectForKey(smin);
    writeDic(pConfInfo);
}


//******************Player class *******************
Player::Player(string name, int mark)
{
    this->mark = mark;
    this->name = name;
}
Player::~Player(){}
int Player::getMark()
{
    return this->mark;
}
string Player::getName()
{
    return this->name;
}
void Player::setMark(int mark){}
void Player::setName(string name){}