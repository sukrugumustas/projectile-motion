//Şükrü GÜMÜŞTAŞ, 150114032, HW1Q1
//Projectile motion calculator
#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int checkCharacters(char *a);

double getValue();

double getValueWithBound(double b);

void hByInterval(double time, double flyingTime, double Vy, double g);

void xByInterval(double time, double flyingTime, double Vx);

int main() {
    double theta, radian, V0, time, Vx = 0, Vy, flyingTime, g = 9.80665;
    //entering the V0
    printf("Please enter the initial velocity (V0): ");
    V0 = getValue();
    printf("Please enter the initial angle (between 0 and 180): ");
    theta = getValueWithBound(180);

    //If V0 is less than or equal to 0, the user will be prompt to enter it again.
    //theta value
    radian = (theta * M_PI) / 180;
    if (theta != 90) {
        Vx = V0 * cos(radian);
    }
    Vy = V0 * sin(radian);
    flyingTime = (Vy * 2) / g;
    //I put this here so user can see the flying time and can not enter a time interval out of flying time's bounds.
    printf("\nThe flying time is: %.16lf\nPlease enter the time interval: ", flyingTime);
    //entering the time interval
    time = getValueWithBound(flyingTime);
    printf("\nThe Vx value of V0 is %.16lf.\n"
           "The Vy value of V0 is %.16lf.\n\n"
           "h by %.16lf time interval:\n\n"
           "Time\t\t\t\tHeight\n"
           "-----------------------------------------------\n", Vx, Vy, time);
    hByInterval(time, flyingTime, Vy, g);
    printf("\nx by %.16lf time interval:\n\n"
           "Time\t\t\t\tDistance\n-----------------------------------------------\n", time);
    xByInterval(time, flyingTime, Vx);
    printf("\nHighest point is %.16lf.\n\nDistance at highest point is %.16lf.", (Vy * Vy) / (2 * g),
           (Vx * flyingTime) / 2);
    return 0;
}

//This method is used to get values from user.
double getValue() {
    //A character array to store user entered string.
    char *a = (char *) malloc(sizeof(char)), *ptr;
    int boolean = 1;
    double returner;
    while (boolean) {
        fgets(a, INT_MAX, stdin);
        if (a[strlen(a) - 1] == '\n') {
            a[strlen(a) - 1] = '\0';
        }
        switch (checkCharacters(a)) {
            case 0:
                printf("You must enter positive integer number! Please reenter: ");
                break;
            default:
                boolean = 0;
        }
    }
    returner = strtod(a, &ptr);
    free(a);
    return returner;
}

int checkCharacters(char *a) {
    int i, length = (int) strlen(a);
    for (i = 0; i < length; i++) {
        if (!(isdigit(a[i]) || a[i] == '.')) {
            return 0;
        }
    }
    return 1;
}

double getValueWithBound(double b) {
    double a;
    while ((a = getValue()) >= b) {
        printf("You must enter the value less than ");
        if ((double) ((int) b) == b) {
            printf("%d", (int) b);
        } else {
            printf("%.16lf", b);
        }
        printf("! Please reenter: ");
    }
    return a;
}

void hByInterval(double time, double flyingTime, double Vy, double g) {
    double j = time;
    while (j <= flyingTime) {
        printf("%.16lf\t%.16lf\n", j, j * (Vy - (0.5 * g * j)));
        j += time;
    }
}

void xByInterval(double time, double flyingTime, double Vx) {
    double j = time;
    while (j <= flyingTime) {
        printf("%.16lf\t%.16lf\n", j, j * Vx);
        j += time;
    }
}
