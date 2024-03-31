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

function posicionarRaton(appname, windowtitle, x, y) {

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  //Posicion del texto "Establecer LTV" -> Objetivo identificar el jframe en vez de la posicion
  InpSim_Mouse_Click(posx + x, posy + y);

  //Revisar. El click no posiciona
  TracePrintColor(1, "The mouse position in the %s app has moved to x = %d and y = %d", appname, posx, posy);

}

function cierreSesionUsuarioPe(appname, windowtitle) {

  TracePrintColor(1, "Entering in the 'cierreSesionUsuarioPe' user function.");
  TracePrintColor(1, "Deploying user login menu from  the menu toolbar.");

  posicionarRaton(appname, windowtitle, 70, 40);

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

  posicionarRaton(appname, windowtitle, 70, 40);
  
  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 100);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 100);

  // Rellenamos el campo "Usuario"
  InpSim_Key_ClickByLiteral("TAB", 100);
  InpSim_Key_ClickByText(usr, 10);
  TracePrintColor(1, "Entered username: %s", usr);

  // Rellenamos el campo "Contraseña"
  InpSim_Key_ClickByLiteral("TAB", 1000);
  InpSim_Key_ClickByText(pswd, 10);
  TracePrintColor(1, "Entered password (%s) for the user (%s)", pswd, usr);

  // Accionamos el boton de "Aceptar"
  InpSim_Key_ClickByLiteral("TAB", 100);
  InpSim_Key_ClickByLiteral("ENTER", 100);

  TracePrintColor(1, "Exiting the 'loginSesionUsuarioPe' function.");

}

function limpiarLTV(appname, windowtitle, posx, posy) {

  TracePrintColor(1, "Entering the function 'limpiarLTV'");

  posicionarRaton(appname, windowtitle, posx, posy);

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
  limpiarLTV(appname, windowtitle);

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

  //var maskbitmapname  = "establecerLTV.png"
  
  TracePrintColor(1, "Entrando en panelEstablecerLTV");

  posicionarRaton(appname, windowtitle, posx, posy);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function purgarLTV(appname, windowtitle) {

  //var bitmapeliminar  = "eliminarLTV.png"
  
  TracePrintColor(1, "Entrando en purgarLTV");

  var posx = Window_GetPosX(appname, windowtitle, bitmapeliminar);
  var posy = Window_GetPosY(appname, windowtitle, bitmapeliminar);

  posicionarRaton(appname, windowtitle, posx, posy);

  // Seleccionamos y accionamos el boton 'Purgar'
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}


function eliminarLTV(appname, windowtitle) {

  //var bitmapeliminar  = "eliminarLTV.png"
  
  TracePrintColor(1, "Entrando en eliminarLTV");

  var posx = Window_GetPosX(appname, windowtitle, bitmapeliminar);
  var posy = Window_GetPosY(appname, windowtitle, bitmapeliminar);

  posicionarRaton(appname, windowtitle, posx, posy);

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
//  cierreSesionUsuarioPe(appname, windowtitle);
//  Sleep(1000);
//  loginSesionUsuarioPe(appname, windowtitle, user, password);
//  panelEstablecerLTV(appname, windowtitle, "2100", 2, "2600", 2, "20", 0, 1, 1);
//  activarLTV(appname, windowtitle);
//  Sleep(3000);
//  eliminarLTV(appname, windowtitle);
//  purgarLTV(appname, windowtitle);
//  posicionarRaton(appname, windowtitle, 30, 310);
//
//  TracePrintColor(1, "Fin test prueba001");
//
//}

function establecerLTV(appname, windowtitle, posx, posy, viaInicio, viaFin, pkInicio, pkFin, velocidad) {

  //var bitmapactivar = "activar.png"
  var scriptname  = GetNameScript() + ".js";
  var isActive;

  TracePrintColor(1, "Entering the function 'establecerLTV'");

  posicionarRaton(appname, windowtitle, posx, posy);

  panelEstablecerLTV(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, 0, 1, 1);
  //Log_AddEntry(1, "Script", "[script %s] El valor de isActive es %d", scriptname, isActive);
  isActive = Window_GetPosX(appname, windowtitle, bitmapestablecer);

  TracePrintColor(1, "Valor de posición de imagen es %08X  %d", isActive, isActive);
  
  if(isActive == Error.NOWINDOW || isActive == Error.NOBITMAP){
   TracePrintColor(1, "Valor de posición de imagen es un error-> %d", isActive);
   Log_AddEntry(1, "Script", "[script %s] El valor de isActive es %d. El CEM no retorna los datos de la LTV a Activar. No se puede Activar.", scriptname, isActive);
  }
  else{
   TracePrintColor(1, "Se activa el botón de activar LTV");
   activarLTV(appname, windowtitle);
   TracePrintColor(1, "Valor de posición de imagen es %d", isActive);
   //Log_AddEntry(1, "Script", "[script %s] El valor de isActive es %d", scriptname, isActive);
   Sleep(500);
  }
 
  limpiarLTV(appname, windowtitle);

  TracePrintColor(1, "Exiting the function 'establecerLTV'");
}

