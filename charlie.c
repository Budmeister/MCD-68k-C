
#include "utils/malloc.h"
#include "utils/68k.h"
#include "utils/io.h"
#include "utils/string.h"
#include "utils/math.h"

/*
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

////////    //////  //    //     //////       //    //
///       //        //    //   //      //    //    //
/////    //         ////////   //      //   ////////
///       //        //    //   //      //        //
////////    //////  //    //     //////         //

//////////////////////////////////////////////////////
///////////////By: Micah Heikkila/////////////////////
              ////////////////////

//Charlie

*/

/*Variables//-----------------------------------------*/

/* ////////////////////////////////////////////// */
/* Modification Variables */
/* Random Modifier */
int RandMod = 10;
/* Midpoint Modifier */
int MM = 2;
/* Midpoint Preference Modifier */
int MC = 5;  /* Center */
int MC1 = 4; /* 1-off */
int MC2 = 2; /* 2-off */
/* Horizontal Blocking Modifier */
int HBMod = 10;
/* Vertical Blocking Modifier */
int VBMod = 9;
/* Diagonal Blocking Modifier */
int DBMod = 11;
/* Horizontal Link Modifier */
int HLMod = 4;
/* Vertical Link Modifier */
int VLMod = 4;
/* Diagonal Link Modifier */
int DLMod = 4;
/* Link Exponential Modifier */
int LEMod = 2;
/* Opponent Move Value Modifier */
int OppMod = 2;
/* Opponent Advantage Value Modifier */
int OppAdv = 10;
/* 2-1 Gap Value Modifier */
int GapMod = 1000;
/* ////////////////////////////////////////////// */

/* ////////////////////////////////////////////// */
/* Standard Variables */
/* Gameboard Matrix */
int Game[8][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0, 0}};
/* Placement Selection */
int Placement = 0;
/* Placement Height */
int Height[7] = {0, 0, 0, 0, 0, 0, 0};
/* End Game: 4 in a Row */
int EndGame = 0;
/* Shift for Blocking Value */
int Shift = 1;
/* Blocking Search Break */
int Break = 1;
/* Turn  */
int ComNum = 2;
/* Player Move */
int PlayerMove = 0;
/* Player Number */
int PlyNum = 1;
/* Player Input Search */
int Search = 1;
/* Serial Char Input */
char Input = '0';
/* Horizontal 2-1 Gap Arrays */
int HRight[7] = {0, 0, 0, 0, 0, 0, 0};
int HLeft[7] = {0, 0, 0, 0, 0, 0, 0};
/* Diagonal 2-1 Gap Arrays */
int TRight[7] = {0, 0, 0, 0, 0, 0, 0};
int BLeft[7] = {0, 0, 0, 0, 0, 0, 0};
int BRight[7] = {0, 0, 0, 0, 0, 0, 0};
int TLeft[7] = {0, 0, 0, 0, 0, 0, 0};
/* First Player */
int FirstPlayer = 0;
/* ////////////////////////////////////////////// */

/*Setup//---------------------------------------------*/

/* ////////////////////////////////////////////// */
/* Setup Function */
/*
void setup() {
Serial.begin(9600);
}
*/
/* ////////////////////////////////////////////// */

#define zeroout(x, var, len)        \
    for (var = 0; var < len; var++) \
        x[var] = 0;

void loop();

