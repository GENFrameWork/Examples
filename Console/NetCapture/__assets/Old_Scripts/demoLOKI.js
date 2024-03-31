/* ****************************************************************************************************** */
/*                                                                                                        */
/*                                                         :::         :::::::::::    :::    :::    :::   */
/*   establecerLTV.js                                     :+:         :+:     :+:    :+:   :+:     :+:    */
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

var bitmapestablecer  = "establecerLTV.png";
var bitmapactivar = "activarLTV.png";

function cierreSesionUsuarioPe(appname, windowtitle) {

  TracePrintColor(1, "Entering in the 'cierreSesionUsuarioPe' user function.");
  TracePrintColor(1, "Deploying user login menu from  the menu toolbar.");

  InpSim_Mouse_Click( 70, 40);

  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 100);
  //TAB para posicionarnos en "Cierre sesion"
  InpSim_Key_ClickByLiteral("TAB", 100);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 100);

  TracePrintColor(1, "The close session option is selected.");

  TracePrintColor(1, "Exiting the 'cierreSesionUsuarioPe' function.");

}

function loginSesionUsuarioPe(appname, windowtitle, usr, pswd) {

  TracePrintColor(1, "Entering in the 'loginSesionUsuarioPe' function.");

  InpSim_Mouse_Click( 70, 40);
  
  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 100);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 100);

  // Rellenamos el campo "Usuario"
  InpSim_Key_ClickByLiteral("TAB", 100);
  InpSim_Key_ClickByText(usr, 10);
  TracePrintColor(1, "Entered username: %s", usr);

  // Rellenamos el campo "Contraseña"
  InpSim_Key_ClickByLiteral("TAB", 100);
  InpSim_Key_ClickByText(pswd, 10);
  TracePrintColor(1, "Entered password (%s) for the user (%s)", pswd, usr);

  // Accionamos el boton de "Aceptar"
  InpSim_Key_ClickByLiteral("TAB", 100);
  InpSim_Key_ClickByLiteral("ENTER", 100);

  TracePrintColor(1, "Exiting the 'loginSesionUsuarioPe' function.");

}

function limpiarLTV(appname, windowtitle, posx, posy) {

  TracePrintColor(1, "Entering the function 'limpiarLTV'");

  InpSim_Mouse_Click( posx, posy);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  TracePrintColor(1, "Exiting the 'limpiarLTV' function.");


}

function panelEstablecerLTV(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, desvio, causa, responsable) {

  var scriptname  = GetNameScript() + ".js";
  
  TracePrintColor(1, "Entering the function 'panelEstablecerLTV'");

  // Como buena practica conviene limpiar primero el panel
  //limpiarLTV(appname, windowtitle);

  // Rellenamos pkInicio
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pkInicio, 1);
  TracePrintColor(1, "Filling 'pkInicio': %s", pkInicio);

  // Rellenamos pkFin
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pkFin, 1);
  TracePrintColor(1, "Filling 'pkFin': %s", pkFin);

  // Rellenamos viaInicio
  InpSim_Key_ClickByLiteral("TAB", 1);
  for (i = 0; i < viaInicio; i++) {
    InpSim_Key_ClickByLiteral("DOWN ARROW", 1);
  }

  // Rellenamos velocidad
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(velocidad, 1);
  TracePrintColor(1, "Filling 'velocidad': %s", velocidad);

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

  TracePrintColor(1, "Exiting the 'panelEstablecerLTV' function.");

}

function activarLTV(appname, windowtitle, posx, posy) {

  TracePrintColor(1, "Entering the function 'activarLTV'");

  InpSim_Mouse_Click( posx, posy);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  TracePrintColor(1, "Exiting the 'activarLTV' function.");

}

function purgarLTV(appname, windowtitle) {

  //var bitmapeliminar  = "eliminarLTV.png"
  
  TracePrintColor(1, "Entering the function 'purgarLTV'");

  var posx = Window_GetPosX(appname, windowtitle, bitmapeliminar);
  var posy = Window_GetPosY(appname, windowtitle, bitmapeliminar);

  InpSim_Mouse_Click( posx, posy);

  // Seleccionamos y accionamos el boton 'Purgar'
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  TracePrintColor(1, "Exiting the 'purgarLTV' function.");

}


function eliminarLTV(appname, windowtitle) {

  //var bitmapeliminar  = "eliminarLTV.png"
  TracePrintColor(1, "Entering the function 'eliminarLTV'");
  
  var posx = Window_GetPosX(appname, windowtitle, bitmapeliminar);
  var posy = Window_GetPosY(appname, windowtitle, bitmapeliminar);

  InpSim_Mouse_Click( posx, posy);

  //Escogemos la LTV a eliminar (buscar nuevo método)
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("DOWN ARROW", 1);

  // Nos deplazamos hasta el boton limpiar
  InpSim_Key_ClickByLiteral("TAB", 1);

  // Seleccionamos y accionamos el boton establecer
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);
  Sleep(500);

  TracePrintColor(1, "Exiting the 'eliminarLTV' function.");

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
//  cierreSesionUsuarioPe(appname, windowtitle);
//  Sleep(1000);
//  loginSesionUsuarioPe(appname, windowtitle, user, password);
//  panelEstablecerLTV(appname, windowtitle, "2100", 2, "2600", 2, "20", 0, 1, 1);
//  activarLTV(appname, windowtitle);
//  Sleep(3000);
//  eliminarLTV(appname, windowtitle);
//  purgarLTV(appname, windowtitle);
//  InpSim_Mouse_Click( 30, 310);
//
//  TracePrintColor(1, "Fin test prueba001");
//
//}

