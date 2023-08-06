// ----------------------------------------------------------------------------
// Example Scrip + Input Simulate
// ----------------------------------------------------------------------------


function main()
{
  var scriptname  = "inputsimul.js";
  var appname     = "Notepad.exe";
  var apppath     = "C:\\Windows\\System32\\" + appname;
  var windowtitle = "Bloc de notas";

  LogAddEntry(1, "Script", "[script %s] Iniciado Test...", scriptname);

  ExecApplication(apppath);

  LogAddEntry(1, "Script", "[script %s] Exec application: %s", scriptname, appname);
 
  Window_SetPosition(appname, windowtitle, 10, 10);
  Window_Resize(appname, windowtitle, 800, 600);
  Window_SetFocus(appname, windowtitle);

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

  LogAddEntry(1, "Script", "[script %s] Simulate Key A + Enter.", scriptname)
  
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

  LogAddEntry(1, "Script", "[script %s] Terminate application: %s", scriptname, appname);

  TerminateAplicationWithWindow(appname, windowtitle);  

  LogAddEntry(1, "Script", "[script %s] End script.", scriptname);
}

