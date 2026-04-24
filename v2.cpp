#include <iostream>
#include <windows.h>
#include <random>
#include <conio.h>
using namespace std;

// FUNCTION PROTOTYPES

// UI/header prototypes
void printGameHeader();
int printUserInterface();
void printInstructionHeader();
void printInstructions();
void printStoryLine();

// Special Effects prototypes
void typewriterEffect(const string &text);
void playLaserSound();
void playExplosionSound();
void dramaticSoundEffect();

// random prototype
random_device rd;
mt19937 gen(rd());
int generateRandomNumber(int min, int max);
void spawnSpaceship(int &spaceshipX, int &spaceshipY);

// maze prototypes
void gotoxy(int, int);
void printMaze();
void printSpaceship(int sx, int sy);
void eraseSpaceship(int sx, int sy);
char getCharAtxy(short int x, short int y);
void resizeConsoleToMaxScreenSize();
string setColor(unsigned short color);
void cursorHide();

// player prototypes
void printPlayerGunRight(int px, int py);
void printPlayerGunLeft(int px, int py);
void erasePlayer(int px, int py);
void movePlayerleft(int &px, int &py, char gunDirection);
void movePlayerright(int &px, int &py, char gunDirection);
void movePlayerup(int &px, int &py, char gunDirection);
void movePlayerdown(int &px, int &py, char gunDirection);

// enemy prototypes
void printEnemy(int ex[], int ey[], int index);
void printArmedEnemy(int ex[], int ey[], int index);
void printBossEnemy(int ex[], int ey[], int index);
void eraseEnemy(int ex[], int ey[], int index);
void moveEnemy(bool goRight, int ex[], int ey[], int index, int enemyHealth[], int playerHealth);
void swapDirection(bool &goRight, int ex[], int ey[], int index);

// laser prototypes
void printLaserShooter(int lx[], int ly[], int index);
void printLaser(int x, int y);
void eraseLaser(int laserX, int laserY);
void createLasers(int lx[], int ly[], int laserX[], int laserY[], char laserDirection[], int &laserFired, int px, int py);
void moveLasers(int &playerHealth, int px, int py, int &playerLives, int laserX[], int laserY[], char laserDirection[], int &laserFired);
void deleteLasers(int laserX[], int laserY[], char laserDirection[], int &laserFired, int index);

// player bullet prototypes
void printBullet(int px, int py, char gunDirection);
void removeBullet(int px, int py, char gunDirection);
void moveBullet(int &bulletFired, int bulletsX[], int bulletsY[], char bulletDirection[], int ex[], int ey[], int enemyHealth[]);
void createBullets(int px, int py, int &bulletFired, int bulletsX[], int bulletsY[], char gunDirection, char bulletDirection[]);
void checkEnemyBulletCollision(int bulletsX[], int bulletsY[], char bulletDirection[], int &bulletFired, int ex[], int ey[], int enemyHealth[], int &killCount);

// enemy bullet prototypes
void printEnemyBullet(int, int);
void createEnemyBullets(int ex[], int ey[], int px, int py, int enemyBulletsX[], int enemyBulletsY[], char enemyBulletDirection[], int &enemyBulletFired, int enemyHealth[]);
void moveEnemyBullet(int &playerHealth, int px, int py, int &playerLives, int enemyBulletsX[], int enemyBulletsY[], char enemyBulletDirection[], int &enemyBulletFired);
void eraseEnemyBullet(int bulletX, int bulletY);
void deleteEnemyBullets(int index, int enemyBulletsX[], int enemyBulletsY[], char enemyBulletDirection[], int &enemyBulletFired);

// health prototypes
void checkEnemyHealth(int ex[], int ey[], int enemyHealth[], int i, int playerHealth, int &killCount);
void checkPlayerHealth(int &playerHealth, int &playerLives);
void checkPlayerLives(int &playerLives);
void printPlayerHealth();

// end game prototypes
bool checkWinCondition(int killCount, int spaceshipX, int spaceshipY, int px, int py, bool &gameWon);

