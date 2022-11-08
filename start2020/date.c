/*
 * This is my own work as defined in the Academic Ethics agreement I have signed.
 */

#include "date.h"
#include <stdlib.h>
#include <string.h>

//-----dd/mm/yyyy
#define DATE_LEN 10

struct date {
    int day;
    int month;
    int year;
};

Date *date_create(char *datestr) {
    struct date *d = (struct date *) malloc(sizeof(struct date));

    char input_date[DATE_LEN + 1];
    strcpy(input_date, datestr);

    const char *delim = "/";

    if (input_date[0] == '\0') input_date[0] = '0'; //if datestr[0] == 0 than after strcpy input_date[0] == '\0'
    if (strlen(datestr) != DATE_LEN || input_date[2] != '/' || input_date[5] != '/') return NULL; //straightforward way to parse date

    d->day = atoi(strtok(input_date, delim));
    d->month = atoi(strtok(NULL, delim));
    d->year = atoi(strtok(NULL, delim));

    if ((d->day < 1 || d->day > 31) || (d->month < 1 || d->month > 12) || d->year < 1) {
        free(d);
        d = NULL;
        return NULL;
    }
    return d;
}

Date *date_duplicate(Date *d) {
    struct date *copy = NULL;
    if ((copy = (struct date *) malloc(sizeof(struct date))) != NULL) {
        copy->day = d->day;
        copy->month = d->month;
        copy->year = d->year;
    }
    return copy;
}

int date_compare(Date *date1, Date *date2) {
    if (date1->year != date2->year) {
        return (date1->year - date2->year);
    }
    if (date1->month != date2->month) {
        return (date1->month - date2->month);
    }
    if (date1->day != date2->day) {
        return date1->day - date1->day;
    }
    return 0;
}

void date_destroy(Date *d) {
    if (d != NULL) {
        free(d);
    }
}

