#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#define filefornames "users.txt" 
#define wall '|'
#define floor '.'
#define door '+'
#define corridor '#'
#define pillar 'O'
#define window '='
char map[25][50];
void initialize_map_1() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            if ( j == 0 || j == 49) {
                map[i][j] = wall;
            }else if(i == 0 || i == 24){
                map[i][j] = '_';
            } else {
                map[i][j] = floor; 
            }
        }
    }
    for(int i=0; i<25; i++){
        for (int j=0; j<50 ; j++){
             mvprintw(i, j, "%c", map[i][j]);
        }
    }
    printw("\n");
}
void room_wall() {
    for(int i =28 ; i<=35 ; i++){
        map[8][i] = '_';
        map[14][i] = '_';
    }
    map[9][27] = '|';
    map[9][36] = '|';
    for(int i=11 ; i<=13 ; i++){
        map[i][27] = '|';
        map[i][36] = '|';
    }
    map[4][6] = '|';
    map[9][28] = 'c';
    map[9][29] = 'u';
    map[9][30] = 'r';
    map[9][31] = 's';
    map[9][32] = 'e';
    map[11][26] = '?';
    for(int i = 2 ; i<=5; i++){
        map[5][i] = '_'; 
        map[2][i] = '_';
        map[14][i] = '_'; 
        map[11][i] = '_';
    }
        map[3][1] = '|';
        map[4][1] = '|';
        map[13][6] = '|';
        map[12][1] = '|';
        map[13][1] = '|';
        map[7][9] = '|';
        map[7][5] = '|';
        map[8][5] = '|';
        map[17][9] = '|';
        map[17][5] = '|';
        map[18][5] = '|';
        map[10][36] = '|';
    for(int i=6; i<=9; i++){
         map[6][i] = '_';
         map[9][i] = '_';
         map[16][i] = '_';
         map[19][i] = '_';
    }
        map[7][14] = '|';
        map[7][19] = '|';
        map[8][19] = '|';
        map[17][13] = '|';
        map[17][20] = '|';
        map[18][20] = '|';
    for(int i=19; i<=21; i++){
        map[i][14] = '|';
        map[i][20] = '|';
    }
    map[9][17] = '_';
    map[6][18] = '_';
    map[9][18] = '_';
    for(int i=15; i<=16; i++){
        map[6][i] = '_';
        map[9][i] = '_';
    }
    for(int i=15; i<=20; i++){
        map[16][i] = '_';
        map[22][i] = '_';
    }
    map[17][16] = 'f';
    map[17][8] = '^';
    map[18][8] = 'G';
    map[8][8] = '^';
    map[7][8] = 'G';
    map[18][16] = 'i';
    map[19][16] = 'g';
    map[20][16] = 'h';
    map[21][16] = 't';
    
    map[8][10] = door;  
    map[8][13] = door;  
    map[3][7] = door;
    map[3][5] = 'F';
    map[12][5] = 'F';
    map[5][17] = door;
    map[18][10] = door;  
    map[18][13] = door;  
    map[12][7] = door;
    map[10][26] = door;
    map[2][30] = 'T';
    map[19][22] = 'T';
    map[10][45] = 'T';

    map[10][32] = pillar;
    map[10][33] = pillar;
    map[13][29] = pillar;
    map[8][18] = pillar; 
    map[7][6] = pillar; 
    map[3][3] = pillar; 
    map[18][18] = pillar; 
    map[20][18] = pillar;
    map[17][6] = pillar; 
    map[13][3] = pillar; 

    map[8][4] = window; 
    map[6][3] = window; 
    map[18][4] = window; 
    map[15][3] = window; 
}
void corridors() {
        map[8][11] = corridor;
        map[8][12] = corridor;
        map[8][11] = corridor;
        map[18][11] = corridor;
        map[18][12] = corridor;
        map[18][11] = corridor;
        map[9][13] = corridor;
        map[11][25] = corridor;
        for(int i=23; i<=25; i++){
            map[10][i] = corridor;
        }
        for (int i=13; i<=22; i++){
            map[10][i] = corridor;
        }
        for (int i=11; i<15; i++){
            map[i][22] = corridor;
        }
        for(int i= 21; i>=17 ; i--){
            map[14][i] = corridor;
        }
        for (int i=4 ; i<=5; i++){
            map[i][7] = corridor;
        }
        for (int i=15 ; i>=13; i--){
            map[i][7] = corridor;
        }
        for(int i=8 ; i<=17 ; i++){
            map[4][i] = corridor;
        }
        for(int i=8 ; i<=17 ; i++){
            map[14][i] = corridor;
        }
}


