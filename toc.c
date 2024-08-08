#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SPACES 4

void die(const char *msg)
{
    printf("%s", msg);
    exit(1);
}

int main(int argc, char const *argv[])
{
    FILE *fptr = fopen("README.md", "r+");
    if (fptr == NULL)
    {
        die("File is null");
    }
    fseek(fptr, 0, SEEK_END);
    int file_len = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    // Relies on stack max capacity as this buff grows up in the stack
    // Don't go too crazy :D
    char buff[file_len + 1];
    char toc[file_len + 1];
    strcpy(toc, "");

    // To prevent reading # from code blocks
    int backticks = 0;
    int max_hierarchy = 6;
    do
    {
        int i = 0;
        char title_buff[1025] = "";
        int title_buff_cursor = 0;
        /**
         * 1 = h1
         * 2 = h2
         * 3 = h3
         * 4 = h4
         * 5 = h5
         * 6 = h6
         */
        int title_hierarchy = 0;

        while (buff[i] != '\0')
        {
            if (buff[i] == '`')
                backticks++;
            if (buff[i] == '#' && backticks % 2 == 0)
                title_hierarchy++;
            if (title_hierarchy < max_hierarchy && title_hierarchy > 0)
                max_hierarchy = title_hierarchy;
            if (title_hierarchy > 0)
            {
                if (buff[i] != '#' && buff[i] != '\n' && !(buff[i] == ' ' && buff[i - 1] == '#'))
                {
                    title_buff[title_buff_cursor] = buff[i];
                    title_buff_cursor++;
                }
                if (buff[i] == '\n')
                {
                    char *formatted_item;
                    char sanitized_title[1025] = "";

                    int c = 0;
                    while (title_buff[c])
                    {
                        if (title_buff[c] == ' ')
                        {
                            sanitized_title[c] = '-';
                        }
                        else
                        {
                            sanitized_title[c] = tolower(title_buff[c]);
                        }
                        c++;
                    }

                    if (asprintf(&formatted_item, "%*s- [%s](#%s)\n", title_hierarchy * SPACES - SPACES - max_hierarchy * SPACES, "", title_buff, sanitized_title) < 0)
                        die("Ooops asnprintf didn't work");

                    strcat(toc, formatted_item);
                    free(formatted_item);
                }
            }
            i++;
        }

    } while (fgets(buff, file_len, fptr) && !feof(fptr));

    printf("%s\n", toc);
    printf("\nIs TOC (table of content) generated OK? ---> y/n\n\n");

    fflush(stdin);
    char user_decision = 'n';
    scanf("%c", &user_decision);
    if (user_decision == 'y')
    {
        // move cursor to begin of readme
        fseek(fptr, 0, SEEK_SET);
        fread(buff, sizeof(char), file_len, fptr);
        fseek(fptr, 0, SEEK_SET);

        char *new_content;

        if (asprintf(&new_content, "## Table of content\n%s\n%s", toc, buff) < 0)
            die("Ooops asnprintf didn't work when prepending toc to readme");
        fprintf(fptr, "%s\n", new_content);
        free(new_content);
        printf("🎉 Done!");
    }
    else if (user_decision == 'n')
    {
        printf("oh well 🥺\n");
    }
    else
    {
        printf("🧐 I only undestand n/y\n");
    }
    fclose(fptr);
    return 0;
}
