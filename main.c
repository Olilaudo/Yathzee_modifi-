#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_DICES 5
#define NUMBEROFROUNDS 14
#define FILENAME "Yathzee.txt"

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

/// prototypes des fonctions
void home();
void show_menu(char*, int, int, int);
char game_choice();
void create_table(int*);
void animation();
void show_dices(int*);
int charToInt(char);
char intToChar(int);
void choice(char*, int*);
void result_choice(char*, int*);
void upper_section(int*, char*, int, int*, int*, int*);
void brelan(int*, char*, int*);
void two_pairs(int*, char*, int*);
void square(int*, char*, int*);
void verify_if_used(char*, int*);
void full_house(int*, char*, int*);
void big_suite(int*, char*, int*);
void yams(int*, char*, int*);
void save_game(char*, int, int, int, int);
void load_game(char*, int*, int*, int*, int*);

int main()
{
    /// déclaration des variables
    int continue_game = 0;
    char table_values[NUMBEROFROUNDS+1];
    int i;
    int dices[SIZE_DICES] = {0};
    char choice[5];
    int card;
    int total = 0;
    int bonus = 0;
    int total_general = 0;
    int result = 0;
    char save;

    /// initialisation du rand et on jette le premier nombre
    srand(time(NULL));
    rand();

    /// boucle pour initialiser les valeurs de mon tableau
    for(i=0; i < NUMBEROFROUNDS+1; i++) //boucle pour initialiser le tableau
    {
        table_values[i] = '-';
    }

    home();

    load_game(table_values, &total, &bonus, &total_general, &continue_game);

    /// boucle du jeu
    while(continue_game < NUMBEROFROUNDS)
    {
        show_menu(table_values, total, bonus, total_general);
        create_table(dices);
        result_choice(choice, dices);
        show_dices(dices);
        printf("     Votre choix pour ces des (1 . . . %i) : ", NUMBEROFROUNDS);
        scanf("%i", &card);
        fflush(stdin);
        verify_if_used(table_values, &card);

        /// switch pour choisir le contrat
        switch(card)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            upper_section(dices, table_values, card, &total, &total_general, &bonus);
            break;
        case 7:
            brelan(dices, table_values, &total_general);
            break;
        case 8:
            two_pairs(dices, table_values, &total_general);
            break;
        case 9:
            square(dices, table_values, &total_general);
            break;
        case 10:
            full_house(dices, table_values, &total_general);
            break;
        case 11:
            small_suite(dices, table_values, &total_general);
            break;
        case 12:
            big_suite(dices, table_values, &total_general);
            break;
        case 13:
            yams(dices, table_values, &total_general);
            break;
        case 14:
            result = 0;
            for(i=0; i < SIZE_DICES; i++)
            {
                result += dices[i];
            }
            table_values[13] = intToChar(result);
            total_general += result;
            break;
        }

        continue_game ++;
        system(CLEAR_COMMAND);
        show_menu(table_values, total, bonus, total_general);
        /// condition pour sauvegarde sauf au premier tour
        if(continue_game != 0)
        {
            printf("Save game ? (y/n) : ");
            scanf("%c", &save);
            if(save == 'y' || save == 'Y')
            {
                save_game(table_values, total, bonus, total_general, continue_game);
            }
            else
            {
                system(CLEAR_COMMAND);
            }
        }
    }
    show_menu(table_values, total, bonus, total_general);
    printf("End game !");
    return 0;
}

void home()
{
    printf("Bonjour, Bienvenu(e) sur Yathsee\n");
    printf("Bonne chance vous avez %i jets de des", NUMBEROFROUNDS);
    _sleep(3000);
    system(CLEAR_COMMAND);
}

