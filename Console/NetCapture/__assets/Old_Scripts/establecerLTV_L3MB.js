/* ****************************************************************************************************** */
/*                                                                                                        */
/*                                                         :::         :::::::::::    :::    :::    :::   */
/*   EstablishLTV.js                                     :+:         :+:     :+:    :+:   :+:     :+:    */
/*                                                       +:+         +:+     +:+    +:+   +:+     +:+     */
/*   By: jaormaetxea                                    +#+         +#+     +#+    +#+  +#+      +#+      */
/*                                                     +#+         +#+     +#+    +#+ +#+       +#+       */
/*   Created: 2023/08/24 13:29:31 by jaormaetxea      +#+#+##+#   +#+#+##++#+    +#+   #++     +#+        */
/*   Updated: 2023/08/24 13:29:31 by jaormaetxea     #########   ###########    ###     ###   ###         */
/*                                                                                                        */
/* ****************************************************************************************************** */


Vias = 
{
  CERO: 0,
  UNOA: 1,
  UNOB: 2,
  DOSA: 3,
  DOSB: 4
}

Error = 
{
  NOWINDOW: 0XFFFFFF,
  NOBITMAP: 0XFFFFFE
}

var bitmapeliminar  = "EstablishLTV.png";
var bitmapactivar = "ActivateLTV.png";

function SetMousePosition(appname, windowtitle, x, y) {

  TracePrintColor(1, "Funcion SetMousePosition", appname, posx, posy);

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  //Posicion del texto "Establecer LTV" -> Objetivo identificar el jframe en vez de la posicion
  InpSim_Mouse_Click(posx + x, posy + y);

  //Revisar. El click no posiciona
  TracePrintColor(1, "La posición del puntero de la app %s es x = %d e y = %d", appname, posx, posy);

}

function MenuToolbarLogin(appname, windowtitle) {

  TracePrintColor(1, "FuncionMenuToolbarLogin", appname);

  SetMousePosition(appname, windowtitle, 70, 40);
  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function PEUserLogout(appname, windowtitle) {

  TracePrintColor(1, "Desplegando Login de Usuario en la Barra de Herramientas", appname);

  SetMousePosition(appname, windowtitle, 70, 40);

  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //TAB para posicionarnos en "Cierre sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  TracePrintColor(1, "Se pulsa el boton de cierre de sesion de usuario");

}

function PEUserLogin(appname, windowtitle, usr, pswd) {

  TracePrintColor(1, "Entrando en el login de Usuario");

  MenuToolbarLogin(appname, windowtitle);

  TracePrintColor(1, "Volviendo al login de Usuario");

  // Rellenamos el campo "Usuario"
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(usr, 1);
  TracePrintColor(1, "Introducido la clave de nombre del usuario %s", usr);

  // Rellenamos el campo "Contraseña"
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pswd, 1);
  TracePrintColor(1, "Introducida la clave de contraseña (%s) del usuario %s", pswd, usr);

  // Accionamos el boton de "Aceptar"
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("ENTER", 1);
  TracePrintColor(1, "Se pulsa el boton de 'ACEPTAR' para el envio de credenciales", pswd, usr);

}

function CleanLTV(appname, windowtitle) {

  //var maskbitmapname  = "EstablishLTV.png"

  TracePrintColor(1, "Entrando en CleanLTV");

  var posx = Window_GetPosX(appname, windowtitle, maskbitmapname);
  var posy = Window_GetPosY(appname, windowtitle, maskbitmapname);

  SetMousePosition(appname, windowtitle, posx, posy);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  TracePrintColor(1, "Saliendo de CleanLTV");

}