main()
{
    // LOCAL VARIABLE DECLARATION
    bool gameWon = false; // check game status

    int sx = 13, sy = 4;  // spaceship coordinates
    int px = 11, py = 35; // player coordinates

    int playerHealth = 100;
    int playerLives = 5;

    char gunDirection = 'R';

    // LOCAL ARRAY DECLARATION
    int lx[2] = {120, 120}; // laser coordinates
    int ly[2] = {14, 28};

    int ex[11] = {23, 33, 113, 11, 73, 15, 110, 11, 40, 22, 63}; // 11 enemies' coordinated
    int ey[11] = {35, 30, 30, 26, 26, 22, 18, 14, 8, 10, 5};

    bool goRight[11] = {true, true, true, true, true, true, true, true, true, true, true}; // 11 enemies' movement direction

    int enemyHealth[11] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}; // 11 enemies' health
    int enemyCount = 11;
    int killCount = 0;

    int bulletsX[200]; // player bullet arrays
    int bulletsY[200];
    char bulletDirection[200];
    int bulletFired = 0;

    int laserX[200]; // laser bullet arrays
    int laserY[200];
    char laserDirection[200];
    int laserFired = 0;

    int enemyBulletsX[200]; // enemy bullet arrays
    int enemyBulletsY[200];
    char enemyBulletDirection[200];
    int enemyBulletFired = 0;

    // LOCAL POINTERS DECLARATION
    int *ptrpx = &px, *ptrpy = &py; // player movement pointers

    while (true)
    {
        system("cls");
        // resizeConsoleToMaxScreenSize();

        printGameHeader();
        int UIoption = printUserInterface();

        if (UIoption == 1) // read instructions
        {
            system("cls");
            printInstructionHeader();
            printInstructions();
            getch();
            continue; // go back to user interface
        }

        else if (UIoption == 2) // start game
        {
            system("cls");

            int story;
            gotoxy(55, 25);
            cout << "if you wish to skip the story line enter 0, if not enter 1...";
            cin >> story;

            if (story == 1)
            {
                system("cls");
                printStoryLine();
            }

            system("cls");
            cursorHide();

            printMaze();
            printSpaceship(sx, sy);
            printPlayerGunRight(px, py);

            printLaserShooter(lx, ly, 0);
            printLaserShooter(lx, ly, 1);

            printPlayerHealth();

            printEnemy(ex, ey, 0);
            printEnemy(ex, ey, 1);
            printEnemy(ex, ey, 2);
            printEnemy(ex, ey, 3);
            printEnemy(ex, ey, 4);
            printArmedEnemy(ex, ey, 5);
            printArmedEnemy(ex, ey, 6);
            printArmedEnemy(ex, ey, 7);
            printArmedEnemy(ex, ey, 8);
            printBossEnemy(ex, ey, 9);
            printBossEnemy(ex, ey, 10);

            dramaticSoundEffect();

            for (int i = 0; i < 11; i++)
            {
                checkEnemyHealth(ex, ey, enemyHealth, i, playerHealth, killCount);
            }

            int iterationCount = 0;

            while (killCount <= 10) //&& checkWinCondition(killCount, sx, sy, px, py, gameWon))
            {

                iterationCount++;

                if (iterationCount >= 100)
                {
                    spawnSpaceship(sx, sy);
                    iterationCount = 0;
                }

                if (GetAsyncKeyState(VK_LEFT))
                {
                    if ((getCharAtxy(px - 1, py) == ' ') || (getCharAtxy(px - 1, py) == '*') || (getCharAtxy(px - 1, py) == '+'))
                    {
                        movePlayerleft(px, py, gunDirection);
                    }
                }
                if (GetAsyncKeyState(VK_RIGHT))
                {
                    if ((getCharAtxy(px + 4, py) == ' ') || (getCharAtxy(px + 4, py) == '*') || (getCharAtxy(px - 1, py) == '+'))
                    {
                        movePlayerright(*ptrpx, *ptrpy, gunDirection);
                    }
                }
                if (GetAsyncKeyState(VK_UP))
                {
                    if (getCharAtxy(px, py - 1) == ' ')
                    {
                        movePlayerup(*ptrpx, *ptrpy, gunDirection);
                    }
                }
                if (GetAsyncKeyState(VK_DOWN))
                {
                    if (getCharAtxy(px, py + 3) == ' ')
                    {
                        movePlayerdown(*ptrpx, *ptrpy, gunDirection);
                    }
                }
                if (GetAsyncKeyState('V'))
                {
                    gunDirection = 'L';
                    printPlayerGunLeft(px, py);
                }
                if (GetAsyncKeyState('B'))
                {
                    gunDirection = 'R';
                    printPlayerGunRight(px, py);
                }
                if (GetAsyncKeyState(VK_SPACE))
                {
                    createBullets(px, py, bulletFired, bulletsX, bulletsY, gunDirection, bulletDirection);
                }

                moveBullet(bulletFired, bulletsX, bulletsY, bulletDirection, ex, ey, enemyHealth);
                checkEnemyBulletCollision(bulletsX, bulletsY, bulletDirection, bulletFired, ex, ey, enemyHealth, killCount);

                for (int i = 0; i < 11; i++)
                {
                    checkEnemyHealth(ex, ey, enemyHealth, i, playerHealth, killCount);
                }

                createEnemyBullets(ex, ey, px, py, enemyBulletsX, enemyBulletsY, enemyBulletDirection, enemyBulletFired, enemyHealth);
                moveEnemyBullet(playerHealth, px, py, playerLives, enemyBulletsX, enemyBulletsY, enemyBulletDirection, enemyBulletFired);

                for (int i = 0; i < enemyCount - 6; i++)
                {
                    if (enemyHealth[i] > 0)
                    {
                        moveEnemy(goRight[i], ex, ey, i, enemyHealth, playerHealth);
                        swapDirection(goRight[i], ex, ey, i);
                    }
                }

                createLasers(lx, ly, laserX, laserY, laserDirection, laserFired, px, py);
                moveLasers(playerHealth, px, py, playerLives, laserX, laserY, laserDirection, laserFired);

                if (playerLives == 0)
                {
                    checkPlayerLives(playerLives);
                    return 0;
                }

                // if (checkWinCondition(killCount, sx, sy, px, py, gameWon))
                // {
                //     break;
                // }
                // Sleep(10);
            }

            setColor(15);
            gotoxy(130, 11);
            cout << "       YOU WIN";
            break;
        }

        else if (UIoption == 3) // exit game
        {
            return 0;
        }

        else // validation
        {
            gotoxy(70, 32);
            cout << "Invalid option...";
            gotoxy(70, 34);
            cout << "Press any key to try again";
            getch();
            continue;
        }
    }
}

void printGameHeader()
{
    setColor(3);
    gotoxy(20, 9);
    cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    gotoxy(20, 10);
    cout << "//                                                                                                                              //" << endl;
    gotoxy(20, 11);
    cout << "//    ____    __           ___    ___                          ____                                                ___          //" << endl;
    gotoxy(20, 12);
    cout << "//   /\\  _`\\ /\\ \\__       /\\_ \\  /\\_ \\                        /\\  _`\\                          __                 /\\_ \\         //" << endl;
    gotoxy(20, 13);
    cout << "//   \\ \\,\\L\\_\\ \\ ,_\\    __\\//\\ \\ \\//\\ \\      __    _ __       \\ \\,\\L\\_\\  __  __  _ __   __  __/\\_\\  __  __    __  \\//\\ \\        //" << endl;
    gotoxy(20, 14);
    cout << "//    \\/_\\__ \\ \\\\ \\/  /'__`\\\\ \\ \\  \\ \\ \\   /'__`\\ /\\`'__\\      \\/_\\__ \\ /\\ \\/\\ \\/\\`'__\\/\\ \\/\\ \\/\\ \\/\\ \\/\\ \\ /'__`\\  \\ \\ \\       //" << endl;
    gotoxy(20, 15);
    cout << "//      /\\ \\L\\ \\ \\ \\_/\\  __/ \\_\\ \\_ \\_\\ \\_/\\ \\L\\.\\\\ \\ \\/         /\\ \\L\\ \\ \\ \\_\\ \\ \\ \\/ \\ \\ \\_/ \\ \\ \\ \\ \\_/ /\\ \\L\\.\\_ \\_\\ \\_     //" << endl;
    gotoxy(20, 16);
    cout << "//      \\ `\\____\\ \\__\\ \\____\\/\\____\\/\\____\\ \\__/.\\_\\ \\_\\         \\ `\\____\\ \\____/\\ \\_\\  \\ \\___/ \\ \\_\\ \\___/\\ \\__/.\\_\\/\\____\\    //" << endl;
    gotoxy(20, 17);
    cout << "//       \\/_____/\\/__/\\/____/\\/____/\\/____/\\/__/\\/_/\\/_/          \\/_____/\\/___/  \\/_/   \\/__/   \\/_/\\/__/  \\/__/\\/_/\\/____/    //" << endl;
    gotoxy(20, 18);
    cout << "//                                                                                                                              //" << endl;
    gotoxy(20, 19);
    cout << "//                                                                                                                              //" << endl;
    gotoxy(20, 20);
    cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
}

