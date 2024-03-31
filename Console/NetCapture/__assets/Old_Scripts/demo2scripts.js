function main()
{

/*---- VARIABLES ----------------------------------------------------------------------------------------------------*/

  var scriptname;
  var scriptname  = GetNameScript() + ".js";
       
/*---- SCRIPT -------------------------------------------------------------------------------------------------------*/
  
  TraceClearScreen(true);
  TraceClearMsgsStatus(true);

  TracePrintColor(1, "Starting Loki");

  for (u = 0; u < LTV.length; u++)
  {
    const elements = LTV[u];

    TracePrintColor(1, "[script %s] %s, %d, %s, %d, %s, %d, %s, %s, %s", scriptname, elements.id_LTV,  elements.pkInicio, elements.viaInicio, elements.pkFin, elements.viaFin, elements.velocidad, elements.desvio, elements.causa, elements.responsable);
  }

  Log_AddEntry(1, "Script", "[script %s] Ending Loki demo script", scriptname);

}
