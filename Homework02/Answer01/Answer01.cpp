// Answer01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <tuple>
using namespace std;

int getDaysSince01_01_1900(const tuple<int, int, int>& date);
void setDateSince01_01_1900(int days, tuple<int, int, int>& date);

/*
Write a class “TRADE_DATE” to store a period of time with the following
member variables:
1.1. int ID;
1.2. tuple <int, int, int> begin_date
1.3. tuple <int, int, int> end_date
1.4. int druation; //the number of days in this period
*/

class TRADE_DATE
{
private:
    int ID;
    //
    // date [begin_date, end_date)
    //
    tuple<int, int, int> begin_date; // year, month, date
    tuple<int, int, int> end_date;
    int duration; //the number of days in this period

    static int SN;

public:
    TRADE_DATE(const tuple<int, int, int>& b_date, int days)
        : ID(SN++)
        , begin_date(b_date)
        , duration(days)
    {
        calculateEndDate();
    }

    TRADE_DATE(const tuple<int, int, int>& b_date, const tuple<int, int, int>&e_date)
        : ID(SN++)
        , begin_date(b_date)
        , end_date(e_date)
    {
        calculateDuration();
    }

    inline
    const tuple<int, int, int>& getBeginDate() const
    {
        return begin_date;
    }

    inline
    const tuple<int, int, int>& getEndDate() const
    {
        return end_date;
    }

    inline
    int getDuration() const
    {
        return duration;
    }

    void print()
    {
        cout << "ID: " << ID << endl;
        cout << "begin_date: " << get<0>(begin_date) << "/" << get<1>(begin_date) << "/" << get<2>(begin_date) << endl;
        cout << "end_date: " << get<0>(end_date) << "/" << get<1>(end_date) << "/" << get<2>(end_date) << endl;
        cout << "duration: " << duration << endl;
    }

private:
    void calculateEndDate()
    {
        int days = getDaysSince01_01_1900(begin_date);
        days += duration;
        setDateSince01_01_1900(days, end_date);
    }

    void calculateDuration()
    {
        int days1 = getDaysSince01_01_1900(begin_date);
        int days2 = getDaysSince01_01_1900(end_date);
        duration = days2 - days1;
    }
};

int TRADE_DATE::SN = 0;

int getDaysSince01_01_1900(const tuple<int, int, int>& date)
{
    int year, month, mday;
    tie<int, int, int>(year, month, mday) = date;

    int days = 0;
    for (int i = 1900; i < year; i++)
    {
        days += 365 + ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0) ? 1 : 0);
    }

    int totalMonthDays[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        // leap year
        totalMonthDays[1] = 29;
    }

    for (int i = 1; i < month; i++)
    {
        days += totalMonthDays[i - 1];
    }

    days += mday - 1;

    return days;
}

void setDateSince01_01_1900(int days, tuple<int, int, int>& date)
{
    int year = 1900, month = 1, mday = 1;

    while (days >= 365)
    {
        int totalYearDays = 365 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 1 : 0);
        if (days < totalYearDays)
            break;
        days -= totalYearDays;
        year++;
    }

    int totalMonthDays[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        totalMonthDays[1] = 29;
    }

    while (days >= 28)
    {
        int d = totalMonthDays[month - 1];
        if (days < d)
            break;
        days -= d;
        month++;
    }

    mday += days;

    get<0>(date) = year;
    get<1>(date) = month;
    get<2>(date) = mday;
}



int _tmain(int argc, _TCHAR* argv[])
{
    TRADE_DATE tdate1(make_tuple<int, int, int>(1900, 2, 28), 1);
    tdate1.print();

    TRADE_DATE tdate2(make_tuple<int, int, int>(1904, 2, 28), 1);
    tdate2.print();

    TRADE_DATE tdate3(make_tuple<int, int, int>(2000, 2, 28), 1);
    tdate3.print();

    TRADE_DATE tdate4(make_tuple<int, int, int>(1980, 12, 1), make_tuple<int, int, int>(1981, 1, 1));
    tdate4.print();

    TRADE_DATE tdate5(make_tuple<int, int, int>(2000, 12, 31), make_tuple<int, int, int>(2001, 1, 1));
    tdate5.print();

    return 0;
}

