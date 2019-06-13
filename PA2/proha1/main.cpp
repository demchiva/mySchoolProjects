#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;

#endif /* __PROGTEST__ */

#define OneChanel 0x0000
#define TwoChanel 0x0002
#define TreeChanel 0x0003
#define ItIs16 0x0004
#define ItIs8 0x0003

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

class Image
{
public:
    template <typename T>
    static void VerticalReflection(vector<vector<vector<T>>> & Array)
    {
        for(unsigned int i = 0; i < Array.size() / 2; i++)
        {
            vector<vector<T>> tmp = Array[i];
            Array[i] = Array[Array.size() - i - 1];
            Array[Array.size() - i - 1] = tmp;
        }
    }

     static int WhatsEndian(uint16_t tmp)
    {
        if(tmp == ENDIAN_LITTLE)
        {
            return 1;
        }
        else if(tmp == ENDIAN_BIG)
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

     static bool ItEOF(ifstream & source)
    {
        char b;
        if(source.read((char *)&b, sizeof(char)))
        {
            return false;
        }

        return true;
    }

     template <typename T>
    static bool readBit(int NumOfChan, uint16_t RangeOfHight, vector<vector<vector<T>>> & Array,
                        uint16_t RangeOfWidth, ifstream & src)
    {
        T a;
        for(uint16_t i = 0; i < RangeOfHight; i++)
        {
            vector<vector<T>> FirstVec;
            for(uint16_t j = 0; j < RangeOfWidth; j++)
            {
                vector<T> SecondVec;
                for(int z = 0; z < NumOfChan; z++) // как работает считывание этих каналов
                {
                    if(!src.read((char *)&a, sizeof(T)))
                    {
                        return false;
                    }

                    SecondVec.push_back(a);
                }
                FirstVec.push_back(SecondVec);

            }
            Array.push_back(FirstVec);
        }

        if(!ItEOF(src))
        {
            return false;
        }

        return true;
    }

    static bool TopRead(ifstream & source, vector<uint16_t> & top)
    {
        uint16_t a = 0;

        if(!source.read((char *) &a, sizeof(uint16_t)))
        {
            return false;
        }
        top.push_back(a);

        if(!source.read((char *) &a, sizeof(uint16_t)))
        {
            return false;
        }
        top.push_back(a);

        if(!source.read((char *) &a, sizeof(uint16_t)))
        {
            return false;
        }
        top.push_back(a);

        if(!source.read((char *) &a, sizeof(uint16_t)))
        {
            return false;
        }
        top.push_back(a);

        return true;
    }

    template <typename T>
    static void HorizontalReflection(vector<vector<vector<T>>> & Array)
    {
        for(unsigned int i = 0; i < Array.size(); i++)
        {
            for(unsigned int j = 0; j < Array[i].size() / 2; j++)
            {
                vector<T> tmp = Array[i][j];
                Array[i][j] = Array[i][Array[i].size() - j - 1];
                Array[i][Array[i].size() - j - 1] = tmp;
            }
        }
    }

    template <typename T>
    static bool writeImgbit(int NumOfChan, vector<uint16_t> head, uint16_t RangeOfHight, vector<vector<vector<T>>> & Array,
                        uint16_t RangeOfWidth, ofstream & destination)
    {
        WriteTop(head, destination);
        for(uint16_t i = 0; i < RangeOfHight; i++)
        {
            for(uint16_t j = 0; j < RangeOfWidth; j++)
            {
                for(int k = 0; k < NumOfChan; k++)
                {
                    if(!destination.write((char *)&Array[i][j][k],sizeof(T)))
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    static bool WriteTop(vector<uint16_t> top, ofstream & destination)
    {
         for(int i = 0; i <= 3; i++)
        {
            if(!destination.write((char *)&top[i], sizeof(uint16_t)))
            {
                return false;
            }
        }

        return true;
    }

    static bool CountOfChanel(uint16_t tmp, int & numberOfChannels)
    {

        if(tmp != OneChanel && tmp != TwoChanel && tmp != TreeChanel)
        {
            return false;
        }

        if(tmp == OneChanel)
        {
            numberOfChannels = 1;
        }

        if (tmp == TwoChanel)
        {
            numberOfChannels = 3;
        }

        if(tmp == TreeChanel)
        {
            numberOfChannels=4;
        }

        return true;
    }

    static bool CheckZero(uint16_t a)
    {
         a = a >> 5;

         if(a != 0x0000)
         {
            return false;
         }

         return true;
    }

    static void ChangeEndian(vector<uint16_t> Top, uint16_t & a)
    {
        a = Top[3];
        a = (a << 8) | (a >> 8);
    }
};

bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{
    ifstream source;
    uint16_t RangeOfWidth = 0;
    uint16_t tmp = 0x0000;
    ofstream destination;
    uint16_t RangeOfHidth = 0;
    vector <uint16_t> Top;
    int NumOfChan = 0;

    source.open(srcFileName, ios::binary);
    destination.open(dstFileName, ios::binary);

    if(!source.is_open() || !destination.is_open())
    {
        return false;
    }

    if(!Image::TopRead(source, Top))
    {
        return false;
    }

    uint16_t control = Top[0];

    if(Image::WhatsEndian(control) == 3)
    {
        return false;
    }

    if(Image::WhatsEndian(control) == 1)
    {
        RangeOfWidth = Top[1];
        RangeOfHidth = Top[2];
    }

    if (Image::WhatsEndian(control) == 2)
    {
        RangeOfWidth = Top[1];
        RangeOfWidth = (RangeOfWidth << 8) | (RangeOfWidth >> 8);

        RangeOfHidth = Top[2];
        RangeOfHidth = (RangeOfHidth >> 8) | (RangeOfHidth << 8);
    }

    if(RangeOfHidth <= 0 || RangeOfWidth <= 0)
    {
        return false;
    }

    if(Image::WhatsEndian(control) == 1)
    {
        tmp = Top[3];
    }
    else
    {
        Image::ChangeEndian(Top, tmp);
    }

    Image::CheckZero(tmp);

    tmp=tmp << 14;
    tmp=tmp >> 14;

    if(!Image::CountOfChanel(tmp, NumOfChan))
    {
        return false;
    }

    if(Image::WhatsEndian(control) == 1)
    {
        tmp = Top[3];
    }
    else
    {
        Image::ChangeEndian(Top, tmp);
    }

    tmp = tmp >> 2;

    if(tmp != ItIs8 && tmp != ItIs16)
    {
        return false;
    }

    if(tmp == ItIs8 )
    {
        vector<vector<vector<uint8_t>>> pixels;
        if(!Image::readBit(NumOfChan, RangeOfHidth, pixels, RangeOfWidth, source))
        {
            return false;
        }
        if(flipVertical)
        {
            Image::VerticalReflection(pixels);
        }
        if(flipHorizontal)
        {
            Image::HorizontalReflection(pixels);
        }
        if(!Image::writeImgbit(NumOfChan, Top, RangeOfHidth, pixels, RangeOfWidth, destination))
        {
            return false;
        }
    }
    else if(tmp == ItIs16)
    {
        vector<vector<vector<uint16_t>>> pixels;
        if(!Image::readBit(NumOfChan, RangeOfHidth, pixels, RangeOfWidth, source))
        {
            return false;
        }
        if(flipVertical)
        {
            Image::VerticalReflection(pixels);
        }
        if(flipHorizontal)
        {
            Image::HorizontalReflection(pixels);
        }
        if(!Image::writeImgbit(NumOfChan, Top, RangeOfHidth, pixels, RangeOfWidth, destination))
        {
            return false;
        }
    }

    return true;
}

#ifndef __PROGTEST__

bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    ifstream firstFile ( fileName1, ios::in );
    ifstream secondFile ( fileName2, ios::in );

    char a, b;

    firstFile.seekg( 0, ios::end );
    secondFile.seekg( 0, ios::end );
    unsigned long size1 = firstFile.tellg(), size2 = secondFile.tellg();

    if ( size2 != size1 )
    {
        firstFile.close();
        secondFile.close();
        return false;
    }

    firstFile.seekg( 0, ios::beg );
    secondFile.seekg( 0, ios::beg );

    for ( unsigned int i = 0; i < size1; i ++ )
    {
        firstFile.read( &a, 1 );
        secondFile.read( &b, 1 );
        if ( a != b )
        {
            firstFile.close();
            secondFile.close();
            return false;
        }
    }

    firstFile.close();
    secondFile.close();
    return true;
}

int main ( void )
{
    assert ( flipImage ( "input_00.img", "output_00.img", true, false )
             && identicalFiles ( "output_00.img", "ref_00.img" ) );

    assert ( flipImage ( "input_01.img", "output_01.img", false, true )
             && identicalFiles ( "output_01.img", "ref_01.img" ) );

    assert ( flipImage ( "input_02.img", "output_02.img", true, true )
             && identicalFiles ( "output_02.img", "ref_02.img" ) );

    assert ( flipImage ( "input_03.img", "output_03.img", false, false )
             && identicalFiles ( "output_03.img", "ref_03.img" ) );

    assert ( flipImage ( "input_04.img", "output_04.img", true, false )
             && identicalFiles ( "output_04.img", "ref_04.img" ) );

    assert ( flipImage ( "input_05.img", "output_05.img", true, true )
             && identicalFiles ( "output_05.img", "ref_05.img" ) );

    assert ( flipImage ( "input_06.img", "output_06.img", false, true )
             && identicalFiles ( "output_06.img", "ref_06.img" ) );

    assert ( flipImage ( "input_07.img", "output_07.img", true, false )
             && identicalFiles ( "output_07.img", "ref_07.img" ) );

    assert ( flipImage ( "input_08.img", "output_08.img", true, true )
             && identicalFiles ( "output_08.img", "ref_08.img" ) );

    assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );
    /*
        // extra inputs (optional & bonus tests)
        assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
                && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
        assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
                && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
        assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
                && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
        assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
                && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
        assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
                && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
        assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
                && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
        assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
                && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
        assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
                && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
        assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
                && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
        assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
                && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
        assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
                && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
        assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
                && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
        */return 0;
}
#endif /* __PROGTEST__ */
