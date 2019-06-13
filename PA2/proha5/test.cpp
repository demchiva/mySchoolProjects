#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;

class CTimeStamp
{
public:
    CTimeStamp                              ( int               year,
            int               month,
            int               day,
            int               hour,
            int               minute,
            double            sec )
        : m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_sec(sec) {}

    int            Compare                                 ( const CTimeStamp & x ) const
    {
        if(x.m_year > this->m_year)
        {
            return -1;
        }
        else if(x.m_year < this->m_year)
        {
            return 1;
        }
        else if(x.m_month > this->m_month)
        {
            return -1;
        }
        else if(x.m_month < this->m_month)
        {
            return 1;
        }
        else if(x.m_day > this->m_day)
        {
            return -1;
        }
        else if(x.m_day < this->m_day)
        {
            return 1;
        }
        else if(x.m_hour > this->m_hour)
        {
            return -1;
        }
        else if(x.m_hour < this->m_hour)
        {
            return 1;
        }
        else if(x.m_minute > this->m_minute)
        {
            return -1;
        }
        else if(x.m_minute < this->m_minute)
        {
            return 1;
        }
        else if(x.m_sec > this->m_sec)
        {
            return -1;
        }
        else if(x.m_sec < this->m_sec)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    friend ostream & operator <<                           ( ostream          & os,
            const CTimeStamp & x )
    {
        return os << x.m_year << "-" << x.m_month << "-" << x.m_day << " " << x.m_hour << ":" << x.m_minute << ":" << x.m_sec;
    }
private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    double m_sec;
};
class CMail
{
public:
    CMail ( const CTimeStamp & timeStamp,
            const string     & from,
            const string     & to,
            const string     & subject )
            : m_from(from), m_to(to), m_subject(subject), m_Stamp(timeStamp) {}

    int            CompareByTime                           ( const CTimeStamp & x ) const
    {
        return this->m_Stamp.Compare(x);
    }

    int            CompareByTime                           ( const CMail      & x ) const
    {
        return this->m_Stamp.Compare(x.m_Stamp);
    }

    const string & From                                    ( void ) const
    {
        return m_from;
    }

    const string & To                                      ( void ) const
    {
        return m_to;
    }

    const string & Subject                                 ( void ) const
    {
        return m_subject;
    }

    const CTimeStamp & TimeStamp                           ( void ) const
    {
        return m_Stamp;
    }

