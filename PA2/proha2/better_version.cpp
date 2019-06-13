#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>  /* assert */
#include <iostream> /* standart library */
#include <iomanip>
#include <string> /* string */
#include <vector> /* vector */
#include <list>
#include <algorithm> /* sort */
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

/*
 * The program implements cadastre database and uses to browse the land list.
 * Our cadastre remembers the list of lands and their respective owners.
 * For each lands program remembers City, Address, Region, Id identify and Owner.
 * The couples City, Address and Region, Id must be unique.
 *
 * In this version, the program works well, uses efficient algorithms for both allocation
 * and modality.
 */

/*
 * The structure that represents land characteristic
 */
struct DATA{
    pair<string, string> CityAddress;       // pair of City and Address
    pair<string, unsigned int> RegionId;    // pair of Region and Id identify
    string Owner;                           // name of lands owner
    unsigned int ForOwn;                    // unique id for sorting by owners
};

/*-----------------------------------------------------------------------------------------------*/

/*
 * The class uses to browse the land list
 */
class CIterator
{
public:
    
    /*
     * Constructor for class CIterator
     *
     * @param[in] n - input vector
     *
     * Copy a received vector and set inner iterator
     */
    
    CIterator                                              ( vector<struct DATA> n );
    
    /*
     * The method controls end of vector
     *
     * @return true if it is end of vector
     */
    
    bool                     AtEnd                         ( void ) const;
    
    /*
     * The method set iterator on next element
     */
    
    void                     Next                          ( void );
    
    /*
     * The method returns city of actual land
     *
     * @return city of current element in vector
     */
    
    string                   City                          ( void ) const;
    
    /*
     * The method returns address of actual land
     *
     * @return address of current element in vector
     */
    
    string                   Addr                          ( void ) const;
    
    /*
     * The method returns region of actual land
     *
     * @return region of current element in vector
     */
    
    string                   Region                        ( void ) const;
    
    /*
     * The method returns id of actual land
     *
     * @return id of current element in vector
     */
    
    unsigned                 ID                            ( void ) const;
    
    /*
     * The method returns owner of actual land
     *
     * @return owner of current element in vector
     */
    
    string                   Owner                         ( void ) const;

private:
    vector<struct DATA>::iterator attr;     // iterator to browse the vector ListByAddress
    vector<struct DATA> ListByAddress;      // vector to browse, represents lands sorting by Owners or Address
};

/*-----------------------------------------------------------------------------------------------*/

 /*
  * The class implements cadastre database.
  */
class CLandRegister
{
public:

    /*
     * Constructor for class CLandRegister
     *
     * Set initial value for Size and ForOwn
     */
    
    CLandRegister                                          ( void );

    
    /*
     * The method inserts a new land in vectors
     * Complexity O(log(n))
     *
     * @param[in] city - the City of new land
     * @param[in] addr - the Address of new land
     * @param[in] region - the Region of new land
     * @param[in] id - the Id of new land
     *
     * @return true if City, Address are unique and Region, Id are unique
     */
    
    bool                     Add                           ( const string & city, const string & addr,
                                                             const string & region, unsigned int id );

    /*
     * The method deletes element from lands database
     * Complexity O(log(n))
     *
     * @param[in] city - the City which we need to find
     * @param[in] addr - the Address which we need to find
     *
     * @return true if element was found and deleted, otherwise false
     */
    
    bool                     Del                           ( const string & city, const string & addr );

    /*
     * The method deletes element from lands database
     * Complexity O(log(n))
     *
     * @param[in] region - the Region which we need to find
     * @param[in] id - the Id which we need to find
     *
     * @return true if element was found and deleted, otherwise false
     */
    
    bool                     Del                           ( const string & region, unsigned int id );

    
    /*
     * The method sets parameter owner if we find him
     * Complexity O(log(n))
     *
     * @param[in] city - the City by which we need to find the element
     * @param[in] addr - the Address by which we need to find the element
     * @param[in,out] owner - parameter which we set if find the element
     *
     * @return true if element was found, otherwise false
     */
    
