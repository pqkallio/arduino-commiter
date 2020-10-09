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
    uint16_t year = this->dateparts[Timepart::YEAR];

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

  void set(uint16_t year, uint16_t month, uint16_t day, uint16_t time)
  {
    this->dateparts[Timepart::YEAR] = year;
    this->dateparts[Timepart::MONTH] = month;
    this->dateparts[Timepart::DAY] = day;
    this->dateparts[Timepart::TIME] = time;
  }

  void setYear(uint16_t year)
  {
    this->dateparts[Timepart::YEAR] = year;
  }

  void setMonth(uint16_t month)
  {
    this->dateparts[Timepart::MONTH] = month;
  }

  void setDay(uint16_t day)
  {
    this->dateparts[Timepart::DAY] = day;
  }

  void setTime(uint16_t time)
  {
    this->dateparts[Timepart::TIME] = time;
  }

  uint16_t getMaxDay()
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

  uint16_t getYear()
  {
    return this->dateparts[Timepart::YEAR];
  }

  uint16_t getMonth()
  {
    return this->dateparts[Timepart::MONTH];
  }

  uint16_t getDay()
  {
    return this->dateparts[Timepart::DAY];
  }

  uint16_t getTime()
  {
    return this->dateparts[Timepart::TIME];
  }

  uint8_t getSelectedTimepart()
  {
    return this->selectedDatePart;
  }

  void selectNext()
  {
    switch (this->selectedDatePart) {
      case Timepart::NO_PART:
      case Timepart::YEAR:
        this->selectedDatePart = Timepart::DAY;
        break;
      case Timepart::DAY:
        this->selectedDatePart = Timepart::MONTH;
        break;
      case Timepart::MONTH:
        this->selectedDatePart = Timepart::YEAR;
        break;
    }
  }
};

#endif /* _COMMITTER_DATE_HPP */
