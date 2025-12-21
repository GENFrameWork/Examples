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
#pragma region INCLUDES

#include "helloworld.h"

#include <stdio.h>

#include "XString.h"
#include "XLog.h"

#pragma endregion

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

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
  
  status = GEN_XLOG.Ini(__L("helloword.log"), __L("helloword"), true);
  if(status)
    {       
  
      GEN_XLOG.SetLimit(XLOGTYPELIMIT_SIZE, 3000*1000, 10);
      GEN_XLOG.SetFilters(__L("GENERIC"), 0x000F);
      GEN_XLOG.SetBackup(true, 10,  true);       
  
      GEN_XLOG.AddEntry(XLOGLEVEL_INFO,__L("GENERIC"), false, __L("Hello World!"));
        
      GEN_XLOG.End();
    }
  
  return 0;
}

#pragma endregion
