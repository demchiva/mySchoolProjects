#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidRangeException
{
};
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class TmpRange
{
   public:
    TmpRange(long long int Begin, long long int End, char Op)
    {
        if( Begin > End )
        {
            throw InvalidRangeException();
        }

        m_Begin = Begin;
        m_End = End;
        Operation = Op;
    }

    long long int m_Begin;
    long long int m_End;
    char Operation;
};

class TmpClass
{
public:
    vector<TmpRange> TmpList;

    void Do(long long int Begin, long long int End, char Op)
    {
        TmpRange n(Begin, End, Op);
        TmpList.push_back(n);
    }
};

class CRange
{
  public:
    CRange(long long int Begin, long long int End)
    {
        if( Begin > End )
        {
            throw InvalidRangeException();
        }

        m_Begin = Begin;
        m_End = End;
    }

    long long int m_Begin;
    long long int m_End;
};

const TmpClass operator + (const CRange First, const CRange Second){
    TmpClass ReturnList;
    ReturnList.Do(First.m_Begin, First.m_End, '+');
    ReturnList.Do(Second.m_Begin, Second.m_End, '+');
    return ReturnList;
}

const TmpClass operator + (const TmpClass First, const CRange Second){
    TmpClass ReturnList;
    ReturnList.TmpList = First.TmpList;
    //ReturnList.TmpList.assign(First.TmpList.begin(), First.TmpList.end());
    ReturnList.Do(Second.m_Begin, Second.m_End, '+');
    return ReturnList;
}

const TmpClass operator - (const TmpClass First, const CRange Second){
    TmpClass ReturnList;
    ReturnList.TmpList = First.TmpList;
    ReturnList.Do(Second.m_Begin, Second.m_End, '-');
    return ReturnList;
}

const TmpClass operator - (const CRange First, const CRange Second){
    TmpClass ReturnList;
    ReturnList.Do(First.m_Begin, First.m_End, '+');
    ReturnList.Do(Second.m_Begin, Second.m_End, '-');
    return ReturnList;
}

class CRangeList
{
  public:
    bool Includes ( const long long int a ) const;
    bool Includes ( const CRange a ) const;
    const CRangeList operator += (const CRange AddRange);
    const CRangeList operator -= (const CRange SubRange);
    const CRangeList operator += (const TmpClass AddVector);
    const CRangeList operator -= (const TmpClass SubVector);
    const CRangeList operator += (const CRangeList ChangeList);
    const CRangeList operator -= (const CRangeList ChangeList);
    CRangeList operator + (const CRange & other);
    CRangeList operator - (const CRange & SubRange);
    CRangeList   operator =  (const CRange Par);
    CRangeList   operator = (const TmpClass AssignVector);
    bool         operator == ( const CRangeList & other ) const;
    bool         operator != ( const CRangeList & other ) const;
    friend ostream & operator << ( ostream & str, const CRangeList & date );
  private:
    vector<CRange> ListOfInterval;
    static bool IsContain     ( CRange data, long long int Number );
    static bool IsContain1    ( const CRange & a, const CRange & b );
};

const CRangeList CRangeList::operator += (const CRangeList ChangeList)
{
    for(unsigned int i = 0; i < ChangeList.ListOfInterval.size(); i++)
    {
        *this += ChangeList.ListOfInterval[i];
    }

    return *this;
}

const CRangeList CRangeList::operator -= (const CRangeList ChangeList)
{
    for(unsigned int i = 0; i < ChangeList.ListOfInterval.size(); i++)
    {
        *this -= ChangeList.ListOfInterval[i];
    }

    return *this;
}

const CRangeList CRangeList::operator -= (const TmpClass SubVector)
{
    for(unsigned int i = 0; i < SubVector.TmpList.size(); i++)
    {
        CRange tmp(SubVector.TmpList[i].m_Begin, SubVector.TmpList[i].m_End);
        if(SubVector.TmpList[i].Operation == '+')
        {
            *this -= tmp;
        }
        else
        {
            *this += tmp;
        }
    }

    return *this;
}

const CRangeList CRangeList::operator += (const TmpClass AddVector)
{
    for(unsigned int i = 0; i < AddVector.TmpList.size(); i++)
    {
        CRange tmp(AddVector.TmpList[i].m_Begin, AddVector.TmpList[i].m_End);
        if(AddVector.TmpList[i].Operation == '+')
        {
            *this += tmp;
        }
        else
        {
            *this -= tmp;
        }
    }

    return *this;
}

