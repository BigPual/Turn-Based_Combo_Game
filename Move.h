/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Functions and Data Members for a Move that are implemented in the cpp (MORE_COMPLETE_DESCRIPTION_HERE)
 */#ifndef MOVE_H
#define MOVE_H
#include <iostream>
#include "Enemy.h"

using namespace std;


class Move
{
    private:
        string name;
        int number;
        int damage;
        int accuracy;
        int DOT;
        int eDefense;
        int pDefense;
        int eAttack;
        string description;
    public:
        Move();
        Move(string n, int num, int dam, int dot, int eDef, string des, int acc, int eAtt, int pDef);
        string getName() const;
        int getNumber() const;
        int getDamage() const;
        int getDOT() const;
        int getEDefense() const;
        int getPDefense() const;
        int getEAttack() const;
        int getAccuracy() const;
        string getDescription() const;
        
};










#endif