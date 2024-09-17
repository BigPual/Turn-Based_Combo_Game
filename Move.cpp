/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Functions to intialize and get Move values (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#include "Move.h"
#include "Enemy.h"
#include <iostream>

using namespace std;

Move::Move()
{
    name = "";
    number = 0;
    damage = 0;
    DOT = 0;
    eDefense = 0;
    description = "";
    accuracy = 0;
    eAttack = 0;
    pDefense = 0;
}

Move::Move(string n,int num, int dam, int dot, int eDef, string des, int acc, int eAtt, int pDef)
{
    name = n;
    number = num;
    damage = dam;
    DOT = dot;
    eDefense = eDef;
    description = des;
    accuracy = acc;
    eAttack = eAtt;
    pDefense = pDef;
}

string Move::getName() const
{
    return name;
}

int Move::getNumber() const
{
    return number;
}

int Move::getDamage() const
{
    return damage;
}

int Move::getDOT() const
{
    return DOT;
}

int Move::getAccuracy() const
{
    return accuracy;
}

int Move::getEDefense() const
{
    return eDefense;
}

int Move::getEAttack() const
{
    return eAttack;
}

int Move::getPDefense() const
{
    return pDefense;
}

string Move::getDescription() const
{
    return description;
}


