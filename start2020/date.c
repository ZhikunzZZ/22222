#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "date.h"
/*  
 * This is my own work as defined in the Academic Ethics agreement I have signed.
 */
struct date{
    int year;
    int month;
    int day;
};

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){
    Date *date = (Date*)malloc(sizeof(Date));
    sscanf(datestr, "%d/%d/%d", &date->day, &date->month, &date->year);
    if ((0 < date->day) && (date->day < 32) && (0 < date->month) && (date->month < 13) && (0 < date->year) && (date->year < 3000)){
        return date;
    }else{
        free(date);
        return NULL;
    }
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d){
    Date *date = (Date*)malloc(sizeof(Date));
    date->day = d->day;
    date->month = d->month;
    date->year = d->year;
    if(date){
        return date;
    }else{
        free(date);
        return NULL;
    }
    
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2){
    if(date1->year < date2->year){
        return -1;
    }
    else if(date1->year > date2->year){
        return 1;
    }
    else{
        if(date1->month < date2->month){
            return -1;
        }
        else if(date1->month > date2->month){
            return 1;
        }
        else{
            if(date1->day < date2->day){
                return -1;
            }
            else if(date1->day < date2->day){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d){
    free(d);
}