int printUserInterface()
{
    setColor(6);
    int option;
    gotoxy(70, 24);
    cout << "1. Read Instructions";
    gotoxy(70, 26);
    cout << "2. Start Game";
    gotoxy(70, 28);
    cout << "3. Exit Game";
    gotoxy(70, 30);
    cout << "Enter your option: ";
    cin >> option;

    return option;
}

void printInstructionHeader()
{
    setColor(7);
    gotoxy(20, 3);
    cout << "                                                                                         __                               " << endl;
    gotoxy(20, 4);
    cout << "                                                                     __                 /\\ \\__  __                        " << endl;
    gotoxy(20, 5);
    cout << "        __      __      ___ ___      __        ___      __    __  __/\\_\\     __      __ \\ \\ ,_\\/\\_\\    ___     ___        " << endl;
    gotoxy(20, 6);
    cout << "      /'_ `\\  /'__`\\  /' __` __`\\  /'__`\\    /' _ `\\  /'__`\\ /\\ \\/\\ \\/\\ \\  /'_ `\\  /'__`\\\\ \\ \\/\\/\\ \\  / __`\\ /' _ `\\      " << endl;
    gotoxy(20, 7);
    cout << "     /\\ \\L\\ \\/\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\/\\  __/    /\\ \\/\\ \\/\\ \\L\\.\\\\ \\ \\_/ \\ \\ \\/\\ \\L\\ \\/\\ \\L\\.\\\\ \\ \\_\\ \\ \\/\\ \\L\\ \\/\\ \\/\\ \\     " << endl;
    gotoxy(20, 8);
    cout << "     \\ \\____ \\ \\__/.\\_\\ \\_\\ \\_\\ \\_\\ \\____\\   \\ \\_\\ \\_\\ \\__/.\\_\\ \\___/ \\ \\_\\ \\____ \\ \\__/.\\_\\ \\__\\\\ \\_\\ \\____/\\ \\_\\ \\_\\    " << endl;
    gotoxy(20, 9);
    cout << "      \\/___L\\ \\/__/\\/_/\\/_/\\/_/\\/_/\\/____/    \\/_/\\/_/\\/__/\\/_/\\/__/   \\/_/\\/___L\\ \\/__/\\/_/\\/__/ \\/_/\\/___/  \\/_/\\/_/    " << endl;
    gotoxy(20, 10);
    cout << "        /\\____/                                                              /\\____/                                      " << endl;
    gotoxy(20, 11);
    cout << "        \\_/__/                                                               \\_/__/                                       " << endl;
}
void printInstructions()
{
    setColor(6);
    gotoxy(20, 14);
    cout << "==============================================================";
    gotoxy(20, 15);
    cout << "=                                                            =";
    gotoxy(20, 16);
    cout << "=                  --< GAME OBJECTIVE >-                     =";
    gotoxy(20, 17);
    cout << "=                                                            =";
    gotoxy(20, 18);
    cout << "=   Survive the alien attacks, defeat at least 10 enemies,   =";
    gotoxy(20, 19);
    cout << "=   and reach the spaceship to escape the hostile planet.    =";
    gotoxy(20, 20);
    cout << "=                                                            =";
    gotoxy(20, 21);
    cout << "==============================================================";
    setColor(7);
    gotoxy(20, 23);
    cout << "==============================================================";
    gotoxy(20, 24);
    cout << "=                                                            =";
    gotoxy(20, 25);
    cout << "=                     --< GAME SETUP >--                     =";
    gotoxy(20, 26);
    cout << "=                                                            =";
    gotoxy(20, 27);
    cout << "=        1. Your player starts equipped with a gun.          =";
    gotoxy(20, 28);
    cout << "=        2. The spaceship spawns randomly in one of          =";
    gotoxy(20, 29);
    cout << "=                 two top areas of the maze.                 =";
    gotoxy(20, 30);
    cout << "=        3. Enemies and laser turrets are distributed        =";
    gotoxy(20, 31);
    cout << "=                    throughout the maze.                    =";
    gotoxy(20, 32);
    cout << "=                                                            =";
    gotoxy(20, 33);
    cout << "==============================================================";
    setColor(3);
    gotoxy(20, 35);
    cout << "==============================================================";
    gotoxy(20, 36);
    cout << "=                                                            =";
    gotoxy(20, 37);
    cout << "=                  --< GAME CONTROLS >--                     =";
    gotoxy(20, 38);
    cout << "=                                                            =";
    gotoxy(20, 39);
    cout << "=                Arrow Keys: Move the player.                =";
    gotoxy(20, 40);
    cout << "=                   V: Aim gun to the left.                  =";
    gotoxy(20, 41);
    cout << "=                   B: Aim gun to the right.                 =";
    gotoxy(20, 42);
    cout << "=                   Spacebar: Fire bullets.                  =";
    gotoxy(20, 43);
    cout << "=                                                            =";
    gotoxy(20, 44);
    cout << "==============================================================";
    setColor(3);
    gotoxy(84, 16);
    cout << "===========================================================";
    gotoxy(84, 17);
    cout << "=                                                         =";
    gotoxy(84, 18);
    cout << "=               --< GAMEPLAY RULES >--                    =";
    gotoxy(84, 19);
    cout << "=                                                         =";
    gotoxy(84, 20);
    cout << "=     1. Defeat enemies by shooting bullets at them.      =";
    gotoxy(84, 21);
    cout << "=                                                         =";
    gotoxy(84, 22);
    cout << "=     2. Health reduces by 1 when hit by lasers or        =";
    gotoxy(84, 23);
    cout << "=                     enemy bullets.                      =";
    gotoxy(84, 24);
    cout << "=                                                         =";
    gotoxy(84, 25);
    cout << "=      3. Lives decrease when health reaches 0.           =";
    gotoxy(84, 26);
    cout << "=                                                         =";
    gotoxy(84, 27);
    cout << "=     4. Destroy enemies or evade them to progress        =";
    gotoxy(84, 28);
    cout << "=                 towards the spaceship.                  =";
    gotoxy(84, 29);
    cout << "=                                                         =";
    gotoxy(84, 30);
    cout << "=   5. A kill count of at least 10 is required to win.    =";
    gotoxy(84, 31);
    cout << "=                                                         =";
    gotoxy(84, 32);
    cout << "=    6. Reach the spaceship with the required kills       =";
    gotoxy(84, 33);
    cout << "=                  to win the game.                       =";
    gotoxy(84, 34);
    cout << "=                                                         =";
    gotoxy(84, 35);
    cout << "=  7. Enjoy your adventure and make your daring escape!   =";
    gotoxy(84, 36);
    cout << "=                                                         =";
    gotoxy(84, 37);
    cout << "===========================================================";
    setColor(6);
    gotoxy(84, 39);
    cout << "===========================================================";
    gotoxy(84, 40);
    cout << "=                                                         =";
    gotoxy(84, 41);
    cout << "=           Enjoy your adventure and make your            =";
    gotoxy(84, 42);
    cout << "=                     daring escape!                      =";
    gotoxy(84, 43);
    cout << "=                                                         =";
    gotoxy(84, 44);
    cout << "=              Press any key to go back...                =";
    gotoxy(84, 45);
    cout << "=                                                         =";
    gotoxy(84, 46);
    cout << "===========================================================";
}

