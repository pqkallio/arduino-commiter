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
  uint8_t dateparts[5];
  uint8_t selectedDatePart;

  uint8_t getMaxForFebruary()
  {
    uint8_t year = this->dateparts[Timepart::YEAR];

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
  Date(uint8_t year = 0, uint8_t month = 0, uint8_t day = 0, uint8_t time = 0): selectedDatePart(Timepart::NO_PART)
  {
    this->dateparts[0] = 0;
    this->dateparts[1] = day;
    this->dateparts[2] = month;
    this->dateparts[3] = year;
    this->dateparts[4] = time;
  }

  bool isSet()
  {
    return this->dateparts[Timepart::MONTH] && this->dateparts[Timepart::DAY];
  }

  void set(uint8_t year, uint8_t month, uint8_t day, uint8_t time)
  {
    this->dateparts[Timepart::YEAR] = year;
    this->dateparts[Timepart::MONTH] = month;
    this->dateparts[Timepart::DAY] = day;
    this->dateparts[Timepart::TIME] = time;
  }

  void setYear(uint8_t year)
  {
    this->dateparts[Timepart::YEAR] = year;
  }

  void setMonth(uint8_t month)
  {
    this->dateparts[Timepart::MONTH] = month;
  }

  void setDay(uint8_t day)
  {
    this->dateparts[Timepart::DAY] = day;
  }

  void setTime(uint8_t time)
  {
    this->dateparts[Timepart::TIME] = time;
  }

  uint8_t getMaxDay()
  {
    switch (this->dateparts[Timepart::MONTH]) {
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

  uint8_t getYear()
  {
    return this->dateparts[Timepart::YEAR];
  }

  uint8_t getMonth()
  {
    return this->dateparts[Timepart::MONTH];
  }

  uint8_t getDay()
  {
    return this->dateparts[Timepart::DAY];
  }

  uint8_t getTime()
  {
    return this->dateparts[Timepart::TIME];
  }

  uint8_t getSelectedTimepart()
  {
    return this->selectedDatePart;
  }

  uint8_t selectNext()
  {
    this->selectedDatePart++;
    this->selectedDatePart /= 5;
  }
};

#endif /* _COMMITTER_DATE_HPP */
