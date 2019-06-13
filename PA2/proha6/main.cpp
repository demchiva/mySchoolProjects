#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */

bool LastH = true;
bool LastC = true;
bool Net = false;

class Object
{
public:
    friend ostream & operator << (ostream & os, const Object & n)
    {
        return n.Print(os);
    }
    virtual ostream & Print (ostream & os) const = 0;
};

class CCPU : public Object // GOOD
{
public:
    CCPU(int Kernels, int Frequency) : m_kernels(Kernels), m_frequency(Frequency) {}

    CCPU(const CCPU & src) : m_kernels(src.m_kernels), m_frequency(src.m_frequency) {}

    CCPU operator = (const CCPU & other)
    {
        m_kernels = other.m_kernels;
        m_frequency = other.m_frequency;
        return *this;
    }

    virtual ostream & Print (ostream & os ) const override
    {
        return os << "CPU, " << m_kernels << " cores @ " << m_frequency << "MHz" << endl;
    }

private:
    int m_kernels;
    int m_frequency;
};

class CMemory : public Object // GOOD
{
public:
    CMemory(int Size): m_size(Size) {}

    CMemory(const CMemory & src) { m_size = src.m_size; }

    CMemory operator = (const CMemory & other) { m_size = other.m_size; return *this; }

    virtual ostream & Print (ostream & os ) const override
    {
        return os << "Memory, " << m_size << " MiB" << endl;
    }

private:
    int m_size;
};

class CDisk : public Object // TODO rewrite Print function operator
{
public:

    enum TYPE
    {
        MAGNETIC,
        SSD
    };

    CDisk(TYPE type, int Size): m_type(type), m_size(Size) {}

    CDisk & AddPartition(int Size, string Path)
    {
        Parcel.push_back(make_pair(Size, Path));
        return *this;
    }

    CDisk(const CDisk & src)
    {
        m_type = src.m_type;
        m_size = src.m_size;

        for(auto i : src.Parcel)
        {
            Parcel.push_back(i);
        }
    }

    CDisk operator = (const CDisk & other)
    {
        Parcel.clear();
        m_size = other.m_size;
        m_type = other.m_type;

        for(auto i : other.Parcel)
        {
            Parcel.push_back(i);
        }

        return *this;
    }

    virtual ostream & Print(ostream & os) const override
    {
        string type = "";
        if ( m_type == SSD )
        {
            type = "SSD";
        }
        else
        {
            type = "HDD";
        }

        os << type << ", " << m_size << " GiB" << endl;

        unsigned int Check = 0;

        for( auto i : Parcel )
        {

            if ( Net )
            {
                if ( LastH )
                {
                    os << "  ";
                }
                else
                {
                    os << "| ";
                }
            }

            if ( LastC )
            {
                os << "  ";
            }
            else
            {
                os << "| ";
            }

            if ( Parcel.size() - 1 != Check )
            {
                os << "+-";
            }
            else
            {
                os << "\\-";
            }

            os << "[" << Check++ << "]: " << i.first << " GiB, " << i.second << endl;
        }
        return os;
    }

private:
    TYPE m_type;
    int m_size;
    vector<pair<int, string>> Parcel;
};

class CComputer
{
public:
    CComputer(string Name) : m_name(Name) {}

    CComputer & AddComponent(const CCPU & x)
    {
        cpu.push_back(x);
        control.push_back(CPU);
        return *this;
    }

    CComputer & AddComponent(const CMemory & x)
    {
        memory.push_back(x);
        control.push_back(MEMORY);
        return *this;
    }

    CComputer & AddComponent(const CDisk & x)
    {
        disk.push_back(x);
        control.push_back(DISK);
        return *this;
    }

    CComputer(const CComputer & src) : m_name(src.m_name)
    {
        for(auto i : src.m_adsress)
        {
            m_adsress.push_back(i);
        }

        for(auto i : src.disk)
        {
            disk.push_back(i);
        }

        for(auto i : src.cpu)
        {
            cpu.push_back(i);
        }

        for(auto i : src.memory)
        {
            memory.push_back(i);
        }

        for(auto i : src.control)
        {
            control.push_back(i);
        }
    }

    CComputer & operator = (const CComputer & src)
    {
        m_name = src.m_name;

        for(auto i : src.m_adsress)
        {
            m_adsress.push_back(i);
        }

        for(auto i : src.disk)
        {
            disk.push_back(i);
        }

        for(auto i : src.cpu)
        {
            cpu.push_back(i);
        }

        for(auto i : src.memory)
        {
            memory.push_back(i);
        }

        for(auto i : src.control)
        {
            control.push_back(i);
        }

        return *this;
    }

    CComputer & AddAddress(const string & Ad)
    {
        m_adsress.push_back(Ad);
        return *this;
    }

