/* ****************************************************************************************************** */
/*                                                                                                        */
/*                                                         :::         :::::::::::    :::    :::    :::   */
/*   pruebaPCap.js                                        :+:         :+:     :+:    :+:   :+:     :+:    */
/*                                                       +:+         +:+     +:+    +:+   +:+     +:+     */
/*   By: jaormaetxea                                    +#+         +#+     +#+    +#+  +#+      +#+      */
/*                                                     +#+         +#+     +#+    +#+ +#+       +#+       */
/*   Created: 2023/09/19 15:25:00 by jaormaetxea      +#+#+##+#   +#+#+##++#+    +#+   #++     +#+        */
/*   Updated: 2023/09/19 15:25:00 by jaormaetxea     #########   ###########    ###     ###   ###         */
/*                                                                                                        */
/* ****************************************************************************************************** */

function main()
{

  var scriptlog;
  var scriptname;
  

  scriptlog   = GetPathScript() +  GetNameScript() + ".log";
  scriptname  = GetNameScript() + ".js";

  
  if(!Log_Ini(scriptlog, GetNameScript))
    {
      return;  
    }
  
  Log_CFG_SetLimit(300000, 3);
  Log_CFG_SetFilters("LTV,PECEM", 0x000F);
  Log_CFG_SetBackup(true, 10, true);     
  

  Log_AddEntry(1, "LTV", "[script %s] Iniciado Test...", scriptname);

  Console_Printf("Escritura a consola correcta! []===||===[] ");

  TraceClearScreen(true);

  TracePrintColor(1, "Lanzando prueba de función PCap");

  PulsarCaptureIni();

  Sleep(30000);

  PulsarCaptureEnd();

  TracePrintColor(1, "[script %s] Terminada bateria de tests", scriptname);

}
