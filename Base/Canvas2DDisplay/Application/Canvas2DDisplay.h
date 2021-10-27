/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DataAIOStream.h
*
* @class      CANVAS2DDISPLAY
* @brief      Data I/O stream UART / USB MICROCONTROLLER example class
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _CANVAS2DDISPLAY_H_
#define _CANVAS2DDISPLAY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "APPBase.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define CANVAS2DDISPLAY_VERSION            0
#define CANVAS2DDISPLAY_SUBVERSION         1
#define CANVAS2DDISPLAY_SUBVERSIONERR      0
#define CANVAS2DDISPLAY_NAMEAPP            __L("TestMicro")


#ifdef HW_PC

  #define SCREEN_GRP_RESET              DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_RESET              0

  #define SCREEN_GRP_DC                 DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_DC                 1

  #define SCREEN_GRP_SPI_CS             DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_SPI_CS             5

  #define SCREEN_GRP_SPI_MOSI           DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_SPI_MOSI           2

  #define SCREEN_GRP_SPI_MISO           DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_SPI_MISO           3

  #define SCREEN_GRP_SPI_CLK            DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_SPI_CLK            4

#endif



#if HW_RASPBERRYPI

  #define SCREEN_GRP_RESET              DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_RESET              31

  #define SCREEN_GRP_DC                 DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_DC                 29

#endif




#ifdef STM32F072xB

  #define SCREEN_GRP_RESET              DIOGPIO_PINSGROUP_B
  #define SCREEN_PIN_RESET              9

  #define SCREEN_GRP_DC                 DIOGPIO_PINSGROUP_A
  #define SCREEN_PIN_DC                 8

#endif



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAM;
class MAIN;

class CANVAS2DDISPLAY : public APPBASE
{
  public:
                        CANVAS2DDISPLAY                     ();
    virtual            ~CANVAS2DDISPLAY                     ();

    bool                AppProc_Ini                         ();
    bool                AppProc_FirstUpdate                 ();
    bool                AppProc_Update                      ();
    bool                AppProc_End                         ();

    bool                Test_DIOStreamI2C                   ();
    bool                Test_DIOStreamSPI                   ();

  private:

    void                Clean                               ();

};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/


#endif