function EstablishLTVPanelset(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, desvio, causa, responsable) {

  //var maskbitmapname  = "EstablishLTV.png"
  var scriptname  = GetNameScript() + ".js";
  
  TracePrintColor(1, "Entrando en EstablishLTVPanelset");

  // Como buena practica conviene limpiar primero el panel
  CleanLTV(appname, windowtitle);

  var posx = Window_GetPosX(appname, windowtitle, maskbitmapname);
  var posy = Window_GetPosY(appname, windowtitle, maskbitmapname);

  SetMousePosition(appname, windowtitle, posx, posy);

  // Rellenamos pkInicio
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pkInicio, 1);
  TracePrintColor(1, "Rellenado campo %s", pkInicio);

  // Rellenamos pkFin
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pkFin, 1);
  TracePrintColor(1, "Rellenado campo %s", pkFin);

  // Rellenamos viaInicio
  InpSim_Key_ClickByLiteral("TAB", 1);
  for (i = 0; i < viaInicio; i++) {
    InpSim_Key_ClickByLiteral("DOWN ARROW", 1);
  }

  // Rellenamos velocidad
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(velocidad, 1);
  TracePrintColor(1, "Introducimos %s", velocidad);

  // No asignamos desvío
  InpSim_Key_ClickByLiteral("TAB", 1);

  // Rellenamos viaFin
  InpSim_Key_ClickByLiteral("TAB", 1);
  for (i = 0; i < viaFin; i++) {
    InpSim_Key_ClickByLiteral("DOWN ARROW", 1);
  }

  // Rellenamos el campo causa
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("DOWN ARROW", 1);

  //Rellenamos el campo Responsable
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("DOWN ARROW", 1);

  // Nos deplazamos hasta el boton limpiar
  InpSim_Key_ClickByLiteral("TAB", 1);

  // Seleccionamos y accionamos el boton establecer
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  //Log_AddEntry(1, "Script", "[script %s] Establecer LTV [%s, SIN DESVIO, Trabajos en via, Mantenimiento]", scriptname, pkInicio,  );
  Sleep(500);

}

function ActivateLTV(appname, windowtitle) {

  //var maskbitmapname  = "EstablishLTV.png"
  
  TracePrintColor(1, "Entrando en EstablishLTVPanelset");

  var posx = Window_GetPosX(appname, windowtitle, maskbitmapname);
  var posy = Window_GetPosY(appname, windowtitle, maskbitmapname);

  SetMousePosition(appname, windowtitle, posx, posy);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function PurgeLTV(appname, windowtitle) {

  //var bitmapeliminar  = "DeleteLTV.png"
  
  TracePrintColor(1, "Entrando en PurgeLTV");

  var posx = Window_GetPosX(appname, windowtitle, bitmapeliminar);
  var posy = Window_GetPosY(appname, windowtitle, bitmapeliminar);

  SetMousePosition(appname, windowtitle, posx, posy);

  // Seleccionamos y accionamos el boton 'Purgar'
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}


function DeleteLTV(appname, windowtitle) {

  //var bitmapeliminar  = "DeleteLTV.png"
  
  TracePrintColor(1, "Entrando en DeleteLTV");

  var posx = Window_GetPosX(appname, windowtitle, bitmapeliminar);
  var posy = Window_GetPosY(appname, windowtitle, bitmapeliminar);

  SetMousePosition(appname, windowtitle, posx, posy);

  //Escogemos la LTV a eliminar (buscar nuevo método)
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("DOWN ARROW", 1);

  // Nos deplazamos hasta el boton limpiar
  InpSim_Key_ClickByLiteral("TAB", 1);

  // Seleccionamos y accionamos el boton establecer
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);
  Sleep(500);

}