int game_difficulty;
char hero_color[20];

int check_username(char *username) {
    FILE *file = fopen(filefornames, "r");
    if (file == NULL) {
        return 0;
    }
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char saved_username[1000];
        sscanf(line, "%s", saved_username);
        if (strcmp(saved_username, username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int check_password(char *password) {
    int length = strlen(password);
    int has_digit = 0, has_upper = 0, has_lower = 0;
    if (length < 7)
        return 0;
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i]))
            has_digit = 1;
        if (isupper(password[i])) 
            has_upper = 1;
        if (islower(password[i])) 
            has_lower = 1;
    }
    return has_digit && has_upper && has_lower;
}

int e_mail(char *email) {
    char *atsign = strchr(email, '@');
    if (atsign == NULL)
        return 0;
    char *dot = strchr(email, '.');
    if (dot == NULL){
        return 0;
    }
    return 1;
}

void saveuser(char *username, char *password, char *email) {
    FILE *file = fopen(filefornames, "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s\n", username, password, email);
        fclose(file);
    }
}

int login(char *username, char *password) {
    FILE *file = fopen(filefornames, "r");
    if (file == NULL) {
        return 0;
    }
    char line[1000], saved_username[1000], saved_password[1000], saved_email[1000];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %s", saved_username, saved_password, saved_email);
        if (strcmp(saved_username, username) == 0 && strcmp(saved_password, password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
char game_message[1000];

void display_message(const char* message) {
    clear();
    mvprintw(0, 0, "Game Messages:"); 
    mvprintw(1, 0, message);
    refresh();
}

void game_action() {
    strcpy(game_message, "You hit the enemy!");
    display_message(game_message);
    getch();
}

void game_hit() {
    strcpy(game_message, "You were hit by the enemy!");
    display_message(game_message);
    getch();
}

void weapon_pickup() {
    strcpy(game_message, "You picked up a new weapon!");
    display_message(game_message);
    getch(); 
}

void shooting() {
    strcpy(game_message, "You shot the weapon!");
    display_message(game_message);
    getch(); 
}
void settings_menu() {
    int choice;
    clear();
    printw("Settings Menu:\n");
    printw("1. Set Game Difficulty\n");
    printw("2. Change Hero Color\n");
    printw("3. Back to Main Menu\n");
    printw("Enter your choice: ");
    refresh();
    choice = getch() - '0';

    switch (choice) {
        case 1: {
            printw("Select Game Difficulty:\n");
            printw("1. Easy\n");
            printw("2. Medium\n");
            printw("3. Hard\n");
            printw("Enter your choice: ");
            game_difficulty = getch() - '0';
            if (game_difficulty == 1) printw("Difficulty set to Easy.\n");
            else if (game_difficulty == 2) printw("Difficulty set to Medium.\n");
            else if (game_difficulty == 3) printw("Difficulty set to Hard.\n");
            else printw("Invalid choice. Keeping previous difficulty.\n");
            break;
        }
        case 2: {
            printw("Select Hero Color:\n");
            printw("1. Red\n");
            printw("2. Blue\n");
            printw("3. Green\n");
            printw("4. White\n");
            printw("Enter your choice: ");
            int color_choice;
            color_choice = getch() - '0';
            if (color_choice == 1){
                strcpy(hero_color, "red");
                printw("Hero color set to red");
            } else if (color_choice == 2) {
                strcpy(hero_color, "blue");
                printw("Hero color set to blue");
            } else if (color_choice == 3) {
                strcpy(hero_color, "green");
                printw("Hero color set to green");
            } else if (color_choice == 4) {
                strcpy(hero_color, "white");
                printw("Hero color set to white");
            } else printw("Invalid choice. Keeping previous color.\n");
            break;
        }
        case 3:
            printw("Return to main menu...\n");
            
            break;
        default:
            printw("Invalid choice.\n");
    }
    getch();
}
typedef struct {
    char username[1000];
    int score;
    int gold;
    int completed_games;
    int experience; 
} User;
User scoreboard[10];
char logged_in_user[1000];
void inf_scoreboard() {
    FILE *file = fopen(filefornames, "r");
    if (!file) return;

    int i = 0;
    char line[1000], username[1000];
    int score, gold, completed_games, experience;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d %d %d %d", username, &score, &gold, &completed_games, &experience);
        if (i < 10) {
            strcpy(scoreboard[i].username, username);
            scoreboard[i].score = score;
            scoreboard[i].gold = gold;
            scoreboard[i].completed_games = completed_games;
            scoreboard[i].experience = experience;
            i++;
        }
    }
    fclose(file);
}
void display_scoreboard(char *logged_in_user) {
    clear();
    printw("Score board:\n");
    printw("Rank     Username      Score     Gold     Completed Games      Experience\n");
}
int player_loc_x = 1, player_loc_y = 1;

int crash(int x, int y) {
    if (map[x][y] == wall || map[x][y] == pillar || map[x][y] == '_') {
        return 0;
    }
    return 1;
}
void show_map(int x, int y) {
    if (map[x][y] == door) {
        corridors(); 
        room_wall(); 
        }
}
void move_character(int x, int y) {
    int new_loc_x = player_loc_x + x;
    int new_loc_y = player_loc_y + y;
    if (crash(new_loc_x, new_loc_y)!=0) {
        player_loc_x = new_loc_x;
        player_loc_y = new_loc_y;
        show_map(new_loc_x, new_loc_y);
    }
}
int move_1(){
    int c ; 
    c= getch()-'0';
    switch (c) {
        case '8': move_character(-1, 0); 
        break; 
        case '2': move_character(1, 0); 
        break; 
        case '4': move_character(0, -1);
        break; 
        case '6': move_character(0, 1); 
        break; 
        case '7': move_character(-1, -1);
        break;
        case '9': move_character(-1, 1); 
        break;  
        case '1': move_character(1, -1); 
        break;  
        case '3': move_character(1, 1); 
        break;  
        case '5':
        endwin();
        return 0;
    }
}
void display_map() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            mvprintw(i, j, "%c", map[i][j]);
        }
    }
    mvprintw(player_loc_x, player_loc_y, "@");
    refresh(); 
}