int main()
{
    int i, j;

    /* Random Modifier */
    RandMod = 10;
    /* Midpoint Modifier */
    MM = 2;
    /* Midpoint Preference Modifier */
    MC = 5;  /* Center */
    MC1 = 4; /* 1-off */
    MC2 = 2; /* 2-off */
    /* Horizontal Blocking Modifier */
    HBMod = 10;
    /* Vertical Blocking Modifier */
    VBMod = 9;
    /* Diagonal Blocking Modifier */
    DBMod = 11;
    /* Horizontal Link Modifier */
    HLMod = 4;
    /* Vertical Link Modifier */
    VLMod = 4;
    /* Diagonal Link Modifier */
    DLMod = 4;
    /* Link Exponential Modifier */
    LEMod = 1.6;
    /* Opponent Move Value Modifier */
    OppMod = 2;
    /* Opponent Advantage Value Modifier */
    OppAdv = 10;
    /* 2-1 Gap Value Modifier */
    GapMod = 1000;
    /* ////////////////////////////////////////////// */

    /* ////////////////////////////////////////////// */
    /* Standard Variables */
    /* Gameboard Matrix */
    for (i = 0; i < 8; i++)
        for (j = 0; j < 9; j++)
            Game[i][j] = 0;
    /*
    Game[8][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    */
    /* Placement Selection */
    Placement = 0;
    /* Placement Height */
    /* Height[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(Height, i, 7);
    /* End Game: 4 in a Row */
    EndGame = false;
    /* Shift for Blocking Value */
    Shift = 1;
    /* Blocking Search Break */
    Break = 1;
    /* Turn  */
    ComNum = 2;
    /* Player Move */
    PlayerMove = 0;
    /* Player Number */
    PlyNum = 1;
    /* Player Input Search */
    Search = 1;
    /* Serial Char Input */
    Input = '0';
    /* Horizontal 2-1 Gap Arrays */
    /* int HRight[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(HRight, i, 7);
    /* int HLeft[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(HLeft, i, 7);
    /* Diagonal 2-1 Gap Arrays */
    /* int TRight[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(TRight, i, 7);
    /* int BLeft[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(BLeft, i, 7);
    /* int BRight[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(BRight, i, 7);
    /* int TLeft[7] = {0, 0, 0, 0, 0, 0, 0}; */
    zeroout(TLeft, i, 7);
    /* First Player */
    FirstPlayer = 0;

    /*
    printf("        ________    ________    ____  ____    __________    ___   ___          \r\n");
    printf("       /       /   /       /   /   / /   /   /   __    /   /  /  /  /          \r\n");
    printf("      /   ____/   /   ____/   /   / /   /   /   / /   /   /  /  /  /           \r\n");
    printf("     /   /       /   /       /   /_/   /   /   / /   /   /  /__/  /_           \r\n");
    printf("    /   _/      /   /       /   __    /   /   / /   /   /____    __/           \r\n");
    printf("   /   /___    /   /___    /   / /   /   /   / /   /        /   /              \r\n");
    printf("  /       /   /       /   /   / /   /   /   /_/   /        /   /               \r\n");
    printf(" /_______/   /_______/   /___/ /___/   /_________/        /___/                \r\n");
    */
    printf("\033[0;31m        ________    ________    ____  ____    __________\033[0;33m    ___   ___          \r\n");
    printf("\033[0;31m       /       /   /       /   /   / /   /   /   __    /\033[0;33m   /  /  /  /          \r\n");
    printf("\033[0;31m      /   ____/   /   ____/   /   / /   /   /   / /   / \033[0;33m  /  /  /  /           \r\n");
    printf("\033[0;31m     /   /       /   /       /   /_/   /   /   / /   /  \033[0;33m /  /__/  /_           \r\n");
    printf("\033[0;31m    /   _/      /   /       /   __    /   /   / /   /   \033[0;33m/____    __/           \r\n");
    printf("\033[0;31m   /   /___    /   /___    /   / /   /   /   / /   /    \033[0;33m    /   /              \r\n");
    printf("\033[0;31m  /       /   /       /   /   / /   /   /   /_/   /     \033[0;33m   /   /               \r\n");
    printf("\033[0;31m /_______/   /_______/   /___/ /___/   /_________/      \033[0;33m  /___/                \r\n\033[0m");
    printf("\r\n");

    while (1)
    {
        loop();
    }

    return 0;
}

#define TOKEN0 " "
#define TOKEN1 "\033[0;31mX\033[0m"
#define TOKEN2 "\033[0;33mO\033[0m"