bool CRangeList::IsContain           ( CRange data, long long int Number )
{
    if(data.m_Begin != LLONG_MIN && data.m_End != LLONG_MAX)
    {
        if(data.m_Begin - 1 <= Number && Number <= data.m_End + 1)
         {
             return true;
         }
    }

        if(data.m_Begin == LLONG_MIN && data.m_End != LLONG_MAX)
    {
        if(data.m_Begin <= Number && Number <= data.m_End + 1)
         {
             return true;
         }
    }

        if(data.m_Begin != LLONG_MIN && data.m_End == LLONG_MAX)
    {
        if(data.m_Begin - 1 <= Number && Number <= data.m_End)
         {
             return true;
         }
    }

        if(data.m_Begin == LLONG_MIN && data.m_End == LLONG_MAX)
    {
        if(data.m_Begin <= Number && Number <= data.m_End )
         {
             return true;
         }
    }

    return false;
}

const CRangeList CRangeList::operator += (const CRange AddRange)
{
    *this = *this + AddRange;
    return *this;
}

const CRangeList CRangeList::operator -= (const CRange SubRange)
{
    *this = *this - SubRange;
    return *this;
}

CRangeList CRangeList::operator + (const CRange & other)
{
    int Check = 0;
    unsigned int itter = 0;
    unsigned int i;

    for(i = 0; i < ListOfInterval.size(); i++)
    {
        if(other.m_End != LLONG_MAX)
        {
             if(IsContain(ListOfInterval[i], other.m_Begin) && IsContain(ListOfInterval[i], other.m_End + 1 ))
             {
                 if(other.m_Begin < ListOfInterval[i].m_Begin)
                 {
                     ListOfInterval[i].m_Begin = other.m_Begin;
                 }
                 else if(other.m_End > ListOfInterval[i].m_End)
                 {
                     ListOfInterval[i].m_End = other.m_End;
                 }
                 else
                 {
                     return *this;
                 }
             }
        }
        else
        {
            if(IsContain(ListOfInterval[i], other.m_Begin) && IsContain(ListOfInterval[i], other.m_End))
             {
                 if(other.m_Begin < ListOfInterval[i].m_Begin)
                 {
                     ListOfInterval[i].m_Begin = other.m_Begin;
                 }
                 else if(other.m_End > ListOfInterval[i].m_End)
                 {
                     ListOfInterval[i].m_End = other.m_End;
                 }
                 else
                 {
                     return *this;
                 }
             }
        }

        if(IsContain(ListOfInterval[i], other.m_Begin) && ListOfInterval[i].m_End < other.m_End)
        {
            ListOfInterval[i].m_End = other.m_End;
            Check = 1;
            itter = i;
            break;
        }

        if(IsContain(ListOfInterval[i], other.m_End) && ListOfInterval[i].m_Begin > other.m_Begin)
        {
            ListOfInterval[i].m_Begin = other.m_Begin;
            Check = 2;
            itter = i;
            break;
        }

        if(other.m_Begin <= ListOfInterval[i].m_Begin && other.m_End >= ListOfInterval[i].m_End)
        {
            ListOfInterval.erase(ListOfInterval.begin() + i);
            --i;
        }
    }

    if(ListOfInterval.size() == 0)
    {
        ListOfInterval.push_back(other);
        return *this;
    }

    if(Check == 1)
    {
        for(i = itter + 1; i < ListOfInterval.size(); i++)
        {
            if(ListOfInterval[i].m_End < ListOfInterval[itter].m_End)
            {
                ListOfInterval.erase(ListOfInterval.begin() + i);
            }

         //   if(ListOfInterval[itter].m_End == LLONG_MAX)
         //   {
                if(IsContain(ListOfInterval[i], ListOfInterval[itter].m_End))
                {
                   ListOfInterval[i].m_Begin = ListOfInterval[itter].m_Begin;
                   ListOfInterval.erase(ListOfInterval.begin() + itter);
                   break;
                }
          //  }
         /*   else
            {
                 if(IsContain(ListOfInterval[i], ListOfInterval[itter].m_End + 1))
                {
                   ListOfInterval[i].m_Begin = ListOfInterval[itter].m_Begin;
                   ListOfInterval.erase(ListOfInterval.begin() + itter);
                   break;
                }
            }*/
        }
    }
    else if(Check == 2)
    {
        for(int j = (int)itter - 1; j >= 0; j--)
        {
            if(ListOfInterval[j].m_Begin > ListOfInterval[itter].m_Begin)
            {
                ListOfInterval.erase(ListOfInterval.begin() + j);
            }

         //   if(ListOfInterval[itter].m_Begin == LLONG_MIN)
          //  {
                if(!IsContain(ListOfInterval[i], ListOfInterval[itter].m_Begin))
                {
                    ListOfInterval[itter].m_Begin = ListOfInterval[j].m_Begin;
                    ListOfInterval.erase(ListOfInterval.begin() + j);
                    break;
                }
       /*     }
            else
            {
                if(!IsContain(ListOfInterval[i], ListOfInterval[itter].m_Begin + 1))
                {
                    ListOfInterval[itter].m_Begin = ListOfInterval[j].m_Begin;
                    ListOfInterval.erase(ListOfInterval.begin() + j);
                    break;
                }
            }*/
        }
    }
    else
    {
        if(ListOfInterval[0].m_Begin > other.m_End)
        {
            ListOfInterval.insert(ListOfInterval.begin(), other);
            return *this;
        }

        for(int j = ListOfInterval.size() - 1; j >= 0; j--)
        {
            if(ListOfInterval[j].m_End < other.m_Begin)
            {
                ListOfInterval.insert(ListOfInterval.begin() + j + 1, other);
                return *this;
            }
        }
    }

    return *this;
}

