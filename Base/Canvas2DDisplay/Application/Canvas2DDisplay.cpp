/**-------------------------------------------------------------------------------------------------------------------
*
* @file       CANVAS2DDISPLAY.cpp
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XFactory.h"
#include "XSleep.h"
#include "XRand.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOGPIO.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStreamUART.h"
#include "DIOStreamUSBConfig.h"
#include "DIOStreamUSB.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"
#include "DIOStreamSPIConfig.h"
#include "DIOStreamSPI.h"
#include "DIOGPIO.h"

#include "Canvas2DDisplay.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(CANVAS2DDISPLAY, uart_usb)

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




//-------------------------------------------------------------------
//  CANVAS2DDISPLAY::CANVAS2DDISPLAY
/**
//
//
//  @author       Abraham J. Velez
//  @version      13/08/2002 13:15:15
//
//  @return
//  */
//-------------------------------------------------------------------
CANVAS2DDISPLAY::CANVAS2DDISPLAY()
{
  Clean();
}


//-------------------------------------------------------------------
//  CANVAS2DDISPLAY::~CANVAS2DDISPLAY
/**
//
//
//  @author       Abraham J. Velez
//  @version      13/08/2002 13:15:40
//
//  @return
//  */
//-------------------------------------------------------------------
CANVAS2DDISPLAY::~CANVAS2DDISPLAY()
{
  Clean();
}


//-------------------------------------------------------------------
//  CANVAS2DDISPLAY::AppProc_Ini
/**
//
//
//  @author       Abraham J. Velez
//  @version      13/08/2002 13:17:31
//
//  @return       bool :
//  */
//-------------------------------------------------------------------
bool CANVAS2DDISPLAY::AppProc_Ini()
{
  XSTRING string;

  string = CANVAS2DDISPLAY_NAMEAPP;
  XTRACE_SETAPPLICATIONNAME(string);
  XTRACE_SETAPPLICATIONVERSION(CANVAS2DDISPLAY_VERSION, CANVAS2DDISPLAY_SUBVERSION, CANVAS2DDISPLAY_SUBVERSIONERR);

  #ifdef MICROCONTROLLER
    XTRACE_SETTARGET(0, XTRACE_TYPE_SPECIAL , XTRACE_DEFAULT_SPECIALAIM);
  #else
    XTRACE_SETTARGET(0, XTRACE_TYPE_NET     , XTRACE_DEFAULT_NETAIM1);
  #endif

  XTRACE_PRINTCOLOR(1, __L("Start Application"));

  return true;
}



//-------------------------------------------------------------------
//  CANVAS2DDISPLAY::AppProc_FirstUpdate
/**
//
//  @author        Abraham J. Velez
//  @version       20/2/2003   16:26:12
//
//  @return        bool :
*/
//-------------------------------------------------------------------
bool CANVAS2DDISPLAY::AppProc_FirstUpdate()
{
  //Test_DIOStreamI2C();
  Test_DIOStreamSPI();

  return true;
}



//-------------------------------------------------------------------
//  CANVAS2DDISPLAY::AppProc_Update
/**
//
//
//  @author       Abraham J. Velez
//  @version      15/03/2004 16:53:03
//
//  @return       bool :
//  */
//-------------------------------------------------------------------
bool CANVAS2DDISPLAY::AppProc_Update()
{
  return true;
}




/*-------------------------------------------------------------------
//  CANVAS2DDISPLAY::AppProc_End
*/
/**
//
//
//  @author       Abraham J. Velez
//  @version      14/05/2012 19:02:07
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool CANVAS2DDISPLAY::AppProc_End()
{

  return true;
}



/*-------------------------------------------------------------------
//  CANVAS2DDISPLAY::Test_DIOStreamI2C
*/
/**
//
//
//
//  @author       Abraham J. Velez
//  @version      23/09/2016 9:42:03
//
//  @return       bool :
//
*/
/*-----------------------------------------------------------------*/
bool CANVAS2DDISPLAY::Test_DIOStreamI2C()
{
  //----------------------------------------------------------------------------

  /*
  DIOI2COLEDSCREENSSD1306* screenOLEDSSD1306 = new DIOI2COLEDSCREENSSD1306();
  if(!screenOLEDSSD1306) return false;

  if(screenOLEDSSD1306->Ini(1, 0x78, 10))
    {
      XTRACE_PRINTCOLOR(2, __L("Connect I2C device... Ok!"));

      screenOLEDSSD1306->End();

    } else XTRACE_PRINTCOLOR(2,__L("Error to connect I2C device..."));

  */

  //----------------------------------------------------------------------------

  return true;
}