void show_menu(char* table, int total, int bonus, int total_general)
{
    /// Si la valeur stocké n'est pas un tiret, je transforme mon char en int
    if(table[0]== '-')
    {
        printf("1.  AS            :   %c\n", table[0]);
    }
    else
    {
        printf("1.  AS            :   %i\n", charToInt(table[0]));
    }

    if(table[1]== '-')
    {
        printf("2.  DEUX          :   %c\n", table[1]);
    }
    else
    {
        printf("2.  DEUX          :   %i\n", charToInt(table[1]));
    }

    if(table[2]== '-')
    {
        printf("3.  TROIS         :   %c\n", table[2]);
    }
    else
    {
        printf("3.  TROIS         :   %i\n", charToInt(table[2]));
    }

    if (table[3] == '-')
    {
        printf("4.  QUATRE        :   %c\n", table[3]);
    }
    else
    {
        printf("4.  QUATRE        :   %i\n", charToInt(table[3]));
    }

    if (table[4] == '-')
    {
        printf("5.  CINQ          :   %c\n", table[4]);
    }
    else
    {
        printf("5.  CINQ          :   %i\n", charToInt(table[4]));
    }

    if (table[5] == '-')
    {
        printf("6.  SIX           :   %c\n", table[5]);
    }
    else
    {
        printf("6.  SIX           :   %i\n", charToInt(table[5]));
    }

    if (total == 0)
    {
        printf("    Total         :   -\n");
    }
    else
    {
        printf("    Total         :   %i\n", total);
    }

    if (bonus == 0)
    {
        printf("    Bonus         :   -\n");
    }
    else
    {
        printf("    Bonus         :   %i\n", bonus);
    }

    if (table[6] == '-')
    {
        printf("7.  BRELAN        :   %c\n", table[6]);
    }
    else
    {
        printf("7.  BRELAN        :   %i\n", charToInt(table[6]));
    }

    if (table[7] == '-')
    {
        printf("8.  2 paires      :   %c\n", table[7]);
    }
    else
    {
        printf("8.  2 paires      :   %i\n", charToInt(table[7]));
    }

    if (table[8] == '-')
    {
        printf("9.  CARRE         :   %c\n", table[8]);
    }
    else
    {
        printf("9.  CARRE         :   %i\n", charToInt(table[8]));
    }

    if (table[9] == '-')
    {
        printf("10. FULL HOUSE    :   %c\n", table[9]);
    }
    else
    {
        printf("10. FULL HOUSE    :   %i\n", charToInt(table[9]));
    }

    if (table[10] == '-')
    {
        printf("11. PETITE SUITE  :   %c\n", table[10]);
    }
    else
    {
        printf("11. PETITE SUITE  :   %i\n", charToInt(table[10]));
    }

    if (table[11] == '-')
    {
        printf("12. GRANDE SUITE  :   %c\n", table[11]);
    }
    else
    {
        printf("12. GRANDE SUITE  :   %i\n", charToInt(table[11]));
    }

    if (table[12] == '-')
    {
        printf("13. YAHTSEE       :   %c\n", table[12]);
    }
    else
    {
        printf("13. YAHTSEE       :   %i\n", charToInt(table[12]));
    }

    if (table[13] == '-')
    {
        printf("14. CHANCE        :   %c\n", table[13]);
    }
    else
    {
        printf("14. CHANCE        :   %i\n", charToInt(table[13]));
    }

    if (total_general == 0)
    {
        printf("    TOTAL GENERAL :   -\n\n");
    }
    else
    {
        printf("    TOTAL GENERAL :   %i\n\n", total_general);
    }

    printf("Encodage des des a rejouer (A=aucun T=tous 135=le un, le trois et le cinq)\n");
}

/// fonction qui remplit mon tableau de dés
void create_table(int* tab)
{
    for(int i=0; i < SIZE_DICES; i++)
    {
        tab[i] = rand() % (6 - 1 + 1) + 1;
    }
}

/// Animation des tirets
void animation()
{
    for(int i=0; i<4; i++)
    {
        printf("-");
        _sleep(80);
        printf("\b");
        printf("\\");
        _sleep(80);
        printf("\b");
        printf("/");
        printf("\b");
    }
}

/// affiche les dés
void show_dices(int* dices)
{
    for(int i=0; i < SIZE_DICES; i++)
    {
        animation();
        printf("%i", dices[i]);
        if(i!=4)
        {
            printf(" - ");
        }
    }
}