CRangeList CRangeList::operator - (const CRange & other)
{
    for(unsigned int i = 0; i < ListOfInterval.size(); i++)
    {
        if(ListOfInterval[i].m_Begin >= other.m_Begin && ListOfInterval[i].m_End <= other.m_End)
        {
            ListOfInterval.erase(ListOfInterval.begin() + i);
            i--;
        }
    }

   /* for(unsigned int i = 0; i < ListOfInterval.size(); i++)
    {
        if(ListOfInterval[i].m_Begin < other.m_Begin && ListOfInterval[i].m_End > other.m_End)
        {
            long long int tmp_int = ListOfInterval[i].m_End;
            CRange tmp_range = other;
            ListOfInterval[i].m_End = other.m_Begin - 1;
            tmp_range.m_Begin = other.m_End + 1;
            tmp_range.m_End = tmp_int;

            ListOfInterval.insert(ListOfInterval.begin() + i + 1, tmp_range);
            break;
        }

        if(ListOfInterval[i].m_End >= other.m_Begin && ListOfInterval[i].m_Begin < other.m_Begin) 0 .. 9 1..7
        {
            ListOfInterval[i].m_End = other.m_Begin - 1;
        }

        if(ListOfInterval[i].m_Begin <= other.m_End && ListOfInterval[i].m_End > other.m_End)
        {
            ListOfInterval[i].m_Begin = other.m_End + 1;
        }
    }*/


    for(unsigned int i = 0; i < ListOfInterval.size(); i++)
    {
        if(ListOfInterval[i].m_Begin < other.m_Begin && ListOfInterval[i].m_End > other.m_End)
        {
            long long int tmp_int = ListOfInterval[i].m_End;
            CRange tmp_range = other;
            if(other.m_Begin == LLONG_MIN)
            {
                ListOfInterval[i].m_End = other.m_Begin;
            }
            else
            {
                ListOfInterval[i].m_End = other.m_Begin - 1;
            }

            if(other.m_End == LLONG_MAX)
            {
                tmp_range.m_Begin = other.m_End;
            }
            else
            {
                tmp_range.m_Begin = other.m_End + 1;
            }
            tmp_range.m_End = tmp_int;

            ListOfInterval.insert(ListOfInterval.begin() + i + 1, tmp_range);
            break;
        }

         if(ListOfInterval[i].m_End >= other.m_Begin && ListOfInterval[i].m_Begin < other.m_Begin)
        {
            if(other.m_Begin == LLONG_MIN)
            {
                ListOfInterval[i].m_End = other.m_Begin;
            }
            else
            {
                ListOfInterval[i].m_End = other.m_Begin - 1;
            }
        }

        if(ListOfInterval[i].m_Begin <= other.m_End && ListOfInterval[i].m_End > other.m_End)
        {
            if(other.m_End == LLONG_MAX)
            {
                ListOfInterval[i].m_Begin = other.m_End;
            }
            else
            {
                ListOfInterval[i].m_Begin = other.m_End + 1;
            }
        }
    }

    return *this;
}

CRangeList CRangeList::operator = (CRange Par)
{
    ListOfInterval.clear();
    ListOfInterval.push_back(Par);
    return *this;
}

CRangeList CRangeList::operator = (TmpClass AssignVector)
{
    ListOfInterval.clear();

    for(unsigned int i = 0; i < AssignVector.TmpList.size(); i++)
    {
        CRange r(AssignVector.TmpList[i].m_Begin, AssignVector.TmpList[i].m_End);

        if ( AssignVector.TmpList[i].Operation == '+' )
        {
            *this= *this + r;
        } else
        {
            *this= *this - r;
        }

    }

    return *this;
}

