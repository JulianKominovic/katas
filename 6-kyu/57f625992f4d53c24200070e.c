#include <stdio.h>
typedef struct mini_win_t
{
    char *letters;
    unsigned code;
} MiniWin;

typedef struct ticket_t
{
    MiniWin *mini_wins;
    unsigned count;
} Ticket;

const char *bingo(const Ticket *ticket, unsigned win)
{
    unsigned int mini_wins = 0;
    for (size_t i = 0; i < ticket->count; i++)
    {
        unsigned int c = 0;
        int j = 0;
        do
        {
            c = ticket->mini_wins[i].letters[j];
            j++;
            // Char can be understood as a decimal using ASCII table
            if (c == ticket->mini_wins[i].code)
            {
                mini_wins++;
                break;
            }
            // If c is 0 it means end of string
        } while (c);
    }

    return mini_wins >= win ? "Winner!" : "Loser!";
}