    friend ostream & operator << (ostream & os, const CComputer & CC)
    {
        os << "Host: " << CC.m_name << endl;
        for(auto i : CC.m_adsress)
        {
            if ( Net )
            {
                if ( LastH )
                {
                    os << "  ";
                }
                else
                {
                    os << "| ";
                }
            }

            if ( CC.control.size() > 0 )
            {
                os << "+-" << i << endl;
            }
            else
            {
                os << "\\-" << i << endl;
            }

        }

        int attr = 0; // memory
        int pttr = 0; // cpu
        int kttr = 0; // disk
        unsigned int Check = 0;
        LastC = false;

        for(auto i : CC.control)
        {

            if ( Net )
            {
                if ( LastH )
                {
                    os << "  ";
                }
                else
                {
                    os << "| ";
                }
            }

            if ( CC.control.size() - 1 == Check )
            {
                os << "\\-";
                LastC = true;
            }
            else
            {
                os << "+-";
            }

            Check++;

            if(i == MEMORY)
            {
                os << CC.memory[attr++];
            }

            if(i == CPU)
            {
                os << CC.cpu[pttr++];
            }

            if(i == DISK)
            {
                os << CC.disk[kttr++];
            }
        }
        LastC = false;

        return os;
    }

    string GetName() const { return m_name; }

private:

    enum TypeOfVec
    {
        DISK,
        MEMORY,
        CPU
    };

    string m_name;
    vector<CDisk> disk;
    vector<CMemory> memory;
    vector<CCPU> cpu;
    vector<string> m_adsress;
    vector<TypeOfVec> control;
};

class CNetwork
{
public:
    CNetwork(const string Name) : m_name(Name) {}

    CNetwork(const CNetwork & src)
    {
        m_name = src.m_name;

        for(auto i : src.CompInNetwork)
        {
            CompInNetwork.push_back(i);
        }
    }

    CNetwork & operator = (const CNetwork & src)
    {
        m_name = src.m_name;
        CompInNetwork.clear();

        for(auto i : src.CompInNetwork)
        {
            CompInNetwork.push_back(i);
        }

        return *this;
    }

    CNetwork & AddComputer(const CComputer & CC)
    {
        CComputer a(CC);
        CompInNetwork.push_back(CC);
        return *this;
    }

    CComputer * FindComputer(const string NameOfComp)
    {
        for(auto & i : CompInNetwork)
        {
            if( i.GetName() == NameOfComp )
            {
                return (&i);
            }
        }

        return nullptr;
    }

    friend ostream & operator << (ostream & os, const CNetwork & net)
    {
        os << "Network: " << net.m_name << endl;

        Net = true;
        LastH = false;
        unsigned int Check = 0;

        for(auto i : net.CompInNetwork)
        {
            if(Check != net.CompInNetwork.size() - 1)
            {
                os << "+-";
            }
            else
            {
                LastH = true;
                os << "\\-";
            }

            Check++;
            os << i;
        }

        Net = false;
        return os;
    }
private:
    string m_name;
    vector<CComputer> CompInNetwork;
};

#ifndef __PROGTEST__
template<typename _T>
string toString ( const _T & x )
{
    ostringstream oss;
    oss << x;
//    cout << x;
    return oss . str ();
}

