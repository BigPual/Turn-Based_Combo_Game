/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Sets enemy statistics and has functions to access and change them (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#include <iostream>
#include "Enemy.h"
#include <cmath>
#include <ctime>

using namespace std;

Enemy::Enemy()
{
    health = 0;
    eAttack = 0;
    defense =0;
    baseAtt = 0;
    baseDef = 0;
    name = "";
    description = "";
}

Enemy::Enemy(int num)
{
    if(num == 1)
    {
        name = "Wretched Runt";
        health = 100;
        eAttack = 7;
        defense = 90;
        description = "A sad creature with little ambition in life.";
    }
    if(num == 2)
    {
        //slots for future enemies
    }
    if(num == 3)
    {
        
    }
    if(num == 4)
    {
        
    }
    baseAtt = eAttack;
    baseDef = defense;
}

int Enemy::getHealth() const
{
    return health;
}

int Enemy::getAttack() const
{
    return eAttack;
}

int Enemy::getDefense() const
{
    return defense;
}

int Enemy::getBaseAtt() const
{
    return baseAtt;
}

int Enemy::getBaseDef() const
{
    return baseDef;
}

string Enemy::getName() const
{
    return name;
}

string Enemy::getDescription() const
{
    return description;
}

void Enemy::setHealth(int h)
{
    health = h;
}

void Enemy::setAttack(int a)
{
    eAttack = a;
}

void Enemy::setDefense(int d)
{
    defense = d;
}