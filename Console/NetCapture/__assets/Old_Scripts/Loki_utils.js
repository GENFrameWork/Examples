/* ****************************************************************************************************** */
/*                                                                                                        */
/*                                                         :::         :::::::::::    :::    :::    :::   */
/*   loki_utils.js                                        :+:         :+:     :+:    :+:   :+:     :+:    */
/*                                                       +:+         +:+     +:+    +:+   +:+     +:+     */
/*   By: jaormaetxea                                    +#+         +#+     +#+    +#+  +#+      +#+      */
/*                                                     +#+         +#+     +#+    +#+ +#+       +#+       */
/*   Created: 2023/08/24 13:29:31 by jaormaetxea      +#+#+##+#   +#+#+##++#+    +#+   #++     +#+        */
/*   Updated: 2023/08/24 13:29:31 by jaormaetxea     #########   ###########    ###     ###   ###         */
/*                                                                                                        */
/* ****************************************************************************************************** */


var bitmapeliminar  = "EstablishLTV.png";
var bitmapactivar = "ActivateLTV.png";
var posxltvpanel;
var posyltvpanel;

VIAS = 
{
  CERO: 0,
  UNOA: 1,
  UNOB: 2,
  DOSA: 3,
  DOSB: 4
}

LOGLEVEL = 
{
  INFO: 1,
  WARNING: 2,
  ERROR: 3
}

ERROR = 
{
  NOWINDOW: 0XFFFFFF,
  NOBITMAP: 0XFFFFFE
}

