/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Anjali Kalambe
 * Student ID: 13204678
 * Date of submission: 08/09/2020
 * A brief statement on what you could achieve (less than 50 words):
 * Completed all functionality 
 * Passed all tests on Ed 
 * Practiced good coding style
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h>
/*Functions used - flcose(), fopen(), fread(), fwrite(), 
printf(), scanf(), getchar()*/

#include <string.h>
/*Functions used - strcmp(), strlen()*/

#include <stdlib.h>
/*Functions used - exit(),*/

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"
#define DEPARTURE_CITY "SYD"

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/

struct date
{
    int month;
    int day;
    int hour;
    int minute;
};
typedef struct date date_t;

struct flight
{
    char flightcode[MAX_FLIGHTCODE_LEN+1]; /*plus 1 to account for null term*/
    date_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN+1]; /*plus 1 to account for null term*/
    date_t arrival_dt;
};
typedef struct flight flight_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void print_menu(void);
void select_menu_option(flight_t flights[], int flights_array_len);

void add_flight(flight_t flights[], int flights_array_len);
int check_flight_code(const char input[]);
int check_date(const date_t date);

void show_flights(flight_t flights[], int size);
void format_flight_details(const flight_t flight);

void save_flight(flight_t flights[], int size);
void load_flights();
void exit_program();

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /*An array is initalised when program start which stores all flights that
    * get added, this array is passed around and is manipulated.*/
    flight_t flights[MAX_NUM_FLIGHTS]; 
    int flights_array_len = 0;
    print_menu();
    select_menu_option(flights, flights_array_len); 

    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu(void)
{
    printf("\n"
           "1. add a flight\n"
           "2. display all flights to a destination\n"
           "3. save the flights to the database file\n"
           "4. load the flights from the database file\n"
           "5. exit the program\n"
           "Enter choice (number between 1-5)>\n");
}

/*******************************************************************************
 * After print_menu displays the menu, this function reads user choice/input and 
 * directs them to the assigned function which will carry out that functionality.
 * inputs:
 * - flights array: passess through the array which was first created in 
 * the main 
 * - flights_array_len: passes through the size of the array.
 * outputs:
 * - none
*******************************************************************************/
void select_menu_option(flight_t flights[], int flights_array_len)
{
    int choice;
    scanf("%d", &choice);

    switch (choice) /*takes user input to determine what function to run*/
    {
    case 1:
        add_flight(flights, flights_array_len);
        break;
    case 2:
        show_flights(flights, flights_array_len);
        break;
    case 3:
        save_flight(flights, flights_array_len);
        break;
    case 4:
        load_flights();
        break;
    case 5:
        exit_program();
        break;
    default:
        /*if incorrect input given then it will continue to show menu unless 5 
        is typed*/
        printf("Invalid choice\n"); 
        print_menu();
        select_menu_option(flights, flights_array_len);
    }
}

/*******************************************************************************
 * This function allows user to add a flight and store it in the flights array
 * if the array is not full already, otherwise tells the user no more 
 * flights can be added.
 * inputs: The inputs allow updating of the flights array.
 * - flights array: passess through the array which was first created in 
 * the main 
 * - flights_array_len: passes through the size of the array.
 * outputs:
 * - none
*******************************************************************************/
void add_flight(flight_t flights[], int flights_array_len)
{

    flight_t flight; 
    /*this struct will store the flight created through this function and 
    will add it to the array in the end if created successfully*/
    int current_available_pos = flights_array_len;
    /*the length of the array tells which position in array is available 
    to add the flight struct created from this function*/

    /*shouldnt add more flights if array is full*/
    if (flights_array_len != MAX_NUM_FLIGHTS)
    {
        /*all do-while loops here check to see if given input is invalid, 
        this is done using helper functions which are called and if they 
        return 0 (false) then input is valid and loop breaks thus moves on.*/

        do
        {
            printf("Enter flight code>\n");
            getchar();
            scanf("%[^\n]s", flight.flightcode); 
            /*this scanf accepts spaces as char-useful to see if space exists*/
        } while (check_flight_code(flight.flightcode) == 1);

        printf("Enter departure info for the flight leaving %s.\n", 
        DEPARTURE_CITY);
        do
        {
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", 
            &flight.departure_dt.month, 
            &flight.departure_dt.day, 
            &flight.departure_dt.hour, 
            &flight.departure_dt.minute);
        } while (check_date(flight.departure_dt) == 1);

        printf("Enter arrival city code>\n");
        scanf("%s", flight.arrival_city);

        printf("Enter arrival info.\n");
        do
        {
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", 
            &flight.arrival_dt.month, 
            &flight.arrival_dt.day,
            &flight.arrival_dt.hour, 
            &flight.arrival_dt.minute);
        } while (check_date(flight.arrival_dt) == 1);

        /*if every check is successful then the flight struct is added to 
        the array of flights structures*/
        flights[current_available_pos] = flight;
        flights_array_len++; /*since a flight struct was added, num of structs 
        in array also increases by 1. */
    }
    else
    {
        printf("Cannot add more flights - memory full\n");
        /*if length of array (num of flights) is equal to capacity of array
        then user cannot be allowed to add more flights.*/
    }

    print_menu();
    select_menu_option(flights, flights_array_len);
    /*passes updated array and its new occupied length*/
}

