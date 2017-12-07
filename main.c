//Şükrü GÜMÜŞTAŞ, 150114032, HW1Q1
//Projectile motion calculator
#include<stdio.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int checkCharacters(char *a);

double getValue();

double getValueWithBound(double b);

void xByInterval();

void hByInterval();

double V0, time, Vx = 0, Vy, flyingTime, g = 9.80665;

int main() {
    double theta, radian;
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
                   "Time\t\t\tHeight\n"
                   "-----------------------------------------------\n", Vx, Vy, time);
    hByInterval();
    printf("\nx by %.16lf time interval:\n\n"
                   "Time\t\t\tDistance\n-----------------------------------------------\n", time);
    xByInterval();
    printf("\nHighest point is %.16lf.\n\nDistance at highest point is %.16lf.", (Vy * Vy) / (2 * g),
           (Vx * flyingTime) / 2);
    return 0;
}

int checkCharacters(char *a) {
    int i, length = strlen(a);
    for (i = 0; i < length; i++) {
        if (!(isdigit(a[i]) || a[i] == '.' || a[i] == '-')) {
            return 1;
        }
    }
    if (atof(a) <= 0) {
        return 0;
    }
    return 2;
}

double getValue() {
    char *a = (char *) malloc(sizeof(char));
    while (1) {
        switch (checkCharacters(gets(a))) {
            case 0    :
                printf("Your value must be greater than zero! Please reenter: ");
                break;
            case 1    :
                printf("You entered invalid characters! Please reenter: ");
                break;
            default    :
                goto exit_loop;
        }
    }
    exit_loop:;
    return atof(a);
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

void hByInterval() {
    double j;
    for (j = time; j <= flyingTime; j += time) {
        printf("%.16lf\t%.16lf\n", j, j * (Vy - (0.5 * g * j)));
    }
}

void xByInterval() {
    double j;
    for (j = time; j < flyingTime; j += time) {
        printf("%.16lf\t%.16lf\n", j, j * Vx);
    }
}