/// Transforme char en int
int charToInt(char caract)
{
    return caract -= 48;
}

/// Transforme int en char
char intToChar(int caract)
{
    return caract += 48;
}

/// demande l'action à réaliser et la réalise
void result_choice(char* choice, int* dices)
{

    for(int j=0; j<2 ;j++)
    {
        show_dices(dices);
        printf("     Votre choix de des a rejouer: ");
        scanf("%s", choice);
        fflush(stdin);

        for(int i=0; choice[i] != '\0'; i++) /// boucle jusqu'a la fin du tableau
        {
            switch(choice[i])
            {
            case 'a':
            case 'A':
                j = 2;
                break;
            case 't':
            case 'T':
                create_table(dices);
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                dices[charToInt(choice[i])-1] = rand() % (6 - 1 + 1) + 1;
            }
        }
    }
}

/// Vérifier si un contrat n'est pas utilisé et reposé la question si jamais
void verify_if_used(char* table, int* nbr)
{
    if(table[*nbr-1] != '-')
    {
        printf("Impossible, choix deja ete utilise\n");
        printf("Votre choix : ");
        scanf("%i", &*nbr);
        verify_if_used(table, &*nbr);
    }
    else
    {
        return;
    }
}

/// fonction qui vérifie les 6 premiers contrats
void upper_section(int* dices, char* table, int x, int* total, int* total_general, int* bonus)
{
    int counter = 0;
    int i;

    for(i=0; i < SIZE_DICES; i++)
    {
        if(dices[i] == x)
        {
            counter++;
        }
    }

    if(table[x-1] == '-')
    {
        table[x-1] = intToChar(counter * x);

        *total += counter * x;
        *total_general += counter * x;
    }

    counter = 0;
    for(i=0; i<6; i++)
    {
        if(table[i] != '-')
        {
            counter++;
        }
    }

    if(counter == 6 && *total >= 63)
    {
        *bonus += 35;
        *total_general += 35;
    }
}

/// fonction qui vérifie le brelan
void brelan(int* dices, char* table, int* total_general)
{
    for(int i=1; i<7; i++)
    {
        int counter = 0;
        for(int j=0; j<SIZE_DICES; j++)
        {
            if(dices[j] == i)
            {
                counter++;
            }
            if(counter == 3)
            {
                table[6] = intToChar(counter * i);
                *total_general += counter * i;
                return;
            }
        }
    }
    if(table[6] == '-')
    {
        table[6] = '0';
    }
}

void two_pairs(int* dices, char* table, int* total_general)
{
    for(int i=0; i<7; i++)
    {
        int counter = 0;
        for(int j=0; j<SIZE_DICES; j++)
        {
            if(dices[j] == i)
            {
                counter++;
            }
            if(counter == 2)
            {
                for(int k=0; k<7; k++)
                {
                    int counter2 = 0;
                    for(int l=0; l<SIZE_DICES; l++)
                    {
                        if(dices[l] == k && k != i)
                        {
                            counter2++;
                        }
                        if(counter2 == 2)
                        {
                            table[7] = intToChar((i*2)+(k*2));
                            *total_general += (i*2)+(k*2);
                            return;
                        }
                    }
                }
            }
        }
    }
    if(table[7] == '-')
    {
        table[7] = '0';
    }
    return;
}

/// fonction qui vérifie le carrée
void square(int* dices, char* table, int* total_general)
{
    for(int i=1; i<7; i++) /// boucle pour comparer avec les dés
    {
        int counter = 0;
        for(int j=0; j<SIZE_DICES; j++) /// boucler sur les dés
        {
            if(dices[j] == i)
            {
                counter++;
            }
            if(counter == 4)
            {
                table[8] = intToChar(counter * i);
                *total_general += counter * i;
                return;
            }
        }
    }
    if(table[8] == '-')
    {
        table[8] = '0';
    }
}

