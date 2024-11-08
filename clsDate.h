#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include "clsString.h"

class clsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

protected:

	/*clsDate FullDating()
	{
		clsDate Date;

		Date.Day = clsInputValidate::ReadShortNumberBetween("Please enter a day?  ", 1, 31);
		Date.Month = clsInputValidate::ReadShortNumberBetween("Please enter a month?  ", 1, 12);
		Date.Year = clsInputValidate::ReadShortNumberBetween("Please enter a year?  ", 1, 3000);
		cout << "\n---------------------------------\n\n";

		return Date;
	}*/

	void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;

		Date1 = TempDate;

		Date2 = TempDate;
	}

	clsDate StringToDate(string stLine, string Sptr = "#//#")
	{
		vector <string> vLine = clsString::Sblit(stLine, Sptr);
		clsDate Date;

		Date.Day = stoi(vLine.at(0));
		Date.Month = stoi(vLine.at(1));
		Date.Year = stoi(vLine.at(2));

		return Date;
	}

	static int GetDiffrenceDays(clsDate Date1, clsDate Date2, short NumOfDaysInDate1, short NumOfDaysInDate2)
	{
		short DiffrenceDays = 0;

		if (Date1._Year < Date2._Year)
		{
			if (Date1._Month > Date2._Month)
			{
				for (Date1._Year; Date1._Year < Date2._Year; Date1._Year++)
					DiffrenceDays += (getTotalDaysInYear(Date1._Year));

				return  DiffrenceDays - NumOfDaysInDate1 + NumOfDaysInDate2;

			}
			else
			{
				for (Date1._Year; Date1._Year < Date2._Year; Date1._Year++)
					DiffrenceDays += getTotalDaysInYear(Date1._Year);
			}
		}
		return NumOfDaysInDate1 >= NumOfDaysInDate2 ? DiffrenceDays + (NumOfDaysInDate1 - NumOfDaysInDate2) : DiffrenceDays + (NumOfDaysInDate2 - NumOfDaysInDate1);
	}

	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t TimeNow = time(0);  //Get time now
		tm* now = localtime(&TimeNow);  //Convert in string form

		Date._Year = now->tm_year + 1900;
		Date._Month = now->tm_mon + 1;
		Date._Day = now->tm_mday;

		return Date;
	}


