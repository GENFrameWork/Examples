/**-------------------------------------------------------------------------------------------------------------------
 *
 * @file       HelloWorld_CI.cpp
 *
 * @class      HELLOWORLD_CI
 * @brief      Hello World Continous Integration
 * @ingroup
 *
 * @copyright  Arin. All rights reserved.
 *
 * --------------------------------------------------------------------------------------------------------------------*/


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "helloworld.h"

#include <stdio.h>


#include "MainLibrary.h"
#include "XLog.h"



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/




/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

/**-------------------------------------------------------------------------------------------------------------------
 *
 * @fn         int main()
 * @brief      main
 * @ingroup
 *
 * @return     int :
 *
 * --------------------------------------------------------------------------------------------------------------------*/
int main()
{
  bool status;

  LIBRARY_Ini();

  status = GEN_XLOG.Ini(__L("helloword.log"), __L("helloword"), true);
  if(status)
    {       
  
      GEN_XLOG.SetLimit(XLOGTYPELIMIT_SIZE, 3000*1000, 10);
      GEN_XLOG.SetFilters(__L("GENERIC"), 0x000F);
      GEN_XLOG.SetBackup(true, 10,  true);       
  
      GEN_XLOG.AddEntry(XLOGLEVEL_INFO,__L("GENERIC"), false, __L("Hello World!"));
        
      GEN_XLOG.End();
    }


  LIBRARY_End();
  
  return status;
}

