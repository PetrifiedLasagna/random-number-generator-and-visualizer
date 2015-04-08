#include <stdio.h>
#include <time.h>
#include "utils.h"

/* This comment must not be removed
This  File was written by PetrifiedLasagna and is from the following Github repository
https://github.com/PetrifiedLasagna/random-number-generator-and-visualizer

these files should come with a file explaining their usage/license.
*/

static unsigned long int rseed = 590178402;


///Generate a seed with the date (year/month/day) and time (hour/minute/second)
///All values that can be a possible zero(0) have one(1) added to them
void genrseed(){
    time_t timer;
    struct tm *now;

    time(&timer);
    now = localtime(&timer);

    int year = now->tm_year + 1900;
    int month = now->tm_year + 1;
    int day = now->tm_mday;

    unsigned long calcnt = year * day * (year + month * day);
    unsigned long calcnt2 = day * month * (day + year * day);
    unsigned long calcnt3 = month * year * (month + day * year);

    int hour = now->tm_hour + 1;
    int minute = now->tm_mday + 1;
    int sec = now->tm_sec + 1;

    unsigned long timcnt = hour * sec * (hour + minute * hour);
    unsigned long timcnt2 = sec * minute * (sec + hour * sec);
    unsigned long timcnt3 = minute * hour * (minute + sec * minute);

    rseed = (calcnt * calcnt2 - calcnt3) * (timcnt * timcnt2 - timcnt3);
    rseed = rseed ^ (calcnt3 * calcnt2 - calcnt) * (timcnt3 * timcnt2 - timcnt);
}

///Generates random number with each call
///The low and high halfs are stored into two variables and the get swapped when they are packed into the rseed variable again
unsigned long rnd(){
    unsigned long lowb = (rseed << sizeof(rseed) * 8 / 2) >> sizeof(rseed) * 8 / 2;
    unsigned long higb = rseed >> sizeof(rseed) * 8 / 2;

    lowb += higb / 3;
    unsigned long res = lowb;

    rseed = (lowb << sizeof(rseed) * 8 / 2) | higb;

    return res;
}