void printStoryLine()
{
    setColor(11);

    string narration =
        "\n\n\n\n\n\t\t\t\tThe year is 2147. Humanity's reach has stretched far into the galaxy, but so have its enemies. "
        "\n\n\n\t\t\t\tYou are the last survivor of a reconnaissance mission gone horribly wrong. Stranded on a hostile "
        "\n\n\n\t\t\t\talien planet teeming with relentless adversaries, your only hope lies in reaching the extraction "
        "\n\n\n\t\t\t\tspaceship that awaits in the labyrinthine maze of alien structures. The air crackles with the  "
        "\n\n\n\t\t\t\t   sound of alien lasers, and the ground trembles under the weight of approaching foes. "
        "\n\n\n\t\t\t\t     Your blaster is low on charge, but your determination burns brighter than ever. "
        "\n\n\n\t\t\t\t             Every step you take brings you closer to freedom or destruction."
        "\n\n\n\n\t\t\t\t\t                       DEFEAT THEM! OUTWIT THEM! SURVIVE! "
        "\n\n\n\t\t\t\t\t         The spaceship is your salvation, but it will not wait forever. "
        "\n\n\n\t\t\t\t\t     Will you escape this alien siege, or will the planet claim another soul?"
        "\n\n\n\n\n\t\t\t\t\t                          (Press any key to begin...)";

    typewriterEffect(narration);
    getch();
}

void typewriterEffect(const string &text)
{
    for (char c : text)
    {
        cout << c << flush;
        Beep(800, 30); // morse code sound effect
        Sleep(10);
    }
    cout << endl;
}

void printMaze()
{
    setColor(9);
    cout << endl;
    cout << "                               ####################################################################################################" << endl;
    cout << "                   ###############                                                                       ##                 ##   #################" << endl;
    cout << "            ######### ##                                                                                 ##                 ##                  ##########" << endl;
    cout << "         ###          ##                                                                                 ##                 ##                           ###" << endl;
    cout << "        ##            ##                                                                                 ##                 ##  --------( PLAYER )-------- ##" << endl;
    cout << "       ##                                                                                                                   ##                              ##" << endl;
    cout << "       ##                            #######################          ########################                              ##                               ##" << endl;
    cout << "       ##                            ##                                                     ##                              ##                               ##" << endl;
    cout << "       #####################         ##                                                     ##          ######################                               ##" << endl;
    cout << "        ##                           ##                                                     ##                              ##                              ##" << endl;
    cout << "        ##                           ##         ###############    ################         ##                              ##                             ##" << endl;
    cout << "        ##                           ##         ##        ##          ##         ##         ##                              ##                             ##" << endl;
    cout << "       ########       #################         ##        ##          ##         ##         #################################################################" << endl;
    cout << "      ##                                        ##        ##############         ##                                         ##                              ##" << endl;
    cout << "     ##                                         ##                               ##                                         ##  ------( KILL COUNT )------   ##" << endl;
    cout << "    ##                                          ##                               ##                                         ##                                ##" << endl;
    cout << "   ###############################################                               ##################        ###################                                 ##" << endl;
    cout << "   ##                                                                                                                       ##                                 ##" << endl;
    cout << "   ##                                                                                                                       ##                                 ##" << endl;
    cout << "    ##||                                                                                                                    #####################################" << endl;
    cout << "     ##==|=                                ###################################################################################                                 ##" << endl;
    cout << "      ##||                                                                                                                  ##  -------( ALIENS )--------     ##" << endl;
    cout << "       ##                                                                                                                   ##                               ##" << endl;
    cout << "        ##                                                                                                                  ##                              ##" << endl;
    cout << "        ####################################      #############################      #########################################                             ##" << endl;
    cout << "         ##                                                                                                                 ##                             ##" << endl;
    cout << "         ##                                                                                                                 ##                             ##" << endl;
    cout << "        ##                                                                                                                  ##                              ##" << endl;
    cout << "       ###################################################################################                                  ##                               ##" << endl;
    cout << "      ##                                                                                                                    ##                                ##" << endl;
    cout << "     ##                                                                                                                     ##                                 ##" << endl;
    cout << "    ##                                                                                                                      ##                                 ##" << endl;
    cout << "    ###############              #############################          ##############################          ##############                                 ##" << endl;
    cout << "    ##                           ##############################        ###############################                      ##                                ##" << endl;
    cout << "    ##                                                                                                                      ##                               ##" << endl;
    cout << "     ##                                                                                                                     ##                              ##" << endl;
    cout << "       ###                                                                                                                  ##                            ###" << endl;
    cout << "          #################                                                                                                 ##          ####################" << endl;
    cout << "                        #####################                                                                          ###################" << endl;
    cout << "                                       ##################################                         ##############################" << endl;
    cout << "                                                                       ############################" << endl;
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void resizeConsoleToMaxScreenSize()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    COORD coord;
    coord.X = screenWidth / 4;
    coord.Y = screenHeight / 8;

    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = coord.X - 1;
    rect.Bottom = coord.Y - 1;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);

    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);
}

