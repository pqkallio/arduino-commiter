#ifndef _COMMITTER_DATE_HPP
#define _COMMITTER_DATE_HPP

enum DatePartSelection {
  UNSELECTED,
  YEAR,
  MONTH,
  DAY,
  HOUR,
  MINUTES,
  SECONDS
};

class Date {
private:
  uint8_t day;
  uint8_t month;
  uint16_t year;
  uint16_t time;
  DatePartSelection selection;

  uint8_t getMaxForFebruary()
  {
    if (this->year % 400 == 0) {
      return 29;
    } else if (this->year % 100 == 0) {
      return 28;
    } else if (this->year % 4 == 0) {
      return 29;
    }

    return 28;
  }

public:
  Date(uint8_t year = 0, uint8_t month = 0, uint8_t day = 0, uint8_t time = 0):
    year(year),
    month(month),
    day(day),
    time(time),
    selection(DatePartSelection::UNSELECTED)
  {}

  bool isSet()
  {
    return this->month && this->day;
  }

  void set(uint8_t year, uint8_t month, uint8_t day, uint8_t time)
  {
    this->year = year;
    this->month = month;
    this->day = day;
    this->time = time;
  }

  void setYear(uint8_t year)
  {
    this->year = year;
  }

  void setMonth(uint8_t month)
  {
    this->month = month;
  }

  void setDay(uint8_t day)
  {
    this->day = day;
  }

  void setTime(uint8_t time)
  {
    this->time = time;
  }

  uint8_t getMaxDay()
  {
    switch (this->month) {
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
        return this->getMaxForFebruary();
      default:
        return 0;
    }
  }
};

#endif /* _COMMITTER_DATE_HPP */