public:

	void SetDay(short Day) {
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth() {
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year) {
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	clsDate()
	{
		time_t TimeNow = time(0);  //Get time now
		tm* now = localtime(&TimeNow);  //Convert in string form

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	clsDate(string sDate)
	{
		*this = StringToDate(sDate, "/");
	}
	clsDate(short year, short NumOfDaysFromBegainYear)
	{
		*this = GetDateFromDayOrderInYear(year, NumOfDaysFromBegainYear);
	}
	clsDate(short day, short month, short year)
	{
		Day = day;
		Month = month;
		Year = year;
	}

	void Print()
	{
		cout << "Date : " << DateToString() << endl;
	}

	string GetCurrentDate()
	{
		time_t t = time(0);   // get time now
		tm* now = localtime(&t);

		clsDate();

		return to_string(_Day) + "/" + to_string(_Month) + "/" + to_string(_Year);
	}

	string GetCurrentTime()
	{
		time_t t = time(0);   // get time now
		tm* now = localtime(&t);

		clsDate();

		return to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
	}

	static bool IsValideDate(clsDate Date)
	{
		return (Date._Month < 13) ? ((Date._Day <= NumOfDaysInMonth(Date._Year, Date._Month)) ? true : false) : false;
	}
	bool IsValideDate()
	{
		return IsValideDate(*this);
	}


	static clsDate DateAddDays(clsDate& Date, short AdditionalDays)
	{
		short MonthDays = 0;
		short RemainingDays = AdditionalDays + NumOfDaysFromTheBegainingOfTheYear(Date._Year, Date._Month, Date._Day);

		Date._Month = 1;
		// We must update it after using func. "NumOfDaysFromTheBegainingOfTheYear()"
		 //If we use it before using func. "NumOfDaysFromTheBegainingOfTheYear()", We get incorrect result

		while (true)
		{
			MonthDays = NumOfDaysInMonth(Date._Year, Date._Month);


			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}
	void AddDaysToDate(short AdditionalDays)
	{
		*this = DateAddDays(*this, AdditionalDays);
	}


	static string DateToString(clsDate Date, string Sptr = "-")
	{
		return to_string(Date._Day) + Sptr + to_string(Date._Month) + Sptr + to_string(Date._Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}


	static string FormateDate(clsDate Date, string DateFormat)
	{
		DateFormat = clsString::ReplaceWordInStringUsingBuiltInFunction(DateFormat, "mm", to_string(Date._Month));
		DateFormat = clsString::ReplaceWordInStringUsingBuiltInFunction(DateFormat, "dd", to_string(Date._Day));
		DateFormat = clsString::ReplaceWordInStringUsingBuiltInFunction(DateFormat, "yyy", to_string(Date._Year));

		return DateFormat;
	}
	string FormateDate(string DateFormat)
	{
		return FormateDate(*this, DateFormat);
	}


	static bool IsLeapYear(short Year)
	{
		return !(Year % 4 != 0) || (Year % 100 == 0 && Year % 400 != 0);
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}


	static short getTotalDaysInYear(short year)
	{
		return  IsLeapYear(year) ? 366 : 365;
	}
	short getTotalDaysInYear()
	{
		return getTotalDaysInYear(_Year);
	}


	static int TotalHoursInYear(short year)
	{
		return getTotalDaysInYear(year) * 24;
	}
	short TotalHoursInYear()
	{
		return TotalHoursInYear(_Year);
	}


	static int TotalMinutesInYear(short year)
	{
		return (TotalHoursInYear(year) * 60);
	}
	short TotalMinutesInYear()
	{
		return TotalMinutesInYear(_Year);
	}


	static long TotalSecondsInYear(short year)
	{
		return (TotalMinutesInYear(year) * 60);
	}
	short TotalSecondsInYear()
	{
		return TotalSecondsInYear(_Year);
	}


	static short TotalDaysInFrebuary(short year)
	{
		return  IsLeapYear(year) ? 29 : 28;
	}
	short TotalDaysInFrebuary()
	{
		return TotalDaysInFrebuary(_Year);
	}


	static short NumOfDaysInMonth(short year, short Month)
	{
		short arr31Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return ((Month == 2) ? TotalDaysInFrebuary(year) : arr31Days[Month - 1]);
	}
	short NumOfDaysInMonth()
	{
		return NumOfDaysInMonth(_Year, _Month);
	}


	static short DayOfWeekOrder(short year, short month, short day)
	{
		int a, y, m;

		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;
		return ((day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Year, _Month, _Day);
	}


	static string DayShortName(short dayOrder)
	{
		string arrDayName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arrDayName[dayOrder];
	}
	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder(_Year, _Month, _Day));
	}


	static string MonthShortName(short month)
	{
		string arrMonthName[] = { "", "Jun", "Feb", "Mrs", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arrMonthName[month];
	}
	string MonthShortName()
	{
		return MonthShortName(_Month);
	}


	static void PrintMonthCalender(short Year, short Month)
	{

		short NumberOfDaysInMonth = NumOfDaysInMonth(Year, Month);
		short Counter;
		short FirsdDayOrderInMonth = DayOfWeekOrder(Year, Month, 1); // "1" mean the first day order in month

		printf("\n  ________________%s________________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		for (Counter = 0; Counter < FirsdDayOrderInMonth; Counter++)
		{
			printf("     ");
		}

		for (short i = 1; i <= NumberOfDaysInMonth; i++)
		{
			printf("%5d", i);

			if (++Counter == 7)
			{
				Counter = 0;
				printf("\n");
			}
		}
	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(Year, Month);
	}


	static void PrindYearCalender(short year)
	{
		printf("\n  ___________________________________\n\n");
		printf("           Calender - %d\n", year);
		printf("  ___________________________________\n\n");

		for (short MonthCount = 1; MonthCount <= 12; MonthCount++)
			PrintMonthCalender(year, MonthCount);
	}
	void PrindYearCalender()
	{
		PrindYearCalender(Year);
	}


	static short NumOfDaysFromTheBegainingOfTheYear(short year, short month, short days)
	{
		short NumOfDays = 0;

		for (short i = 1; i < month; i++)
		{
			NumOfDays += NumOfDaysInMonth(year, i);
		}
		return NumOfDays + days;
	}
	short NumOfDaysFromTheBegainingOfTheYear()
	{
		return NumOfDaysFromTheBegainingOfTheYear(Year, Month, Day);
	}


	static clsDate GetDateFromDayOrderInYear(short Year, short DayOrderInYear)
	{
		clsDate Date;
		Date._Year = Year;
		Date._Month = 1;
		short RemainDays = DayOrderInYear;
		short MonthDays = 0;

		while (true)
		{
			MonthDays = NumOfDaysInMonth(Year, Date._Month);

			if (RemainDays > MonthDays)
			{
				RemainDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainDays;
				break;
			}
		}
		return Date;
	}
	void GetDateFromDayOrderInYear()
	{
		*this = GetDateFromDayOrderInYear(Year, NumOfDaysFromTheBegainingOfTheYear(Year, Month, Day));
	}


	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		if (Date1._Year != Date2._Year)
			return (Date1._Year < Date2._Year) ? true : false;
		else if (Date1._Month != Date2._Month)
			return (Date1._Month < Date2._Month) ? true : false;
		else if (Date1._Day != Date2._Day)
			return (Date1._Day < Date2._Day) ? true : false;
	}
	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EquelDate2(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsDate1EquelDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? (((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false)) : false;
	}
	bool IsDate1EquelDate2(clsDate Date2)
	{
		return IsDate1EquelDate2(*this, Date2);
	}

	static bool IfDayIsLastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumOfDaysInMonth(Date._Year, Date._Month));
	}
	bool IfDayIsLastDayInMonth()
	{
		return IfDayIsLastDayInMonth(*this);
	}

	static bool IfMonthIsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IfMonthIsLastMonthInYear()
	{
		return IfMonthIsLastMonthInYear(Month);
	}


	static clsDate IncreaseDateByOneDay(clsDate& Date)
	{
		if (IfDayIsLastDayInMonth(Date))
			(IfMonthIsLastMonthInYear(Date._Month) ? (Date._Year++, Date._Month = 1, Date._Day = 1) : (Date._Month++, Date._Day = 1));
		else
			Date._Day++;

		return Date;
	}
	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDay(clsDate& Date, short ManyDays)
	{
		for (int i = 1; i <= ManyDays; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDay(short ManyDays)
	{
		*this = IncreaseDateByXDay(*this, ManyDays);
	}


	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		Date = IncreaseDateByXDay(Date, 7);
		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}


	static clsDate IncreaseDateByXWeek(clsDate& Date, short ManyWeeks)
	{
		for (int i = 1; i <= ManyWeeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeek(short ManyWeeks)
	{
		*this = IncreaseDateByXWeek(*this, ManyWeeks);
	}


	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IfMonthIsLastMonthInYear(Date._Month))
		{
			Date._Month = 1;
			Date._Year++;
			return Date;

		}
		else if (Date._Month == 1)
		{
			switch (Date._Day)
			{
			case 29:
			{
				Date._Month++;
				IsLeapYear(Date._Year) ? Date._Day = 29 : Date._Day = 1;
				break;
			}
			case 30:
			{
				Date._Month = 3;
				IsLeapYear(Date._Year) ? Date._Day = 1 : Date._Day = 2;
				break;
			}
			case 31:
			{
				Date._Month = 3;
				IsLeapYear(Date._Year) ? Date._Day = 2 : Date._Day = 3;
				break;
			}
			default:
				Date._Month++;
				break;
			}
			return Date;
		}
		else
		{
			short NumberOfDaysInCurrentMonth = NumOfDaysInMonth(Date._Year, Date._Month);

			for (short i = 1; i <= NumberOfDaysInCurrentMonth; i++)
			{
				Date = IncreaseDateByOneDay(Date);
			}
			return Date;
		}

	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}


	static clsDate IncreaseDateByXMonth(clsDate& Date, short ManyMoths)
	{
		for (int i = 1; i <= ManyMoths; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}
	void IncreaseDateByXMonth(short ManyMoths)
	{
		*this = IncreaseDateByXMonth(*this, ManyMoths);
	}


	static clsDate IncreaseDateByOneYear(clsDate& Date, short ManyYears = 1)
	{
		Date = IncreaseDateByXMonth(Date, 12 * ManyYears);
		return Date;
	}
	void IncreaseDateByOneYear(short ManyYears = 1)
	{
		*this = IncreaseDateByOneYear(*this, ManyYears);
	}


	static clsDate IncreaseDateByXYears(clsDate& Date, short ManyYears)
	{
		Date = IncreaseDateByOneYear(Date, ManyYears);

		return Date;
	}
	void IncreaseDateByXYears(short ManyYears)
	{
		*this = IncreaseDateByXYears(*this, ManyYears);
	}


	clsDate IncreaseDateByXYearsFaster(clsDate& Date, short ManyYears)
	{
		for (int i = 1; i <= ManyYears; i++)
		{
			if (IsLeapYear(Date._Year))
				*this = IncreaseDateByOneDay(*this);
			Date._Year++;
		}
		return Date;
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date = IncreaseDateByXYears(Date, 10);
		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}


	static clsDate IncreaseDateByXDecades(clsDate& Date, short ManyDecades)
	{
		for (int i = 1; i <= ManyDecades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}
	void IncreaseDateByXDecades(short ManyDecades)
	{
		*this = IncreaseDateByXDecades(*this, ManyDecades);
	}


	clsDate IncreaseDateByXDecadesFaster(clsDate& Date, short ManyDecades)
	{
		Date = IncreaseDateByXYearsFaster(Date, ManyDecades * 10);

		return Date;
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date, short ManyCentury = 1)
	{
		Date = IncreaseDateByXDecades(Date, 10 * ManyCentury);

		return Date;
	}
	void IncreaseDateByOneCentury(short ManyCentury = 1)
	{
		*this = IncreaseDateByOneCentury(*this, ManyCentury);
	}


	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date = IncreaseDateByOneCentury(Date, 10);

		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}


	static clsDate decreaseDateByOneDay(clsDate& Date)
	{
		if (Date._Day == 1)
			(Date._Month == 1) ? (Date._Year--, Date._Month = 12, Date._Day = 31) : ((--Date._Month), Date._Day = NumOfDaysInMonth(Date._Year, Date._Month));
		else
			Date._Day--;

		return Date;
	}
	void decreaseDateByOneDay()
	{
		decreaseDateByOneDay(*this);
	}


	static clsDate decreaseDateByXDay(clsDate& Date, short ManyDays)
	{
		for (int i = 1; i <= ManyDays; i++)
		{
			Date = decreaseDateByOneDay(Date);
		}
		return Date;
	}
	void decreaseDateByXDay(short ManyDays)
	{
		decreaseDateByXDay(*this, ManyDays);
	}


	static clsDate decreaseDateByOneWeek(clsDate& Date)
	{
		Date = decreaseDateByXDay(Date, 7);
		return Date;
	}
	void decreaseDateByOneWeek()
	{
		decreaseDateByOneWeek(*this);
	}


	static clsDate decreaseDateByXWeek(clsDate& Date, short ManyWeeks)
	{
		for (int i = 1; i <= ManyWeeks; i++)
		{
			Date = decreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void decreaseDateByXWeek(short ManyWeeks)
	{
		decreaseDateByXWeek(*this, ManyWeeks);
	}


	static clsDate decreaseDateByOneMonth(clsDate& Date)
	{
		switch (Date._Month)
		{
		case 3:
		{
			(Date._Day == 31 || Date._Day == 30 || Date._Day == 29) ? (IsLeapYear(Date._Year) ? Date._Day = 29 : Date._Day = 28), Date._Month = 2 : Date._Month = 2;
			break;
		}
		case 1:
		{
			Date._Month = 12;
			--Date._Year;
			break;
		}
		default:
			Date._Month--;

			if (Date._Day == NumOfDaysInMonth(Date._Year, Date._Month))
				Date._Day = NumOfDaysInMonth(Date._Year, Date._Month);
			break;
		}
		return Date;
	}
	void decreaseDateByOneMonth()
	{
		decreaseDateByOneMonth(*this);
	}


	static clsDate decreaseDateByXMonth(clsDate& Date, short ManyMoths)
	{
		for (int i = 1; i <= ManyMoths; i++)
		{
			Date = decreaseDateByOneMonth(Date);
		}

		return Date;
	}
	void decreaseDateByXMonth(short ManyMoths)
	{
		decreaseDateByXMonth(*this, ManyMoths);
	}


	static clsDate decreaseDateByOneYear(clsDate& Date)
	{
		(IsLeapYear(Date._Year)) ? Date = decreaseDateByOneDay(Date) : Date;
		Date._Year--;
		return Date;
	}
	void decreaseDateByOneYear()
	{
		decreaseDateByOneYear(*this);
	}


	static clsDate decreaseDateByXYears(clsDate& Date, short ManyYears)
	{
		for (short i = 1; i <= ManyYears; i++)
			Date = decreaseDateByOneYear(Date);

		return Date;
	}
	void decreaseDateByXYears(short ManyYears)
	{
		decreaseDateByXYears(*this, ManyYears);
	}


	static clsDate decreaseDateByXYearsFaster(clsDate& Date, short ManyYears)
	{
		Date._Year -= ManyYears;
		return Date;
	}
	void decreaseDateByXYearsFaster(short ManyYears)
	{
		*this = decreaseDateByXYearsFaster(*this, ManyYears);
	}


	static clsDate decreaseDateByOneDecade(clsDate& Date)
	{
		const short OneDecade = 10;
		Date = decreaseDateByXYears(Date, OneDecade);
		return Date;
	}
	void decreaseDateByOneDecade()
	{
		decreaseDateByOneDecade(*this);
	}


	static  clsDate decreaseDateByXDecades(clsDate& Date, short ManyDecades)
	{
		for (int i = 1; i <= ManyDecades; i++)
		{
			Date = decreaseDateByOneDecade(Date);
		}
		return Date;
	}
	void decreaseDateByXDecades(short ManyDecades)
	{
		decreaseDateByXDecades(*this, ManyDecades);
	}


	static clsDate decreaseDateByXDecadesFaster(clsDate& Date, short ManyDecades)
	{
		const short OneDecade = 10;

		Date._Year -= (ManyDecades * OneDecade);
		return Date;
	}
	void decreaseDateByXDecadesFaster(short ManyDecades)
	{
		decreaseDateByXDecadesFaster(*this, ManyDecades);
	}


	static clsDate decreaseDateByOneCentury(clsDate& Date)
	{
		Date._Year -= 100;

		return Date;
	}
	void decreaseDateByOneCentury()
	{
		decreaseDateByOneCentury(*this);
	}


	static clsDate decreaseDateByOneMillennium(clsDate& Date)
	{
		Date._Year -= 1000;
		return Date;
	}
	void decreaseDateByOneMillennium()
	{
		decreaseDateByOneMillennium(*this);
	}

	static int CalculateDiffrenceDays(clsDate Date1, clsDate Date2, bool IncludingEndDay = false)
	{
		short NumOfDaysInDate1 = NumOfDaysFromTheBegainingOfTheYear(Date1._Year, Date1._Month, Date1._Day);
		short NumOfDaysInDate2 = NumOfDaysFromTheBegainingOfTheYear(Date2._Year, Date2._Month, Date2._Day);
		short DiffrenceDays = 0;


		if (Date1._Year == Date2._Year)
		{
			DiffrenceDays = NumOfDaysInDate1 >= NumOfDaysInDate2 ? (NumOfDaysInDate1 - NumOfDaysInDate2) : (NumOfDaysInDate2 - NumOfDaysInDate1);
		}
		else
		{
			DiffrenceDays = (Date1._Year < Date2._Year) ? GetDiffrenceDays(Date1, Date2, NumOfDaysInDate1, NumOfDaysInDate2)
				: GetDiffrenceDays(Date2, Date1, NumOfDaysInDate2, NumOfDaysInDate1);
		}
		return IncludingEndDay ? ++DiffrenceDays : DiffrenceDays;
	}

	int CalculateDiffrenceDays(clsDate& Date2, bool IncludingEndDay = false)
	{
		return CalculateDiffrenceDays(*this, Date2, IncludingEndDay);
	}

	int CalculateMyAgeInDays(bool IncludingEndDay = false)
	{
		return CalculateDiffrenceDays(GetSystemDate(), *this, IncludingEndDay);
	}


	static bool IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date._Year, Date._Month, Date._Day) == 6);
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}


	static bool IsWeekend(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date._Year, Date._Month, Date._Day);

		return (DayIndex == 6 || DayIndex == 5);
	}
	bool IsWeekend()
	{
		return IsWeekend(*this);
	}


	static bool IsBusinessDay(clsDate Date)
	{
		return (!IsWeekend(Date));
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}


	static short DaysUntillEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
	}
	short DaysUntillEndOfWeek()
	{
		return DaysUntillEndOfWeek(*this);
	}


	static short DaysUntillEndOfMonth(clsDate Date)
	{
		return (NumOfDaysInMonth(Date._Year, Date._Month) - Date._Day); // Firts Method
	}
	short DaysUntillEndOfMonth()
	{
		return DaysUntillEndOfMonth(*this);
	}


	static short DaysUntillEndOfYear(clsDate Date)
	{
		return (getTotalDaysInYear(Date._Year) - NumOfDaysFromTheBegainingOfTheYear(Date._Year, Date._Month, Date._Day));
	}
	short DaysUntillEndOfYear()
	{
		return DaysUntillEndOfYear(*this);
	}


	static short ActulalVacation(clsDate DateFrom, clsDate DateTo)
	{
		int Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return Days;
	}
	short ActulalVacation(clsDate DateTo)
	{
		return ActulalVacation(*this, DateTo);
	}


	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		//in case the data  is weekend keep adding one day util you reach business day
		//we get rid of all weekends before the first business day
		while (IsWeekend(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		//here we increase the vacation dates to add all weekends to it.

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekend(DateFrom))
				WeekEndCounter++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		//in case the return date is week end keep adding one day util you reach business day
		while (IsWeekend(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}
	void CalculateVacationReturnDate(short VacationDays)
	{
		*this = CalculateVacationReturnDate(*this, VacationDays);
		cout << "\n\nReturn Date: " << DayShortName(DayOfWeekOrder(_Year, _Month, _Day)) << " , "
			<< Day << "/" << Month << "/" << Year << endl;
	}
};