string setColor(unsigned short color)
{

    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}

void cursorHide()
{
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}

// PLAYER FUNCTION DEFINITIONS
void printSpaceship(int sx, int sy)
{
    setColor(6);
    gotoxy(sx, sy);
    cout << "  /\\" << endl;
    gotoxy(sx, sy + 1);
    cout << " |==|" << endl;
    gotoxy(sx, sy + 2);
    cout << "/|++|\\" << endl;
    gotoxy(sx, sy + 3);
    cout << " ||||$$" << endl;
    gotoxy(sx, sy + 4);
    cout << " ^^^^" << endl;
}

void eraseSpaceship(int sx, int sy)
{
    gotoxy(sx, sy);
    cout << "    " << endl;
    gotoxy(sx, sy + 1);
    cout << "     " << endl;
    gotoxy(sx, sy + 2);
    cout << "      " << endl;
    gotoxy(sx, sy + 3);
    cout << "       " << endl;
    gotoxy(sx, sy + 4);
    cout << "      " << endl;
}

void printPlayerGunRight(int px, int py)
{
    setColor(6);
    gotoxy(px, py);
    cout << " 0 ";
    gotoxy(px, py + 1);
    cout << "/|\\T";
    gotoxy(px, py + 2);
    cout << "/ \\";
}

void printPlayerGunLeft(int px, int py)
{
    setColor(6);
    gotoxy(px, py);
    cout << "  0";
    gotoxy(px, py + 1);
    cout << "T/|\\";
    gotoxy(px, py + 2);
    cout << " / \\";
}

void erasePlayer(int px, int py)
{
    gotoxy(px, py);
    cout << "   ";
    gotoxy(px, py + 1);
    cout << "    ";
    gotoxy(px, py + 2);
    cout << "    ";
}

void movePlayerleft(int &px, int &py, char gunDirection)
{
    char hurdle1 = getCharAtxy(px - 1, py);
    char hurdle2 = getCharAtxy(px - 1, py + 1);
    char hurdle3 = getCharAtxy(px - 1, py + 2);
    if ((hurdle1 != ' ' && hurdle1 != '*' && hurdle1 != '+') || (hurdle2 != ' ' && hurdle2 != '*' && hurdle2 != '+') || (hurdle3 != ' ' && hurdle3 != '*' && hurdle3 != '+'))
    {
        return; // dont move in case of these hurdles
    }
    else
    {

        erasePlayer(px, py); // erase from previous coordinate
        px = px - 1;         // move to next coordinate to the left

        if (gunDirection == 'R') // direction from V and B keys
        {
            printPlayerGunRight(px, py); // print on next coordinate
        }
        else if (gunDirection == 'L')
        {
            printPlayerGunLeft(px, py); // print on next coordinate
        }
    }
}

void movePlayerright(int &px, int &py, char gunDirection)
{
    char hurdle1 = getCharAtxy(px + 3, py);
    char hurdle2 = getCharAtxy(px + 4, py + 1);
    char hurdle3 = getCharAtxy(px + 4, py + 2);
    if ((hurdle1 != ' ' && hurdle1 != '*' && hurdle1 != '+') || (hurdle2 != ' ' && hurdle2 != '*' && hurdle2 != '+') || (hurdle3 != ' ' && hurdle3 != '*' && hurdle3 != '+'))
    {
        return; // dont move in case of these hurdles
    }
    else
    {

        erasePlayer(px, py); // erase from previous coordinate
        px = px + 1;         // move to next coordinate to the right

        if (gunDirection == 'R') // direction from V and B keys
        {
            printPlayerGunRight(px, py); // print on next coordinate
        }
        else if (gunDirection == 'L')
        {
            printPlayerGunLeft(px, py); // print on next coordinate
        }
    }
}

void movePlayerup(int &px, int &py, char gunDirection)
{
    char hurdle1 = getCharAtxy(px, py - 1);
    char hurdle2 = getCharAtxy(px + 1, py - 1);
    char hurdle3 = getCharAtxy(px + 2, py - 1);
    char hurdle4 = getCharAtxy(px + 3, py);
    if ((hurdle1 != ' ' && hurdle1 != '*' && hurdle1 != '+') || (hurdle2 != ' ' && hurdle2 != '*' && hurdle2 != '+') ||
        (hurdle3 != ' ' && hurdle3 != '*' && hurdle3 != '+') || (hurdle4 != ' ' && hurdle4 != '*' && hurdle4 != '+'))
    {
        return; // dont move in case of these hurdles
    }
    else
    {
        erasePlayer(px, py); // erase from previous coordinate
        py = py - 1;         // move to next coordinate above

        if (gunDirection == 'R') // direction from V and B keys
        {
            printPlayerGunRight(px, py); // print on next coordinate
        }
        else if (gunDirection == 'L')
        {
            printPlayerGunLeft(px, py); // print on next coordinate
        }
    }
}

void movePlayerdown(int &px, int &py, char gunDirection)
{
    char hurdle1 = getCharAtxy(px, py + 3);
    char hurdle2 = getCharAtxy(px + 1, py + 3);
    char hurdle3 = getCharAtxy(px + 2, py + 3);
    char hurdle4 = getCharAtxy(px + 3, py + 3);
    if ((hurdle1 != ' ' && hurdle1 != '*' && hurdle1 != '+') || (hurdle2 != ' ' && hurdle2 != '*' && hurdle2 != '+') ||
        (hurdle3 != ' ' && hurdle3 != '*' && hurdle3 != '+') || (hurdle4 != ' ' && hurdle4 != '*' && hurdle4 != '+'))
    {
        return; // dont move in case of these hurdles
    }
    else
    {
        erasePlayer(px, py); // erase from previous coordinate
        py = py + 1;         // move to next coordinate down

        if (gunDirection == 'R') // direction from V and B keys
        {
            printPlayerGunRight(px, py); // print on next coordinate
        }
        else if (gunDirection == 'L')
        {
            printPlayerGunLeft(px, py); // print on next coordinate
        }
    }
}

// LASER FUNCTION DEFINITIONS

