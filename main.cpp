
#include <iostream>
#include "serial.h"
#include "ThinkGearStreamParser.h"

using namespace std;
using namespace boost;

void
handleDataValueFunc( unsigned char extendedCodeLevel,
                     unsigned char code,
                     unsigned char valueLength,
                     const unsigned char *value,
                     void *customData )
{
    if ( extendedCodeLevel == 0 )
    {
        switch ( code )
        {
        /* [CODE]: ATTENTION eSense */
        case (PARSER_CODE_ATTENTION):
            printf( "Attention Level: %d\n", value[0] & 0xFF );
            break;
        /* [CODE]: MEDITATION eSense */
        case (PARSER_CODE_MEDITATION):
            printf( "Meditation Level: %d\n", value[0] & 0xFF );
            break;
        /* Other [CODE]s */
        default:
            printf( "EXCODE level: %d CODE: 0x%02X vLength: %d\n",
                    extendedCodeLevel, code, valueLength );
            printf( "Data value(s):" );
            for (int i = 0; i < valueLength; i++ ) printf( " %02X", value[i] & 0xFF );
            printf( "\n" );
        }
    }
}

int main(int argc, char *argv[])
{
    SerialPort mindset("/dev/tty.MindWaveMobile-DevA", 57600);
    ThinkGearStreamParser parser;
    THINKGEAR_initParser( &parser, PARSER_TYPE_PACKETS,
                          handleDataValueFunc, NULL );
    while (true)
    {
        try
        {
            unsigned char byte = mindset.readByte();
            THINKGEAR_parseByte(&parser, byte);
        }
        catch (boost::system::system_error &e)
        {
            cout << "Error: " << e.what() << endl;
            return 1;
        }
    }
}