function establecerLTV(appname, windowtitle, posx, posy, viaInicio, viaFin, pkInicio, pkFin, velocidad) {

  //var bitmapactivar = "activar.png"
  var scriptname  = GetNameScript() + ".js";
  var posx_isActive;
  var posy_isActive;


  TracePrintColor(1, "Entering the function 'establecerLTV'");

  InpSim_Mouse_Click(posx, posy);

  panelEstablecerLTV(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, 0, 1, 1);

  Sleep(3000);

  var posx_isActive = Window_GetPosX(appname, windowtitle, bitmapactivar);
  var posy_isActive = Window_GetPosX(appname, windowtitle, bitmapactivar);

  
  if(posx_isActive == Error.NOWINDOW || posx_isActive == Error.NOBITMAP)
    {
      TracePrintColor(1, "The bitmap search returns an error-> %06X", posx_isActive);
      Log_AddEntry(1, "Script", "[script %s] The CEM does not respond with the LTV values. The LTV estblishment is aborted.", scriptname, posx_isActive);
    }
   else
    {
      Log_AddEntry(1, "Script", "[script %s] The 'Activar' bitmap has been found. posx= %06X, posy= %06X", scriptname, posx_isActive, posy_isActive);
      activarLTV(appname, windowtitle);
      Sleep(500);
    }
 
  limpiarLTV(appname, windowtitle, posx, posy);

  TracePrintColor(1, "Exiting the function 'establecerLTV'");
}

