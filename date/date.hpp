#ifndef _COMMITTER_DATE_HPP
#define _COMMITTER_DATE_HPP

typedef struct _date_t {
  uint8_t day;
  uint8_t month;
  uint16_t year;
  uint16_t time;
} Date;

bool date_set(Date* date)
{
  return date->day && date->month && date->year;
}

#endif /* _COMMITTER_DATE_HPP */
