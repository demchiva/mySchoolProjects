#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

class InvalidIndexException
{
};

#endif /* __PROGTEST__ */

class TextString
{
public:
    char * text = nullptr;
    TextString(const char * input)
    {
        text = new char[sizeof(char)*strlen(input)];
        for(int i=0; i<strlen(input); i++)
        {
            text[i] = input[i];
        }
    }
    ~TextString()
    {
        if(text == nullptr)
        {
            //return;
        }
        else
        {
            delete[] text;
        }
    }

    bool operator == (const TextString & x) const
    {
        if(sizeof(this->text) != sizeof(x.text))
        {
            return false;
        }

        for(unsigned int i = 0; i < strlen(this->text); i++)
        {
            if(this->text[i] != x.text[i])
            {
                return false;
            }
        }

        return true;
    }
};
class MyString
{
public:
    MyString * next;
    MyString * previous;
    shared_ptr<TextString> text;
    int offset;
    int length;
};


class CPatchStr
{
public:
    MyString * first;
    MyString * last;
    int length;

    CPatchStr ( void )
    {
        length = 0;
        first = nullptr;
        last = nullptr;
    }

    CPatchStr ( const char * str )
    {
        MyString * mystr = new MyString;
        mystr->text = shared_ptr<TextString>(new TextString(str));
        first = mystr;
        last = mystr;
        mystr->next = nullptr;
        mystr->previous = nullptr;
        mystr->length = strlen(str);
        length = mystr -> length;
        mystr->offset = 0;
    }

    ~CPatchStr() // free list of MyString
    {
        while(this->first)
        {
            MyString * tmp = this->first->next;

            delete this->first->text;
            delete this->first;

            this->first = tmp;
        }
    }

    bool operator = (const CPatchStr & src)
    {

    }

    CPatchStr operator = (const char * src)
    {
        this->~CPatchStr();
        CPatchStr a(src);
        return a;
    }
   /* bool operator == (const CPatchStr & x) const
    {
        MyString * tmp1 = this->first;
        MyString * tmp2 = x.first;
        while(true)
        {
            if(tmp1 == nullptr && tmp2 == nullptr)
            {
                break;
            }

            if((tmp1 == nullptr && tmp2 != nullptr) || (tmp1 != nullptr && tmp2 == nullptr))
            {
                return false;
            }

            if(tmp1->next != tmp2->next || tmp1->previous != tmp2->previous || tmp1->offset != tmp2->offset || tmp1->length != tmp2->length || tmp1->text != tmp2->text)
            {
                return false;
            }
        }

        return true;
    }*/

    CPatchStr   SubStr    ( size_t from, size_t len ) const
    {
        if(from + len > (size_t)this->length)
        {
            throw InvalidIndexException();
        }

        if(len == 0)
        {
            return "";
        }

        int tmp_length = 0;
        int last_length = 0;
        int i = 0;
        char String[sizeof(char) * len + sizeof(char)];
        MyString * tmp = this->first;
        while(true)
        {
            int Count = 0;
            if(tmp == nullptr)
            {
                String[i] = '\0';
                break;
            }

            tmp_length += tmp->length;
            if(from <= tmp_length && from + len <= tmp_length)
            {
                int k = from - last_length;
                for(int j = 0; j < len; j++)
                {
                    String[i] = tmp->text->text[k];
                    i++;
                    k++;
                }
                String[i] = '\0';
                break;
            } else if(from <= tmp_length)
            {
                for(int j = from - last_length; j < tmp->length; j++)
                {
                    String[i] = tmp->text->text[j];
                    i++;
                    Count++;
                }

                len -= Count;
                from = tmp_length;
            }

            last_length += tmp->length;
            tmp = tmp->next;
        }

        return CPatchStr(String);
    }

    CPatchStr & Append    ( const CPatchStr & src )
    {
        if(src.first == nullptr)
        {
            return *this;
        }

        bool Check = false;
        CPatchStr Copy;

        if(&src == this)
        {
            Copy = src;
            Check = true;
        }

        MyString * tmp = nullptr;
        if(Check)
        {
            tmp = Copy.first;
        }
        else
        {
            tmp = src.first;
        }
        if(this->first == nullptr && src.first != nullptr)
        {
            MyString * mystr = new MyString;
            mystr->length = src.first->length;
            mystr->offset = src.first->offset;
            mystr->text = src.first->text;
            this->length = mystr->length;
            this->first = mystr;
            this->last = mystr;
            tmp = tmp->next;
        }
        while(true)
        {
            if(tmp == nullptr)
            {
                return *this;
            }
            else
            {
                MyString * mystr = new MyString;
                mystr->text = tmp->text;
                mystr->length = tmp->length;
                mystr->offset = tmp->offset;
                mystr->previous = this->last;
                mystr->next = nullptr;
                this->last->next = mystr;
                this->last = mystr;
                this->length += mystr->length;
            }
            tmp = tmp->next;
        }
    }