void printGame() {
    int r, c;
    for (r = 6; r > 0; r--)
    {
        for (c = 1; c < 8; c++)
        {
            /* printf("%d|", Game[r][c]); */
            if(Game[r][c] == 0)
                printf(TOKEN0 "|");
            else if(Game[r][c] == 1)
                printf(TOKEN1 "|");
            else if(Game[r][c] == 2)
                printf(TOKEN2 "|");
        }
        printf("\r\n");
    }
    printf("--------------\r\n");
    printf("1|2|3|4|5|6|7|\r\n");
    printf("--------------\r\n");
}

void updateHeights() {
    int c, h;
    for (c = 1; c < 8; c++)
    {
        for (h = 1; h > 0; h++)
        {
            if (Game[h][c] == 0)
            {
                Height[c - 1] = h;
                h = -1;
            }
        }
    }
}

#define ROWS 6
#define COLS 7

int checkGameOver() {
    int i, j;
    int player, count;

    /* Check for horizontal wins */
    for (i = 1; i < ROWS+1; i++) {
        for (j = 1; j < COLS - 3+1; j++) {
            if (Game[i][j] != 0 && Game[i][j] == Game[i][j+1] && Game[i][j] == Game[i][j+2] && Game[i][j] == Game[i][j+3]) {
                return Game[i][j];
            }
        }
    }

    /* Check for vertical wins */
    for (j = 1; j < COLS-1; j++) {
        for (i = 1; i < ROWS - 3+1; i++) {
            if (Game[i][j] != 0 && Game[i][j] == Game[i+1][j] && Game[i][j] == Game[i+2][j] && Game[i][j] == Game[i+3][j]) {
                return Game[i][j];
            }
        }
    }

    /* Check for diagonal wins (top-left to bottom-right) */
    for (i = 1; i < ROWS - 3+1; i++) {
        for (j = 1; j < COLS - 3+1; j++) {
            if (Game[i][j] != 0 && Game[i][j] == Game[i+1][j+1] && Game[i][j] == Game[i+2][j+2] && Game[i][j] == Game[i+3][j+3]) {
                return Game[i][j];
            }
        }
    }

    /* Check for diagonal wins (bottom-left to top-right) */
    for (i = ROWS - 1+1; i >= 3; i--) {
        for (j = 1; j < COLS - 3+1; j++) {
            if (Game[i][j] != 0 && Game[i][j] == Game[i-1][j+1] && Game[i][j] == Game[i-2][j+2] && Game[i][j] == Game[i-3][j+3]) {
                return Game[i][j];
            }
        }
    }

    /* Check for a tie game */
    count = 0;
    for (i = 1; i < ROWS+1; i++) {
        for (j = 1; j < COLS+1; j++) {
            if (Game[i][j] != 0) {
                count++;
            }
        }
    }
    if (count == ROWS * COLS) {
        return -1;
    }

    /* Game is not over yet */
    return 0;
}