    bool                     GetOwner                      ( const string & city, const string & addr,
                                                             string & owner ) const;

    /*
     * The method sets parameter owner if we find him
     * Complexity O(log(n))
     *
     * @param[in] region - the Region by which we need to find the element
     * @param[in] id - the Id by which we need to find the element
     * @param[in,out] owner - parameter which we set if find the element
     *
     * @return true if element was found, otherwise false
     */
    
    bool                     GetOwner                      ( const string & region, unsigned int id,
                                                             string & owner ) const;

    /*
     * The method sets owner for some lands
     * Complexity O(log(n))
     *
     * @param[in] city - the City by which we need to find the element
     * @param[in] addr - the Address by which we need to find the element
     * @param[in] owner - parameter which we use for setting owner for some land
     *
     * @return true if element was found and don`t have the same owner, otherwise false
     */
    
    bool                     NewOwner                      ( const string & city, const string & addr,
                                                             const string & owner );

    /*
     * The method sets owner for some lands
     * Complexity O(log(n))
     *
     * @param[in] region - the Region by which we need to find the element
     * @param[in] id - the Id by which we need to find the element
     * @param[in] owner - parameter which we use for setting owner for some land
     *
     * @return true if element was found and don`t have the same owner, otherwise false
     */
    
    bool                     NewOwner                      ( const string & region, unsigned int id,
                                                             const string & owner );

    /*
     * The method uses for counting the owners lands
     * Complexity O(n)
     *
     * @param[in] owner - names of owner which lands we need to find
     *
     * @return count of lands owner haves
     */
    
    unsigned                 Count                         ( const string & owner ) const;

    /*
     * The method uses for return list of lands sort by City and Address
     * Complexity O(1)
     *
     * @return instance of CIterator with list sort by City and Address
     */
    
    CIterator                ListByAddr                    ( void ) const;

    /*
     * The method uses for return list of lands sorting by time of receive by some owner
     * Complexity O(n * log(n))
     *
     * @param[in] owner - names of owner whose lands we need sort by receive
     *
     * @return instance of CIterator with sort list by receive
     */
    
    CIterator                ListByOwner                   ( const string & owner ) const;

private:

    vector< struct DATA >::iterator attr;          // iterator to browse the vector LandsRegisterByAddress
    vector< struct DATA >::iterator kttr;          // iterator to browse the vector LandsRegisterByRegion
    vector<struct DATA> LandsRegisterByAddress;    // vector which contains lands sorting by city and address
    vector<struct DATA> LandsRegisterByRegion;     // vector which contains lands sorting by region and id
    unsigned int Size;                             // parameters to resize the vectors
    unsigned int ForOwn;                           // parameters to sorting vectors by owners
    
    /*
     * The method controls unique of data and set iterator attr on necessary position
     * Complexity O(log(n))
     *
     * @param[in] city - the City which we need to find in vector
     * @param[in] addr - the Address which we need to find in vector
     * @param[in] LandsRegisterByAddress - vector sorting by city and address
     *
     * @return true if city and address are not unique
     */
    
    bool FindByCityAddress                                 ( const string city, const string addr, vector<struct DATA> & LandsRegisterByAddress );
    
    /*
     * The method controls unique of data and set iterator kttr on necessary position
     * Complexity O(log(n))
     *
     * @param[in] region - the Region which we need to find in vector
     * @param[in] id - the Id which we need to find in vector
     * @param[in] LandsRegisterByRegion - vector sorting by region and id
     *
     * @return true if region and id are not unique, false if they are ont
     */
    
    bool FindByRegionId                                    ( const string region, unsigned int id, vector<struct DATA> & LandsRegisterByRegion );
    
    /*
     * The method compares two string
     *
     * @param[in] First - some string
     * @param[in] Second - another string
     *
     * @return true if they are equal, false if they are ont
     */
    
    static bool CompareTwoString                           ( const string First, const string Second );
    
    /*
     * The method uses for function sort and decides which lands was be receive first for some owner
     *
     * @param[in] n1 - some elements of vector
     * @param[in] n2 - another elements of vector
     *
     * @return true if they are equal, false if they are ont
     */
    
