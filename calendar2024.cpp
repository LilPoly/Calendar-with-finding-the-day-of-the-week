#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

string monthList[] = { "January",   "February",   "March", "April",
                      "May",  "June", "July",   "August",
                      "September", "October", "November", "December" };

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void printCalendar(int year) {
    cout << "-----------------------------------" << endl;
    cout << "          Calendar - " << year << endl;
    cout << "-----------------------------------" << endl;
    int* monthDays = (int*)malloc(12 * sizeof(int));
    if (!monthDays) {
        cerr << "Error" << endl;
        exit(1);
    }

    int tempDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int i = 0; i < 12; i++) {
        monthDays[i] = tempDays[i];
    }

    int startingGap;
    int tempY = year - 1;
    startingGap = (tempY + tempY / 4 - tempY / 100 + tempY / 400) % 7;

    for (int i = 0; i < 12; i++) {
        if (isLeapYear(year)) {
            monthDays[1] = 29;
        }
        else {
            monthDays[1] = 28;
        }

        cout << endl;
        cout << "  ------------" << monthList[i] << "-------------" << endl;
        cout << "  Mon  Tue  Wed  Thu  Fri  Sat  Sun" << endl;

        int k = startingGap;
        for (int j = 0; j < k; j++) {
            cout << setw(5) << " ";
        }

        for (int j = 1; j <= monthDays[i]; j++) {
            cout << setw(5) << j;

            if (k % 7 == 6) {
                cout << endl;
            }

            k++;
        }

        if (k % 7 != 0) {
            cout << endl;
        }

        startingGap = (startingGap + monthDays[i]) % 7;
    }

    free(monthDays);
}

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int getMaxDay(int month, int year) {
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return (isLeapYear(year) ? 29 : 28);
    default:
        return -1;
    }
}

int calculateDayOfWeek(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int century = (year / 100);
    year %= 100;
    int dayOfWeek = (day + ((13 * (month + 1)) / 5) + year + (year / 4) +
        ((century / 4)) - 2 * century) %
        7;
    if (dayOfWeek == 0) {
        dayOfWeek += 7;
    }
    return dayOfWeek;
}

int main() {
    while (true) {
        cout << "------------------------------------------------" << endl;
        cout << "Select an option:" << endl;
        cout << "1. Display the calendar" << endl;
        cout << "2. Find the day of the week" << endl;
        cout << "3. Go out" << endl;
        cout << "4. Download year from file" << endl;
        cout << "------------------------------------------------" << endl;

        string choice;
        cin >> choice;

        if (choice == "1") {
            bool validYear = false;
            while (!validYear) {
                int year;
                cout << "Enter the year: ";
                cin >> year;
                if (year >= 1900 && year <= 2099) {
                    printCalendar(year);
                    validYear = true;
                }
                else {
                    cout << "Unacceptable year. Please enter a year in the range from "
                        "1900 to 2099."
                        << endl;
                }
            }
        }
        else if (choice == "2") {
            int year, month, day;
            while (true) {
                string input;
                cout << "Ââåä³òü ð³ê: ";
                cin >> input;
                if (isNumber(input)) {
                    year = stoi(input);
                    if (year >= 1900 && year <= 2099) {
                        break;
                    }
                }
                cout << "Unacceptable year. Please enter a year in the range from "
                        "1900 to 2099."
                    << endl;
            }
            while (true) {
                string input;
                cout << "Enter the month: ";
                cin >> input;
                if (isNumber(input)) {
                    month = stoi(input);
                    if (month >= 1 && month <= 12) {
                        break;
                    }
                }
                cout << "Incorrect input. Please try again." << endl;
            }
            while (true) {
                string input;
                cout << "Enter the day: ";
                cin >> input;
                if (isNumber(input)) {
                    day = stoi(input);
                    if (day >= 1 && day <= getMaxDay(month, year)) {
                        break;
                    }
                }
                cout << "Incorrect input. Please try again." << endl;
            }

            int dayOfWeek = calculateDayOfWeek(year, month, day);
            string dayOfWeekString;
            switch (dayOfWeek) {
            case 1:
                dayOfWeekString = "Sunday";
                break;
            case 2:
                dayOfWeekString = "Monday";
                break;
            case 3:
                dayOfWeekString = "Tuesday";
                break;
            case 4:
                dayOfWeekString = "Wednesday";
                break;
            case 5:
                dayOfWeekString = "Thursday";
                break;
            case 6:
                dayOfWeekString = "Friday";
                break;
            case 7:
                dayOfWeekString = "Saturday";
                break;
            }

            cout << "Day of the week: " << dayOfWeekString << endl;
        }
        else if (choice == "3") {
            break;
        }
        else if (choice == "4") {
            ifstream yearFile("year.txt");
            if (yearFile.is_open()) {
                int year;
                yearFile >> year;
                if (year >= 1900 && year <= 2099) {
                    printCalendar(year);
                }
                else {
                    cout << "Unacceptable year.Please enter a year in the range from "
                        "1900 to 2099."
                        << endl;
                }
                yearFile.close();
            }
            else {
                cout << "The file year.txt could not be opened." << endl;
            }
        }
        else {
            cout << "Incorrect input. Please try again." << endl;
        }
    }
    return 0;
}



