#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#define filefornames "users.txt" 

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
    if (dot == NULL)
        return 0;
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
    scanw("%d", &choice);
    if(choice == 1) {
        printw("Starting new game...\n");
    }
    else if(choice == 2) {
        printw("Continuing previous game...\n");
    }
    else if(choice == 3) {
        printw("Displaying scoreboard...\n");
    }
    else if(choice == 4) {
        printw("Settings menu...\n");
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

void settings_menu() {
    int choice;
    clear();
    printw("Settings Menu:\n");
    printw("1. Set Game Difficulty\n");
    printw("2. Change Hero Color\n");
    printw("3. Back to Main Menu\n");
    printw("Enter your choice: ");
    scanw("%d", &choice);

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
    scanw("%d ", &choice);

    if(choice == 1) {
        printw("Enter username: ");
        echo();
        scanw("%s", username); 
        noecho();

        printw("Enter password: ");
        echo();
        scanw("%s", password);
        noecho();

        if (login(username, password)) {
            printw("Login successful! Welcome %s.\n", username);
            pre_game_menu();
        } else {
            printw("Error: Invalid username or password!\n");
        }
    } else if (choice == 2) {
        printw("Logged in as guest! Welcome, %s.\n", guest);
        pre_game_menu();
    } else if (choice == 3) {
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
        printw("Exiting...\n");
        getch();
        endwin();
        return 0;
    } else {
        printw("Invalid option. Try again.\n");
    }
    getch();
    endwin();
    return 0;
}
