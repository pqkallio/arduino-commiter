#ifndef _COMMITTER_TIMEPART_HPP
#define _COMMITTER_TIMEPART_HPP

enum class Timepart {
  NO_PART,
  DAY,
  MONTH,
  YEAR,
  TIME,
  HOUR,
  MINUTE,
  SECOND,
};

Timepart& operator++(Timepart& t)
{
  switch (t) {
    case Timepart::NO_PART:
      return t = Timepart::NO_PART;
    case Timepart::TIME:
      return t = Timepart::TIME;
    case Timepart::DAY:
      return t = Timepart::MONTH;
    case Timepart::MONTH:
      return t = Timepart::YEAR;
    case Timepart::YEAR:
      return t = Timepart::HOUR;
    case Timepart::HOUR:
      return t = Timepart::MINUTE;
    case Timepart::MINUTE:
      return t = Timepart::SECOND;
    case Timepart::SECOND:
      return t = Timepart::DAY;
  }
}

Timepart& operator--(Timepart& t)
{
  switch (t) {
    case Timepart::NO_PART:
      return t = Timepart::NO_PART;
    case Timepart::TIME:
      return t = Timepart::TIME;
    case Timepart::DAY:
      return t = Timepart::SECOND;
    case Timepart::MONTH:
      return t = Timepart::DAY;
    case Timepart::YEAR:
      return t = Timepart::MONTH;
    case Timepart::HOUR:
      return t = Timepart::YEAR;
    case Timepart::MINUTE:
      return t = Timepart::HOUR;
    case Timepart::SECOND:
      return t = Timepart::MINUTE;
  }
}

#endif /* _COMMITTER_TIMEPART_HPP */