function main()
{

/*---- VARIABLES ----------------------------------------------------------------------------------------------------*/

  //var scriptlog;
  var scriptname;
  //var appname         = "java.exe";
  //var windowtitle     = "PCE_ZR";
  //var posx_establecerLTV;
  //var posy_establecerLTV;
  //var user            = "Supervisor1";
  //var password        = "SUPERVISOR1";

/*---- LOG INI ------------------------------------------------------------------------------------------------------*/

  //var scriptlog   = GetPathScript() +  GetNameScript() + ".log";
  //var scriptname  = GetNameScript() + ".js";
  //if(!Log_Ini(scriptlog, "ScriptsExample"))
  //  {
  //    return;  
  //  }
  //Log_CFG_SetLimit(30000, 3);
  //Log_CFG_SetFilters("Script", 0x000F);
  //Log_CFG_SetBackup(true, 10, true);     
   
  TraceClearScreen(true);
  TraceClearMsgsStatus(true);

/*---- SCRIPT -------------------------------------------------------------------------------------------------------*/

 // Log_AddEntry(1, "Script", "[script %s] Starting Loki demo script", scriptname);
 TracePrintColor(1, "Starting Loki");

  //Window_SetFocus(appname, windowtitle);
  //
  //cierreSesionUsuarioPe(appname, windowtitle, user, password);
  //Sleep(4000);
  //loginSesionUsuarioPe(appname, windowtitle, user, password);
  //
  //posx_establecerLTV = Window_GetPosX(appname, windowtitle, bitmapestablecer);
  //TracePrintColor(1, "'EstablecerLTV' X axis position value is: [hex] %06X | [dec] %d", posx_establecerLTV, posx_establecerLTV);
  //posy_establecerLTV = Window_GetPosY(appname, windowtitle, bitmapestablecer);
  //TracePrintColor(1, "'EstablecerLTV' Y axis position value is: [hex] %06X | [dec] %d", posy_establecerLTV, posy_establecerLTV);

  //if(posx_establecerLTV == Error.NOWINDOW || posx_establecerLTV == Error.NOBITMAP)
  //  {
  //    Log_AddEntry(1, "Script", "[script %s] The 'establecerLTV' bitmap is not found. The script execution is aborted.", scriptname);
  //    return;
  //  }
       
  //Log_AddEntry(1, "Script", "[script %s] The 'establecerLTV' bitmap has been found. posx= %06X, posy= %06X", scriptname, posx_establecerLTV, posy_establecerLTV);
  
  fetch('./LTVs.json')
  .then(response => response.json())
  .then(parsedData => {
    for (let u = 0; u < parsedData.length; u++){
     // const elements = parsedData[u];
      //TracePrintColor(1, "[script %s] %s, %s, %s, %s, %s, %s, %s, %s, %s", scriptname, elements.id_LTV,  elements.pkInicio, elements.viaInicio, elements.pkFin, elements.viaFin, elements.velocidad, elements.desvio, elements.causa, elements.responsable);
    }
  })
  .catch(error => console.error("Error al cargar el JSON:", error));
  
  Sleep(500);  
  
  //establecerLTV(elements.id_LTV, elements.pkInicio, elements.viaInicio, elements.pkFin, elements.viaFin, elements.velocidad, elements.desvio, elements.responsable);
  //OK//establecerLTV(appname, windowtitle, user, password, "0", "750", Vias.UNOB, Vias.UNOB, "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "0"      , "4031"   , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "0"      , "4181"   , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "0"      , "1466"   , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "0"      , "1466"   , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA, Vias.UNOB, "838", "932", "20");
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOA, "932"    , "838"    , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSB, "838"    , "932"    , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSA, "932"    , "838"    , "20")
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1530", "1466", "20") // "6" , "MKVA3A6"             
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1466", "1332", "20") // "7" , "MKVE1MK"              
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1332", "1235", "20") // "8" , "MKA2_D"                
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "1235", "1223", "20") // "9" , "MKA2_C"                
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "122" , "966" , "20") // "10", "MKVM2"               
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "966" , "838" , "20") // "11", "MKVE1UR"            
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "838" , "69"  , "20") // "12", "MKVT5"                
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOA,  Vias.UNOA, "6993", "0"   , "20") // "13", "MKVE1CVA"           
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "0"   , "54"  , "20") // "14", "MKVE1CVB"             
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "54"  , "932" , "20") // "15", "ZRV1"                   
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "932" , "1051", "20") // "16", "ZRVE1ZR"            
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1051", "1056", "20") // "17", "ZRA1_C"             
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1056", "1090", "20") // "18", "ZRA1_I"              
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1090", "1109", "20") // "19", "ZRA4_C"              
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1109", "1241", "20") // "20", "ZRVM4"               
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1241", "1963", "20") // "21", "ZRVT1"               
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "1963", "2085", "20") // "22", "ZRVE1TX"           
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "2085", "2652", "20") // "23", "ZRVT3"                
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "2652", "2785", "20") // "24", "ZRVE1OT"           
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "2785", "3862", "20") // "25", "SAVT1"               
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "4031", "4080", "20") // "28", "SAA1_I"             
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "4080", "4203", "20") // "29", "SAVE1SA"           
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "4203", "4469", "20") // "30", "SAVA2"               
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1530", "1466", "20") // "38", "MKVA4A5"           
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1466", "1332", "20") // "39", "MKVE2MK"           
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1332", "1280", "20") // "40", "MKA7_C"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "1280", "965" , "20") // "41", "MKA7_D"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "965" , "838" , "20") // "42", "MKVE2UR"            
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "838" , "70"  , "20") // "43", "MKVT2"                
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSA,  Vias.DOSA, "70"  , "0"   , "20") // "44", "MKVE2CVA"           
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "0"   , "54"  , "20") // "45", "MKVE2CVB"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "54"  , "932" , "20") // "46", "ZRV2"                   
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "932" , "1051", "20") // "47", "ZRVE2ZR"            
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1051", "1056", "20") // "48", "ZRA3_C"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1056", "1090", "20") // "49", "ZRA3_D"              
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1090", "1109", "20") // "50", "ZRA2_C"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1109", "1241", "20") // "51", "ZRVM2"               
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1241", "1964", "20") // "52", "ZRVT4"               
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "1964", "208" , "20") // "53", "ZRVE2TX"            
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "2084", "2652", "20") // "54", "ZRVT2"               
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "2652", "2785", "20") // "55", "ZRVE2OT"           
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "2785", "3861", "20") // "56", "SAVT4"               
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "3861", "4010", "20") // "57", "SAVC"                 
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4049", "4076", "20") // "61", "SAA6_I"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4076", "4081", "20") // "62", "SAA6_C"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4081", "4181", "20") // "63", "SAVE2SA"           
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1280", "1258", "20") // "83", "MKA7_I"      
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1258", "1235", "20") // "84", "MKA2_I"      
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1056", "1072", "20") // "85", "ZRA1_D"       
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1072", "1090", "20") // "86", "ZRA2_D"       
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1056", "1074", "20") // "87", "ZRA3_I"       
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "1074", "1090", "20") // "88", "ZRA4_I"       
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "4031", "4053", "20") // "89", "SAA1_D"      
  //establecerLTV(appname, windowtitle, user, password, Vias.CERO,  Vias.CERO, "4053", "4076", "20") // "90", "SAA6_D"      
  //establecerLTV(appname, windowtitle, user, password, Vias.UNOB,  Vias.UNOB, "3862", "4031", "20") // "92", "SAA1_C"             
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4010", "4049", "20") // "94", "SAVA3A8"            
  //establecerLTV(appname, windowtitle, user, password, Vias.DOSB,  Vias.DOSB, "4181", "4300", "20") // "95", "SAVA4A5"            


   Log_AddEntry(1, "Script", "[script %s] Ending Loki demo script", scriptname);

  //TerminateAplicationWithWindow(appname, windowtitle);  

}