/*******************************************************************************
 * This function is called when the flight code needs to be validated to see 
 * if it is in the required format. 
 * inputs: 
 * - flightcode array: this is an array of chars - a 'string' which user gave as
 * input when asked give flight code in the add_flight function. This is the 
 * string on which checks will be performed. The array is accepted as a 'const'
 * as this function shouldnt be able to accidently change what the user input
 * initally was.
 * outputs:
 * - returns 0 or 1. If the flight code is valid then 0 is returned, 
 * otherwise if any check is failed then 1 is returned.
*******************************************************************************/
int check_flight_code(const char flightcode[])
{
    /*checks string length - must be in between 2 and 7 (not inclusive) */
    if ((int)strlen(flightcode) > 2 && (int)strlen(flightcode) < 7)
    {   
        /*checks to see first char is not in lowercase*/
        if (flightcode[0] >= 'A' && flightcode[0] <= 'Z')
        {
            /*checks to see second char is not in lowercase*/
            if (flightcode[1] >= 'A' && flightcode[1] <= 'Z')
            {
                int i;
                for (i = 2; i < (int)strlen(flightcode); i++)
                {/*this loop checks every char after the 2nd char is a number*/
                    int num = flightcode[i] - '0'; /*conversts char to int*/
                    if (num < 0 || num > 9 || flightcode[i] == ' ')
                    {
                        printf("Invalid input\n");
                        return 1;/*if char is not a number*/
                    }
                }
                return 0; /*return 0 if all checks passed*/
            }
        }
    }
    printf("Invalid input\n");
    return 1;/*if any check is not passed*/
}

/*******************************************************************************
 * This function is called when any date(arrival/departure) needs to be 
 * checked to see if its in the correct date/time format. The format is just 
 * basic checks to see if month is in between 0 to 12, day is in between 1 to 31, 
 * hour is in between 0 to 23 and minute is in between 0 to 60. 
 * inputs: input is passed as a const as its values shouldnt be changed.
 * - date stucture: the entire date struct in which user input for a date is 
 * stored is passed through to be checked.
 * outputs:
 * - returns 0 or 1. If the date is valid then 0 is returned, otherwise if
 * any check is failed then 1 is returned.
*******************************************************************************/
int check_date(const date_t date)
{   
    /*checks that num entered for month and day are valid month/day dates*/
    if(date.month > 0 && date.month < 13 && date.day > 0 && date.day < 32)
    {
        /*checks that num entered for hour and minute are valid*/
        if(date.hour>=0 && date.hour<24 && date.minute>=0 && date.minute<60)
        {
            return 0; /*return 0 if all checks passed*/
        }
    }
    printf("Invalid input\n");
    return 1;/*if any check is not passed*/
}

/*******************************************************************************
 * This function is called when user chooses to view the flights stored 
 * in the flights array.
 * inputs:
 * - flights array: passess through the array which was first created in 
 * the main 
 * - flights_array_len: passes through the size of the array.
 * outputs:
 * - none
*******************************************************************************/
void show_flights(flight_t flights[], int flights_array_len)
{

    char city_code[MAX_CITYCODE_LEN];/*accounts for null terminator*/

    printf("Enter arrival city code or enter * to show all destinations>\n");
    scanf("%s", city_code); /*takes user choice of what to filter by*/

    if (strcmp(city_code, "*") == 0)
    {
        if (flights_array_len != 0)
        {
            /*if user selects to see all and flights is not empty then for
            loop goes over every flight and sends every flight to a helper 
            function which prints it in a specific format*/

            printf("Flight Origin          Destination\n");
            printf("------ --------------- ---------------\n");

            int i;
            for (i = 0; i < flights_array_len; i++)
            {
                format_flight_details(flights[i]);
            }
        }
        else
        {
            /*if array length of flights is 0*/
            printf("No flights\n");
        }
    }
    else
    {
        /*enters this block if user wants to filter by flight code rather than 
        see all*/
        int matched_codes = 0;
        int i;
        for (i = 0; i < flights_array_len; i++)
        {
            /*the for loop goes through each flight struct in the flights 
            array and checks if any match with what user wants to filter by*/
            if (strcmp(city_code, flights[i].arrival_city) == 0)
            {
                matched_codes++; /*increments if match found*/
                if (matched_codes == 1) 
                {
                    /*print the following only once which is when 
                    any one match is found*/
                    printf("Flight Origin          Destination\n");
                    printf("------ --------------- ---------------\n");
                }
                /*sends the flight to a helper function which prints it.*/
                format_flight_details(flights[i]);
            }
        }

        /*if no flight code in array matched then that flight doesnt exist 
        in array*/
        if (matched_codes == 0)
        {
            printf("No flights\n");
        }
    }
    print_menu();
    select_menu_option(flights, flights_array_len);
}

