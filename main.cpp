/* CSCI 200: Final Project
 *
 * Author: Paul Russell (INSERT_NAME)
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): N/A
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Determines a players stats and then pits them against an enemy until one dies (MORE_COMPLETE_DESCRIPTION_HERE)
 */
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <fstream>


using namespace std;



int main()
{
    cout << "Before the battle begins be sure to:\n1. Enlarge your terminal\n2. Open the CurrentStats.txt document to monitor you and the enemy's stats" << endl;
    cin.ignore();

    cout << "Now its time to decide which stats you want to have!" << endl;
    cin.ignore();

    int points = 5;
    int choice = 0;
    int health = 1;
    int att = 1;
    int def = 1;
    //allows the player to allowicate stats to specific areas
    while(choice!=7)
    {
        cout << "Your current point distribution:\nPoints to use: " << points << "\nPoints in health: " << health << "\nPoints in attack: " << att << "\nPoints in defense: " << def << endl;
        cout << "1)  Add a point to health\n2)  Remove a point from health\n3)  Add a point to attack\n4)  Remove a point from attack\n5)  Add a point to defense\n6)  Remove a point from defense\n7)  Confirm stat distribution" << endl;
        cin >> choice;
        while(cin.fail()||choice<1||choice>7)
        {
            cin.clear();
            cin.ignore();
            cout << "Enter a valid number" << endl;
            cin >> choice;
        }

        if(choice==1)
        {
            if(points>0)
            {
                health++;
                points--;
            }
            else
            {
                cout << "No more points to give" << endl;
            }
        }
        if(choice==2)
        {
            if(health>1)
            {
                health--;
                points++;
            }
            else
            {
                cout << "The minimum a stat can have is 1" << endl;
            }
        }
        if(choice==3)
        {
            if(points>0)
            {
                att++;
                points--;
            }
            else
            {
                cout << "No more points to give" << endl;
            }
        }
        if(choice==4)
        {
            if(att>1)
            {
                att--;
                points++;
            }
            else
            {
                cout << "The minimum a stat can have is 1" << endl;
            }
        }
        if(choice==5)
        {
            if(points>0)
            {
                def++;
                points--;
            }
            else
            {
                cout << "No more points to give" << endl;
            }
        }
        if(choice==6)
        {
            if(def>1)
            {
                def--;
                points++;
            }
            else
            {
                cout << "The minimum a stat can have is 1" << endl;
            }
        }
    }
    health = health*25;
    def = def*2;

    //creates the player based on the stats chosen and also makes the enemy
    Player* player = new Player(health, att, def);
    Enemy* e1 = new Enemy(1);

    cout << "Now that you have picked your stats its time to decide which moves you want to use!\n" << endl;
    cin.ignore();

    //The Player can add 3 abilities to use in the fight
    player->addAbility();
    player->addAbility();
    player->addAbility();

    cout << "A " << e1->getName() << " approaches...\nIt appears you are destined to fight!" << endl;
    cin.ignore();
    
    //The player and eneemy take turns attacking until one dies
    while(player->getHealth()>0&&e1->getHealth()>0)
    {
        player->attack(e1);
        player->enemyAttack(e1);
    }

    if(player->getHealth()<=0)
    {
        cout << "Shaken by your injuries you sink to the ground\n\nGame Over" << endl;
    }
    else
    {
        cout << "You stand high over the corpse of your enemy\n\nYou Win!" << endl;
    }

    //clears the file being used to display the player and enemy stats throughout the fight
    ofstream file("CurrentStats.txt");

    if(file.fail())
    {
        cerr << "File failed to open" << endl;
        return -1;
    }

    file << "";
    file.close();
    delete player;
    delete e1;
}