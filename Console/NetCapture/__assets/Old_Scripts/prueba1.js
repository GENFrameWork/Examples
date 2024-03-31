/* ****************************************************************************************************** */
/*                                                                                                        */
/*                                                         :::         :::::::::::    :::    :::    :::   */
/*   establecerLTV.js                                     :+:         :+:     :+:    :+:   :+:     :+:    */
/*                                                       +:+         +:+     +:+    +:+   +:+     +:+     */
/*   By: jaormaetxea                                    +#+         +#+     +#+    +#+  +#+      +#+      */
/*                                                     +#+         +#+     +#+    +#+ +#+       +#+       */
/*   Created: 2023/08/24 21:29:31 by jaormaetxea      +#+#+##+#   +#+#+##++#+    +#+   #++     +#+        */
/*   Updated: 2023/08/24 21:29:31 by jaormaetxea     #########   ###########    ###     ###   ###         */
/*                                                                                                        */
/* ****************************************************************************************************** */

// https://docs.oracle.com/cd/E19957-01/817-7307/keynav-0/index.html
function posicionarRaton(appname, windowtitle, x, y){
  
  XTRACE_PRINTCOLOR(1, "Funcion posicionarRaton", appname, posx, posy);

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  //Posicion del texto "Establecer LTV" -> Objetivo identificar el jframe en vez de la posicion
  InpSim_SetMouseClick(posx + x, posy + y);

  //Revisar. El click no posiciona
  XTRACE_PRINTCOLOR(1, "La posición del puntero de la app %s es x = %d e y = %d", appname, posx, posy);

}

function despliegueLoginBarraHerramientas(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "FunciondespliegueLoginBarraHerramientas", appname);

  posicionarRaton(appname, windowtitle, 70, 40);
  //TAB para posicionarnos en "Inicio sesion"
  InpSim_PressKeyByLiteral("TAB", 100);
  //SPACEBAR para accionarlo
  InpSim_PressKeyByLiteral("SPACEBAR", 100);

}

function cierreSesionUsuarioPe(appname, windowtitle) {
  
  XTRACE_PRINTCOLOR(1, "Desplegando Login de Usuario en la Barra de Herramientas", appname);

  posicionarRaton(appname, windowtitle, 70, 40);

  //TAB para posicionarnos en "Inicio sesion"
  InpSim_PressKeyByLiteral("TAB", 100);
  //TAB para posicionarnos en "Cierre sesion"
  InpSim_PressKeyByLiteral("TAB", 100);
  //SPACEBAR para accionarlo
  InpSim_PressKeyByLiteral("SPACEBAR", 100);

  XTRACE_PRINTCOLOR(1, "Se pulsa el boton de cierre de sesion de usuario");

}

function loginSesionUsuarioPe(appname, windowtitle, usr, pswd) {
  
  XTRACE_PRINTCOLOR(1, "Entrando en el login de Usuario");

  despliegueLoginBarraHerramientas(appname, windowtitle);

  XTRACE_PRINTCOLOR(1, "Volviendo al login de Usuario");

  // Rellenamos el campo "Usuario"
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByText(usr, 100);
  XTRACE_PRINTCOLOR(1, "Introducido la clave de nombre del usuario %s", usr);

  // Rellenamos el campo "Contraseña"
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByText(pswd, 1);
  XTRACE_PRINTCOLOR(1, "Introducida la clave de contraseña (%s) del usuario %s", pswd, usr);
  
  // Accionamos el boton de "Aceptar"
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("ENTER", 100);
  XTRACE_PRINTCOLOR(1, "Se pulsa el boton de 'ACEPTAR' para el envio de credenciales", pswd, usr);

}

function limpiarLTV (appname, windowtitle){

  XTRACE_PRINTCOLOR(1, "Entrando en limpiarLTV");

  posicionarRaton(appname, windowtitle, 30, 310);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++){
  InpSim_PressKeyByLiteral("TAB", 100);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_PressKeyByLiteral("SPACEBAR", 100);

  XTRACE_PRINTCOLOR(1, "Saliendo de limpiarLTV");

}