void printLaserShooter(int lx[], int ly[], int index)
{
    setColor(5);
    gotoxy(lx[index], ly[index]);
    cout << "==||";
    gotoxy(lx[index], ly[index] + 1);
    cout << "  |=";
    gotoxy(lx[index], ly[index] + 2);
    cout << "  ||";
}

void printLaser(int x, int y)
{
    setColor(13);
    gotoxy(x, y);
    cout << "+";
}

void createLasers(int lx[], int ly[], int laserX[], int laserY[], char laserDirection[], int &laserFired, int px, int py)
{
    for (int i = 0; i < 2; i++)
    {
        // check if the player is in range
        bool playerInRangeHorizontally = (px >= lx[i] - 30 && px <= lx[i] + 30);
        bool playerInRangeVertically = (py >= ly[i] - 1 && py <= ly[i] + 1);

        if (playerInRangeHorizontally && playerInRangeVertically)
        {
            laserX[laserFired] = lx[i]; // laser coordinates stored in arrays to avoid using loops
            laserY[laserFired] = ly[i];
            laserDirection[laserFired] = 'L';
            printLaser(laserX[laserFired], laserY[laserFired]); // print laser in front of the laser shooter
            laserFired++;                                       // laser count increase
        }
    }
}

void eraseLaser(int laserX, int laserY)
{
    gotoxy(laserX, laserY);
    cout << "               ";
}

void moveLasers(int &playerHealth, int px, int py, int &playerLives, int laserX[], int laserY[], char laserDirection[], int &laserFired)
{
    for (int i = 0; i < laserFired; i++)
    {
        // check if the laser hits the player
        bool laserHitsPlayer = (laserX[i] >= px && laserX[i] <= px + 3) &&
                               (laserY[i] >= py && laserY[i] <= py + 3);

        if (laserHitsPlayer)
        {
            checkPlayerHealth(playerHealth, playerLives); // player health decreases

            eraseLaser(laserX[i], laserY[i]);                            // erase laser on hitting the player
            deleteLasers(laserX, laserY, laserDirection, laserFired, i); // remove that laser and decrease the count
            i--;                                                         // cuz laser count decreases
            continue;
        }

        if (laserDirection[i] == 'L') // to move that laser
        {
            if (getCharAtxy(laserX[i] - 1, laserY[i]) == ' ')
            {
                eraseLaser(laserX[i], laserY[i]); // erase from peviously stored coordinates
                laserX[i] = laserX[i] - 1;        // move to next coordinates to the left
                printLaser(laserX[i], laserY[i]); // printon new coordnates
            }
            else // if laser goes out of bound /hits the maze then remove it
            {
                eraseLaser(laserX[i], laserY[i]);
                deleteLasers(laserX, laserY, laserDirection, laserFired, i);
                i--;
            }
        }
    }
}

void deleteLasers(int laserX[], int laserY[], char laserDirection[], int &laserFired, int index)
{
    for (int i = index; i < laserFired - 1; i++)
    {
        laserX[i] = laserX[i + 1];
        laserY[i] = laserY[i + 1];
        laserDirection[i] = laserDirection[i + 1];
    }
    laserFired--;
}

// ENEMY FUNCTION DEFINITIONS

void printEnemy(int ex[], int ey[], int index)
{
    setColor(2);
    gotoxy(ex[index], ey[index]);
    cout << "o.o";
    gotoxy(ex[index], ey[index] + 1);
    cout << "~|~";
    gotoxy(ex[index], ey[index] + 2);
    cout << "/ \\";
}

void printArmedEnemy(int ex[], int ey[], int index)
{
    setColor(13);
    gotoxy(ex[index], ey[index]);
    cout << "ooo";
    gotoxy(ex[index], ey[index] + 1);
    cout << "=|=";
    gotoxy(ex[index], ey[index] + 2);
    cout << "/ \\";
}

void printBossEnemy(int ex[], int ey[], int index)
{
    setColor(12);
    gotoxy(ex[index], ey[index]);
    cout << "oOo";
    gotoxy(ex[index], ey[index] + 1);
    cout << "=0=";
    gotoxy(ex[index], ey[index] + 2);
    cout << "/|\\";
}

void eraseEnemy(int ex[], int ey[], int index)
{
    gotoxy(ex[index], ey[index]);
    cout << "   ";
    gotoxy(ex[index], ey[index] + 1);
    cout << "   ";
    gotoxy(ex[index], ey[index] + 2);
    cout << "    ";
}

void moveEnemy(bool goRight, int ex[], int ey[], int index, int enemyHealth[], int playerHealth)
{
    eraseEnemy(ex, ey, index); // erase fom previous coordinates

    if (goRight == true)
    {
        ex[index] = (ex[index] + 1); // move to next coordinate to the right
        printEnemy(ex, ey, index);   // print at new coordinates
    }

    if (goRight == false)
    {
        ex[index] = (ex[index] - 1); // move to next coordinate to the left
        printEnemy(ex, ey, index);   // print at new coordinates
    }
}

void swapDirection(bool &goRight, int ex[], int ey[], int index)
{
    if (ex[index] <= 11) // maze left wall
    {
        goRight = true;
    }
    if (ex[index] >= 116) // maze right wall
    {
        goRight = false;
    }
}

// BULLET FUNCTIONS

void printBullet(int bulletX, int bulletY, char gunDirection)
{
    if (gunDirection == 'R') // direction acc to V B keys
    {
        setColor(6); // yellow color
        gotoxy(bulletX, bulletY);
        cout << ">";
    }
    else if (gunDirection == 'L')
    {
        setColor(6);
        gotoxy(bulletX, bulletY);
        cout << "<";
    }
}

void removeBullet(int bulletX, int bulletY, char gunDirection)
{
    gotoxy(bulletX, bulletY);
    cout << " ";
}

void createBullets(int px, int py, int &bulletFired, int bulletsX[], int bulletsY[], char gunDirection,
                   char bulletDirection[])
{
    if (bulletFired < 200) // max bullets 200
    {

        if (gunDirection == 'R')
        {
            bulletDirection[bulletFired] = 'R'; // store bullet direction
            bulletsX[bulletFired] = px + 5;     // store bullet coordinates in arrays
            bulletsY[bulletFired] = py + 1;
        }
        else if (gunDirection == 'L')
        {
            bulletDirection[bulletFired] = 'L'; // store bullet direction
            bulletsX[bulletFired] = px - 2;     // store bullet coordinates in arrays
            bulletsY[bulletFired] = py + 1;
        }
        printBullet(bulletsX[bulletFired], bulletsY[bulletFired], gunDirection); // print bullets on the coordinates stored
        bulletFired++;                                                           // increase bullet count
    }
}