    friend ostream & operator <<                           ( ostream & os, const CMail & x )
    {
        return os << x.m_Stamp << " " << x.m_from << " -> " << x.m_to << ", subject:" << x.m_subject << endl;
    }

private:
    CTimeStamp m_Stamp;
    const string m_from;
    const string m_to;
    const string m_subject;
};
// your code will be compiled in a separate namespace
namespace MysteriousNamespace
{
#endif /* __PROGTEST__ */
//----------------------------------------------------------------------------------------

int GetMonth (const string & month)
{
    if(month == "Jan")
    {
        return 1;
    }
    if(month == "Feb")
    {
        return 2;
    }

    if(month == "Mar")
    {
        return 3;
    }

    if(month == "Apr")
    {
        return 4;
    }

    if(month == "May")
    {
        return 5;
    }

    if(month == "Jun")
    {
        return 6;
    }

    if(month == "Jul")
    {
        return 7;
    }

    if(month == "Aug")
    {
        return 8;
    }

    if(month == "Sep")
    {
        return 9;
    }

    if(month == "Okt")
    {
        return 10;
    }

    if(month == "Nov")
    {
        return 11;
    }

    if(month == "Dec")
    {
        return 12;
    }

    return 0;
}

class CMailLog
{
public:
    int            ParseLog                                ( istream          & in )
    {
        vector<string> log;
        string tmp;
        int checkWhiteSpace = 0;
        int checkSymbol = 0;
        int Month = 0;
        int Year = 0;
        int Day = 0;
        int Hour = 0;
        int Minutes = 0;
        double Sec = 0.0;
        int CheckCond = 0;

        string Password = "";
        string Mail = "";

        while(in)
        {
            getline(in, tmp);
            log.push_back(tmp);
        }

        for(auto str : log)
        {
            checkSymbol = 0;
            checkWhiteSpace = 0;
            CheckCond = 0;
            tmp = "";
            Mail = "";
            Password = "";
            for(unsigned int i = 0; i < str.length(); i++)
            {

                if(str[i] == ' ')
                {
                    if(checkWhiteSpace == 0)
                    {
                        Month = GetMonth(tmp);
                        tmp = "";
                    }

                    if(checkWhiteSpace == 1)
                    {
                        Day = atoi(tmp.c_str());
                        tmp = "";
                    }

                    if(checkWhiteSpace == 2)
                    {
                        Year = atoi(tmp.c_str()); /** "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"*/
                        tmp = "";
                    }

                    if(checkWhiteSpace == 3)
                    {
                        Sec = atof(tmp.c_str());
                        tmp = "";
                    }

                    if(checkWhiteSpace == 4)
                    {
                        tmp = "";
                    }

                    checkWhiteSpace ++;
                }

                if(str[i] == ':')
                {
                    if(checkSymbol == 0 && checkWhiteSpace == 3)
                    {
                       Hour = atoi(tmp.c_str());
                       tmp = "";
                    }

                    if(checkSymbol == 1 && checkWhiteSpace == 3)
                    {
                        Minutes = atoi(tmp.c_str());
                        tmp = "";
                    }

                    if(checkWhiteSpace == 5 && checkSymbol == 2)
                    {
                        Password = tmp;
                        checkWhiteSpace ++;
                        tmp = "";
                    }

                    checkSymbol ++;
                }

                if(str[i] == '=')
                {
                    i++;
                    if(tmp == "from")
                    {
                        for(; i < str.length(); i++)
                        {
                            Mail += str[i];
                        }
                        CheckCond = 1;
                        tmp = "";

                    } else

                    if(tmp == "to")
                    {
                        for(; i < str.length(); i++)
                        {
                            Mail += str[i];
                        }
                        CheckCond = 2;
                        tmp = "";

                    } else

                    if(tmp == "subject")
                    {
                        for(; i < str.length(); i++)
                        {
                            Mail += str[i];
                        }
                        CheckCond = 3;
                        tmp = "";

                    } else
                    {
                        break;
                    }
                }

                if(CheckCond == 1)
                {
                    MapOfFrom.insert(make_pair(Password, CMail(CTimeStamp(Year, Month, Day, Hour, Minutes, Sec), Mail, "", "")));
                    break;
                }

                if(CheckCond == 2)
                {
                    VectorOfTo.push_back(make_pair(Password, CMail(CTimeStamp(Year, Month, Day, Hour, Minutes, Sec), "", Mail, "")));
                    break;
                }

                if(CheckCond == 3)
                {
                    MapOfSubject.insert(make_pair(Password, CMail(CTimeStamp(Year, Month, Day, Hour, Minutes, Sec), "", "", Mail)));
                    break;
                }

                if(str[i] != ':' && str[i] != ' ' && str[i] != '\n' && str[i] != '=')
                {
                    tmp += str[i];
                }
            }

        }

        for(auto i : VectorOfTo)
        {
            MailInfo r;
            r.key = i.first;
            r.from = i.second.From();
            r.to = i.second.To();
            r.subject = i.second.Subject();
            Info.push_back(make_pair(i.second.TimeStamp(), r));
        }

        for(auto & i : Info)
        {
            auto attr = MapOfFrom.find(i.second.key);
            auto pttr = MapOfSubject.find(i.second.key);

            if(attr != MapOfFrom.end())
            {
                i.second.from = attr->second.From();
            }

            if(pttr != MapOfSubject.end())
            {
                i.second.subject = pttr->second.Subject();
            }
        }

        sort(Info.begin(), Info.end(), CompareTwoMails);

            /*   for(auto i : Info)
        {
            cout << i.first << " " << i.second.from << " " <<  i.second.to << " " << i.second.subject << " " << i.second.key << endl;
        }*/

        return (int)VectorOfTo.size();
    }

