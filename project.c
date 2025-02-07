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
void initialize_map() {
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
}
void display_map() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 50; j++) {
            mvprintw(i, j, "%c", map[i][j]);
        }
    }
    refresh(); 
}
void room_wall() {
    for(int i = 2 ; i<=5; i++){
        map[4][i] = '_'; 
        map[1][i] = '_';
    }
    for (int i = 2; i<=3; i++){
        map[i][6] = '|';
        map[i][1] = '|';
    }
    for(int i =7; i<=8; i++){
        map[i][9] = '|';
        map[i][5] = '|';
    }
    for(int i=6; i<=9; i++){
         map[6][i] = '_';
         map[9][i] = '_';
    }
    for(int i=7; i<=8; i++){
        map[i][14] = '|';
        map[i][19] = '|';
    }
    for(int i=15; i<=18; i++){
        map[6][i] = '_';
        map[9][i] = '_';
    }
}
void doors() {
    map[8][10] = door;  
    map[8][13] = door;  
    map[2][7] = door;
    map[5][17] = door;
}
void corridors() {
        map[8][11] = corridor;
        map[8][12] = corridor;
        map[8][11] = corridor;
        for (int i=5 ; i>=3; i--){
            map[i][7] = corridor;
        }
        for(int i=8 ; i<=17 ; i++){
            map[4][i] = corridor;
        }
}
void pillars() {
    map[8][18] = pillar; 
    map[7][6] = pillar; 
    map[3][3] = pillar; 
}
void windows() {
    map[8][4] = window; 
    map[8][4] = window; 
    map[5][3] = window; 
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
            scanw("%d", &game_difficulty);
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
            scanw("%d", &color_choice);
            if (color_choice == 1){
                strcpy(hero_color, "red");
            } else if (color_choice == 2) {
                strcpy(hero_color, "blue");
            } else if (color_choice == 3) {
                strcpy(hero_color, "green");
            } else if (color_choice == 4) {
                strcpy(hero_color, "white");
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
        initialize_map();  
        doors();
        room_wall();
        corridors(); 
        pillars();   
        windows();   
        display_map(); 
    }
    else if(choice == 2) {
        printw("Continuing previous game...\n");
    }
    else if(choice == 3) {
        printw("Displaying scoreboard...\n");
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
    printw("5. Exit\n");
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
    } else if (choice == 5) {
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