/*******************************************************************************
 * This function is called inside the show_flights function and it handles 
 * every flight should be printed out to the user. 
 * inputs: input is passed as a const as its values shouldnt be changed.
 * - flight struture: a whole flight struct is passed through so that all its 
 * members can be accessed when printing flight details.
 * outputs:
 * - none
*******************************************************************************/
void format_flight_details(const flight_t flight)
{
    /*as flight code can vary in length, format still needs to be consistent
    thus spaces vary accordign to flight code length*/
    int code_trail_spaces = MAX_FLIGHTCODE_LEN - strlen(flight.flightcode);
    printf("%s ", flight.flightcode);

    int i;
    for (i = 0; i < code_trail_spaces; i++)
    {
        printf(" ");
    } /*paaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaarints the trailing spaces required for that flight's flightcode.*/

    printf("%s %02d-%02d %02d:%02d ", 
    DEPARTURE_CITY, 
    flight.departure_dt.month, 
    flight.departure_dt.day, 
    flight.departure_dt.hour, 
    flight.departure_dt.minute); /*prints arrival info*/

    /*calculates trailing spaces required after the city code for consistent
    format*/
    int city_trail_spaces = MAX_CITYCODE_LEN - strlen(flight.arrival_city);
    printf("%s ", flight.arrival_city);

    int j;
    for (j = 0; j < city_trail_spaces; j++)
    {
        printf(" ");
    }/*prints trailing spaces for that flight's arrival city code*/

    printf("%02d-%02d %02d:%02d\n", 
    flight.arrival_dt.month, 
    flight.arrival_dt.day, 
    flight.arrival_dt.hour, 
    flight.arrival_dt.minute); /*prints arrival info*/
}

/*******************************************************************************
 * This function is called when the contents of the flight array (flights) need 
 * to be saved in the memory as a file. 
 * inputs:
  * - flights array: passess through the flights array which which stores all
  * the flights added so far.
 * - flights_array_len: passes through the size of the array.
 * outputs:
 * - none
*******************************************************************************/
void save_flight(flight_t flights[], int flights_array_len)
{
    /*creates a file pointer which will hold address of file when found/created 
    successfully*/
    FILE *file_p = NULL;
    file_p = fopen(DB_NAME, "wb"); /*opens binary file with name given*/
    if (file_p != NULL)
    {
        /*if it successfully creates/finds that file it then writes each flight
        struct to the file individually on a new line.*/
        int i;
        for (i = 0; i < flights_array_len; i++)
        {
            fwrite(&flights[i], sizeof(flight_t), 1, file_p);
        }
    }
    else
    {
        /*if file is unable to be created/found then address is still null thus
        no file thus error*/
        printf("Read error\n");
    }
    fclose(file_p); /*after atempt to write data is done file can be closed*/

    print_menu();
    select_menu_option(flights, flights_array_len);
    /*flights array sent for optional further operation*/
}

/*******************************************************************************
 * This function is called when a file needs to be loaded from memory which
 * can populate the flights array which then is sent to the select_menu_option 
 * from where further operations can take place. 
 * inputs: 
 * - none
 * outputs:
 * - none
*******************************************************************************/
void load_flights()
{
    /*aim is to read flights from a file thus intialises an array with the max
    amount of flights it will take*/
    flight_t flights[MAX_NUM_FLIGHTS];
    int flights_len = 0; /*initally no flights are read*/

    FILE *file_p = NULL; /*pointer will be used to read data in file*/
    int items_read = 0; /*initally no items are read*/

    file_p = fopen(DB_NAME, "rb");
    if (file_p != NULL)
    {
        /*if binary file is sucessfully opened it goes through data items and 
        reads each individally and stores it in the flights array created before
        using the length to indicate which index is free.*/
        int i;
        for (i = 0; i < MAX_NUM_FLIGHTS - 1; i++)
        {
            items_read = fread(&flights[i], sizeof(flight_t), 1, file_p);
            if (items_read == 1)
            {
                flights_len++;/*increments occupied length as a flight is read*/
            }
        }
        fclose(file_p); 
        /*after array has accepted its max amount, file is closed*/
    }
    else
    {
        printf("Read error\n");
        /*if file cannot be opened and read then there is an error*/
    }

    print_menu();
    select_menu_option(flights, flights_len);
    /*sends the newly initalised and declared array for further operations.*/
}

/*******************************************************************************
 * This function is called when the user chooses to exit the program. 
 * inputs:
  * - none
 * outputs:
 * - none
*******************************************************************************/
void exit_program()
{
    exit(0);
    /*allows user to exit program*/
}