/*-------------------------------------------------------------------
//  CANVAS2DDISPLAY::Test_DIOStreamSPI
*/
/**
//
//
//
//  @author       Abraham J. Velez
//  @version      28/10/2016 8:35:41
//
//  @return       bool :
//
*/
/*-----------------------------------------------------------------*/
bool CANVAS2DDISPLAY::Test_DIOStreamSPI()
{
  bool status = false;

  /*
  //----------------------------------------------------------------------------

  DIOGPIO* diogpio = GEN_DIOFACTORY.CreateGPIO();
  if(diogpio)
    {
      if(diogpio->Ini())
        {
          DIOSPILCDSCREENPCF8833* lcdscreen = new DIOSPILCDSCREENPCF8833();
          if(lcdscreen)
            {
              lcdscreen->SetDIOGPIO(diogpio);
              lcdscreen->SetResetPinsGroup(DIOGPIO_PINSGROUP_A);
              lcdscreen->SetResetPin(TEST_PINLCD_RESET);

              status  = lcdscreen->Ini(1, 0, 10);
              XTRACE_PRINTCOLOR(1, __L("Send screen INI   : %s "), status?__L("Ok!"):__L("Error!"));
              if(status)
                {

                  //status = lcdscreen->Clear(DIOSPILCDSCREENPHILIPSPCF8833_RED);
                  //XDEBUG_PRINTCOLOR(1, __L("Send screen Clean : %s "), status?__L("Ok!"):__L("Error!"));

                  //GEN_XSLEEP.Seconds(1);
                  if(status)
                    {
                      //status = lcdscreen->Clear(DIOSPILCDSCREENPHILIPSPCF8833_GREEN);
                      //XDEBUG_PRINTCOLOR(1, __L("Send screen Clean : %s "), status?__L("Ok!"):__L("Error!"));

                      //GEN_XSLEEP.Seconds(1);

                      if(status)
                        {
                          //status = lcdscreen->Clear(DIOSPILCDSCREENPHILIPSPCF8833_BLUE);
                          //XDEBUG_PRINTCOLOR(1, __L("Send screen Clean : %s "), status?__L("Ok!"):__L("Error!"));

                          //GEN_XSLEEP.Seconds(1);
                          XRAND*  rnd = GEN_XFACTORY.CreateRand();
                          if(rnd)
                            {
                              for(int y=0; y< lcdscreen->GetHeight(); y++)
                                {
                                  for(int x=0; x< lcdscreen->GetWidth(); x++)
                                    {
                                       lcdscreen->PutPixel(x , y, rnd->Between(0,65535));
                                    }
                                }

                               GEN_XFACTORY.DeleteRand(rnd);
                            }



                          XWORD*  buffer = NULL;
                          XRAND*  rnd = GEN_XFACTORY.CreateRand();

                          if(rnd)
                            {
                              XDEBUG_PRINTCOLOR(1, __L("Create Random..."));

                              buffer = new XWORD[lcdscreen->GetNPixels()];
                              if(buffer)
                                {
                                  XDEBUG_PRINTCOLOR(1, __L("Create Buffer Random..."));

                                  int nframes = 0;

                                  while(nframes<100)
                                    {
                                      for(XDWORD c=0; c<lcdscreen->GetNPixels(); c++)
                                        {
                                          buffer[c] = 23; //rnd->Between(0,65535);
                                        }

                                      lcdscreen->Update((XBYTE*)buffer);
                                      XDEBUG_PRINTCOLOR(1, __L("Send screen Update: %05d  %s    "), nframes,  status?__L("Ok!"):__L("Error!"));

                                      nframes++;
                                   }

                                } else XDEBUG_PRINTCOLOR(1, __L("Error Create Buffer Random..."));

                              delete buffer;

                           } else XDEBUG_PRINTCOLOR(1, __L("Error Create Random..."));

                         GEN_XFACTORY.DeleteRand(rnd);



                      }


                    }

                  lcdscreen->End();
                }

              delete lcdscreen;
            }

          diogpio->End();
        }

      GEN_DIOFACTORY.DeleteGPIO(diogpio);
    }

  //----------------------------------------------------------------------------
  */
  /*
  DIOGPIO* diogpio = DIOFACTORY::GetInstance().CreateGPIO();
  if(diogpio)
    {
      if(diogpio->Ini())
        {
          DIOSPIOLEDSCREENSSD1331*  oledscreenSSD1331 = new DIOSPIOLEDSCREENSSD1331();
          if(oledscreenSSD1331)
            {
              oledscreenSSD1331->SetDIOGPIO(diogpio);

              oledscreenSSD1331->SetResetPin(SCREEN_PIN_RESET, SCREEN_GRP_RESET);
              oledscreenSSD1331->SetDCPin(SCREEN_PIN_DC, SCREEN_GRP_DC);

              status  =  oledscreenSSD1331->Ini(1, 0, 3);
              XTRACE_PRINTCOLOR((status?1:4), __L("Send screen INI   : %s \n"), (status?__L("Ok!"):__L("Error!")));
              if(status)
                {
                  while(1)
                    {
                      status = oledscreenSSD1331->Clear(DIOSPIOLEDSCREENSSD1331_COLOR_RED);
                      GEN_XSLEEP.Seconds(1);

                      status = oledscreenSSD1331->Clear(DIOSPIOLEDSCREENSSD1331_COLOR_GREEN);
                      GEN_XSLEEP.Seconds(1);

                      status = oledscreenSSD1331->Clear(DIOSPIOLEDSCREENSSD1331_COLOR_BLUE);
                      GEN_XSLEEP.Seconds(1);
                    }
                }

              oledscreenSSD1331->End();
              delete oledscreenSSD1331;
            }

          diogpio->End();
        }

      DIOFACTORY::GetInstance().DeleteGPIO(diogpio);

      return true;
    }
  */

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void CANVAS2DDISPLAY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:30
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void CANVAS2DDISPLAY::Clean()
{

}


