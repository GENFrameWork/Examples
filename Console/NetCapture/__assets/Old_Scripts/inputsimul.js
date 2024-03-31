// ----------------------------------------------------------------------------
// Example Scrip + Input Simulate
// ----------------------------------------------------------------------------


function main()
{
  var scriptname  = "inputsimul.js";
  var appname     = "Notepad.exe";
  var apppath     = "C:\\Windows\\System32\\" + appname;
  var windowtitle = "Bloc de notas";

  Log_AddEntry(1, "Script", "[script %s] Iniciado Test...", scriptname);

  ExecApplication(apppath);

  Log_AddEntry(1, "Script", "[script %s] Exec application: %s", scriptname, appname);
 
  Window_SetPosition(appname, windowtitle, 10, 10);
  Window_Resize(appname, windowtitle, 800, 600);
  Window_SetFocus(appname, windowtitle);

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  XTRACE_PRINTCOLOR(1, "Position of %s %d, %d", appname, posx, posy);

  InpSim_Mouse_Click(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_Mouse_Click(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_Mouse_Click(posx + 30, posy + 150);

  Sleep(1000);

  InpSim_Key_ClickByLiteral("A", 100);
  InpSim_Key_ClickByLiteral("ENTER", 100);

  Log_AddEntry(1, "Script", "[script %s] Simulate Key A + Enter.", scriptname)
  
  InpSim_Key_ClickByLiteral("!"  , 1);
  InpSim_Key_ClickByLiteral("@"  , 1);
  InpSim_Key_ClickByLiteral("#"  , 1);
  InpSim_Key_ClickByLiteral("$"  , 1);
  InpSim_Key_ClickByLiteral("%"  , 1);
  InpSim_Key_ClickByLiteral("^"  , 1);
  InpSim_Key_ClickByLiteral("&"  , 1);
  InpSim_Key_ClickByLiteral("*"  , 1);
  InpSim_Key_ClickByLiteral("("  , 1);
  InpSim_Key_ClickByLiteral(")"  , 1);
  InpSim_Key_ClickByLiteral("_"  , 1);
  InpSim_Key_ClickByLiteral("+"  , 1);
  InpSim_Key_ClickByLiteral("-"  , 1);
  InpSim_Key_ClickByLiteral("="  , 1);
  InpSim_Key_ClickByLiteral("["  , 1);
  InpSim_Key_ClickByLiteral("]"  , 1);
  InpSim_Key_ClickByLiteral("{"  , 1);
  InpSim_Key_ClickByLiteral("}"  , 1);
  InpSim_Key_ClickByLiteral("|"  , 1);
  InpSim_Key_ClickByLiteral(";"  , 1);
  InpSim_Key_ClickByLiteral(":"  , 1);
  InpSim_Key_ClickByLiteral("'"  , 1);
  InpSim_Key_ClickByLiteral(","  , 1);
  InpSim_Key_ClickByLiteral("."  , 1);
  InpSim_Key_ClickByLiteral("<"  , 1);   
  InpSim_Key_ClickByLiteral("?"  , 1);
  InpSim_Key_ClickByLiteral("/"  , 1);
  InpSim_Key_ClickByLiteral("\\" , 1);
  InpSim_Key_ClickByLiteral("\"" , 1);
  
  //InpSim_Key_ClickByLiteral("�"  , 1);
  //InpSim_Key_ClickByLiteral("�"  , 1);
  //InpSim_Key_ClickByLiteral("�"  , 1);
  //InpSim_Key_ClickByLiteral("�"  , 1);
  //InpSim_Key_ClickByLiteral("�"  , 1);
 
  InpSim_Key_ClickByLiteral("ENTER", 1);

  InpSim_Key_ClickByText("Texto De Prueba 0123456789 !@#$%^&*()_+-=[]{}|;:',.<����?/\\\"�", 1);

  Sleep(1000);

  Log_AddEntry(1, "Script", "[script %s] Terminate application: %s", scriptname, appname);

  TerminateAplicationWithWindow(appname, windowtitle);  

  Log_AddEntry(1, "Script", "[script %s] End script.", scriptname);
}

