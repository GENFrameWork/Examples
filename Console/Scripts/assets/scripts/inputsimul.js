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

  var posx = InpSim_GetWindowPosX(appname, windowtitle);
  var posy = InpSim_GetWindowPosY(appname, windowtitle);

  XTRACE_PRINTCOLOR(1, "Position of %s %d, %d", appname, posx, posy);
  
  InpSim_SetMouseClick(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_SetMouseClick(posx + 30, posy + 50);

  Sleep(1000);

  InpSim_SetMouseClick(posx + 30, posy + 150);

  Sleep(1000);

  InpSim_PressKeyByLiteral("A", 100);

  InpSim_PressKeyByLiteral("ENTER", 100);

  InpSim_PressKeyByText("TEXTO DE PRUEBA", 1);

  Sleep(1000);

  XTRACE_PRINTCOLOR(1, "Terminate application: %s", appname);

  TerminateAplicationWithWindow(appname, windowtitle);  
}

