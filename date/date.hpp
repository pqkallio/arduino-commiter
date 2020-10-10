#ifndef _COMMITTER_DATE_HPP
#define _COMMITTER_DATE_HPP

enum Timepart {
  NO_PART,
  DAY,
  MONTH,
  YEAR,
  TIME
};

class Date {
private:
  uint16_t dateparts[5];
  uint8_t selectedDatePart;

  uint16_t getMaxForFebruary()
  {
    uint16_t year = dateparts[Timepart::YEAR];

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
  Date(uint16_t year = 0, uint16_t month = 0, uint16_t day = 0, uint16_t time = 0): selectedDatePart(Timepart::NO_PART)
  {
    dateparts[0] = 0;
    dateparts[1] = day;
    dateparts[2] = month;
    dateparts[3] = year;
    dateparts[4] = time;
  }

  bool isSet()
  {
    return getMonth() && getDay();
  }

  void set(uint16_t year, uint16_t month, uint16_t day, uint16_t time)
  {
    setYear(year);
    setMonth(month);
    setDay(day);
    setTime(time);
  }

  void setYear(uint16_t year)
  {
    dateparts[Timepart::YEAR] = year;
    validateDay();
  }

  void setMonth(uint16_t month)
  {
    if (month > 0 && month < 13) {
      dateparts[Timepart::MONTH] = month;
      validateDay();
    }
  }

  void setDay(uint16_t day)
  {
    if (day > 0 && day <= getMaxDay()) {
      dateparts[Timepart::DAY] = day;
    }
  }

  void setTime(uint16_t time)
  {
    if (time <= 86400) {
      dateparts[Timepart::TIME] = time;
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

  void increment()
  {
    switch (selectedDatePart) {
      case Timepart::DAY:
        incrementDay();
        break;
      case Timepart::MONTH:
        incrementMonth();
        break;
      case Timepart::YEAR:
        incrementYear();
        break;
    }
  }

  void decrement()
  {
    switch (selectedDatePart) {
      case Timepart::DAY:
        decrementDay();
        break;
      case Timepart::MONTH:
        decrementMonth();
        break;
      case Timepart::YEAR:
        decrementYear();
        break;
    }
  }

  uint16_t getMaxDay()
  {
    switch (getMonth()) {
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
        return getMaxForFebruary();
      default:
        return 0;
    }
  }

  uint16_t getYear()
  {
    return dateparts[Timepart::YEAR];
  }

  uint16_t getMonth()
  {
    return dateparts[Timepart::MONTH];
  }

  uint16_t getDay()
  {
    return dateparts[Timepart::DAY];
  }

  uint16_t getTime()
  {
    return dateparts[Timepart::TIME];
  }

  uint8_t getSelectedTimepart()
  {
    return selectedDatePart;
  }

  void selectPrevious()
  {
    selectedDatePart--;

    if (selectedDatePart < 1) {
      selectedDatePart = 4;
    }
  }

  void selectNext()
  {
    selectedDatePart++;

    if (selectedDatePart >= 5) {
      selectedDatePart = 1;
    }
  }

  void unselect()
  {
    selectedDatePart = Timepart::NO_PART;
  }
};

#endif /* _COMMITTER_DATE_HPP */