    static bool CompareByOwners                            ( struct DATA n1, struct DATA n2 );
    
    /*
     * The method uses in function lower_bound like a compare function by City and Address
     *
     * @param[in] data - elements of vector
     * @param[in] CityAddress - pair of City and Address that own a new element of vector
     *
     * @return true if they are equal, false if they are ont
     */
    
    static bool CompareByCityAddress                       ( struct DATA data, const pair<string, string> & CityAddress );
    
    /*
     * The method uses in function lower_bound like a compare function by Region and Id
     *
     * @param[in] data - elements of vector
     * @param[in] RegionId - pair of Region and Id that own a new element of vector
     *
     * @return true if they are equal, false if they are ont
     */
    
    static bool CompareByRegionId                          ( struct DATA data, const pair<string, unsigned int> & RegionId );
};

// ************************************************************************** //
// ----------------------------- Implementation ----------------------------- //
// ************************************************************************** //

//----------------------------------------------------------------------------//
// ------------------------------ CLandRegister ----------------------------- //
//----------------------------------------------------------------------------//

CLandRegister::CLandRegister                               ( void )
{
    this->Size = 10;
    this->ForOwn = 0;
}

/*-----------------------------------------------------------------------------------------------*/

bool CLandRegister::CompareByOwners                        ( struct DATA n1, struct DATA n2 )
{
    return n1.ForOwn < n2.ForOwn;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::CompareByCityAddress              ( struct DATA data, const pair<string, string> & CityAddress )
{
    return data.CityAddress.first == CityAddress.first ? data.CityAddress.second < CityAddress.second : data.CityAddress.first < CityAddress.first;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::CompareByRegionId                 ( struct DATA data, const pair<string, unsigned int> & RegionId )
{
    return data.RegionId.first == RegionId.first ? data.RegionId.second < RegionId.second : data.RegionId.first < RegionId.first;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::FindByCityAddress                 ( string city,  string addr, vector<struct DATA> & LandsRegisterByAddress )
{
    this->attr = lower_bound(LandsRegisterByAddress.begin(), LandsRegisterByAddress.end(), make_pair( city, addr ), CompareByCityAddress);

    if(this->attr->CityAddress.first == city && this->attr->CityAddress.second == addr)
    {
        return true;
    }

    return false;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::FindByRegionId                    ( const string region, unsigned int id, vector<struct DATA> & LandsRegisterByRegion )
{
    this->kttr = lower_bound(LandsRegisterByRegion.begin(), LandsRegisterByRegion.end(), make_pair( region, id ), CompareByRegionId);

    if(this->kttr->RegionId.first == region && this->kttr->RegionId.second == id)
    {
        return true;
    }

    return false;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::CompareTwoString                  ( string First, string Second )
{
    if(First.size() != Second.size())
    {
        return false;
    }

    for(unsigned int i = 0; i < First.size(); i++)
    {
        First[i] = tolower(First[i]);
        Second[i] = tolower(Second[i]);
    }

    if(First != Second)
    {
        return false;
    }

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::Add                               ( const string & city, const string & addr, const string & region, unsigned int id )
{
    if(!LandsRegisterByAddress.empty())
    {
        if( FindByCityAddress(city, addr, LandsRegisterByAddress) || FindByRegionId(region, id, LandsRegisterByRegion) )
        {
            return false;
        }
    }

    if(LandsRegisterByAddress.size() >= Size)
    {
        LandsRegisterByAddress.resize(Size * 2);
        LandsRegisterByRegion.resize(Size * 2);
    }

    this->Size++;

    struct DATA n;
    n.CityAddress = make_pair(city, addr);
    n.RegionId = make_pair(region, id);
    n.Owner = "";
    n.ForOwn = ForOwn++;
    LandsRegisterByAddress.insert(this->attr, n);
    LandsRegisterByRegion.insert(this->kttr, n);

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

CIterator CLandRegister::ListByAddr                        ( void ) const
{
    CIterator a(LandsRegisterByAddress);
    return a;
}

/*-----------------------------------------------------------------------------------------------*/

unsigned  CLandRegister::Count                             ( const string & owner ) const
{
    unsigned int Counter = 0;

    for(unsigned int i = 0; i < LandsRegisterByRegion.size(); i++)
    {
        if(CompareTwoString(LandsRegisterByRegion[i].Owner, owner))
        {
            Counter++;
        }
    }

    return Counter;
}

/*-----------------------------------------------------------------------------------------------*/

CIterator CLandRegister::ListByOwner                       ( const string & owner ) const
{
    vector<struct DATA> ReturnVector;

    for(unsigned int i = 0; i < this->LandsRegisterByAddress.size(); i++)
    {
        if(CompareTwoString(this->LandsRegisterByAddress[i].Owner, owner))
        {
            ReturnVector.push_back(this->LandsRegisterByAddress[i]);
        }
    }

    sort(ReturnVector.begin(), ReturnVector.end(), CompareByOwners);
    CIterator a(ReturnVector);

    return a;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::GetOwner                          ( const string & city, const string & addr, string & owner ) const
{
    auto it = lower_bound(LandsRegisterByAddress.begin(), LandsRegisterByAddress.end(), make_pair(city, addr), CompareByCityAddress);

    if(it->CityAddress.first != city || it->CityAddress.second != addr)
    {
        return false;
    }

    owner = it->Owner;

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::GetOwner                          ( const string & region, unsigned int id, string & owner ) const
{
    auto it = lower_bound(LandsRegisterByRegion.begin(), LandsRegisterByRegion.end(), make_pair(region, id), CompareByRegionId);

    if(it->RegionId.first != region || it->RegionId.second != id)
    {
        return false;
    }

    owner = it->Owner;

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

bool     CLandRegister::Del                                ( const string & city, const string & addr )
{
    if(!FindByCityAddress(city, addr, LandsRegisterByAddress))
    {
        return false;
    }

    if(!FindByRegionId(this->attr->RegionId.first, this->attr->RegionId.second, LandsRegisterByRegion))
    {
        return false;
    }

    LandsRegisterByAddress.erase(this->attr);
    LandsRegisterByRegion.erase(this->kttr);

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

bool     CLandRegister::Del                                ( const string & region, unsigned int id )
{
    if(!FindByRegionId(region, id, LandsRegisterByRegion))
    {
        return false;
    }

    if(!FindByCityAddress(this->kttr->CityAddress.first, this->kttr->CityAddress.second, LandsRegisterByAddress))
    {
        return false;
    }

    LandsRegisterByAddress.erase(this->attr);
    LandsRegisterByRegion.erase(this->kttr);

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::NewOwner                          ( const string & city, const string & addr, const string & owner )
{
    if(!FindByCityAddress(city, addr, LandsRegisterByAddress))
    {
        return false;
    }

    if(this->attr->Owner == owner)
    {
        return false;
    }

    if(!FindByRegionId(this->attr->RegionId.first, this->attr->RegionId.second, LandsRegisterByRegion))
    {
        return false;
    }

    this->kttr->Owner = owner;
    this->kttr->ForOwn = ForOwn;
    this->attr->Owner = owner;
    this->attr->ForOwn = ForOwn++;

    return true;
}

/*-----------------------------------------------------------------------------------------------*/

bool      CLandRegister::NewOwner                          ( const string & region, unsigned int id, const string & owner )
{
    if(!FindByRegionId(region, id, LandsRegisterByRegion))
    {
        return false;
    }

    if(this->kttr->Owner == owner)
    {
        return false;
    }

    if(!FindByCityAddress(this->kttr->CityAddress.first, this->kttr->CityAddress.second, LandsRegisterByAddress))
    {
        return false;
    }

    this->kttr->Owner = owner;
    this->kttr->ForOwn = ForOwn;
    this->attr->Owner = owner;
    this->attr->ForOwn = ForOwn++;

    return true;
}


//----------------------------------------------------------------------------//
// -------------------------------- CIterator ------------------------------- //
//----------------------------------------------------------------------------//

CIterator::CIterator                                (vector<struct DATA> n)
{
    this->ListByAddress.assign(n.begin(), n.end());

    if(ListByAddress.size() != 0)
    {
        this->attr = ListByAddress.begin();
    }
    else
    {
        this->attr = ListByAddress.end();
    }
}

/*-----------------------------------------------------------------------------------------------*/

bool      CIterator::AtEnd                          ( void ) const
{
    return (this->attr == this->ListByAddress.end()) ? true : false;
}

/*-----------------------------------------------------------------------------------------------*/

void      CIterator::Next                           ( void )
{
    this->attr++;
}

/*-----------------------------------------------------------------------------------------------*/

string    CIterator::City                           ( void ) const
{
    return this->attr->CityAddress.first;
}

/*-----------------------------------------------------------------------------------------------*/

string    CIterator::Addr                           ( void ) const
{
    return this->attr->CityAddress.second;
}

/*-----------------------------------------------------------------------------------------------*/

string    CIterator::Region                         ( void ) const
{
    return this->attr->RegionId.first;
}

/*-----------------------------------------------------------------------------------------------*/

unsigned  CIterator::ID                             ( void ) const
{
    return this->attr->RegionId.second;
}

/*-----------------------------------------------------------------------------------------------*/

string    CIterator::Owner                          ( void ) const
{
    return this->attr->Owner;
}

/*-----------------------------------------------------------------------------------------------*/

#ifndef __PROGTEST__
static void test0 ( void )
{
    CLandRegister x;
    string owner;

    assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( x . Add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
    assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
    CIterator i0 = x . ListByAddr ();
    assert ( ! i0 . AtEnd ()
            && i0 . City () == "Liberec"
            && i0 . Addr () == "Evropska"
            && i0 . Region () == "Librec"
            && i0 . ID () == 4552
            && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
            && i0 . City () == "Plzen"
            && i0 . Addr () == "Evropska"
            && i0 . Region () == "Plzen mesto"
            && i0 . ID () == 78901
            && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
            && i0 . City () == "Prague"
            && i0 . Addr () == "Evropska"
            && i0 . Region () == "Vokovice"
            && i0 . ID () == 12345
            && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
            && i0 . City () == "Prague"
            && i0 . Addr () == "Technicka"
            && i0 . Region () == "Dejvice"
            && i0 . ID () == 9873
            && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
            && i0 . City () == "Prague"
            && i0 . Addr () == "Thakurova"
            && i0 . Region () == "Dejvice"
            && i0 . ID () == 12345
            && i0 . Owner () == "" );
    i0 . Next ();
    assert ( i0 . AtEnd () );

    assert ( x . Count ( "" ) == 5 );
    CIterator i1 = x . ListByOwner ( "" );
    assert ( ! i1 . AtEnd ()
            && i1 . City () == "Prague"
            && i1 . Addr () == "Thakurova"
            && i1 . Region () == "Dejvice"
            && i1 . ID () == 12345
            && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
            && i1 . City () == "Prague"
            && i1 . Addr () == "Evropska"
            && i1 . Region () == "Vokovice"
            && i1 . ID () == 12345
            && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
            && i1 . City () == "Prague"
            && i1 . Addr () == "Technicka"
            && i1 . Region () == "Dejvice"
            && i1 . ID () == 9873
            && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
            && i1 . City () == "Plzen"
            && i1 . Addr () == "Evropska"
            && i1 . Region () == "Plzen mesto"
            && i1 . ID () == 78901
            && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
            && i1 . City () == "Liberec"
            && i1 . Addr () == "Evropska"
            && i1 . Region () == "Librec"
            && i1 . ID () == 4552
            && i1 . Owner () == "" );
    i1 . Next ();
    assert ( i1 . AtEnd () );

    assert ( x . Count ( "CVUT" ) == 0 );
    CIterator i2 = x . ListByOwner ( "CVUT" );
    assert ( i2 . AtEnd () );

    assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( x . NewOwner ( "Dejvice", 9873, "CVUT" ) );
    assert ( x . NewOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
    assert ( x . NewOwner ( "Librec", 4552, "Cvut" ) );
    assert ( x . GetOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Prague", "Evropska", owner ) && owner == "" );
    assert ( x . GetOwner ( "Vokovice", 12345, owner ) && owner == "" );
    assert ( x . GetOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
    assert ( x . GetOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
    assert ( x . GetOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
    assert ( x . GetOwner ( "Librec", 4552, owner ) && owner == "Cvut" );
    CIterator i3 = x . ListByAddr ();
     assert ( ! i3 . AtEnd ()
     && i3 . City () == "Liberec"
     && i3 . Addr () == "Evropska"
     && i3 . Region () == "Librec"
     && i3 . ID () == 4552
     && i3 . Owner () == "Cvut" );
     i3 . Next ();
     assert ( ! i3 . AtEnd ()
     && i3 . City () == "Plzen"
     && i3 . Addr () == "Evropska"
     && i3 . Region () == "Plzen mesto"
     && i3 . ID () == 78901
     && i3 . Owner () == "Anton Hrabis" );
     i3 . Next ();
     assert ( ! i3 . AtEnd ()
     && i3 . City () == "Prague"
     && i3 . Addr () == "Evropska"
     && i3 . Region () == "Vokovice"
     && i3 . ID () == 12345
     && i3 . Owner () == "" );
     i3 . Next ();
     assert ( ! i3 . AtEnd ()
     && i3 . City () == "Prague"
     && i3 . Addr () == "Technicka"
     && i3 . Region () == "Dejvice"
     && i3 . ID () == 9873
     && i3 . Owner () == "CVUT" );
     i3 . Next ();
     assert ( ! i3 . AtEnd ()
     && i3 . City () == "Prague"
     && i3 . Addr () == "Thakurova"
     && i3 . Region () == "Dejvice"
     && i3 . ID () == 12345
     && i3 . Owner () == "CVUT" );
     i3 . Next ();
     assert ( i3 . AtEnd () );

       assert ( x . Count ( "cvut" ) == 3 );
     CIterator i4 = x . ListByOwner ( "cVuT" );
     assert ( ! i4 . AtEnd ()
     && i4 . City () == "Prague"
     && i4 . Addr () == "Thakurova"
     && i4 . Region () == "Dejvice"
     && i4 . ID () == 12345
     && i4 . Owner () == "CVUT" );
     i4 . Next ();
     assert ( ! i4 . AtEnd ()
     && i4 . City () == "Prague"
     && i4 . Addr () == "Technicka"
     && i4 . Region () == "Dejvice"
     && i4 . ID () == 9873
     && i4 . Owner () == "CVUT" );
     i4 . Next ();
     assert ( ! i4 . AtEnd ()
     && i4 . City () == "Liberec"
     && i4 . Addr () == "Evropska"
     && i4 . Region () == "Librec"
     && i4 . ID () == 4552
     && i4 . Owner () == "Cvut" );
     i4 . Next ();
     assert ( i4 . AtEnd () );

     assert ( x . NewOwner ( "Plzen mesto", 78901, "CVut" ) );
     assert ( x . Count ( "CVUT" ) == 4 );
     CIterator i5 = x . ListByOwner ( "CVUT" );
     assert ( ! i5 . AtEnd ()
     && i5 . City () == "Prague"
     && i5 . Addr () == "Thakurova"
     && i5 . Region () == "Dejvice"
     && i5 . ID () == 12345
     && i5 . Owner () == "CVUT" );
     i5 . Next ();
     assert ( ! i5 . AtEnd ()
     && i5 . City () == "Prague"
     && i5 . Addr () == "Technicka"
     && i5 . Region () == "Dejvice"
     && i5 . ID () == 9873
     && i5 . Owner () == "CVUT" );
     i5 . Next ();
     assert ( ! i5 . AtEnd ()
     && i5 . City () == "Liberec"
     && i5 . Addr () == "Evropska"
     && i5 . Region () == "Librec"
     && i5 . ID () == 4552
     && i5 . Owner () == "Cvut" );
     i5 . Next ();
     assert ( ! i5 . AtEnd ()
     && i5 . City () == "Plzen"
     && i5 . Addr () == "Evropska"
     && i5 . Region () == "Plzen mesto"
     && i5 . ID () == 78901
     && i5 . Owner () == "CVut" );
     i5 . Next ();
     assert ( i5 . AtEnd () );

     assert ( x . Del ( "Liberec", "Evropska" ) );
     assert ( x . Del ( "Plzen mesto", 78901 ) );
     assert ( x . Count ( "cvut" ) == 2 );
     CIterator i6 = x . ListByOwner ( "cVuT" );
     assert ( ! i6 . AtEnd ()
     && i6 . City () == "Prague"
     && i6 . Addr () == "Thakurova"
     && i6 . Region () == "Dejvice"
     && i6 . ID () == 12345
     && i6 . Owner () == "CVUT" );
     i6 . Next ();
     assert ( ! i6 . AtEnd ()
     && i6 . City () == "Prague"
     && i6 . Addr () == "Technicka"
     && i6 . Region () == "Dejvice"
     && i6 . ID () == 9873
     && i6 . Owner () == "CVUT" );
     i6 . Next ();
     assert ( i6 . AtEnd () );

     assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
}

 static void test1 ( void )
 {
 CLandRegister x;
 string owner;

 assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
 assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
 assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
 assert ( ! x . Add ( "Prague", "Technicka", "Hradcany", 7344 ) );
 assert ( ! x . Add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
 assert ( !x . GetOwner ( "Prague", "THAKUROVA", owner ) );
 assert ( !x . GetOwner ( "Hradcany", 7343, owner ) );
 CIterator i0 = x . ListByAddr ();
 assert ( ! i0 . AtEnd ()
 && i0 . City () == "Prague"
 && i0 . Addr () == "Evropska"
 && i0 . Region () == "Vokovice"
 && i0 . ID () == 12345
 && i0 . Owner () == "" );
 i0 . Next ();
 assert ( ! i0 . AtEnd ()
 && i0 . City () == "Prague"
 && i0 . Addr () == "Technicka"
 && i0 . Region () == "Dejvice"
 && i0 . ID () == 9873
 && i0 . Owner () == "" );
 i0 . Next ();
 assert ( ! i0 . AtEnd ()
 && i0 . City () == "Prague"
 && i0 . Addr () == "Thakurova"
 && i0 . Region () == "Dejvice"
 && i0 . ID () == 12345
 && i0 . Owner () == "" );
 i0 . Next ();
 assert ( i0 . AtEnd () );

 assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
 assert ( ! x . NewOwner ( "Prague", "technicka", "CVUT" ) );
 assert ( ! x . NewOwner ( "prague", "Technicka", "CVUT" ) );
 assert ( ! x . NewOwner ( "dejvice", 9873, "CVUT" ) );
 assert ( ! x . NewOwner ( "Dejvice", 9973, "CVUT" ) );
 assert ( ! x . NewOwner ( "Dejvice", 12345, "CVUT" ) );
 assert ( x . Count ( "CVUT" ) == 1 );
 CIterator i1 = x . ListByOwner ( "CVUT" );
 assert ( ! i1 . AtEnd ()
 && i1 . City () == "Prague"
 && i1 . Addr () == "Thakurova"
 && i1 . Region () == "Dejvice"
 && i1 . ID () == 12345
 && i1 . Owner () == "CVUT" );
 i1 . Next ();
 assert ( i1 . AtEnd () );

 assert ( ! x . Del ( "Brno", "Technicka" ) );
 assert ( ! x . Del ( "Karlin", 9873 ) );
 assert ( x . Del ( "Prague", "Technicka" ) );
 assert ( ! x . Del ( "Prague", "Technicka" ) );
 assert ( ! x . Del ( "Dejvice", 9873 ) );
 }

int main ( void )
{
    test0();
    test1();
    return 0;
}
#endif /* __PROGTEST__ */
