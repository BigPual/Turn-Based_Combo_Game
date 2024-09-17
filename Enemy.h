
/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Functions and Data Members for a enemy that are implemented in the cpp (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>

using namespace std;

class Enemy
{
    private:
        int health;
        int eAttack;
        int defense;
        int baseAtt;
        int baseDef;
        string description;
        string name;
    public:
        Enemy();
        Enemy(int num);
        int getHealth() const;
        int getAttack() const;
        int getDefense() const;
        int getBaseAtt() const;
        int getBaseDef() const;
        string getName() const;
        string getDescription() const;
        void setHealth(int h);
        void setAttack(int a);
        void setDefense(int d);
        




};













#endif