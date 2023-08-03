// ----------------------------------------------------------------------------
// Example Scrip + Input Simulate
// ----------------------------------------------------------------------------


function main()
{
  var appname     = "Notepad.exe";
  var apppath     = "C:\\Windows\\System32\\" + appname;
  var windowtitle = "Bloc de notas";

  XTRACE_PRINTCOLOR(1, "Exec application: %s", appname);

  ExecApplication(apppath);

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  XTRACE_PRINTCOLOR(1, "Position of %s %d, %d", appname, posx, posy);

  InpSim_SetMouseClick(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_SetMouseClick(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_SetMouseClick(posx + 30, posy + 150);

  Sleep(1000);

  InpSim_PressKeyByLiteral("A", 100);
  InpSim_PressKeyByLiteral("ENTER", 100);

  
  InpSim_PressKeyByLiteral("!"  , 1);
  InpSim_PressKeyByLiteral("@"  , 1);
  InpSim_PressKeyByLiteral("#"  , 1);
  InpSim_PressKeyByLiteral("$"  , 1);
  InpSim_PressKeyByLiteral("%"  , 1);
  InpSim_PressKeyByLiteral("^"  , 1);
  InpSim_PressKeyByLiteral("&"  , 1);
  InpSim_PressKeyByLiteral("*"  , 1);
  InpSim_PressKeyByLiteral("("  , 1);
  InpSim_PressKeyByLiteral(")"  , 1);
  InpSim_PressKeyByLiteral("_"  , 1);
  InpSim_PressKeyByLiteral("+"  , 1);
  InpSim_PressKeyByLiteral("-"  , 1);
  InpSim_PressKeyByLiteral("="  , 1);
  InpSim_PressKeyByLiteral("["  , 1);
  InpSim_PressKeyByLiteral("]"  , 1);
  InpSim_PressKeyByLiteral("{"  , 1);
  InpSim_PressKeyByLiteral("}"  , 1);
  InpSim_PressKeyByLiteral("|"  , 1);
  InpSim_PressKeyByLiteral(";"  , 1);
  InpSim_PressKeyByLiteral(":"  , 1);
  InpSim_PressKeyByLiteral("'"  , 1);
  InpSim_PressKeyByLiteral(","  , 1);
  InpSim_PressKeyByLiteral("."  , 1);
  InpSim_PressKeyByLiteral("<"  , 1);   
  InpSim_PressKeyByLiteral("?"  , 1);
  InpSim_PressKeyByLiteral("/"  , 1);
  InpSim_PressKeyByLiteral("\\" , 1);
  InpSim_PressKeyByLiteral("\"" , 1);
  

  //InpSim_PressKeyByLiteral("¿"  , 1);
  //InpSim_PressKeyByLiteral("¡"  , 1);
  //InpSim_PressKeyByLiteral("ñ"  , 1);
  //InpSim_PressKeyByLiteral("Ñ"  , 1);
  //InpSim_PressKeyByLiteral("·"  , 1);
 
  InpSim_PressKeyByLiteral("ENTER", 1);

  InpSim_PressKeyByText("Texto De Prueba 0123456789 !@#$%^&*()_+-=[]{}|;:',.<¿¡ñÑ?/\\\"·", 1);

  Sleep(1000);

  XTRACE_PRINTCOLOR(1, "Terminate application: %s", appname);

  TerminateAplicationWithWindow(appname, windowtitle);  
}

