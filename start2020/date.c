#include <stdio.h>
#include "date.h"
#include <string.h>
#include <stdlib.h>

struct date{
    int day;
    int month;
    int year;
};

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){
    Date thisDate;
    int day,month,year;
    if( 3 ==  sscanf(datestr, "%d/%d/%d;", &day, &month, &year)){
        if(day<= 31 & day > 0 & month <= 12 & month >= 1 & year >= 1 & year <= 9999){
            thisDate.day = day;
            thisDate.month = month;
            thisDate.year = year;
        }else{return(NULL);}
    }else{return(NULL);};

    Date* ptr = (Date*) malloc(sizeof(Date));

    if(ptr==NULL){
        return(NULL);
    }

    ptr->day = thisDate.day;
    ptr->month = thisDate.month;
    ptr->year = thisDate.year;
    
    return(ptr);
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d){
    Date* dupe = (Date*) malloc(sizeof(Date));
    if(dupe == NULL){
        return(NULL);
    }else{
        memcpy(dupe,d,sizeof(Date));
        return(dupe);
    }
}

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2){

    if(date1->year == date2->year){
        if(date1->month == date2->month){
            if(date1->day == date2->day){
                return(0);
            }else if(date1->day > date2->day){
                return(1);
            }else{
                return(-1);
            }
        }else if(date1->month > date2->month){
            return(1);
        }else{
            return(-1);
        }
    }else if(date1->year > date2->year){
        return(1);
    }else{
        return(-1);
    }
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d){
    free(d);
    d = NULL;
}


//#endif /* _DATE_H_INCLUDED_ */