//function pruebaCicloVidaCompletoLTV(appname, windowtitle, user, password) {
//
//  var user = "Supervisor1";
//  var password = "SUPERVISOR1";
//
//  TracePrintColor(1, "Condiciones previas:");
//  TracePrintColor(1, "- Lanzar Contexto de Pruebas PE-CEM-ENCE-L3MB.");
//  TracePrintColor(1, "- Lanzar MV ATS-CTC con CTC arrancado.");
//
//  TracePrintColor(1, "Inicio test prueba001");
//
//  PEUserLogout(appname, windowtitle);
//  Sleep(1000);
//  PEUserLogin(appname, windowtitle, user, password);
//  EstablishLTVPanelset(appname, windowtitle, "2100", 2, "2600", 2, "20", 0, 1, 1);
//  ActivateLTV(appname, windowtitle);
//  Sleep(3000);
//  DeleteLTV(appname, windowtitle);
//  PurgeLTV(appname, windowtitle);
//  SetMousePosition(appname, windowtitle, 30, 310);
//
//  TracePrintColor(1, "Fin test prueba001");
//
//}

function EstablishLTV(appname, windowtitle, user, password, viaInicio, viaFin, pkInicio, pkFin, velocidad) {

  //var bitmapactivar = "activar.png"]
  var scriptname  = GetNameScript() + ".js";
  var isActive;

  TracePrintColor(1, "Entering the EstablishLTV function");

  //EstablishLTVPanelset(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, 0, 1, 1);
  isActive = Window_GetPosX(appname, windowtitle, maskbitmapname);

  TracePrintColor(1, "The bitmap X axis position is [hex] %08X [dec] %d", isActive, isActive);
  
  if(isActive == Error.NOWINDOW || isActive == Error.NOBITMAP)
  {

   TracePrintColor(1, "The bitmap position value has returned an error -> %06X", isActive);
   Log_AddEntry(1, "KO", "[script %s] The CEM does not confirm the LTV configuration values (posx returns error %06X).", scriptname, isActive);
   CleanLTV(appname, windowtitle);
   return;

  }
  else
  {
    TracePrintColor(1, "ActivateLTV button is active.");
    ActivateLTV(appname, windowtitle);
    Sleep(500);
  }
 
  //CleanLTV(appname, windowtitle);
  //TracePrintColor(1, "Saliendo de función EstablishLTV");

}