/// fonction qui vérifie le full house
void full_house(int* dices, char* table, int* total_general)
{
    int i;
    int found_three = 0;
    int found_two = 0;
    int counts[7] = {0};

    for(i=0; i < SIZE_DICES; i++)
    {
        counts[dices[i]]++;
    }

    for(i=1; i <=6; i++)
    {
        if(counts[i] == 3)
        {
            found_three = 1;
        }
        else if(counts[i] == 2)
        {
            found_two = 1;
        }
    }

    if(found_two && found_three)
    {
        table[9] = intToChar(25);
        *total_general += 25;
        return;
    }
    else
    {
        table[9] = '0';
    }

}

/// fonction qui vérifie la petite suite
void small_suite(int* dices, char* table, int* total_general)
{
    int i;
    int counts[7] = {0};
    int small_Suite = 0;
    int score = 0;

    for(i=0; i<SIZE_DICES; i++) /// mets le nombre de 1 que j'ai dans mes dés dans la tableau avec l'index 1
    {
        counts[dices[i]]++;
    }

    /// vérifie tout les cas possibles
    if(counts[1] != 0 && counts[2] != 0 && counts[3] != 0 && counts[4] != 0)
    {
        score = 25;
    }
    if(counts[2] != 0 && counts[3] != 0 && counts[4] != 0 && counts[5] != 0)
    {
       score = 30;
    }
    if(counts[3] != 0 && counts[4] != 0 && counts[5] != 0 && counts[6] != 0)
    {
       score = 35;
    }

    if(score != 0)
    {
        table[10] = intToChar(score);
        *total_general += score;
        return;
    }
    else
    {
        table[10] = '0';
    }
}

/// fonction qui vérifie la grande suite
void big_suite(int* dices, char* table, int* total_general)
{
    int i;
    int counts[7] = {0};
    int bigSuite = 0;

    for(i=0; i<SIZE_DICES; i++)
    {
        counts[dices[i]]++; /// mets le nombre de 1 que j'ai dans mes dés dans la tableau avec l'index 1
    }

    /// vérifie tout les cas possibles
    if(counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1)
    {
        bigSuite = 1;
    }
    else if(counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1 && counts[6] == 1)
    {
        bigSuite = 1;
    }

    if(bigSuite == 1)
    {
        table[11] = intToChar(40);
        *total_general += 40;
        return;
    }
    else
    {
        table[11] = '0';
    }
}

/// fonction qui vérifie le yahtzee
void yams(int* dices, char* table, int* total_general)
{
    int temp = dices[0];

    for(int i=1; i < SIZE_DICES; i++)
    {
        if(dices[i] != temp)
        {
            table[12] = '0';
            return;
        }
    }
    table[12] = intToChar(50);
    *total_general += 50;
}

/// fonction qui sauvegarde la partie
void save_game(char* table, int total, int bonus, int total_general, int continue_game)
{
    FILE * file = fopen(FILENAME, "w");

    if(file != NULL)
    {
        for(int i = 0; i < NUMBEROFROUNDS ;i++)
        {
            fprintf(file, "%c", table[i]);
        }

        fprintf(file, "\n%i", total);
        fprintf(file, "\n%i", bonus);
        fprintf(file, "\n%i", total_general);
        fprintf(file, "\n%i", continue_game);

        fclose(file);
        exit(EXIT_SUCCESS);
    }
}

/// fonction qui vérifie s'il y a une sauvegarde et la charge si besoin
void load_game(char* table, int* total, int* bonus, int* total_general, int* continue_game)
{
    FILE * file = fopen(FILENAME, "r");
    char choice;

    if(file == NULL)
    {
        return;
    }
    else
    {
        printf("Partie trouvee, continuer la partie ? (y/n) : ");
        scanf("%c", &choice);
        fflush(stdin);

        if(choice != 'y' && choice != 'Y')
        {
            fclose(file);
            remove(FILENAME);
            return;
        }
        else
        {
            for(int i=0; i < NUMBEROFROUNDS; i++)
            {
               fscanf(file,"%c", &table[i]);
            }
            fscanf(file, "%i", total);
            fscanf(file, "%i", bonus);
            fscanf(file, "%i", total_general);
            fscanf(file, "%i", continue_game);
            fclose(file);
            remove(FILENAME);
        }
    }
}