int main ( void )
{
    CNetwork n ( "FIT network" );
    n . AddComputer (
                     CComputer ( "progtest.fit.cvut.cz" ) .
                     AddAddress ( "147.32.232.142" ) .
                     AddComponent ( CCPU ( 8, 2400 ) ) .
                     AddComponent ( CCPU ( 8, 1200 ) ) .
                     AddComponent ( CDisk ( CDisk::MAGNETIC, 1500 ) .
                                   AddPartition ( 50, "/" ) .
                                   AddPartition ( 5, "/boot" ).
                                   AddPartition ( 1000, "/var" ) ) .
                     AddComponent ( CDisk ( CDisk::SSD, 60 ) .
                                   AddPartition ( 60, "/data" )  ) .
                     AddComponent ( CMemory ( 2000 ) ).
                     AddComponent ( CMemory ( 2000 ) ) ) .
    AddComputer (
                 CComputer ( "edux.fit.cvut.cz" ) .
                 AddAddress ( "147.32.232.158" ) .
                 AddComponent ( CCPU ( 4, 1600 ) ) .
                 AddComponent ( CMemory ( 4000 ) ).
                 AddComponent ( CDisk ( CDisk::MAGNETIC, 2000 ) .
                               AddPartition ( 100, "/" )   .
                               AddPartition ( 1900, "/data" ) ) ) .
    AddComputer (
                 CComputer ( "imap.fit.cvut.cz" ) .
                 AddAddress ( "147.32.232.238" ) .
                 AddComponent ( CCPU ( 4, 2500 ) ) .
                 AddAddress ( "2001:718:2:2901::238" ) .
                 AddComponent ( CMemory ( 8000 ) ) );

    assert ( toString ( n ) ==
            "Network: FIT network\n"
            "+-Host: progtest.fit.cvut.cz\n"
            "| +-147.32.232.142\n"
            "| +-CPU, 8 cores @ 2400MHz\n"
            "| +-CPU, 8 cores @ 1200MHz\n"
            "| +-HDD, 1500 GiB\n"
            "| | +-[0]: 50 GiB, /\n"
            "| | +-[1]: 5 GiB, /boot\n"
            "| | \\-[2]: 1000 GiB, /var\n"
            "| +-SSD, 60 GiB\n"
            "| | \\-[0]: 60 GiB, /data\n"
            "| +-Memory, 2000 MiB\n"
            "| \\-Memory, 2000 MiB\n"
            "+-Host: edux.fit.cvut.cz\n"
            "| +-147.32.232.158\n"
            "| +-CPU, 4 cores @ 1600MHz\n"
            "| +-Memory, 4000 MiB\n"
            "| \\-HDD, 2000 GiB\n"
            "|   +-[0]: 100 GiB, /\n"
            "|   \\-[1]: 1900 GiB, /data\n"
            "\\-Host: imap.fit.cvut.cz\n"
            "  +-147.32.232.238\n"
            "  +-2001:718:2:2901::238\n"
            "  +-CPU, 4 cores @ 2500MHz\n"
            "  \\-Memory, 8000 MiB\n" );
    CNetwork x = n;
    auto c = x . FindComputer ( "imap.fit.cvut.cz" );
    assert ( toString ( *c ) ==
            "Host: imap.fit.cvut.cz\n"
            "+-147.32.232.238\n"
            "+-2001:718:2:2901::238\n"
            "+-CPU, 4 cores @ 2500MHz\n"
            "\\-Memory, 8000 MiB\n" );
    c -> AddComponent ( CDisk ( CDisk::MAGNETIC, 1000 ) .
                       AddPartition ( 100, "system" ) .
                       AddPartition ( 200, "WWW" ) .
                       AddPartition ( 700, "mail" ) );
    assert ( toString ( x ) ==
            "Network: FIT network\n"
            "+-Host: progtest.fit.cvut.cz\n"
            "| +-147.32.232.142\n"
            "| +-CPU, 8 cores @ 2400MHz\n"
            "| +-CPU, 8 cores @ 1200MHz\n"
            "| +-HDD, 1500 GiB\n"
            "| | +-[0]: 50 GiB, /\n"
            "| | +-[1]: 5 GiB, /boot\n"
            "| | \\-[2]: 1000 GiB, /var\n"
            "| +-SSD, 60 GiB\n"
            "| | \\-[0]: 60 GiB, /data\n"
            "| +-Memory, 2000 MiB\n"
            "| \\-Memory, 2000 MiB\n"
            "+-Host: edux.fit.cvut.cz\n"
            "| +-147.32.232.158\n"
            "| +-CPU, 4 cores @ 1600MHz\n"
            "| +-Memory, 4000 MiB\n"
            "| \\-HDD, 2000 GiB\n"
            "|   +-[0]: 100 GiB, /\n"
            "|   \\-[1]: 1900 GiB, /data\n"
            "\\-Host: imap.fit.cvut.cz\n"
            "  +-147.32.232.238\n"
            "  +-2001:718:2:2901::238\n"
            "  +-CPU, 4 cores @ 2500MHz\n"
            "  +-Memory, 8000 MiB\n"
            "  \\-HDD, 1000 GiB\n"
            "    +-[0]: 100 GiB, system\n"
            "    +-[1]: 200 GiB, WWW\n"
            "    \\-[2]: 700 GiB, mail\n" );
    assert ( toString ( n ) ==
            "Network: FIT network\n"
            "+-Host: progtest.fit.cvut.cz\n"
            "| +-147.32.232.142\n"
            "| +-CPU, 8 cores @ 2400MHz\n"
            "| +-CPU, 8 cores @ 1200MHz\n"
            "| +-HDD, 1500 GiB\n"
            "| | +-[0]: 50 GiB, /\n"
            "| | +-[1]: 5 GiB, /boot\n"
            "| | \\-[2]: 1000 GiB, /var\n"
            "| +-SSD, 60 GiB\n"
            "| | \\-[0]: 60 GiB, /data\n"
            "| +-Memory, 2000 MiB\n"
            "| \\-Memory, 2000 MiB\n"
            "+-Host: edux.fit.cvut.cz\n"
            "| +-147.32.232.158\n"
            "| +-CPU, 4 cores @ 1600MHz\n"
            "| +-Memory, 4000 MiB\n"
            "| \\-HDD, 2000 GiB\n"
            "|   +-[0]: 100 GiB, /\n"
            "|   \\-[1]: 1900 GiB, /data\n"
            "\\-Host: imap.fit.cvut.cz\n"
            "  +-147.32.232.238\n"
            "  +-2001:718:2:2901::238\n"
            "  +-CPU, 4 cores @ 2500MHz\n"
            "  \\-Memory, 8000 MiB\n" );
    return 0;
}
#endif /* __PROGTEST__ */
