#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define maxCars 100
#define maxString 50

#define colorsfile "BasicColors.txt"
#define companyfile "Companies.txt"
#define carsfile "Cars.txt"


// ===STRUCT AUTOKINHTOU===
typedef struct {
    int plate;
    char color[maxString];
    char company[maxString];
    int year;
} Car;
Car cars[maxCars];
int carCount = 0;
int unsaved_status = 0;
unsigned i,j;
int tempb;
char extra;

// ===FUNCTION NAMES (Den ekane compile to code xwris auta edw panw :(   )
int plate_exists(int plate);
int check_color_or_company(const char *value, int isColor);
void load_cars_from_file();
void read_all_cars();
void insert_car();
void bubble_sort_cars();
int menu();


// ---=== BUBBLE SORT GIA TA AMAJIA ===---A
void bubble_sort_cars() {
    for (i = 0; i < carCount - 1; i++) {
        for (j = 0; j < carCount - i - 1; j++) {
            if (cars[j].plate > cars[j + 1].plate) {
                Car temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}



// ---=== CHECK GIA XRWMA H COMPANY (IMPORTANT FOR LATER) ===---
int check_color_or_company(const char *value, int isColor) {
    FILE *fp;
    char temp[maxString];

    if (isColor == 1) {
        fp = fopen(colorsfile, "r");
    } else {
        fp = fopen(companyfile, "r");
    }

    if (fp == NULL) {
        printf("Error: Can't Open File!\n");
        return 0;
    }

    while (fscanf(fp, "%s", temp) == 1) {
        if (strcmp(temp, value) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// ---=== ELEGXOS AN YPARXEI PINAKIDA (EJISOU IMPORTANT) ===---
int plate_exists(int plate) {
    for (i = 0; i < carCount; i++) {
        if (cars[i].plate == plate)
            return 1;
    }
    return 0;
}


// ---=== HELPER FUNCTION Sth periptwsh pou o user den kanei save thn bash wste na mhn sbhstei ap th RAM ===---
int warn_unsaved_changes() {
    char ans;

    if (!unsaved_status) return 1;

    do {
        printf("\nYPARXOUN MH APOTHIKEUMENES ALLAGES!\n");
        printf("Theleis na synexiseis xwris save? (y/n): ");

        if (scanf("%s%c", &ans, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO mia leksh.\n");
            while (getchar() != '\n');
            continue;
        }

        if (ans == 'y' || ans == 'Y') {
            unsaved_status = 0;
            return 1;
        }
        else if (ans == 'n' || ans == 'N') {
            printf("Press any button to return to menu and save data-base. . . \n");
            system("PAUSE > nul");
            return 0;
        }
        else {
            printf("Lathos eisodos! Dose 'y' H 'n'.\n");
        }

    } while (1);
}


// ---====MAIN MENU: EKEI POU JEKINAEI O XRHSTHS KAI KATALHGEI PISW META APO KA8E EPILOGI====---
int menu() {
     
    int x;
    system("CLS");
    printf("-------------------------------------------------------------------------\n");
    printf("--------------------- BASH DEDOMENWN AUTOKINHTWN ------------------------\n");
    printf("-------------------------------------------------------------------------\n\n\n");

    printf(" BASIKO MENU ------------------------\n\n");
    
    printf("1) EMFANISH OLWN TWN AUTOKINHTWN\n");
    printf("2) EISAGWGH NEAS EGGRAFHS\n");
    printf("3) DIAGRAFH EGGRAFHS\n");
    printf("4) ANANEWSH EGGRAFHS\n");
    printf("5) ANAZHTHSH\n");
    printf("6) ANANEWSH BASHS DEDOMENWN\n");
    printf("0) EJODOS\n\n");



    printf("Ti epi8ymeis?\n");

    while (1) {
            printf("Epilejte: ");
            if (scanf("%d%c", &x, &extra) != 2 || extra != '\n') {
                printf("Lathos eisodos! Dose MONO arithmo.\n");
                while (getchar() != '\n');
                continue;
            }

            if (x < 0 || x > 6) {
                printf("Lathos epilogh! Dose arithmo 0-6.\n");
                continue;
            }

            break;
        }

    return x;
}

// ---====EPILOGI 1: EKTYPWSE OLA TA AUTOKINHTA AP TO CARS.TXT ====---
void read_all_cars() {
    FILE *fp = fopen(carsfile, "r");
    if (!fp) {
        printf("ERROR: CANNOT OPEN -> Cars.txt\n");
        return;
    }

    carCount = 0;

    while (fscanf(fp, "%d %s %s %d",
                  &cars[carCount].plate,
                  cars[carCount].color,
                  cars[carCount].company,
                  &cars[carCount].year) == 4) {
        carCount++;
        if (carCount >= maxCars) break;
    }

    fclose(fp);

    bubble_sort_cars();

    fp = fopen(carsfile, "r");
    if (fp != NULL) {
        for ( i = 0; i < carCount; i++) {
            fprintf(fp, "%d %s %s %d\n",
                    cars[i].plate,
                    cars[i].color,
                    cars[i].company,
                    cars[i].year);
        }
        fclose(fp);
    } else {
        printf("ERROR: Cannot open Cars.txt for writing!\n");
        return;
    }

    printf("----PINAKIDA-----XRWMA-----ETAIRIA------XRONOS---------------\n");
    for (i = 0; i < carCount; i++) {
        printf("%-10d %-15s %-20s %-6d\n",
               cars[i].plate,
               cars[i].color,
               cars[i].company,
               cars[i].year);
    }
    printf("-------------------------------------------------------------\n");
}


// ---==== EPILOGH 2: PROS8ESE KAINOURGIO AUTOKINHTO STO CARS.TXT ====---
void insert_car() {
    Car newCar;
    char temp[maxString];
    
    FILE *fp;

    // PINAKIDES
    fp = fopen(carsfile, "r");
    if (fp) {
        while (fscanf(fp, "%d %*s %*s %*d", &cars[carCount].plate) == 1) printf("%d\n", cars[carCount].plate);
        fclose(fp);
    } else printf("Error opening cars.txt!\n");

    do {
        printf("Ti arithmo Pinakidwn exei to autokinhto sou?: ");

        if (scanf("%d%c", &tempb, &extra) != 2 || extra != '\n') {
        printf("Lathos eisodos! Dose MONO arithmo.\n");
        while (getchar() != '\n');
        continue;
        }

        newCar.plate = tempb;

        if (newCar.plate < 1001 || newCar.plate > 9999)
            printf("Mh egkyros arithmos pinakidas! Prospathise ksana...\n");
            
        else if (plate_exists(newCar.plate))
            printf("Yparxei hdh ayth h pinakida autokinhtou! Prospathise ksana...\n");
        else break;
    } while (1);

    // XRWMA
    fp = fopen(colorsfile, "r");
    if (fp) {
        while (fscanf(fp, "%s", temp) == 1) printf("%s\n", temp);
        fclose(fp);
    } else printf("Error opening colors.txt!\n");

    do {
        printf("Ti xrwma einai to autokinhto?: ");
        if (scanf("%s%c", newCar.color, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO mia leksh.\n");
            while (getchar() != '\n');
            continue;
        }
        for (i = 0; newCar.color[i]; i++) newCar.color[i] = toupper(newCar.color[i]);
        if (!check_color_or_company(newCar.color, 1))
            printf("Den yparxei to ejhs xrwma! Prospathise ksana...\n");
        else break;
    } while (1);

    // KATASKEUASTHS
    fp = fopen(companyfile, "r");
    if (fp) {
        while (fscanf(fp, "%s", temp) == 1) printf("%s\n", temp);
        fclose(fp);
    } else printf("Error opening company file!\n");

    do {
        printf("Poion kataskeuasth exei auto to autokinhto sou?: ");

        if (scanf("%s%c", newCar.company, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO mia leksh.\n");
            while (getchar() != '\n');
            continue;
        }

        for (i = 0; newCar.company[i]; i++) newCar.company[i] = toupper(newCar.company[i]);

        if (!check_color_or_company(newCar.company, 0))
            printf("Den ypaxei auth h etairia! Prospathise ksana...\n");
        else break;

    } while (1);

    // ETOS KYKLOFORIAS
    do {
        printf("Dwse mou to etos kykloforias tou autokinhtou (1960 - 2025): ");

        if (scanf("%d%c", &tempb, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO arithmo.\n");
            while (getchar() != '\n');
            continue;
        }

        newCar.year = tempb;

        if (newCar.year < 1960 || newCar.year > 2025)
            printf("Mh egkyro etos! Prospathise ksana...\n");
        else break;

    } while(1);

    // PROSTHESI
    cars[carCount++] = newCar;
    unsaved_status = 1;
    printf("EPITYXHS NEA EGGRAFH!\n");
}

// ---==== EPILOGH 3: DIAGRAFH ENOS AUTOKINHTOU AP TO CARS.TXT BASH PINAKIDWN ====---
void delete_car() {
    int plateToDelete;
    int found = 0;
     

    if (carCount == 0) {
        printf("Den yparxoun amajia sto cars.txt!.\n");
        return;
    }

    printf("Yparxouses Pinakides:\n");
    for (i = 0; i < carCount; i++) {
        printf("%d\n", cars[i].plate);
    }
    printf("\n");

    do {
        printf("Poia pinakida 8elete na diagrafei: ");

        if (scanf("%d%c", &plateToDelete, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO arithmo.\n");
            while (getchar() != '\n');
            continue;
        }

        found = 0;

        for (i = 0; i < carCount; i++) {
            if (cars[i].plate == plateToDelete) {
                found = 1;

                for (j = i; j < carCount - 1; j++) {
                    cars[j] = cars[j + 1];
                }
                carCount--;
                unsaved_status = 1;
                printf("Epityxhs diagrafh autokinhtou apo thn bash!\n");
            }
        }

        if (!found) {
            printf("H Pinakida den yparxei, janaprospathise!\n");
        }

    } while (!found);

}

// ---==== EPILOGH 4: ANANEWSH MIAS YPARXONTHS EGGRAFHS ====---
void update_car() {
    if (carCount == 0) {
        printf("Den yparxoun amajia sto Cars.txt!\n");
        return;
    }
    FILE *fp;
     
    bubble_sort_cars();

    printf("Yparxouses Pinakides:\n");
    for (i = 0; i < carCount; i++)
        printf("%d\n", cars[i].plate);
    printf("\n");

    int plateToUpdate;
    int index = -1;
    do {
        printf("Poia pinakida 8elete na tropopoihsete: ");

        if (scanf("%d%c", &plateToUpdate, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO arithmo.\n");
            while (getchar() != '\n');
            continue;
        }

        for (i = 0; i < carCount; i++) {
            if (cars[i].plate == plateToUpdate) {
                index = i;
                break;
            }
        }
        if (index == -1)
            printf("H pinakida den yparxei!, prospathise ksana... \n");
    } while (index == -1);

    char temp[maxString];

    // --- xrwma ---
    char tempColor[maxString];
    fp = fopen(colorsfile, "r");
    if (fp) {
        while (fscanf(fp, "%s", temp) == 1) printf("%s\n", temp);
        fclose(fp);
    }
    do {
    printf("Neo xrwma <HDH YPARXON XRWMA: %s>: ", cars[index].color);

        if (scanf("%s%c", tempColor, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO mia leksh.\n");
            while (getchar() != '\n');
            continue;
        }

    for (i = 0; tempColor[i]; i++)
        tempColor[i] = toupper(tempColor[i]);

    if (!check_color_or_company(tempColor, 1))
        printf("Den yparxei to ejhs xrwma! Prospathise ksana...\n");
    else {
        strcpy(cars[index].color, tempColor);
        break;
    }

} while (1);

    // --- company ---
fp = fopen(companyfile, "r");
    if (fp) {
        while (fscanf(fp, "%s", temp) == 1) 
            printf("%s\n", temp);
        fclose(fp);
    }

    do {
        char tempCompany[maxString];
        printf("Neo kataskeuasths <HDH YPARXON COMPANY: %s>: ", cars[index].company);

        if (scanf("%s%c", tempCompany, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO mia leksh.\n");
            while (getchar() != '\n');
            continue;
        }

        for (i = 0; tempCompany[i]; i++)
            tempCompany[i] = toupper(tempCompany[i]);

        if (!check_color_or_company(tempCompany, 0))
            printf("Den ypaxei auth h etairia! Prospathise ksana...\n");
        else {
            strcpy(cars[index].company, tempCompany);
            break;
        }

    } while (1);

    // --- year ---
    do {
        int tempYear;
        printf("Neo etos kykloforias (1960-2025) <to amaji exei tin xronologia: %d>: ", cars[index].year);

        if (scanf("%d%c", &tempYear, &extra) != 2 || extra != '\n') {
            printf("Lathos eisodos! Dose MONO arithmo.\n");
            while (getchar() != '\n');
            continue;
        }

        if (tempYear < 1960 || tempYear > 2025)
            printf("Mh egkyro etos! Prospathise ksana...\n");
        else {
            cars[index].year = tempYear;
        break;
    }

} while (1);

    unsaved_status = 1;
    printf("EPITYXHS ANANEWSH AUTOKINHTOU!\n");
}

// ---==== EPILOGH 5: ANAZHTHSH ====---
void search_cars() {
    int choice;
    char input[maxString];
     

    do {
        printf("MENU ANAZHTHSHS\n");
        printf("1. ME BASH TON ARITHMO\n");
        printf("2. ME BASH TO XRWMA\n");
        printf("3. ME BASH TO KATASKEUASTH\n");
        printf("4. ME BASH TO XRONO KYKLOFORIAS\n");
        printf("0. EPISTROFH STO BASIKO MENU\n\n");

        int result;
        while (1) {
            printf("Epilejte: ");
            if (scanf("%d%c", &choice, &extra) != 2 || extra != '\n') {
                printf("Lathos eisodos! Dose MONO arithmo.\n");
                while (getchar() != '\n');
                continue;
            }

            if (choice < 0 || choice > 4) {
                printf("Lathos epilogh! Dose arithmo 0-4.\n");
                continue;
            }

            break;
        }


        if (choice == 0) return;

        switch (choice) {
        case 1: { 
            char comp;
            int num;
            while (1) {
                printf("KRITHRIA ANAZHTHSHS (e.g. > 7000): ");

                if (scanf(" %c %d%c", &comp, &num, &extra) == 3 &&
                    (comp == '>' || comp == '<') &&
                    extra == '\n') {

                    break;

                } else {
                    printf("Lathos eisodos! Dose '>' h '<' kai ton arithmo pinakidwn!\n");
                    while (getchar() != '\n');
                }
            }

            printf("\nEGGRAFES:\n");
            for (i = 0; i < carCount; i++) {
                if ((comp == '>' && cars[i].plate > num) || (comp == '<' && cars[i].plate < num)) {
                    printf("ARITHMOS: %d\nXRWMA: %s\nKATASKEUASTHS: %s\nXRONOLOGIA: %d\n\n",
                        cars[i].plate, cars[i].color, cars[i].company, cars[i].year);
                }
            }
            break;
        }

        case 2: {
            printf("DIATHESIMA XRWMATA:\n");
            FILE *f = fopen("BasicColors.txt", "r");

            if (f == NULL) {
                printf("Lathos anoigma arxeiou BasicColors.txt!\n");
                break;
            }

            char color[maxString];

            while (fscanf(f, "%s", color) == 1) {
                printf("%s \n", color);
            }
            printf("\n\n");
            fclose(f);

            int valid = 0;
            do {
                printf("XRWMA ANAZHTHSHS: ");

                if (scanf("%s%c", input, &extra) != 2 || extra != '\n') {
                    printf("Lathos eisodos!\n");
                    while (getchar() != '\n');
                    continue;
                }

                for (i = 0; input[i]; i++) input[i] = toupper(input[i]);

                valid = 0;
                FILE *f2 = fopen("BasicColors.txt", "r");
                if (f2 != NULL) {
                    while (fscanf(f2, "%s", color) == 1) {
                        for (i = 0; color[i]; i++) color[i] = toupper(color[i]);
                        if (strcmp(input, color) == 0) {
                            valid = 1;
                            break;
                        }
                    }
                    fclose(f2);
                }

                if (!valid) {
                    printf("Lathos eisodos! Dose ena diathesimo xrwma.\n");
                }

            } while (!valid);

            printf("\nEGGRAFES:\n");
            for (i = 0; i < carCount; i++) {
                char tempColor[maxString];
                strcpy(tempColor, cars[i].color);
                for (j = 0; tempColor[j]; j++) tempColor[j] = toupper(tempColor[j]);

                if (strcmp(tempColor, input) == 0) {
                    printf("ARITHMOS: %d\nXRWMA: %s\nKATASKEUASTHS: %s\nXRONOLOGIA: %d\n\n",
                        cars[i].plate, cars[i].color, cars[i].company, cars[i].year);
                }
            }
            break;
        }

        case 3: {
            printf("DIATHESIMOI KATASKEUASTES:\n");
            FILE *f = fopen("Companies.txt", "r");
            if (f == NULL) {
                printf("Lathos anoigma arxeiou Companies.txt!\n");
                break;
            }
            char company[maxString];
            while (fscanf(f, "%s", company) == 1) {
                printf("%s \n", company);
            }
            printf("\n\n");
            fclose(f);

            int valid = 0;
            do {
                printf("ANAZHTHSH KATASKEUASTH: ");

                if (scanf("%s%c", input, &extra) != 2 || extra != '\n') {
                    printf("Lathos eisodos!\n");
                    while (getchar() != '\n');
                    continue;
                }

                for (i = 0; input[i]; i++) input[i] = toupper(input[i]);

                valid = 0;
                FILE *f2 = fopen("Companies.txt", "r");
                if (f2 != NULL) {
                    while (fscanf(f2, "%s", company) == 1) {
                        for (i = 0; company[i]; i++) company[i] = toupper(company[i]);
                        if (strcmp(input, company) == 0) {
                            valid = 1;
                            break;
                        }
                    }
                    fclose(f2);
                }

                if (!valid) {
                    printf("Lathos eisodos! Dose ena diathesimo kataskeyasth.\n");
                }

            } while (!valid);

            printf("\nEGGRAFES:\n");
            for (i = 0; i < carCount; i++) {
                char tempCompany[maxString];
                strcpy(tempCompany, cars[i].company);
                for (j = 0; tempCompany[j]; j++) tempCompany[j] = toupper(tempCompany[j]);

                if (strcmp(tempCompany, input) == 0) {
                    printf("ARITHMOS: %d\nXRWMA: %s\nKATASKEUASTHS: %s\nXRONOLOGIA: %d\n\n",
                        cars[i].plate, cars[i].color, cars[i].company, cars[i].year);
                }
            }
            break;
        }

        case 4: { 
            char comp;
            int year;
            while (1) {
                printf("KRITHRIA ANAZHTHSHS (e.g. > 2005): ");
                if (scanf(" %c %d%c", &comp, &year, &extra) == 3 &&
                    (comp == '>' || comp == '<') &&
                    extra == '\n') {

                    break;

                } else {
                    printf("Lathos eisodos! Dose '>' h '<' kai ton arithmo pinakidwn!\n");
                    while (getchar() != '\n');
                }
            }

            printf("\nEGGRAFES:\n");
            for (i = 0; i < carCount; i++) {
                if ((comp == '>' && cars[i].year > year) || (comp == '<' && cars[i].year < year)) {
                    printf("ARITHMOS: %d\nXRWMA: %s\nKATASKEUASTHS: %s\nXRONOLOGIA: %d\n\n",
                        cars[i].plate, cars[i].color, cars[i].company, cars[i].year);
                }
            }
            break;
        }

        default:
            printf("LATHOS EPILOGH!\n");
    }

        printf("Press any key to continue...\n");
        system("PAUSE > nul");
        system("CLS");

    }while (1);
}


// ---==== EPILOGH 6: ENHMERWSH PINAKA ====---
void save_cars_to_file() {
    FILE *fp = fopen(carsfile, "w");
    if (!fp) {
        printf("ERROR: Den mporese na ginei save sto Cars.txt. . .\n");
        return;
    }

    for (i = 0; i < carCount; i++) {
        fprintf(fp, "%d %s %s %d\n",
                cars[i].plate,
                cars[i].color,
                cars[i].company,
                cars[i].year);
    }

    fclose(fp);
    unsaved_status = 0;
    printf("EPITYXHS APOTHIKEYSH STO ARXEIO!\n");
}



// TO MAIN PROGRAMM POU TA TREXEI OLA
int main() {
    int x;

    // mikro check to count wste na mhn perimenei to read_all func
    FILE *fp = fopen("Cars.txt", "r");
    if (fp != NULL) {
        carCount = 0;
        while (fscanf(fp, "%d %s %s %d", 
                      &cars[carCount].plate, 
                      cars[carCount].color, 
                      cars[carCount].company, 
                      &cars[carCount].year) == 4) {
            carCount++;
            if (carCount >= maxCars) break;
        }
        fclose(fp);
    } else {
        printf("ERROR: den mporese na anoixtei to Cars.txt\n");
    }

    while (1) {
        x = menu();
            switch (x) {
            case 0:
                if (!warn_unsaved_changes(0)) break;
                return 0;

            case 1:
                if (!warn_unsaved_changes(0)) break;
                system("CLS");
                read_all_cars();
                printf("Press Any Key To Return to the menu . . . ");
                system("PAUSE > nul");
                break;
            case 2:
                if (!warn_unsaved_changes(0)) break;
                system("CLS");
                insert_car();
                printf("Press Any Key To Return to the menu . . . ");
                system("PAUSE > nul");
                break;
            case 3:
                if (!warn_unsaved_changes(0)) break;
                system("CLS");
                delete_car();
                printf("Press Any Key To Return to the menu . . . ");
                system("PAUSE > nul");
                break;
            case 4:
                if (!warn_unsaved_changes(0)) break;
                system("CLS");
                update_car();
                printf("Press Any Key To Return to the menu . . . ");
                system("PAUSE > nul");
                break;
            case 5:
                if (!warn_unsaved_changes(0)) break;
                system("CLS");
                search_cars();
                printf("Press Any Key To Return to the menu . . . ");
                system("PAUSE > nul");
                break;
            case 6:
                system("CLS");
                save_cars_to_file();
                printf("Press Any Key to return to the menu . . . ");
                system("PAUSE > nul");
                break;
            
            default:
                printf("La8os input, pata otidipote gia na gyriseis sto menu kai janaprospa8hse . . . ");
                system("PAUSE > nul");
                break;
        }
    }       
}