/* MainLoop//-------------------------------------------*/
void loop()
{
    int r, c, h, p, g, a, v, trial;
    int Value[7] = {MM, MC2 * MM, MC1 * MM, MC * MM, MC1 * MM, MC2 * MM, MM};
    int OppValue[7] = {0, 0, 0, 0, 0, 0, 0};


    /* ////////////////////////////////////////////// */
    /* First Player */
    if (FirstPlayer > 0)
    {
        /* ////////////////////////////////////////////// */
        /* Gameboard Status Display */
        /* printGame(); */
        /* ////////////////////////////////////////////// */

        /* Data Collection//------------------------------------*/

        /* ////////////////////////////////////////////// */
        /* Placement Height Function */
        updateHeights();
        /* ////////////////////////////////////////////// */

        /*Computer Value Collection//---------------------------------------------*/
        /* ////////////////////////////////////////////// */
        /* Value Array with Midpoint Modifier */
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Random Value Input */
        for (a = 0; a < 7; a++)
        {
            Value[a] = Value[a] + random(RandMod, 0);
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Horizontal Right Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1]][p + Shift] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(HBMod, Shift);
                    HRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Horizontal Left Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1]][p - Shift] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(HBMod, Shift);
                    HLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Vertical Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift][p] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(VBMod, Shift);
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal RT Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + Shift][p + Shift] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(DBMod, Shift);
                    TRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal LT Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + Shift][p - Shift] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(DBMod, Shift);
                    TLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal RB Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift][p + Shift] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(DBMod, Shift);
                    BRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal LB Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift][p - Shift] == 1)
                {
                    Value[p - 1] = Value[p - 1] + pow(DBMod, Shift);
                    BLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* 2-1 Gap Blocking Function */
        for (g = 0; g < 7; g++)
        {
            if (HRight[g] + HLeft[g] >= 3)
            {
                Value[g] = Value[g] + GapMod;
                HRight[g] = 0;
                HLeft[g] = 0;
            }
            if (TRight[g] + BLeft[g] >= 3)
            {
                Value[g] = Value[g] + GapMod;
                TRight[g] = 0;
                BLeft[g] = 0;
            }
            if (BRight[g] + TLeft[g] >= 3)
            {
                Value[g] = Value[g] + GapMod;
                BRight[g] = 0;
                TLeft[g] = 0;
            }
        }
        /* ////////////////////////////////////////////// */

        /*--Offensive--*/
        /* ////////////////////////////////////////////// */
        /* Horizontal Right Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1]][p + Shift] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(HLMod, Shift * LEMod);
                    HRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Horizontal Left Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1]][p - Shift] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(HLMod, Shift * LEMod);
                    HLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Vertical Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift][p] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(VLMod, Shift * LEMod);
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal RT Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + Shift][p + Shift] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(DLMod, Shift * LEMod);
                    TRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal LT Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + Shift][p - Shift] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(DLMod, Shift * LEMod);
                    TLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal RB Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift][p + Shift] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(DLMod, Shift * LEMod);
                    BRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal LB Link Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift][p - Shift] == 2)
                {
                    Value[p - 1] = Value[p - 1] + pow(DLMod, Shift * LEMod);
                    BLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* 2-1 Gap Linking Function */
        for (g = 0; g < 7; g++)
        {
            if (HRight[g] + HLeft[g] >= 3)
            {
                Value[g] = Value[g] + GapMod;
                HRight[g] = 0;
                HLeft[g] = 0;
            }
            if (TRight[g] + BLeft[g] >= 3)
            {
                Value[g] = Value[g] + GapMod;
                TRight[g] = 0;
                BLeft[g] = 0;
            }
            if (BRight[g] + TLeft[g] >= 3)
            {
                Value[g] = Value[g] + GapMod;
                BRight[g] = 0;
                TLeft[g] = 0;
            }
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Full Column Value Modifier (Must Be Last!) */
        for (c = 0; c < 7; c++)
            if (Height[c] == 7)
                Value[c] = 0;
        /* ////////////////////////////////////////////// */

        /* Opponent Placement Value Collection and Prevention//---------------------------------------------*/
        /* ////////////////////////////////////////////// */
        /* Opponent Value for Above Placement */
        for (p = 1; p < 7; p++)
            OppValue[p] = 0;
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Horizontal Right Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + 1][p + Shift] == 1)
                {
                    OppValue[p - 1] = OppValue[p - 1] + pow(HBMod, Shift);
                    HRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Horizontal Left Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + 1][p - Shift] == 1)
                {
                    OppValue[p - 1] = OppValue[p - 1] + pow(HBMod, Shift);
                    HLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal RT Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + Shift + 1][p + Shift] == 1)
                {
                    OppValue[p - 1] = OppValue[p - 1] + pow(DBMod, Shift);
                    TRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal LT Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] + Shift + 1][p - Shift] == 1)
                {
                    OppValue[p - 1] = OppValue[p - 1] + pow(DBMod, Shift);
                    TLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal RB Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift + 1][p + Shift] == 1)
                {
                    OppValue[p - 1] = OppValue[p - 1] + pow(DBMod, Shift);
                    BRight[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Diagonal LB Blocking Value */
        Shift = 1;
        for (p = 1; p < 8; p++)
        {
            while (Break == 1)
            {
                if (Game[Height[p - 1] - Shift + 1][p - Shift] == 1)
                {
                    OppValue[p - 1] = OppValue[p - 1] + pow(DBMod, Shift);
                    BLeft[p - 1] = Shift;
                    Shift++;
                }
                else
                    Break = 0;
            }
            Shift = 1;
            Break = 1;
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* 2-1 Gap Prevention Function */
        for (g = 0; g < 7; g++)
        {
            if (HRight[g] + HLeft[g] >= 3)
            {
                if (Value[g] < 1500)
                    Value[g] = 5;
                HRight[g] = 0;
                HLeft[g] = 0;
            }
            if (TRight[g] + BLeft[g] >= 3)
            {
                if (Value[g] < 1500)
                    Value[g] = 5;
                TRight[g] = 0;
                BLeft[g] = 0;
            }
            if (BRight[g] + TLeft[g] >= 3)
            {
                if (Value[g] < 1500)
                    Value[g] = 5;
                BRight[g] = 0;
                TLeft[g] = 0;
            }
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Opponent Value vs Computer Value */
        for (c = 0; c < 7; c++)
        {
            if (OppValue[c] + OppAdv > Value[c])
            {
                Value[c] = Value[c] / OppMod;
            }
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Value Display */
        for (v = 0; v < 7; v++)
        {
            printf("%d|", Value[v]);
        }
        printf("\r\n");
        /* ////////////////////////////////////////////// */

        /*Placement//--------------------------------------------*/

        /* ////////////////////////////////////////////// */
        /* Placement Value Function */
        for (trial = 1; trial < 7; trial++)
        {
            if (Value[Placement] < Value[trial])
                Placement = trial;
        }
        printf("Placement: %d\r\n", Placement + 1);
        /* ////////////////////////////////////////////// */

        EndGame = checkGameOver();
        /* ////////////////////////////////////////////// */
        /* Piece Placement */
        if (EndGame) {
            printf("Game Over: 4 in a Row\r\n");
            exit();
        } else if (Value[Placement] == 0) {
            printf("Game Over: Full Board\r\n");
            exit();
        } else
            Game[Height[Placement]][Placement + 1] = ComNum;
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Placement Reset */
        Placement = 0;
        FirstPlayer = 0;
        /* ////////////////////////////////////////////// */
    }
    /* End First Player */
    /* ////////////////////////////////////////////// */
    else
    {
        /*Player Move//-----------------------------------------*/

        /* ////////////////////////////////////////////// */
        /* Gameboard Status Display */
        printGame();
        EndGame = checkGameOver();
        if (EndGame) {
            printf("Game Over: 4 in a Row\r\n");
            exit();
        }
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Player Number Input */
        printf("Your Move (1-7):\r\n");
        do {
            PlayerMove = getcb() - '0';
        } while (PlayerMove < 0 || PlayerMove > 7);
        printf("%d\r\n", PlayerMove);
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Placement Height Function */
        updateHeights();
        /* ////////////////////////////////////////////// */


        EndGame = checkGameOver();
        /* ////////////////////////////////////////////// */
        /* Piece Placement */
        if (EndGame) {
            printGame();
            printf("Game Over: 4 in a Row\r\n");
            exit();
        } else if (Height[PlayerMove - 1] > 7)
            printf("Full Column\r\n");
        else
            Game[Height[PlayerMove - 1]][PlayerMove] = PlyNum;
        /* ////////////////////////////////////////////// */

        /* ////////////////////////////////////////////// */
        /* Player Move Reset */
        PlayerMove = 0;
        FirstPlayer = 1;
        /* ////////////////////////////////////////////// */
    }
}

/* Program End///////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////////////////////////////////////////////////// */
