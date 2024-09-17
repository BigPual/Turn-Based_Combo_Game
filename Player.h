/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Functions and Data Members for a player that are implemented in the cpp (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "Move.h"
#include "Enemy.h"

using namespace std;

class Player
{
    private:
        int health;
        int defense;
        int pAttack;
        int maxHealth;
        int DOT;
        int baseHealth;
        int baseDef;
        int baseAtt;
        vector<Move>* abilities;
        vector<Move>* moves;
        int prevMove;
        bool accUp;
    public:
        Player();
        Player(int h, int att, int def);
        void attack(Enemy* e);
        void enemyAttack(Enemy* e);
        int getHealth() const;
        int getDefense() const;
        void setAttack(int a);
        void setHealth(int h);
        void addAbility();
        void combo(Enemy* e, Move& m);
        void displayStats(Enemy* e) const;
        void reset();
        
        







};













#endif