    CPatchStr & Insert    ( size_t            pos,
                            const CPatchStr & src );
    CPatchStr & Delete    ( size_t            from,
                            size_t            len );
    char      * ToStr     ( void ) const
    {
        MyString * strTmp = this->first;
        int count = 0;
        if(strTmp==nullptr)
            throw InvalidIndexException();
        char * tmp = new char[sizeof(char)*length+sizeof(char)];
        while(true)
        {
            if(strTmp == nullptr)
            {
                tmp[length] = '\0';
                return tmp;
            }
            else
            {
                for(int i = strTmp->offset; i < strTmp->offset+strTmp->length; i++)
                {
                    tmp[count++] = (strTmp->text).get()->text[i];
                }
            }
            strTmp = strTmp->next;
        }
    }
};

#ifndef __PROGTEST__
bool stringMatch ( char       * str,
                   const char * expected )
{
    bool res = strcmp ( str, expected ) == 0;
    delete [] str;
    return res;
}

int main ( void )
{
    char tmpStr[100];


    /* CPatchStr fuck("fuck");
     CPatchStr you("you");
     cout << fuck.ToStr() << endl;
     cout << you.ToStr() << endl;
     fuck.Append(you);
     cout << fuck.ToStr() << endl;
     CPatchStr aaaaaaaaaaaaaaaaaaa;
     aaaaaaaaaaaaaaaaaaa.Append(fuck);
     aaaaaaaaaaaaaaaaaaa.Append(you);
     cout << aaaaaaaaaaaaaaaaaaa.ToStr() << endl;*/
    CPatchStr a ( "test" );
    assert ( stringMatch ( a . ToStr (), "test" ) );
    strncpy ( tmpStr, " da", sizeof ( tmpStr ) );
    a . Append ( tmpStr );
    assert ( stringMatch ( a . ToStr (), "test da" ) );
    strncpy ( tmpStr, "ta", sizeof ( tmpStr ) );
    a . Append ( tmpStr );
    assert ( stringMatch ( a . ToStr (), "test data" ) );
    strncpy ( tmpStr, "foo text", sizeof ( tmpStr ) );
    CPatchStr b ( tmpStr );
    assert ( stringMatch ( b . ToStr (), "foo text" ) );
    CPatchStr c ( a );
    assert ( stringMatch ( c . ToStr (), "test data" ) );
    CPatchStr d ( a . SubStr ( 3, 5 ) );
    cout << d . ToStr () << endl;
    assert ( stringMatch ( d . ToStr (), "t dat" ) );
    d . Append ( b );
    assert ( stringMatch ( d . ToStr (), "t datfoo text" ) );
    d . Append ( b . SubStr ( 3, 4 ) );
    cout << d . ToStr () << "123" << endl;
    assert ( stringMatch ( d . ToStr (), "t datfoo text tex" ) );
    c . Append ( d );
    assert ( stringMatch ( c . ToStr (), "test datat datfoo text tex" ) );
    c . Append ( c );
    assert ( stringMatch ( c . ToStr (), "test datat datfoo text textest datat datfoo text tex" ) );
    /*d . Insert ( 2, c . SubStr ( 6, 9 ) );
    assert ( stringMatch ( d . ToStr (), "t atat datfdatfoo text tex" ) );
    b = "abcdefgh";
    assert ( stringMatch ( b . ToStr (), "abcdefgh" ) );
    assert ( stringMatch ( b . ToStr (), "abcdefgh" ) );
    assert ( stringMatch ( d . ToStr (), "t atat datfdatfoo text tex" ) );
    assert ( stringMatch ( d . SubStr ( 4, 8 ) . ToStr (), "at datfd" ) );
    assert ( stringMatch ( b . SubStr ( 2, 6 ) . ToStr (), "cdefgh" ) );*/
    try
    {
      b . SubStr ( 2, 7 ) . ToStr ();
      assert ( "Exception not thrown" == NULL );
    }
    catch ( InvalidIndexException & e )
    {
    }
    catch ( ... )
    {
      assert ( "Invalid exception thrown" == NULL );
    }
   /* a . Delete ( 3, 5 );
    assert ( stringMatch ( a . ToStr (), "tesa" ) );*/
    return 0;
}
#endif /* __PROGTEST__ */
