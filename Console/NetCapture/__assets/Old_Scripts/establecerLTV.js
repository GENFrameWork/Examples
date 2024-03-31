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


Vias = {
  CERO: 0,
  UNOA: 1,
  UNOB: 2,
  DOSA: 3,
  DOSB: 4
}

function posicionarRaton(appname, windowtitle, x, y) {

  XTRACE_PRINTCOLOR(1, "Funcion posicionarRaton", appname, posx, posy);

  var posx = Window_GetPosX(appname, windowtitle);
  var posy = Window_GetPosY(appname, windowtitle);

  //Posicion del texto "Establecer LTV" -> Objetivo identificar el jframe en vez de la posicion
  InpSim_Mouse_Click(posx + x, posy + y);

  //Revisar. El click no posiciona
  XTRACE_PRINTCOLOR(1, "La posición del puntero de la app %s es x = %d e y = %d", appname, posx, posy);

}

function despliegueLoginBarraHerramientas(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "FunciondespliegueLoginBarraHerramientas", appname);

  posicionarRaton(appname, windowtitle, 70, 40);
  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function cierreSesionUsuarioPe(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "Desplegando Login de Usuario en la Barra de Herramientas", appname);

  posicionarRaton(appname, windowtitle, 70, 40);

  //TAB para posicionarnos en "Inicio sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //TAB para posicionarnos en "Cierre sesion"
  InpSim_Key_ClickByLiteral("TAB", 1);
  //SPACEBAR para accionarlo
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  XTRACE_PRINTCOLOR(1, "Se pulsa el boton de cierre de sesion de usuario");

}

function loginSesionUsuarioPe(appname, windowtitle, user, password) {

  XTRACE_PRINTCOLOR(1, "Entrando en el login de Usuario");

  despliegueLoginBarraHerramientas(appname, windowtitle);

  XTRACE_PRINTCOLOR(1, "Volviendo al login de Usuario");

  // Rellenamos el campo "Usuario"
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(user, 1);
  XTRACE_PRINTCOLOR(1, "Introducido la clave de nombre del usuario %s", user);

  // Rellenamos el campo "Contraseña"
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(password, 1);
  XTRACE_PRINTCOLOR(1, "Introducida la clave de contraseña (%s) del usuario %s", password, user);

  // Accionamos el boton de "Aceptar"
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("ENTER", 1);
  XTRACE_PRINTCOLOR(1, "Se pulsa el boton de 'ACEPTAR' para el envio de credenciales", password, user);

}

function limpiarLTV(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "Entrando en limpiarLTV");

  var posx = Window_GetPosX(appname, windowtitle, maskbitmapname);
  var posy = Window_GetPosY(appname, windowtitle, maskbitmapname);

  posicionarRaton(appname, windowtitle, Window_GetPosX, Window_GetPosY);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

  XTRACE_PRINTCOLOR(1, "Saliendo de limpiarLTV");

}

function panelEstablecerLTV(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, desvio, causa, responsable) {

  XTRACE_PRINTCOLOR(1, "Entrando en panelEstablecerLTV");

  // Como buena practica conviene limpiar primero el panel
  limpiarLTV(appname, windowtitle);

  posicionarRaton(appname, windowtitle, 30, 310);


  // Rellenamos pkInicio
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pkInicio, 1);
  XTRACE_PRINTCOLOR(1, "Rellenado campo %s", pkInicio);

  // Rellenamos pkFin
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(pkFin, 1);
  XTRACE_PRINTCOLOR(1, "Rellenado campo %s", pkFin);

  // Rellenamos viaInicio
  InpSim_Key_ClickByLiteral("TAB", 1);
  for (i = 0; i < viaInicio; i++) {
    InpSim_Key_ClickByLiteral("DOWN ARROW", 1);
  }

  // Rellenamos velocidad
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByText(velocidad, 1);
  XTRACE_PRINTCOLOR(1, "Introducimos %s", velocidad);

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

  Sleep(3000);

}

function activarLTV(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "Entrando en panelEstablecerLTV");

  posicionarRaton(appname, windowtitle, 30, 310);

  //Pasamos por todas los elementos con tabulador
  for (i = 0; i < 9; i++) {
    InpSim_Key_ClickByLiteral("TAB", 1);
  }
  //Accionamos el boton de 'Activar' LTV
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}

function purgarLTV(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "Entrando en purgarLTV");

  posicionarRaton(appname, windowtitle, 130, 310);

  // Seleccionamos y accionamos el boton 'Purgar'
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);

}


function eliminarLTV(appname, windowtitle) {

  XTRACE_PRINTCOLOR(1, "Entrando en panelEliminarLTV");

  posicionarRaton(appname, windowtitle, 130, 310);

  //Escogemos la LTV a eliminar (buscar nuevo método)
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("DOWN ARROW", 1);

  // Nos deplazamos hasta el boton limpiar
  InpSim_Key_ClickByLiteral("TAB", 1);

  // Seleccionamos y accionamos el boton establecer
  InpSim_Key_ClickByLiteral("TAB", 1);
  InpSim_Key_ClickByLiteral("SPACEBAR", 1);
  Sleep(3000);

}

function pruebaCicloVidaCompletoLTV(appname, windowtitle) {

  var user = "Supervisor1";
  var password = "SUPERVISOR1";

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

function establecerLTV(appname, windowtitle, user, password, viaInicio, viaFin, pkInicio, pkFin, velocidad) {

  var user = "Supervisor1";
  var password = "SUPERVISOR1";

  XTRACE_PRINTCOLOR(1, "Condiciones previas:");
  XTRACE_PRINTCOLOR(1, "- Lanzar Contexto de Pruebas PE-CEM-ENCE-L3MB.");
  XTRACE_PRINTCOLOR(1, "- Lanzar MV ATS-CTC con CTC arrancado.");

  XTRACE_PRINTCOLOR(1, "Inicio test prueba001");

  panelEstablecerLTV(appname, windowtitle, pkInicio, viaInicio, pkFin, viaFin, velocidad, 0, 1, 1);
  activarLTV(appname, windowtitle);
  Sleep(3000);
  posicionarRaton(appname, windowtitle, 30, 310);

  XTRACE_PRINTCOLOR(1, "Fin test prueba001");

}

function main()
{

  var appname     = "java.exe";
  //var apppath     = "C:\\Program Files (x86)\\Common Files\\Oracle\\Java\\javapath_target_182481281\\" + appname;
  var windowtitle = "PCE_ZR";
  var maskbitmapname = "establecerLTV.png"

  //XTRACE_PRINTCOLOR(1, "Hacemos cierre e inicio de sesión");

  XTRACE_PRINTCOLOR(1, "Lanzando prueba de ciclo de vida completo de una LTV");

  //pruebaCicloVidaCompletoLTV(appname, windowtitle)

  var posx = Window_GetPosX(appname, windowtitle, maskbitmapname);
  var posy = Window_GetPosY(appname, windowtitle, maskbitmapname);

  XTRACE_PRINTCOLOR(1, "Position of %s %d, %d", appname, posx, posy);

  XTRACE_PRINTCOLOR(1, "Terminada bateria de tests");
  //TerminateAplicationWithWindow(appname, windowtitle);  

}
