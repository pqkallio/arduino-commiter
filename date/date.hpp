#ifndef _COMMITTER_DATE_HPP
#define _COMMITTER_DATE_HPP

#include "timepart.hpp"

#define JANUARY   1
#define FEBRUARY  2
#define MARCH     3
#define APRIL     4
#define MAY       5
#define JUNE      6
#define JULY      7
#define AUGUST    8
#define SEPTEMBER 9
#define OCTOBER   10
#define NOVEMBER  11
#define DECEMBER  12

class Date {
private:
  uint8_t day;
  uint8_t month;
  uint16_t year;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;

  uint16_t dateparts[5];

  uint16_t getMaxForFebruary()
  {
    if (year % 400 == 0) {
      return 29;
    } else if (year % 100 == 0) {
      return 28;
    } else if (year % 4 == 0) {
      return 29;
    }

    return 28;
  }

public:
  Date(uint16_t year = 0, uint8_t month = 0, uint8_t day = 0, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second)
  {}

  bool isSet()
  {
    return getMonth() && getDay();
  }

  void set(uint16_t year, uint16_t month, uint16_t day, uint16_t time)
  {
    setYear(year);
    setMonth(month);
    setDay(day);
    setHour(time / 3600);
    setMinute(time % 3600 / 60);
    setSecond(time % 60);
  }

  void setYear(uint16_t year)
  {
    this->year = year;
    validateDay();
  }

  void setMonth(uint16_t month)
  {
    if (month > 0 && month < 13) {
      this->month = month;
      validateDay();
    }
  }

  void setDay(uint16_t day)
  {
    if (day > 0 && day <= getMaxDay()) {
      this->day = day;
    }
  }

  void setHour(uint8_t hour)
  {
    if (hour < 25) {
      this->hour = hour;
    }
  }

  void setMinute(uint8_t minute)
  {
    if (minute < 60) {
      this->minute = minute;
    }
  }

  void setSecond(uint8_t second)
  {
    if (second < 60) {
      this->second = second;
    }
  }

  void validateDay()
  {
    uint16_t max = getMaxDay();

    if (getDay() > max) {
      setDay(max);
    }
  }

  void incrementDay()
  {
    uint16_t day = getDay();
    uint16_t maxDay = getMaxDay();

    day++;

    if (day > maxDay) {
      day = 1;
    }

    setDay(day);
  }

  void decrementDay()
  {
    uint16_t day = getDay();
    uint16_t maxDay = getMaxDay();

    day--;

    if (day < 1) {
      day = maxDay;
    }

    setDay(day);
  }

  void incrementMonth()
  {
    uint16_t month = getMonth();

    month++;

    if (month > 12) {
      month = 1;
    }

    setMonth(month);
    validateDay();
  }

  void decrementMonth()
  {
    uint16_t month = getMonth();

    month--;

    if (month < 1) {
      month = 12;
    }

    setMonth(month);
    validateDay();
  }

  void incrementYear()
  {
    uint16_t year = getYear();

    year++;

    if (year > 9999) {
      year = 0;
    }

    setYear(year);
    validateDay();
  }

  void decrementYear()
  {
    uint16_t year = getYear();

    year--;

    if (year == UINT16_MAX) {
      year = 9999;
    }

    setYear(year);
    validateDay();
  }

  uint16_t getMaxDay()
  {
    switch (getMonth()) {
      case JANUARY:
      case MARCH:
      case MAY:
      case JULY:
      case AUGUST:
      case OCTOBER:
      case DECEMBER:
        return 31;
      case APRIL:
      case JUNE:
      case SEPTEMBER:
      case NOVEMBER:
        return 30;
      case FEBRUARY:
        return getMaxForFebruary();
      default:
        return 0;
    }
  }

  uint16_t getYear()
  {
    return year;
  }

  uint16_t getMonth()
  {
    return month;
  }

  uint16_t getDay()
  {
    return day;
  }

  uint8_t getHour()
  {
    return hour;
  }

  uint8_t getMinute()
  {
    return minute;
  }

  uint8_t getSecond()
  {
    return second;
  }

  uint16_t getTime()
  {
    return 3600 * hour + 60 * minute + second;
  }
};

#endif /* _COMMITTER_DATE_HPP */