function main()
{

  //var scriptlog;
  //var scriptname;
  var maskbitmapname  = "EstablishLTV.png";
  var appname         = "java.exe";
  //var apppath         = "C:\\Program Files (x86)\\Common Files\\Oracle\\Java\\javapath_target_182481281\\" + appname;
  var windowtitle     = "PCE_ZR";
  var user            = "Supervisor1";
  var password        = "SUPERVISOR1";

  var scriptlog   = GetPathScript() +  GetNameScript() + ".log";
  var scriptname  = GetNameScript() + ".js";

  if(!Log_Ini(scriptlog, "ScriptsExample"))
    {
      return;  
    }
  
  Log_CFG_SetLimit(30000, 3);
  Log_CFG_SetFilters("Script, OK, KO", 0x000F);
  Log_CFG_SetBackup(true, 10, true);     
   
  TraceClearScreen(true);
  TraceClearMsgsStatus(true);

  //TracePrintColor(1, "Hacemos cierre e inicio de sesión");

  //PEUserLogout(appname, windowtitle);
  //Sleep(1000);
  //PEUserLogin(appname, windowtitle, user, password);

  TracePrintColor(1, "Lanzando bateria de tests");
  isActive = Window_GetPosX(appname, windowtitle, maskbitmapname);
  //Log_AddEntry(1, "Script", "[script %s] El valor de isActive es %d", scriptname, isActive);
  TracePrintColor(1, "Valor de posición de imagen es %08X  %d", isActive, isActive);

  //Log_AddEntry(1, "Script", "[script %s] Iniciado Test...", scriptname);

  //OK//EstablishLTV(appname, windowtitle, user, password, "0", "750", Vias.UNOB, Vias.UNOB, "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "0"      , "4031"   , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "0"      , "4181"   , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "0"      , "1466"   , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "0"      , "1466"   , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA, Vias.UNOB, "838", "932", "20");
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOA, "932"    , "838"    , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSB, "838"    , "932"    , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSA, "932"    , "838"    , "20")
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1530", "1466", "20") // "6" , "MKVA3A6"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1466", "1332", "20") // "7" , "MKVE1MK"              
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1332", "1235", "20") // "8" , "MKA2_D"                
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1235", "1223", "20") // "9" , "MKA2_C"                
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "122" , "966" , "20") // "10", "MKVM2"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "966" , "838" , "20") // "11", "MKVE1UR"            
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "838" , "69"  , "20") // "12", "MKVT5"                
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "6993", "0"   , "20") // "13", "MKVE1CVA"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "0"   , "54"  , "20") // "14", "MKVE1CVB"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "54"  , "932" , "20") // "15", "ZRV1"                   
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "932" , "1051", "20") // "16", "ZRVE1ZR"            
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1051", "1056", "20") // "17", "ZRA1_C"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1056", "1090", "20") // "18", "ZRA1_I"              
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1090", "1109", "20") // "19", "ZRA4_C"              
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1109", "1241", "20") // "20", "ZRVM4"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1241", "1963", "20") // "21", "ZRVT1"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1963", "2085", "20") // "22", "ZRVE1TX"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "2085", "2652", "20") // "23", "ZRVT3"                
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "2652", "2785", "20") // "24", "ZRVE1OT"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "2785", "3862", "20") // "25", "SAVT1"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "4031", "4080", "20") // "28", "SAA1_I"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "4080", "4203", "20") // "29", "SAVE1SA"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "4203", "4469", "20") // "30", "SAVA2"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1530", "1466", "20") // "38", "MKVA4A5"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1466", "1332", "20") // "39", "MKVE2MK"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1332", "1280", "20") // "40", "MKA7_C"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1280", "965" , "20") // "41", "MKA7_D"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "965" , "838" , "20") // "42", "MKVE2UR"            
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "838" , "70"  , "20") // "43", "MKVT2"                
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "70"  , "0"   , "20") // "44", "MKVE2CVA"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "0"   , "54"  , "20") // "45", "MKVE2CVB"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "54"  , "932" , "20") // "46", "ZRV2"                   
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "932" , "1051", "20") // "47", "ZRVE2ZR"            
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1051", "1056", "20") // "48", "ZRA3_C"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1056", "1090", "20") // "49", "ZRA3_D"              
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1090", "1109", "20") // "50", "ZRA2_C"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1109", "1241", "20") // "51", "ZRVM2"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1241", "1964", "20") // "52", "ZRVT4"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1964", "208" , "20") // "53", "ZRVE2TX"            
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "2084", "2652", "20") // "54", "ZRVT2"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "2652", "2785", "20") // "55", "ZRVE2OT"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "2785", "3861", "20") // "56", "SAVT4"               
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "3861", "4010", "20") // "57", "SAVC"                 
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4049", "4076", "20") // "61", "SAA6_I"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4076", "4081", "20") // "62", "SAA6_C"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4081", "4181", "20") // "63", "SAVE2SA"           
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1280", "1258", "20") // "83", "MKA7_I"      
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1258", "1235", "20") // "84", "MKA2_I"      
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1056", "1072", "20") // "85", "ZRA1_D"       
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1072", "1090", "20") // "86", "ZRA2_D"       
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1056", "1074", "20") // "87", "ZRA3_I"       
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1074", "1090", "20") // "88", "ZRA4_I"       
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "4031", "4053", "20") // "89", "SAA1_D"      
  //EstablishLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "4053", "4076", "20") // "90", "SAA6_D"      
  //EstablishLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "3862", "4031", "20") // "92", "SAA1_C"             
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4010", "4049", "20") // "94", "SAVA3A8"            
  //EstablishLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4181", "4300", "20") // "95", "SAVA4A5"            

//  prueba001(appname, windowtitle);

  TracePrintColor(1, "Terminada bateria de tests");
  //TerminateAplicationWithWindow(appname, windowtitle);  
  //Log_AddEntry(1, "Script", "[script %s] Finalizado Test...", scriptname);


}