void moveBullet(int &bulletFired, int bulletsX[], int bulletsY[], char bulletDirection[], int ex[], int ey[],
                int enemyHealth[])
{
    for (int i = 0; i < bulletFired; i++) // for all bullets fired by the player
    {
        if (bulletDirection[i] == 'R')
        {
            char hurdle1 = getCharAtxy(bulletsX[i] + 1, bulletsY[i]);
            char hurdle2 = getCharAtxy(bulletsX[i] + 2, bulletsY[i]);
            if (hurdle1 != '#' && hurdle2 != '#') // if empty space then move
            {
                removeBullet(bulletsX[i], bulletsY[i], 'R'); // erase from previous coordinates
                bulletsX[i] = bulletsX[i] + 2;               // move to new coordinates
                printBullet(bulletsX[i], bulletsY[i], 'R');  // print at new coordinates
            }
            else
            {
                removeBullet(bulletsX[i], bulletsY[i], 'R');
                for (int j = i; j < bulletFired - 1; j++) // delete bullet from game
                {
                    bulletsX[j] = bulletsX[j + 1];
                    bulletsY[j] = bulletsY[j + 1];
                    bulletDirection[j] = bulletDirection[j + 1];
                }
                bulletFired--;
            }
        }

        else if (bulletDirection[i] == 'L')
        {
            char hurdle1 = getCharAtxy(bulletsX[i] - 1, bulletsY[i]);
            char hurdle2 = getCharAtxy(bulletsX[i] - 2, bulletsY[i]);

            if (hurdle1 != '#' && hurdle2 != '#') // if empty space then move
            {
                removeBullet(bulletsX[i], bulletsY[i], 'L'); // erase from previous coordinates
                bulletsX[i] = bulletsX[i] - 2;               // move to new coordinates
                printBullet(bulletsX[i], bulletsY[i], 'L');  // print at new coordinates
            }
            else
            {
                removeBullet(bulletsX[i], bulletsY[i], 'L');

                for (int j = i; j < bulletFired - 1; j++) // delete bullet from game
                {
                    bulletsX[j] = bulletsX[j + 1];
                    bulletsY[j] = bulletsY[j + 1];
                    bulletDirection[j] = bulletDirection[j + 1];
                }
                bulletFired--;
            }
        }
    }
}

void checkEnemyBulletCollision(int bulletsX[], int bulletsY[], char bulletDirection[], int &bulletFired, int ex[],
                               int ey[], int enemyHealth[], int &killCount)
{
    for (int i = 0; i < bulletFired; i++) // for all bullets fired by player
    {

        for (int j = 0; j < 11; j++) // for all 11 enemies
        {
            // check to see if bullet hits enemy
            if ((bulletsX[i] == ex[j] || bulletsX[i] == ex[j] + 1 || bulletsX[i] == ex[j] + 2) &&
                (bulletsY[i] == ey[j] || bulletsY[i] == ey[j] + 1 || bulletsY[i] == ey[j] + 2) && enemyHealth[j] > 0)
            {
                gotoxy(45, 15);
                enemyHealth[j] = enemyHealth[j] - 2;                        // decrease enemyHealth
                removeBullet(bulletsX[i], bulletsY[i], bulletDirection[i]); // remove bullet after it hits the enemy

                for (int k = i; k < bulletFired - 1; k++) // deleting bullets from the game
                {
                    bulletsX[k] = bulletsX[k + 1];
                    bulletsY[k] = bulletsY[k + 1];
                    bulletDirection[k] = bulletDirection[k + 1];
                }
                bulletFired--;
                if (enemyHealth[j] <= 0) // kill/erase anemy once its health hits zero
                {
                    eraseEnemy(ex, ey, j);
                    killCount++; // increment in kill count
                }
            }
        }
    }
}

void printEnemyBullet(int x, int y)
{
    setColor(5);
    gotoxy(x, y);
    cout << "*";
}

void createEnemyBullets(int ex[], int ey[], int px, int py, int enemyBulletsX[], int enemyBulletsY[],
                        char enemyBulletDirection[], int &enemyBulletFired, int enemyHealth[])
{

    for (int i = 5; i < 11; i++) // for armed and boss type enemies
    {
        // fire only when enemy is alive
        if (enemyHealth[i] > 0)
        {
            // check if player is in range of the enemy
            bool playerInRangeHorizontally = (px + 4 >= ex[i] - 60 && px <= ex[i] + 60);
            bool playerInRangeVertically = (py + 1 >= ey[i] - 1 && py <= ey[i] + 3);

            if (playerInRangeHorizontally && playerInRangeVertically)
            {
                if (i == 5 || i == 7 || i == 8 || i == 9 || i == 10) // for enemys firing on right side
                {
                    enemyBulletsX[enemyBulletFired] = ex[i] + 4; // store coordinates in arrays
                    enemyBulletsY[enemyBulletFired] = ey[i] + 1;
                    enemyBulletDirection[enemyBulletFired] = 'R';                                       // store direction of enemy bullet
                    printEnemyBullet(enemyBulletsX[enemyBulletFired], enemyBulletsY[enemyBulletFired]); // print bullet on new stored coordinate
                    enemyBulletFired++;                                                                 // increment in enemy bullet count
                }

                if (i == 6 || i == 9 || i == 10) // for enemies firing to the left
                {
                    enemyBulletsX[enemyBulletFired] = ex[i] - 1; // store coordinates in arrays
                    enemyBulletsY[enemyBulletFired] = ey[i] + 1;
                    enemyBulletDirection[enemyBulletFired] = 'L';                                       // store direction of enemy bullet
                    printEnemyBullet(enemyBulletsX[enemyBulletFired], enemyBulletsY[enemyBulletFired]); // print bullet on new stored coordinate
                    enemyBulletFired++;                                                                 // increment in enemy bullet count
                }
            }
        }
    }
}

void eraseEnemyBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << " ";
}

