#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */

class NoRouteException
{
};

template <typename _T, typename _E>
class CRoute
{
  public:
   CRoute & Add (const _T source, const _T destination, const _E train)
   {
       city[source].push_back(make_pair(train, destination));
       city[destination].push_back(make_pair(train, source));
       return *this;
   }

   list<_T> Find (const _T from, const _T to, const function<bool(_E)> & functor = nullptr) const
   {
       if(from == to)
       {
           list<_T> ReturnList;
           ReturnList.emplace_back(from);
           return ReturnList;
       }

       if(city.find(from) == city.end() || city.find(to) == city.end())
       {
           throw NoRouteException();
       }

       queue<_T> known;
       map<_T, list<_T>> visit;

       known.push(from);

       list<_T> a;
       a.emplace_back(from);
       visit.emplace(from, a);

       while(!known.empty())
       {
           _T first = known.front();
           known.pop();

           for(unsigned int i = 0; i < (city.at(first)).size(); i++)
           {
               if(visit.find(city.at(first)[i].second) != visit.end() || (functor && !functor(city.at(first)[i].first)))
               {
                   continue;
               }

               known.push(city.at(first)[i].second);
               list<_T> m = visit.at(first);
               m.emplace_back(city.at(first)[i].second);
               visit.emplace(city.at(first)[i].second, m);
           }
       }

       try{ visit.at(to); } catch (out_of_range & e) { throw NoRouteException(); }
       return visit.at(to);
   }

  private:
    map<_T, vector<pair<_E, _T>>> city;
};

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
  public:
                             CTrain                        ( const string    & company,
                                                             int               speed )
                             : m_Company ( company ),
                               m_Speed ( speed )
    {
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed;
};
//=================================================================================================
class TrainFilterCompany
{
  public:
                             TrainFilterCompany            ( const set<string> & companies )
                             : m_Companies ( companies )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    {
      return m_Companies . find ( train . m_Company ) != m_Companies . end ();
    }
    //---------------------------------------------------------------------------------------------
  private:
    set <string>             m_Companies;
};
//=================================================================================================
class TrainFilterSpeed
{
  public:
                             TrainFilterSpeed              ( int               min,
                                                             int               max )
                             : m_Min ( min ),
                               m_Max ( max )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    {
      return train . m_Speed >= m_Min && train . m_Speed <= m_Max;
    }
    //---------------------------------------------------------------------------------------------
  private:
    int                      m_Min;
    int                      m_Max;
};
//=================================================================================================
bool               NurSchnellzug                           ( const CTrain    & zug )
{
  return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
static string      toText                                  ( const list<string> & l )
{
  ostringstream oss;

  auto it = l . cbegin();
  oss << *it;
  for ( ++it; it != l . cend (); ++it )
    oss << " > " << *it;
  return oss . str ();
}
//=================================================================================================
int main ( void )
{
  CRoute<string,CTrain> lines;

  lines . Add ( "Berlin", "Prague", CTrain ( "DB", 120 ) )
        . Add ( "Berlin", "Prague", CTrain ( "CD",  80 ) )
        . Add ( "Berlin", "Dresden", CTrain ( "DB", 160 ) )
        . Add ( "Dresden", "Munchen", CTrain ( "DB", 160 ) )
        . Add ( "Munchen", "Prague", CTrain ( "CD",  90 ) )
        . Add ( "Munchen", "Linz", CTrain ( "DB", 200 ) )
        . Add ( "Munchen", "Linz", CTrain ( "OBB", 90 ) )
        . Add ( "Linz", "Prague", CTrain ( "CD", 50 ) )
        . Add ( "Prague", "Wien", CTrain ( "CD", 100 ) )
        . Add ( "Linz", "Wien", CTrain ( "OBB", 160 ) )
        . Add ( "Paris", "Marseille", CTrain ( "SNCF", 300 ))
        . Add ( "Paris", "Dresden",  CTrain ( "SNCF", 250 ) );

  list<string> r1 = lines . Find ( "Berlin", "Linz" );
  cout << toText ( r1 ) << endl;
  assert ( toText ( r1 ) == "Berlin > Prague > Linz" );

  list<string> r2 = lines . Find ( "Linz", "Berlin" );
   cout << toText ( r2 ) << endl;
  assert ( toText ( r2 ) == "Linz > Prague > Berlin" );

  list<string> r3 = lines . Find ( "Wien", "Berlin" );
   cout << toText ( r3 ) << endl;
  assert ( toText ( r3 ) == "Wien > Prague > Berlin" );

  list<string> r4 = lines . Find ( "Wien", "Berlin", NurSchnellzug );
   cout << toText ( r4 ) << endl;
  assert ( toText ( r4 ) == "Wien > Linz > Munchen > Dresden > Berlin" );

  list<string> r5 = lines . Find ( "Wien", "Munchen", TrainFilterCompany ( set<string> { "CD", "DB" } ) );
   cout << toText ( r5 ) << endl;
  assert ( toText ( r5 ) == "Wien > Prague > Munchen" );

  list<string> r6 = lines . Find ( "Wien", "Munchen", TrainFilterSpeed ( 120, 200 ) );
   cout << toText ( r6 ) << endl;
  assert ( toText ( r6 ) == "Wien > Linz > Munchen" );

  list<string> r7 = lines . Find ( "Wien", "Munchen", [] ( const CTrain & x ) { return x . m_Company == "CD"; } );
   cout << toText ( r7 ) << endl;
  assert ( toText ( r7 ) == "Wien > Prague > Munchen" );

  list<string> r8 = lines . Find ( "Munchen", "Munchen" );
   cout << toText ( r8 ) << endl;
  assert ( toText ( r8 ) == "Munchen" );

  list<string> r9 = lines . Find ( "Marseille", "Prague" );
   cout << toText ( r9 ) << endl;
  assert ( toText ( r9 ) == "Marseille > Paris > Dresden > Berlin > Prague"
           || toText ( r9 ) == "Marseille > Paris > Dresden > Munchen > Prague" );

  try
  {
    list<string> r10 = lines . Find ( "Marseille", "Prague", NurSchnellzug );
    assert ( "Marseille > Prague connection does not exist!!" == NULL );
  }
  catch ( const NoRouteException & e )
  {
  }

  list<string> r11 = lines . Find ( "Salzburg", "Salzburg" );
   cout << toText ( r11 ) << endl;
  assert ( toText ( r11 ) == "Salzburg" );

  list<string> r12 = lines . Find ( "Salzburg", "Salzburg", [] ( const CTrain & x ) { return x . m_Company == "SNCF"; }  );
   cout << toText ( r12 ) << endl;
  assert ( toText ( r12 ) == "Salzburg" );

  try
  {
    list<string> r13 = lines . Find ( "London", "Oxford" );
    assert ( "London > Oxford connection does not exist!!" == NULL );
  }
  catch ( const NoRouteException & e )
  {
  }
  return 0;
}
#endif  /* __PROGTEST__ */