void game_loop() {
     int key;
    while (key!=5) {
        key = getch() -'0';
        clear();  
        display_map(); 
        mvprintw(1,55,"Movement guide:\n");
        mvprintw(2,55,"press B to go down\n");
        mvprintw(3,55,"press H to go up\n");
        mvprintw(4,55,"press F to go right\n");
        mvprintw(5,55,"press D to go left\n");
        mvprintw(6,55,"press I to go right and up\n");
        mvprintw(7,55,"press G to go left and up\n");
        mvprintw(8,55,"press C to go right and down\n");
        mvprintw(9,55,"press A to go left and down\n");
        mvprintw(10,55,"press 5 to exit\n");
        move_1();
      
    }
}

int letter;
void pre_game_menu() {
    int choice;
    initscr();
    clear();
    noecho();
    cbreak();
    printw("Pre-game Menu:\n");
    printw("1. Start New Game\n");
    printw("2. Continue Previous Game\n");
    printw("3. Scoreboard\n");
    printw("4. Settings\n");
    printw("5. Profile Menu\n");
    printw("Choose an option: ");
    refresh();
    choice = getch() - '0';
    if(choice == 1) {
        printw("Starting new game...\n");
        clear();
        initialize_map_1();
        printw("Please press '9' to see the map\n");
        letter = getch() - '0';
        if(letter == 9){
        clear(); 
        room_wall();
        corridors();
        game_loop(); 
        } else{
            printw("Can't show the map!");
        }
    }
    else if(choice == 2) {
        printw("Continuing previous game...\n");
            clear();
        initialize_map_1();
        printw("Please press '9' to see the map\n");
        letter = getch() - '0';
        if(letter == 9){
        clear(); 
        room_wall();
        corridors();
        game_loop(); 
        
        } else{
            printw("Can't show the map!");
        }
    }
    else if(choice == 3) {
        printw("Displaying scoreboard...\n");
        clear();
        inf_scoreboard();
        display_scoreboard(logged_in_user);
    }
    else if(choice == 4) {
        settings_menu();
    }
    else if(choice == 5) {
        printw("Profile menu...\n");
    }
    else {
        printw("Invalid option.\n");
    }
    getch();
    endwin();
}
int main(){
    char username[1000], password[1000], email[1000];
    char guest[] = "Guest"; 
    int choice;
    initscr();
    clear();
    noecho();
    cbreak();
    printw("1. Login\n");
    printw("2. Login as Guest\n");
    printw("3. Register New User\n");
    printw("4. Settings\n");
    printw("6. See messages\n");
    printw("7. Exit\n");
    printw("Choose an option: ");
    refresh();
    choice = getch()- '0';

    if(choice == 1) {
        clear();
        printw("Enter username: ");
        echo();
        scanw("%s", username); 
        noecho();

        printw("Enter password: ");
        echo();
        scanw("%s", password);
        noecho();
        if (login(username, password)!=1) {
            strcpy(logged_in_user, username);
            printw("Login successful! Welcome %s.\n", username);
            pre_game_menu();
        } else {
            printw("Error: Invalid username or password!\n");
        }
    } else if (choice == 2) {
        printw("Logged in as guest! Welcome, %s.\n", guest);
        pre_game_menu();
    } else if (choice == 3) {
        clear();
        printw("Enter username: ");
        echo();
        scanw("%s", username);
        noecho();
        if (check_username(username)) {
            printw("Error: Username already exists!\n");
            getch();
            endwin();
            return 1;
        }else {
        strcpy(logged_in_user, username);
        }

        printw("Enter password: ");
        echo();
        scanw("%s", password);
        noecho();

        while (!check_password(password)) {
            printw("Error: Password must be at least 7 characters and contains at least one digit, one uppercase letter, and one lowercase letter.\n");
            printw("Enter password again: ");
            echo();
            scanw("%s", password);
            noecho();
        }

        printw("Enter email: ");
        echo();
        scanw("%s", email);
        noecho();

        while (!e_mail(email)) {
            printw("Error: Invalid email format!\n");
            printw("Enter email again: ");
            echo();
            scanw("%s", email);
            noecho();
        }

        saveuser(username, password, email);
        printw("User created successfully!\n");
    } else if (choice == 4) {
        settings_menu();
    }else if(choice == 5){
        inf_scoreboard();
        display_scoreboard(logged_in_user);
    }else if(choice == 6){
        game_action();
        game_hit();
        weapon_pickup();
        shooting();
        display_message(game_message);
    } else if (choice == 7) {
        clear();
        endwin();
        return 0;
    } else {
        printw("Invalid option. Try again.\n");
    }
    getch();
    endwin();
    return 0;
}