void moveEnemyBullet(int &playerHealth, int px, int py, int &playerLives, int enemyBulletsX[], int enemyBulletsY[],
                     char enemyBulletDirection[], int &enemyBulletFired)
{
    for (int i = 0; i < enemyBulletFired; i++) // for all the bullets fired by enemys
    {
        // check if enemy bullet hits player
        bool bulletHitsPlayer = (enemyBulletsX[i] >= px && enemyBulletsX[i] <= px + 3) &&
                                (enemyBulletsY[i] >= py && enemyBulletsY[i] <= py + 3);

        if (bulletHitsPlayer)
        {
            checkPlayerHealth(playerHealth, playerLives); // decrease in enemy health

            eraseEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]);                                        // remove bullets after they hit player
            deleteEnemyBullets(i, enemyBulletsX, enemyBulletsY, enemyBulletDirection, enemyBulletFired); // delete bullets from game
            i--;                                                                                         // decrement in bullet count
            continue;
        }
        if (enemyBulletDirection[i] == 'R') // moving bullets to the right
        {
            if (getCharAtxy(enemyBulletsX[i] + 2, enemyBulletsY[i]) == ' ') // if empty space then move
            {
                eraseEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]); // erase from previous coordinates
                enemyBulletsX[i] = enemyBulletsX[i] + 2;              // move to next coordinates
                printEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]); // move to new coordinates
            }
            else // if bullet hits maze or goes out of bound delete it from game
            {
                eraseEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]);
                deleteEnemyBullets(i, enemyBulletsX, enemyBulletsY, enemyBulletDirection, enemyBulletFired);
                i--;
            }
        }

        else if (enemyBulletDirection[i] == 'L') // moving bullets to the left
        {
            if (getCharAtxy(enemyBulletsX[i] - 2, enemyBulletsY[i]) == ' ') // if empty space then move
            {
                eraseEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]); // erase from previous coordinates
                enemyBulletsX[i] -= 2;                                // move to next coordinates
                printEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]); // move to new coordinate
            }
            else // if bullet hits maze or goes out of bound delete it from game
            {
                eraseEnemyBullet(enemyBulletsX[i], enemyBulletsY[i]);
                deleteEnemyBullets(i, enemyBulletsX, enemyBulletsY, enemyBulletDirection, enemyBulletFired);
                i--;
            }
        }
    }
}

void deleteEnemyBullets(int index, int enemyBulletsX[], int enemyBulletsY[], char enemyBulletDirection[],
                        int &enemyBulletFired)
{
    for (int i = index; i < enemyBulletFired - 1; i++)
    {
        enemyBulletsX[i] = enemyBulletsX[i + 1];
        enemyBulletsY[i] = enemyBulletsY[i + 1];
        enemyBulletDirection[i] = enemyBulletDirection[i + 1];
    }
    enemyBulletFired--;
}

void checkEnemyHealth(int ex[], int ey[], int enemyHealth[], int i, int playerHealth, int &killCount) // print enemy health display
{

    if (enemyHealth[i] <= 0) // if enemy health hits zero
    {
        eraseEnemy(ex, ey, i);
        gotoxy(128, 24 + i);
        cout << "Enemy " << i + 1 << " has been defeated!";
    }
    else
    {
        setColor(4);
        gotoxy(130, 24 + i);
        cout << "Enemy Health:        ";
        gotoxy(130, 24 + i);
        cout << "Enemy " << i + 1 << " Health: " << enemyHealth[i];

        setColor(10);
        gotoxy(135, 17);
        cout << "Kill Count: " << killCount;
    }
}

void checkPlayerHealth(int &playerHealth, int &playerLives)
{
    if (playerHealth <= 0) // if player health hits zero new life starts
    {
        checkPlayerLives(playerLives);
        playerHealth = 100;
    }
    else // decrement in player health
    {
        gotoxy(130, 7);
        cout << "                     ";
        setColor(6);
        gotoxy(130, 7);
        playerHealth = playerHealth - 1;
        cout << "Player Health: " << playerHealth;
    }
}

void checkPlayerLives(int &playerLives)
{
    if (playerLives == 0) // if player lives hit zero
    {
        gotoxy(130, 7);
        cout << "Player Health: 0         ";
        gotoxy(130, 7);
        cout << "Player Health: 0";
        gotoxy(130, 9);
        cout << "Player Lives: 0";
        gotoxy(130, 11);
        cout << " Game Over!";
    }
    else // player lives decrement
    {
        gotoxy(130, 9);
        cout << "                       ";
        gotoxy(130, 9);
        playerLives = playerLives - 1;
        cout << "Player Lives: " << playerLives;
    }
}

void printPlayerHealth() // initial player health and lives
{
    gotoxy(130, 7);
    cout << "Player Health: 100";
    gotoxy(130, 9);
    cout << "Player Lives: 5";
}

int generateRandomNumber(int min, int max)
{
    uniform_int_distribution<> range(min, max);
    return range(gen);
}

void spawnSpaceship(int &spaceshipX, int &spaceshipY) // spawn spaceship at the top right or left of the maze by generating random number
{
    int spawnLeft = generateRandomNumber(0, 1); // range o to 1

    if (spawnLeft == 1)
    {
        gotoxy(40, 40);
        cout << generateRandomNumber(0, 1);
        eraseSpaceship(spaceshipX, spaceshipY);
        spaceshipX = 110;
        spaceshipY = 4;
        printSpaceship(spaceshipX, spaceshipY);
    }
    else if (spawnLeft == 0)
    {
        eraseSpaceship(spaceshipX, spaceshipY);
        spaceshipX = 13;
        spaceshipY = 4;
        printSpaceship(spaceshipX, spaceshipY);
    }
}

bool checkWinCondition(int killCount, int spaceshipX, int spaceshipY, int px, int py, bool &gameWon)
{
    if (killCount >= 10 &&
        px >= spaceshipX - 1 && px <= spaceshipX + 6 &&
        py >= spaceshipY - 1 && py <= spaceshipY + 6)
    {
        gameWon = true;
        return gameWon;
    }
    return false;
}

void playLaserSound()
{
    Beep(750, 100);
}

void playExplosionSound()
{
    Beep(500, 300);
}

void dramaticSoundEffect()
{

    for (int i = 500; i <= 1000; i += 50)
    {
        Beep(i, 100); // Gradually increase frequency
    }

    // Short pause before the drop
    Sleep(300);

    // Dramatic drop
    Beep(300, 600);
    Beep(200, 400);

    // Final suspense beep
    Sleep(200);
    Beep(400, 500);
}