function panelEstablecerLTV(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, desvio, causa, responsable){

  XTRACE_PRINTCOLOR(1, "Entrando en panelEstablecerLTV");

  // Como buena practica conviene limpiar primero el panel
  limpiarLTV (appname, windowtitle);

  posicionarRaton(appname, windowtitle, 30, 310);


  // Rellenamos pkInicio
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByText(pkInicio, 100);
  XTRACE_PRINTCOLOR(1, "Rellenado campo %s", pkInicio);

  // Rellenamos pkFin
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByText(pkFin, 100);
  XTRACE_PRINTCOLOR(1, "Rellenado campo %s", pkFin);

  // Rellenamos viaInicio
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);

  // Rellenamos velocidad
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByText(velocidad, 100);
  XTRACE_PRINTCOLOR(1, "Introducimos %s", velocidad);

  // No asignamos desvío
  InpSim_PressKeyByLiteral("TAB", 100);

  // Rellenamos viaFin
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);

  // Rellenamos el campo causa
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);

  //Rellenamos el campo Responsable
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);

  // Nos deplazamos hasta el boton limpiar
  InpSim_PressKeyByLiteral("TAB", 100);

  // Seleccionamos y accionamos el boton establecer
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("SPACEBAR", 100);

  Sleep(3000);

}

function activarLTV (appname, windowtitle){

  XTRACE_PRINTCOLOR(1, "Entrando en panelEstablecerLTV");

  posicionarRaton(appname, windowtitle, 30, 310);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++){
  InpSim_PressKeyByLiteral("TAB", 100);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_PressKeyByLiteral("SPACEBAR", 100);

}

function purgarLTV (appname, windowtitle){

  XTRACE_PRINTCOLOR(1, "Entrando en purgarLTV");

  posicionarRaton(appname, windowtitle, 130, 310);

  // Seleccionamos y accionamos el boton 'Purgar'
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("SPACEBAR", 100);

}


function eliminarLTV (appname, windowtitle){

  XTRACE_PRINTCOLOR(1, "Entrando en panelEliminarLTV");

  posicionarRaton(appname, windowtitle, 130, 310);

  //Escogemos la LTV a eliminar (buscar nuevo método)
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);

  // Nos deplazamos hasta el boton limpiar
  InpSim_PressKeyByLiteral("TAB", 100);
  
  // Seleccionamos y accionamos el boton establecer
  InpSim_PressKeyByLiteral("TAB", 100);
  InpSim_PressKeyByLiteral("SPACEBAR", 100);
  Sleep(3000);

}

function prueba001(appname, windowtitle, user, password){

  var user        = "Supervisor1";
  var password    = "SUPERVISOR1";

  XTRACE_PRINTCOLOR(1, "Condiciones previas:");
  XTRACE_PRINTCOLOR(1, "- Lanzar Contexto de Pruebas PE-CEM-ENCE-L3MB.");
  XTRACE_PRINTCOLOR(1, "- Lanzar MV ATS-CTC con CTC arrancado.");

  XTRACE_PRINTCOLOR(1, "Inicio test prueba001");

  cierreSesionUsuarioPe(appname, windowtitle);
  Sleep(1000);
  loginSesionUsuarioPe(appname, windowtitle, user, password);
  panelEstablecerLTV(appname, windowtitle, "2100", 2, "2600", 2, "20", 0, 1, 1);
  activarLTV(appname, windowtitle);
  Sleep(3000);
  eliminarLTV(appname, windowtitle);
  purgarLTV(appname, windowtitle);
  posicionarRaton(appname, windowtitle, 30, 310);

  XTRACE_PRINTCOLOR(1, "Fin test prueba001");

}

function main()
{

  var appname     = "java.exe";
  //var apppath     = "C:\\Program Files (x86)\\Common Files\\Oracle\\Java\\javapath_target_182481281\\" + appname;
  var windowtitle = "PCE_ZR";

  XTRACE_PRINTCOLOR(1, "Lanzando bateria de tests");

  XTRACE_PRINTCOLOR(1, "Funcion posicionarRaton", appname, posx, posy);

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  //Posicion del texto "Establecer LTV" -> Objetivo identificar el jframe en vez de la posicion
  InpSim_SetMouseClick(posx + 0, posy + 0);
  InpSim_PressKeyByLiteral("ALT", 100);
  InpSim_PressKeyByLiteral("ALT", 100);
  InpSim_PressKeyByLiteral("RIGHT ARROW", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);
  InpSim_PressKeyByLiteral("DOWN ARROW", 100);

  XTRACE_PRINTCOLOR(1, "Terminada bateria de tests");
  //TerminateAplicationWithWindow(appname, windowtitle);  

}
