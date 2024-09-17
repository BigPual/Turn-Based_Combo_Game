/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Sets Player values and has functions to allow both the enemy and player to attack one another as well as add moves to the players arsenal (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#include "Player.h"
#include "Enemy.h"
#include "Move.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

Player::Player()
{
    health = 0;
    defense = 0;
    maxHealth = 0;
    DOT = 0;
    pAttack =0;
    accUp = false;
    baseHealth = 0;
    baseAtt = 0;
    baseDef = 0;
    prevMove = -1;
    moves = new vector<Move>();
    abilities = new vector<Move>();
    abilities->push_back(Move("Heavy Swing", 1, 4, 0, 0, "A heavy strike at the foe!", 60, 0, 0));
    abilities->push_back(Move("Swift Jab", 2, 2, 0, 0, "A quick jab with the blunt of your weapon!", 90, 0, 0));
    abilities->push_back(Move("Gaslight", 3, 0, 0, 0, "You berate the enemy and make them believe they are weak!", 70, 5, 0));
    abilities->push_back(Move("Feint", 4, 0, 0, 5, "You feint an attack to throw the enemy off balance!", 100, 0, 0));
    abilities->push_back(Move("Serrated Edge", 5, 1, 4, 0, "A quick slice that leaves the enemy bleeding!", 80, 0, 0));
    abilities->push_back(Move("Brace", 6, 0, 0, 0, "You brace for the enemies next attack!", 100, 0, 10));
}

Player::Player(int h, int att, int def)
{
    health = h;
    defense = ((7-def)+6)*10;
    maxHealth = h;
    DOT = 0;
    pAttack = att;
    accUp = false;
    baseHealth = h;
    baseAtt = att;
    baseDef = def;
    prevMove = -1;
    moves = new vector<Move>();
    abilities = new vector<Move>();
    abilities->push_back(Move("Heavy Swing", 1, 4, 0, 0, "A heavy strike at the foe!", 60, 0, 0));
    abilities->push_back(Move("Swift Jab", 2, 2, 0, 0, "A quick jab with the blunt of your weapon!", 90, 0, 0));
    abilities->push_back(Move("Gaslight", 3, 0, 0, 0, "You berate the enemy and make them believe they are weak!", 70, 5, 0));
    abilities->push_back(Move("Feint", 4, 0, 0, 5, "You feint an attack to throw the enemy off balance!", 90, 0, 0));
    abilities->push_back(Move("Serrated Edge", 5, 1, 4, 0, "A quick slice that leaves the enemy bleeding!", 80, 0, 0));
    abilities->push_back(Move("Brace", 6, 0, 0, 0, "You brace for the enemies next attack!", 90, 0, 10));
}

//randomly chooses what action the enemy will take to beat the player
void Player::enemyAttack(Enemy* e)
{
    srand(time(0));
    rand();
    int choice = rand()%4;

    if(choice == 0||choice == 1)
    {
        cout << "The enemy swings out!" << endl;
        int damage = (int)(e->getAttack()*(defense/100.0)) + rand()%7 - 3;
        health = health - damage;
        cout << "It deals " << damage << " damage" << endl;
    }
    if(choice == 2)
    {
        cout << "The enemy conserves energy to bolster its attack!" << endl;
        if(e->getAttack()<e->getBaseAtt()*2+1)
        {
            e->setAttack(e->getAttack()+2);
        }
    }
    if(choice == 3)
    {
        cout << "The enemy buckles down to defend against your strikes!" << endl;
        if(e->getDefense()>=60)
        {
            e->setDefense(e->getDefense()-10);
        }
    }
    displayStats(e);
}

void Player::attack(Enemy* e)
{
    //gets player move choice
    cout << "Which move will you use on the enemy?" << endl;

    for(int i = 0;i<moves->size();i++)
    {
        cout << i+1 << ")  " << moves->at(i).getName() << endl;
    }
    
    int move = -1;
    cin >> move;
    while(cin.fail()||move<1||move>moves->size())
    {
        cin.clear();
        cin.ignore();
        cout << "Enter a valid move number" << endl;
        cin >> move;
    }

    cout << moves->at(move-1).getDescription() << endl;

    //move application
    
    //deciding if the move hits
    srand(time(0));
    rand();
    int accRoll = rand()%10+1;
    int moveAcc = moves->at(move-1).getAccuracy();
    
    if(accUp)
    {
        moveAcc = moveAcc + 10;
    }

    if(accRoll*10<=moveAcc)
    {
        cout << "The move lands!" << endl;

        //damage calc
        if(moves->at(move-1).getDamage()>0)
        {
        int dam = (int)((moves->at(move-1).getDamage()*pAttack) * (e->getDefense()/100.0)) + (rand()%5-2);
        cout << "You deal " << dam << " damage to the enemy" << endl;
        e->setHealth(e->getHealth()-dam);
        }

        //DOT calc
        if(moves->at(move-1).getDOT()>0)
        {
            int dot = moves->at(move-1).getDOT() + (rand()%3-1);
            DOT = dot;
        }

        //Defense increase calc
        if(moves->at(move-1).getPDefense()>0)
        {
            if(defense>=60)
            {
                defense = defense - moves->at(move-1).getPDefense();
            }
        }

        //combo calc between move and previous move
        combo(e, moves->at(move-1));

        //set accuracy up if the jab lands
        if(moves->at(move-1).getNumber()==2)
        {
            accUp = true;
            cout << "Landing the jab will increase the accuracy of your next move" << endl;
        }

        //set new previous move
        prevMove = moves->at(move-1).getNumber();

    }
    else
    {
        cout << "You miss ... unfortunate." << endl;
        prevMove = 0; //Resets the combo feature
    }

    //Decide if DOT continues and apply damage
    if(DOT>0)
    {
        int dotCont = rand()%3;
        if(dotCont == 0)
        {
            cout << "The enemy ceases to bleed" << endl;
            DOT = 0;
        }
        else
        {
            cout << "The enemy continues to bleed" << endl;
            int dam = DOT + (rand()%3-1);
            e->setHealth(e->getHealth()-dam);
            cout << "The enemy takes " << dam << " points of bleed damage" << endl;
            displayStats(e);
        }
    }
    
}

//Gives bonus effects to the move used on the enemy based on the previous move (if it connects)
void Player::combo(Enemy* e, Move& m)
{
    srand(time(0));
    rand();
    if(prevMove==0)
    {
        cout << "Because your previous move did not connect you were unable to combo the enemy" << endl;
    }
    if(prevMove==1)
    {
        if(m.getNumber()==1)
        {
            int dam = (6*(e->getDefense()/100.0)) + (rand()%5-2);
            e->setHealth(e->getHealth()-dam);
            cout << "With consecutive brutalizing attacks you deal extra "<< dam << " damage" << endl; 
        }
        if(m.getNumber()==2)
        {
            int dam = (4*(e->getDefense()/100.0)) + (rand()%3-1);
            e->setHealth(e->getHealth()-dam);
            cout << "Taking advantage of the enemy's stagger you are able to hit a weak point with your jab and deal " << dam << " extra damage" << endl;
        }
        if(m.getNumber()==3)
        {
            if(e->getAttack()>=e->getBaseAtt()+2)
            {
                e->setAttack(e->getAttack()-4);
            }
            cout << "Having been beaten down by your previous attack the enemy loses some of its will to fight" << endl;
        }
        if(m.getNumber()==4)
        {
            cout << "Having already staggered the enemy with a heavy swing your feint goes unnoticed" << endl;
        }
        if(m.getNumber()==5)
        {
            DOT = DOT + 2;
            cout << "Due to staggering the enemy with your heavy strike the knife is able to cut deeper and cause the enemy to bleed more quickly" << endl;
        }
        if(m.getNumber()==6)
        {
            cout << "After staggering the enemy you brace in case of a counter attack" << endl;
        }
    }
    if(prevMove==2)
    {
        accUp = false;
        if(m.getNumber()==1)
        {
            int dam = (8*(e->getDefense()/100.0)) + (rand()%5-2);
            e->setHealth(e->getHealth()-dam);
            cout << "Due to the jab your heavy swing is able to land a more critical blow and deal "<< dam << " damage" << endl;
        }
        if(m.getNumber()==2)
        {
            e->setHealth(e->getHealth()-1);
            cout << "Jabbing twice allows the second to deal an extra 1 damage" << endl;
        }
        if(m.getNumber()==3)
        {
            if(e->getAttack()>=e->getBaseAtt()+1)
            {
                e->setAttack(e->getAttack()-1);
            }
            cout << "Having only taken a small amount of damage from the jab the enemy is barely swayed by your attempts to break its will" << endl;
        }
        if(m.getNumber()==4)
        {
            if(e->getDefense()<e->getBaseDef())
            {
                e->setDefense(e->getDefense()+10);
            }
            cout << "After the jab the enemy is sternly focused on you and falls completely off balance to your faint" << endl;
        }
        if(m.getNumber()==5)
        {
            e->setHealth(e->getHealth()-2);
            cout << "The jab makes the enemy unprepared to deal with the swiftness of your blade and you deal 2 extra damage" << endl;
        }
        if(m.getNumber()==6)
        {
            cout << "After jabbing the enemy you brace in case of a counter attack" << endl;
        }
    }
    if(prevMove==3)
    {
        if(m.getNumber()==1)
        {
            int dam = (6*(e->getDefense()/100.0)) + (rand()%5-2);
            e->setHealth(e->getHealth()-dam);
            cout << "With your enemies confidence lowered the strike deals "<< dam << " extra damage" << endl;
        }
        if(m.getNumber()==2)
        {
            int dam = (4*(e->getDefense()/100.0)) + (rand()%3-1);
            e->setHealth(e->getHealth()-dam);
            cout << "With your enemies confidence lowered the jab deals " << dam << "extra damage" << endl;
        }
        if(m.getNumber()==3)
        {
            if(e->getAttack()<e->getBaseAtt()*2+1)
            {
                e->setAttack(e->getAttack()+2);
            }
            cout << "After attempting to gaslight the enemy twice they begin to catch on to your ploy" << endl;
        }
        if(m.getNumber()==4)
        {
            if(e->getDefense()<e->getBaseDef())
            {
                e->setDefense(e->getDefense()+15);
            }
            cout << "With their confidence lowered the enemy is slower to react to your feint and is left more open" << endl;
        }
        if(m.getNumber()==5)
        {
            e->setHealth(e->getHealth()-2);
            cout << "Your verbal berration makes the enemy unprepared to deal with the swiftness of your blade and you deal 2 extra damage" << endl;
        }
        if(m.getNumber()==6)
        {
            if(defense>=55)
            {
                defense = defense - 5;
            }
            cout << "With the enemy in dower spirits you feel more confident in your defense" << endl;
        }
    }
    if(prevMove==4)
    {
        if(m.getNumber()==1)
        {
            int dam = (10*(e->getDefense()/100.0)) + (rand()%5-2);
            e->setHealth(e->getHealth()-dam);
            cout << "Feinting massively opens up the enemy for the strike to deal "<< dam << " extra damage" << endl;
        }
        if(m.getNumber()==2)
        {
            int dam = (6*(e->getDefense()/100.0)) + (rand()%3-1);
            e->setHealth(e->getHealth()-dam);
            cout << "Feinting massively opens up the enemy for the jab to deal "<< dam << " extra damage" << endl;
        }
        if(m.getNumber()==3)
        {
            if(e->getAttack()<e->getBaseAtt()*2+1)
            {
                e->setAttack(e->getAttack()+4);
            }
            cout << "Feinting an attack and then berrating the enemy with verbal abuse sends them into a rage" << endl;
        }
        if(m.getNumber()==4)
        {
            health = health - 3;
            prevMove = 0;
            cout << "Catching your second feint the enemy pushes you back dealing 3 damage" << endl;
        }
        if(m.getNumber()==5)
        {
            DOT = DOT + 3;
            cout << "Due to your feint the enemy is thrown off balance and the knife is able to cut deeper and cause them to bleed more quickly" << endl;
        }
        if(m.getNumber()==6)
        {
            cout << "Feinting before your brace throws you off balance and makes it less effective" << endl;
            defense = defense+5;
        }
    }
    if(prevMove==5)
    {
        if(m.getNumber()==1)
        {
            int dot = 5 + (rand()%3-1);
            DOT = dot;
            cout << "Striking the enemies wound causes it to continue bleeding" << endl;
        }
        if(m.getNumber()==2)
        {
            int dam = (4*(e->getDefense()/100.0)) + (rand()%3-1);
            e->setHealth(e->getHealth()-dam);
            cout << "The bleeding wound weakens the enemy and causes the jab to deal "<< dam << " extra damage" << endl;
        }
        if(m.getNumber()==3)
        {
            DOT = DOT + 2;
            cout << "With demeaned spirits the enemy has issues recovering from the knife wound" << endl;
        }
        if(m.getNumber()==4)
        {
            cout << "Your feint sets up for the next attack as the enemy bleeds" << endl;
        }
        if(m.getNumber()==5)
        {
            DOT = DOT + 4;
            cout << "Slicing the enemy again they begin to bleed extensively" << endl;
        }
        if(m.getNumber()==6)
        {
            cout << "As you brace the enemy continues to bleed" << endl;
        }
    }
    if(prevMove==6)
    {
        if(m.getNumber()==1)
        {
            cout << "Because you braced you are unable to get any bonus effects" << endl;
        }
        if(m.getNumber()==2)
        {
             cout << "Because you braced you are unable to get any bonus effects" << endl;
        }
        if(m.getNumber()==3)
        {
             cout << "Because you braced you are unable to get any bonus effects" << endl;
        }
        if(m.getNumber()==4)
        {
             cout << "Because you braced you are unable to get any bonus effects" << endl;
        }
        if(m.getNumber()==5)
        {
             cout << "Because you braced you are unable to get any bonus effects" << endl;
        }
        if(m.getNumber()==6)
        {
             cout << "Because you braced you are unable to get any bonus effects" << endl;
        }
    }
}

void Player::setAttack(int a)
{
    pAttack = a;
}

int Player::getHealth() const
{
    return health;
}

int Player::getDefense() const
{
    return defense;
}

void Player::setHealth(int h)
{
    health = h;
}

//displays the player and enemy stats to the text file
void Player::displayStats(Enemy* e) const
{
    ofstream file("CurrentStats.txt");

    if(file.fail())
    {
        cerr << "File failed to open" << endl;
        return;
    }

    file << "Player:\n\nHealth: " << health << "\nAttack: " << pAttack << "\nDefense: " << 100-defense << "\n" << endl;
    file << e->getName() << ":\n\nHealth: " << e->getHealth() << "\nAttack: " << e->getAttack() << "\nDefense: " << 100-e->getDefense() << "\n" << endl;

    file.close();
}

//resets player stats for future battles
void Player::reset()
{
    health = baseHealth;
    pAttack = baseAtt;
    defense = baseDef;
}


void Player::addAbility()
{
    cout << "Which move would you like to add?" << endl;

    //Randomly selects moves to for selection by the player to add to their kit
    srand(time(0));
    rand();
    int m1 = rand()%abilities->size();
    int m2 = m1;
    while(m2==m1)
    {
        m2 = rand()%abilities->size();
    }
    int m3 = m1;
    while(m3==m1||m3==m2)
    {
        m3 = rand()%abilities->size();
    }
    cout << "1)  " << abilities->at(m1).getName() << endl;
    cout << "2)  " << abilities->at(m2).getName() << endl;
    cout << "3)  " << abilities->at(m3).getName() << endl;

    int choice = 0;
    cin >> choice;
    if(cin.fail()||choice<1||choice>3)
    {
        cin.clear();
        cin.ignore();
        cout << "Enter a valid number" << endl;
        cin >> choice;
    }
    
    if(moves->size()<3)
    {
        if(choice == 1)
        {
            moves->push_back(abilities->at(m1));
            cout << abilities->at(m1).getName() << " was added!\n" << endl;
            abilities->erase(abilities->begin()+m1);
        }
        if(choice == 2)
        {
            moves->push_back(abilities->at(m2));
            cout << abilities->at(m2).getName() << " was added!\n" << endl;
            abilities->erase(abilities->begin()+m2);
        }
        if(choice == 3)
        {
            moves->push_back(abilities->at(m3));
            cout << abilities->at(m3).getName() << " was added!\n" << endl;
            abilities->erase(abilities->begin()+m3);
        }
    }
    else
    {
        cout << "Your move list is full. Which move would you like to replace?" << endl;

        cout << "0)  Keep the same moves" << endl;
        for(int i = 0;i<moves->size();i++)
        {
            cout << i+1 << ")  " << moves->at(i).getName() << endl;
        }

        int replace = -1;
        cin >> replace;
        while(cin.fail()||replace<0||replace>3)
        {
            cin.clear();
            cin.ignore();
            cout << "Enter a valid number" << endl;
            cin >> replace;
        }

        if(choice == 1)
        {
            moves->push_back(abilities->at(m1));
            abilities->erase(abilities->begin()+m1);
            moves->erase(moves->begin());
            cout << abilities->at(m1).getName() << "was added!" << endl;
        }
        if(choice == 2)
        {
            moves->push_back(abilities->at(m2));
            abilities->erase(abilities->begin()+m2);
            moves->erase(moves->begin()+1);
            cout << abilities->at(m2).getName() << "was added!" << endl;
        }
        if(choice == 3)
        {
            moves->push_back(abilities->at(m3));
            abilities->erase(abilities->begin()+m3);
            moves->erase(moves->begin()+2);
            cout << abilities->at(m3).getName() << "was added!" << endl;
        }

    }
}