    list<CMail>    ListMail                                ( const CTimeStamp & from, const CTimeStamp & to ) const
    {
        list<CMail> ReturnList;
        auto attr = lower_bound(Info.begin(), Info.end(), from, CompareByMail);
        auto pttr = lower_bound(Info.begin(), Info.end(), to, CompareByMail);

        if(pttr == Info.end())
        {
            for(; attr < Info.end(); attr++)
           {
               if(attr->first.Compare(from) >= 0 && attr->first.Compare(to) <= 0)
                ReturnList.push_back(CMail(attr->first, attr->second.from, attr->second.to, attr->second.subject));
           }
        }
        else
        {
            for(; attr <= pttr; attr++)
           {
               if(attr->first.Compare(from) >= 0 && attr->first.Compare(to) <= 0)
                ReturnList.push_back(CMail(attr->first, attr->second.from, attr->second.to, attr->second.subject));
           }
        }

        return ReturnList;
    }

    set<string>    ActiveUsers                             ( const CTimeStamp & from, const CTimeStamp & to ) const
    {
        set<string> ReturnSet;
        auto attr = lower_bound(Info.begin(), Info.end(), from, CompareByMail);
        auto pttr = lower_bound(Info.begin(), Info.end(), to, CompareByMail);

        if(pttr == Info.end())
        {
            for(; attr < Info.end(); attr++)
           {
               if(attr->first.Compare(from) >= 0 && attr->first.Compare(to) <= 0)
               {
                    ReturnSet.insert(attr->second.from);
                    ReturnSet.insert(attr->second.to);
               }
           }
        }
        else
        {
            for(; attr <= pttr; attr++)
           {
                if(attr->first.Compare(from) >= 0 && attr->first.Compare(to) <= 0)
               {
                    ReturnSet.insert(attr->second.from);
                    ReturnSet.insert(attr->second.to);
               }
           }
        }

        return ReturnSet;
    }

private:

struct MailInfo
{
    string from;
    string to;
    string subject;
    string key;
};

  bool static CompareTwoMails(const pair<CTimeStamp, MailInfo> & n, const pair<CTimeStamp, MailInfo> & m)
    {
        if( n.first.Compare(m.first) < 0)
        {
            return true;
        }

        if( n.first.Compare(m.first) > 0)
        {
            return false;
        }

        return false;
    }

    bool static CompareByMail(const pair<CTimeStamp, MailInfo> & n, CTimeStamp time)
    {
        if(n.first.Compare(time) < 0)
        {
            return true;
        }

        if(n.first.Compare(time) > 0)
        {
            return false;
        }

        return false;
    }
    map<string,CMail> MapOfSubject;
    map<string, CMail> MapOfFrom;
    vector<pair<string, CMail>> VectorOfTo;
    vector<CMail> VectorOfMail;
    vector<pair<CTimeStamp, MailInfo>> Info;
};
//----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string             printMail                               ( const list<CMail> & all )
{
  ostringstream oss;
  for ( const auto & mail : all )
  {
      oss << mail << endl;
      //cout << mail << endl;
  }
  return oss . str ();
}
string             printUsers                              ( const set<string> & all )
{
  ostringstream oss;
  bool first = true;
  for ( const auto & name : all )
  {
    if ( ! first )
      oss << ", ";
    else
      first = false;
    oss << name;
    //cout << name << endl;
  }
  return oss . str ();
}
int                main                                    ( void )
{
    MysteriousNamespace::CMailLog m;
    list<CMail> mailList;
    set<string> users;
    istringstream iss;

    iss . clear ();
    iss . str (
        "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"
        "Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
        "Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=New progtest homework!\n"
        "Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
        "Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
        "Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
        "Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
        "Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
        "Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
        "Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
        "Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
        "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
        "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
        "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
        "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n" );
    assert ( m . ParseLog ( iss ) == 8 );
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );
    /*assert ( printMail ( mailList ) ==
      "2019-3-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
      "2019-3-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
      "2019-3-29 14:58:32 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
      "2019-3-29 15:2:34.23 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
      "2019-3-29 15:2:34.23 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
      "2019-3-29 15:2:34.23 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
      "2019-3-29 15:2:34.23 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
      "2019-3-29 15:2:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n" );*/
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 14, 58, 32 ) );
   /* assert ( printMail ( mailList ) ==
      "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
      "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
      "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n" );*/
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 30, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 30, 23, 59, 59 ) );
    assert ( printMail ( mailList ) == "" );
    users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );
    assert ( printUsers ( users ) == "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz" );
    users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 13, 59, 59 ) );
    assert ( printUsers ( users ) == "person3@fit.cvut.cz, user76@fit.cvut.cz" );
    return 0;
}
#endif /* __PROGTEST__ */