function MenuToolbarLogin(appname, windowtitle) {

  TracePrintColor(1, "FuncionMenuToolbarLogin", appname);

  InpSim_Mouse_Click(70, 40);

  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function PEUserLogout(appname, windowtitle) {

  TracePrintColor(1, "Desplegando Login de Usuario en la Barra de Herramientas", appname);

  InpSim_Mouse_Click(70, 40);

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

function CleanLTV(appname, windowtitle, posx, posy) {

  //var maskbitmapname  = "EstablishLTV.png"

  TracePrintColor(1, "Entering the CleanLTV function");

  InpSim_Mouse_Click(posx, posy);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  TracePrintColor(1, "Exiting the CleanLTV function");

}

function EstablishLTVPanelset(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, desvio, causa, responsable) {

  //var maskbitmapname  = "EstablishLTV.png"
  var scriptname  = GetNameScript() + ".js";
  
  TracePrintColor(1, "Entering the EstablishLTVPanelset function");

  // Como buena practica conviene limpiar primero el panel
  CleanLTV(appname, windowtitle);

  InpSim_Mouse_Click(posxltvpanel, posyltvpanel);

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

  //Log_AddEntry(LOGLEVEL.INFO, "Script", "[script %s] Establecer LTV [%s, SIN DESVIO, Trabajos en via, Mantenimiento]", scriptname, pkInicio,  );
  Sleep(500);

}

function ActivateLTV(appname, windowtitle) {

  //var maskbitmapname  = "EstablishLTV.png"
  
  TracePrintColor(1, "Entering the ActivateLTV function");

  InpSim_Mouse_Click(posxltvpanel, posyltvpanel);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function PurgeLTV(appname, windowtitle) {

  //var bitmapeliminar  = "DeleteLTV.png"
  
  TracePrintColor(1, "Entering the PurgeLTV function");

  InpSim_Mouse_Click(posxltvpanel, posyltvpanel);

  // Seleccionamos y accionamos el boton 'Purgar'
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}


function DeleteLTV(appname, windowtitle) {

  //var bitmapeliminar  = "DeleteLTV.png"
  
  TracePrintColor(1, "Entering the DeleteLTV function");

  InpSim_Mouse_Click(posxltvpanel, posyltvpanel);

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

function EstablishLTV(appname, windowtitle, ltvname, user, password, viaInicio, viaFin, pkInicio, pkFin, velocidad) {

  //var bitmapactivar = "activar.png"]
  var scriptname  = GetNameScript() + ".js";
  var isActive;

  TracePrintColor(1, "Entering the EstablishLTV function");

  EstablishLTVPanelset(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, 0, 1, 1);

  Sleep(1000);

  isActive = Window_GetPosX(appname, windowtitle, maskbitmapname);

  TracePrintColor(1, "The bitmap X axis position is [hex] %08X [dec] %d", isActive, isActive);
  
  if(isActive == ERROR.NOWINDOW || isActive == ERROR.NOBITMAP)
  {

   TracePrintColor(1, "The bitmap position value has returned an error -> %06X", isActive);
   Log_AddEntry(LOGLEVEL.INFO, "KO", "[LTV %s] The CEM does not confirm the LTV configuration values (posx returns error %06X).", ltvname, isActive);
   CleanLTV(appname, windowtitle);
   return 1;

  }

  TracePrintColor(1, "ActivateLTV button is active.");
  
  ActivateLTV(appname, windowtitle);

  Sleep(500);
  
  CleanLTV(appname, windowtitle);

  Log_AddEntry(LOGLEVEL.INFO, "OK", "[LTV %s] The LTV was sent succesfully.", ltvname, isActive);

  TracePrintColor(1, "Exiting the EstablishLTV function");

  return 0;
}

function main()
{

  var scriptlog;
  var scriptname;
  var maskbitmapname  = "establecerLTV.png";
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

  //DEFINIR UN IDENTIFICADOR DE SCRIPTS. EL NOMBRE DEL SCRIPT NO SERÁ ACCESIBLE POR EL TESTER
  Log_AddEntry(LOGLEVEL.INFO, "Script", "Launching LTV tests");

  Window_SetFocus(appname, windowtitle);

  posxltvpanel = Window_GetPosX(appname, windowtitle, maskbitmapname);

  if(posxltvpanel == ERROR.NOWINDOW || posxltvpanel == ERROR.NOBITMAP)
  {

   TracePrintColor(1, "The LTV establishmet panel position bitmap position value has returned an error -> %06X", posxltvpanel);
   Log_AddEntry(LOGLEVEL.WARNING, "KO", "[Script %s] The script can´t resolve the LTV establishmet panel position (error %06X)", scriptname, posxltvpanel);
   return;

  }

  TracePrintColor(1, "LTV establishmet panel X coordinate is [hex] %06X [dec] %d", posxltvpanel, posxltvpanel);
  
  posyltvpanel = Window_GetPosY(appname, windowtitle, maskbitmapname);

  InpSim_Mouse_Click(posxltvpanel, posyltvpanel);

  for (u = 0; u < LTV.length; u++)
  {
    const elements = LTV[u];
    TracePrintColor(1, "[script %s] %s, %d, %s, %d, %s, %d, %s, %s, %s", scriptname, elements.id_LTV,  elements.pkInicio, elements.viaInicio, elements.pkFin, elements.viaFin, elements.velocidad, elements.desvio, elements.causa, elements.responsable);
  }

  //Log_AddEntry(LOGLEVEL.INFO, "Script", "[script %s] Iniciado Test...", scriptname);

  //OK//EstablishLTV(appname, windowtitle, ltvname, user, password, "0", "750", VIAS.UNOB, VIAS.UNOB, "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "0"      , "4031"   , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "0"      , "4181"   , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "0"      , "1466"   , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "0"      , "1466"   , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOB, "838"    , "932"    , "20");
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOA, "932"    , "838"    , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSB, "838"    , "932"    , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSA, "932"    , "838"    , "20")
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "1530", "1466", "20") // "6" , "MKVA3A6"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "1466", "1332", "20") // "7" , "MKVE1MK"              
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "1332", "1235", "20") // "8" , "MKA2_D"                
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "1235", "1223", "20") // "9" , "MKA2_C"                
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "122" , "966" , "20") // "10", "MKVM2"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "966" , "838" , "20") // "11", "MKVE1UR"            
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "838" , "69"  , "20") // "12", "MKVT5"                
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOA,  VIAS.UNOA, "6993", "0"   , "20") // "13", "MKVE1CVA"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "0"   , "54"  , "20") // "14", "MKVE1CVB"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "54"  , "932" , "20") // "15", "ZRV1"                   
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "932" , "1051", "20") // "16", "ZRVE1ZR"            
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "1051", "1056", "20") // "17", "ZRA1_C"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "1056", "1090", "20") // "18", "ZRA1_I"              
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "1090", "1109", "20") // "19", "ZRA4_C"              
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "1109", "1241", "20") // "20", "ZRVM4"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "1241", "1963", "20") // "21", "ZRVT1"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "1963", "2085", "20") // "22", "ZRVE1TX"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "2085", "2652", "20") // "23", "ZRVT3"                
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "2652", "2785", "20") // "24", "ZRVE1OT"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "2785", "3862", "20") // "25", "SAVT1"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "4031", "4080", "20") // "28", "SAA1_I"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "4080", "4203", "20") // "29", "SAVE1SA"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "4203", "4469", "20") // "30", "SAVA2"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "1530", "1466", "20") // "38", "MKVA4A5"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "1466", "1332", "20") // "39", "MKVE2MK"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "1332", "1280", "20") // "40", "MKA7_C"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "1280", "965" , "20") // "41", "MKA7_D"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "965" , "838" , "20") // "42", "MKVE2UR"            
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "838" , "70"  , "20") // "43", "MKVT2"                
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSA,  VIAS.DOSA, "70"  , "0"   , "20") // "44", "MKVE2CVA"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "0"   , "54"  , "20") // "45", "MKVE2CVB"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "54"  , "932" , "20") // "46", "ZRV2"                   
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "932" , "1051", "20") // "47", "ZRVE2ZR"            
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "1051", "1056", "20") // "48", "ZRA3_C"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "1056", "1090", "20") // "49", "ZRA3_D"              
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "1090", "1109", "20") // "50", "ZRA2_C"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "1109", "1241", "20") // "51", "ZRVM2"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "1241", "1964", "20") // "52", "ZRVT4"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "1964", "208" , "20") // "53", "ZRVE2TX"            
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "2084", "2652", "20") // "54", "ZRVT2"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "2652", "2785", "20") // "55", "ZRVE2OT"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "2785", "3861", "20") // "56", "SAVT4"               
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "3861", "4010", "20") // "57", "SAVC"                 
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "4049", "4076", "20") // "61", "SAA6_I"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "4076", "4081", "20") // "62", "SAA6_C"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "4081", "4181", "20") // "63", "SAVE2SA"           
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "1280", "1258", "20") // "83", "MKA7_I"      
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "1258", "1235", "20") // "84", "MKA2_I"      
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "1056", "1072", "20") // "85", "ZRA1_D"       
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "1072", "1090", "20") // "86", "ZRA2_D"       
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "1056", "1074", "20") // "87", "ZRA3_I"       
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "1074", "1090", "20") // "88", "ZRA4_I"       
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "4031", "4053", "20") // "89", "SAA1_D"      
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.CERO,  VIAS.CERO, "4053", "4076", "20") // "90", "SAA6_D"      
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.UNOB,  VIAS.UNOB, "3862", "4031", "20") // "92", "SAA1_C"             
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "4010", "4049", "20") // "94", "SAVA3A8"            
  //EstablishLTV(appname, windowtitle, ltvname, user, password, VIAS.DOSB,  VIAS.DOSB, "4181", "4300", "20") // "95", "SAVA4A5"            

  TracePrintColor(1, "Exiting LTV tests");
  //TerminateAplicationWithWindow(appname, windowtitle);  
  //Log_AddEntry(LOGLEVEL.INFO, "Script", "[script %s] Finalizado Test...", scriptname);


}