ostream &                operator << ( ostream & os, const CRangeList & date ) // hotovo
{
    os << '{';

    for(auto i = date.ListOfInterval.begin(); i != date.ListOfInterval.end(); i++)
    {
        if(i == (date.ListOfInterval.end() - 1))
        {
            if(i->m_Begin == i->m_End)
            {
                os << i->m_Begin;
            }
            else
            {
                os << "<" << i->m_Begin << ".." << i->m_End << ">";
            }
        }
        else
        {
            if(i->m_Begin == i->m_End)
            {
                os << i->m_Begin << ",";
            }
            else
            {
                os << "<" << i->m_Begin << ".." << i->m_End << ">,";
            }
        }
    }

    os << '}';

    return os;
}

bool         CRangeList::Includes    ( const long long int a ) const// переписать под лог время // hotovo
{
    for(unsigned int i = 0; i < ListOfInterval.size(); i++)
    {
        if(ListOfInterval[i].m_Begin <= a && a <= ListOfInterval[i].m_End)
        {
            return true;
        }
    }

    return false;
}

bool      CRangeList::IsContain1 ( const CRange & a, const CRange & b )
{
    return a.m_Begin <= b.m_Begin && b.m_End <= a.m_End;
}

bool         CRangeList::Includes    ( const CRange a ) const// переписать под лог время // hotovo
{
    if(a.m_Begin == a.m_End)
    {
        return Includes(a.m_Begin);
    }

    for(unsigned int i = 0; i < ListOfInterval.size(); i++)
    {
        if(ListOfInterval[i].m_Begin <= a.m_Begin && ListOfInterval[i].m_End >= a.m_End)
        {
            return true;
        }
    }

    return false;

 /*   auto attr = lower_bound(ListOfInterval.begin(), ListOfInterval.end(), a, IsContain1);

    CRange n(attr->m_Begin, attr->m_End);
    CRangeList h;
    h = n;
    cout << h << endl;
    if(attr != ListOfInterval.end() && IsContain(n, a.m_Begin) && IsContain(n, a.m_End))
    {
        return true;
    }

    return false;*/

}

bool         CRangeList::operator == ( const CRangeList & other ) const // hotovo
{
    if( (*this).ListOfInterval.size() != other.ListOfInterval.size() )
    {
        return false;
    }

    for(unsigned int i = 0; i < other.ListOfInterval.size(); i++)
    {
        if(other.ListOfInterval[i].m_Begin != (*this).ListOfInterval[i].m_Begin || other.ListOfInterval[i].m_End != (*this).ListOfInterval[i].m_End )
        {
            return false;
        }
    }

    return true;
}

bool         CRangeList::operator != ( const CRangeList & other ) const // hotovo
{
        if( (*this).ListOfInterval.size() != other.ListOfInterval.size() )
    {
        return true;
    }

    for(unsigned int i = 0; i < other.ListOfInterval.size(); i++)
    {
        if(other.ListOfInterval[i].m_Begin != (*this).ListOfInterval[i].m_Begin || other.ListOfInterval[i].m_End != (*this).ListOfInterval[i].m_End )
        {
            return true;
        }
    }

    return false;
}



#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
  CRangeList a, b;

  assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
  a = CRange ( 5, 10 );
  a += CRange ( 25, 100 );
  assert ( toString ( a ) == "{<5..10>,<25..100>}" );
  a += CRange ( -5, 0 );
  a += CRange ( 8, 50 );
  assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
  a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
  assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
  a += CRange ( 106, 119 ) + CRange ( 152, 158 );
  assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
  a += CRange ( -3, 170 );
  a += CRange ( -30, 1000 );
  assert ( toString ( a ) == "{<-30..1000>}" );
  b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
  a += b;
  cout << a << endl;
  assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( -400, -400 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
  a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  try
  {
    a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
    assert ( "Exception not thrown" == NULL );
  }
  catch ( const InvalidRangeException & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception thrown" == NULL );
  }
  assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  b = a;
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 2600, 2700 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
  assert ( a == b );
  assert ( !( a != b ) );
  b += CRange ( 15, 15 );
  assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
  assert ( !( a == b ) );
  assert ( a != b );
  assert ( b . Includes ( 15 ) );
  assert ( b . Includes ( 2900 ) );
  assert ( b . Includes ( CRange ( 15, 15 ) ) );
  assert ( b . Includes ( CRange ( -350, -350 ) ) );
  assert ( b . Includes ( CRange ( 100, 200 ) ) );
  assert ( !b . Includes ( CRange ( 800, 900 ) ) );
  assert ( !b . Includes ( CRange ( -1000, -450 ) ) );
  assert ( !b . Includes ( CRange ( 0, 500 ) ) );
  a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
  assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b += a;
  assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
  b -= a;
  assert ( toString ( b ) == "{}" );
  b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
  assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
  b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
  assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
//#ifdef EXTENDED_SYNTAX
  /*CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
    oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );*/
//#endif /* EXTENDED_SYNTAX */
  return 0;
}
#endif /* __PROGTEST__ */
