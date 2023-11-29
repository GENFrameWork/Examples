/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Databases.cpp
* 
* @class      DATABASES
* @brief      Example Databases class
* @ingroup    EXAMPLES
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Databases.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XRand.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XConsole.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"

#include "HashMD5.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"

#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "DB_SQL_Result.h"

#include "APPLog.h"

#include "Databases_CFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(DATABASES, databases)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------

@fn         DATABASES::DATABASES()
@brief      Constructor
@ingroup    APPLICATION

@return     Does not return anything. 

--------------------------------------------------------------------------------------------------------------------*/
DATABASES::DATABASES() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DATABASES::~DATABASES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DATABASES::~DATABASES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::InitFSMachine()
{
  if(!AddState( DATABASES_XFSMSTATE_NONE            ,
                DATABASES_XFSMEVENT_INI             , DATABASES_XFSMSTATE_INI           ,
                DATABASES_XFSMEVENT_END             , DATABASES_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DATABASES_XFSMSTATE_INI             ,
                DATABASES_XFSMEVENT_NONE            , DATABASES_XFSMSTATE_NONE          ,
                DATABASES_XFSMEVENT_END             , DATABASES_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DATABASES_XFSMSTATE_END             ,
                DATABASES_XFSMEVENT_NONE            , DATABASES_XFSMSTATE_NONE          ,
                DATABASES_XFSMEVENT_INI             , DATABASES_XFSMSTATE_INI           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  GetApplicationName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*GetApplicationName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_DATABASES, APPDEFAULT_DIRECTORY_DATABASES);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------

  APP_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), DATABASES_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }

  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------

  console->Clear();
  Show_Header(true);

  //--------------------------------------------------------------------------------------

  if(APP_CFG.Log_IsActive())
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando sistema LOG"));
      console->PrintMessage(string.Get(), 1, true, false);

      status = APP_LOG.Ini(&APP_CFG, APPLICATION_NAMEFILE , APPLICATION_VERSION
                                                          , APPLICATION_SUBVERSION
                                                          , APPLICATION_SUBVERSIONERR);

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      console->PrintMessage(stringresult.Get(), 0, false, true);

      XSTRING SO_ID;
      status = GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"),  GEN_VERSION.GetAppVersion()->Get());   
      XTRACE_PRINTMSGSTATUS(__L("S.O. version"), SO_ID.Get()); 

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
           
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false,  __L("Identificacion SO: %s"), SO_ID.Get());

      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
    }

  //--------------------------------------------------------------------------------------

  SetEvent(DATABASES_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::AppProc_Update()
{
  if(GetEvent()==DATABASES_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case DATABASES_XFSMSTATE_NONE       : break;

          case DATABASES_XFSMSTATE_INI        : if(GetExitType() == APPBASE_EXITTYPE_UNKNOWN)
                                                {
                                                  if(xtimerupdateconsole)
                                                    {
                                                      if(xtimerupdateconsole->GetMeasureSeconds() >= 1)
                                                        {
                                                          Show_AllStatus();
                                                          xtimerupdateconsole->Reset();
                                                        }

                                                      if(console->KBHit())
                                                        {
                                                          int key = console->GetChar();
                                                          KeyValidSecuences(key);
                                                        }
                                                    }
                                                }
                                              break;

          case DATABASES_XFSMSTATE_END        : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<DATABASES_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case DATABASES_XFSMSTATE_NONE   : break;

              case DATABASES_XFSMSTATE_INI    : break;

              case DATABASES_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::AppProc_End()
* @brief      AppProc_End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(DATABASES_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  DataBase_ChangeType(DB_SQL_DATABASE_TYPE_UNKNOWN);

  //--------------------------------------------------------------------------------------

  if(xmutexshowallstatus)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexshowallstatus);
      xmutexshowallstatus = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  //--------------------------------------------------------------------------------------

  APP_LOG.DelInstance();

  //--------------------------------------------------------------------------------------

  APP_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APP_LOG_ENTRY(XLOGLEVEL_WARNING, APP_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  switch(key)
    {
      case 'Q'  : // ESC Exit application
                  SetExitType(APPBASE_EXITTYPE_BY_USER);
                  break;

      case 'M'  : DataBase_ChangeType(DB_SQL_DATABASE_TYPE_MYSQL);       break;
      case 'L'  : DataBase_ChangeType(DB_SQL_DATABASE_TYPE_SQLITE);      break;
      case 'P'  : DataBase_ChangeType(DB_SQL_DATABASE_TYPE_POSTGRESQL);  break;

      case 'T'  : Database_DoTest();                                   break;

    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::DataBase_ChangeType(DB_SQL_DATABASE_TYPE type)
* @brief      DataBase_ChangeType
* @ingroup    APPLICATION
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::DataBase_ChangeType(DB_SQL_DATABASE_TYPE type)
{
  if(database)
    {
      database->Close();
      delete database;

      database = NULL;
    }

  database = DB_SQL_FACTORY::Create(type);

  return (database?true:false);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::Database_DoTest()
* @brief      Database_DoTest
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::Database_DoTest()
{
  XCHAR*              fields[DATABASES_TABLE_MAXFIELDS];
  DB_SQL_CONNECTION*  connection  = NULL;
  DB_SQL_QUERY*       query     = NULL;
  XSTRING             string;
  XSTRING             stringresult;
  bool                status;

  if(!database) return false;

  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(!datetime) return false;

  memset(fields, 0, (sizeof(XCHAR*)*DATABASES_TABLE_MAXFIELDS));

  connection  = database->CreateConnection();

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Creando Conexion "));
  console->PrintMessage(string.Get(), 1, true,false);

  stringresult = connection?__L("Ok."):__L("Error!");
  console->PrintMessage(stringresult.Get(), 0, false, true);
  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

  if(connection)
    {
      XSTRING str;

      if(APP_CFG.Database_GetURL()->IsEmpty())
             connection->SetOption(__L("URL")      , __L("127.0.0.1"));
        else connection->SetOption(__L("URL")      , APP_CFG.Database_GetURL()->Get());

      connection->SetOption(__L("DATABASE") , APP_CFG.Database_DatabaseName()->Get());

      if(database->GetType() ==  DB_SQL_DATABASE_TYPE_SQLITE)
        {
          XPATH path;

          GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_DATABASES, path);
          connection->SetOption(__L("PATH"), path.Get());
        }
       else
        {
          if(APP_CFG.Database_GetPort())
                 str.Format(__L("%d") , APP_CFG.Database_GetPort());
            else str.Format(__L("%d") , database->GetDefaultPort());

          connection->SetOption(__L("PORT"), str.Get());
        }

      connection->SetOption(__L("USER")     , APP_CFG.Database_GetUser()->Get());
      connection->SetOption(__L("PASSWORD") , APP_CFG.Database_GetPassword()->Get());

      str.Format(__L("%d"), APP_CFG.Database_GetTimeoutConnection());
      connection->SetOption(__L("TIMEOUT")  , str.Get());


      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Abriendo/conectando Base de datos"));
      console->PrintMessage(string.Get(), 1, true,false);

      status = database->Open();

      stringresult.Format(__L("%s Thread Safe: %s"), (status?__L("Ok."):__L("Error!")), (database->IsThreadSafe()?__L("Si"):__L("No")));
      console->PrintMessage(stringresult.Get(), 0, false, true);
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

      if(status)
        {
          /*--- ERASE TABLE -----------------------------------------------------------------------------------------------------*/

          string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Borrando tabla"));
          console->PrintMessage(string.Get(), 1, true,false);

          status = database->Table_Delete(DATABASES_TABLE_TEST_NAME);

          stringresult.Format((status?__L("Ok."):__L("Error!")));
          console->PrintMessage(stringresult.Get(), 0, false, true);
          APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

          /*--- CREATE TABLE ----------------------------------------------------------------------------------------------------*/


          bool isexist = false;

          database->Table_IsThere(DATABASES_TABLE_TEST_NAME, __L("id"), isexist);
          if(!isexist)
            {
              XDWORD nfields = 0;

              switch(database->GetType())
                {
                  case DB_SQL_DATABASE_TYPE_SQLITE          : { XCHAR*  sqllite_fields[] = {  __L("id int PRIMARY KEY")     ,
                                                                                              __L("name varchar(50)")       ,
                                                                                              __L("value float")            ,
                                                                                              __L("date DATETIME")
                                                                                           };

                                                                nfields = (sizeof(sqllite_fields)/sizeof(XCHAR*));

                                                                for(XDWORD c=0; c<nfields; c++)
                                                                  {
                                                                    fields[c] = sqllite_fields[c];
                                                                  }
                                                              }
                                                              break;

                  case DB_SQL_DATABASE_TYPE_MYSQL           : { XCHAR*  mysql_fields[]  = {  __L("id int")                  ,
                                                                                             __L("name varchar(50)")        ,
                                                                                             __L("value float")             ,
                                                                                             __L("date DATETIME")           ,
                                                                                             __L("PRIMARY KEY(id)")
                                                                                           };

                                                                nfields = (sizeof(mysql_fields)/sizeof(XCHAR*));

                                                                for(XDWORD c=0; c<nfields; c++)
                                                                  {
                                                                    fields[c] = mysql_fields[c];
                                                                  }
                                                              }
                                                              break;

                  case DB_SQL_DATABASE_TYPE_POSTGRESQL      : { XCHAR*  posgresql_fields[]  = { __L("id integer CONSTRAINT firstkey PRIMARY KEY") ,
                                                                                                __L("name varchar(50)")                           ,
                                                                                                __L("value float")                                ,
                                                                                                __L("date timestamp")                             ,
                                                                                              };

                                                                nfields = (sizeof(posgresql_fields)/sizeof(XCHAR*));

                                                                for(XDWORD c=0; c<nfields; c++)
                                                                  {
                                                                    fields[c] = posgresql_fields[c];
                                                                  }
                                                              }
                                                              break;
                }

              string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Creando tabla"));
              console->PrintMessage(string.Get(), 1, true,false);

              status = database->Table_Create(DATABASES_TABLE_TEST_NAME, fields, nfields);

              stringresult.Format((status?__L("Ok."):__L("Error!")));
              console->PrintMessage(stringresult.Get(), 0, false, true);
              APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

            }


          if(status)
            {

              /*--- WRITE REGISTERS -------------------------------------------------------------------------------------------------*/

              typedef struct  { int       ID;
                                XCHAR*    name;
                                float     value;

                              } DATAREGISTRY;

              DATAREGISTRY  registers[] = { { 1, __L("Sir Grah\xA0m")  ,  11.5f  },
                                            { 2, __L("Lord Mortimer")  ,   3.3f  },
                                            { 3, __L("Sir Lancelot")   ,   8.5f  },
                                            { 4, __L("Sir Ivanhoe")    ,  35.9f  }
                                          };

              query = database->CreateQuery();
              if(query)
                {
                  XSTRING querystring;

                  querystring.Empty();

                  database->Transaction();

                  switch(database->GetType())
                    {
                      case DB_SQL_DATABASE_TYPE_MYSQL       :
                      case DB_SQL_DATABASE_TYPE_SQLITE      : querystring.Format(__L("INSERT INTO %s (id,name,value,date) VALUES (?,?,?,?);")    , DATABASES_TABLE_TEST_NAME);  break;
                      case DB_SQL_DATABASE_TYPE_POSTGRESQL  : querystring.Format(__L("INSERT INTO %s (id,name,value,date) VALUES ($1,$2,$3,$4);"), DATABASES_TABLE_TEST_NAME);  break;
                    }

                  if(!querystring.IsEmpty())
                    {
                      query->Set(querystring.Get());

                      for(XDWORD c=0; c<(sizeof(registers)/sizeof(DATAREGISTRY)); c++)
                        {
                          datetime->Read();

                          query->Bind(0, registers[c].ID);
                          query->Bind(1, registers[c].name);
                          query->Bind(2, registers[c].value);
                          query->Bind(3, (*datetime));

                          string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Escribiendo registro"));
                          console->PrintMessage(string.Get(), 1, true,false);

                          status = database->Execute(query);

                          stringresult.Format(__L("name %s -> %s"), registers[c].name, (status?__L("Ok."):__L("Error!")));
                          console->PrintMessage(stringresult.Get(), 0, false, true);
                          APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

                          query->UnbindAll();
                        }

                      for(XDWORD c=10; c<300; c++)
                        {
                          datetime->Read();

                          query->Bind(0, (int)c);
                          query->Bind(1, __L("dsfjlsjfdsjfdlk"));
                          query->Bind(2, 10.5f);
                          query->Bind(3, (*datetime));

                          string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Escribiendo registro"));
                          console->PrintMessage(string.Get(), 1, true,false);

                          status = database->Execute(query);

                          stringresult.Format((status?__L("Ok.\r"):__L("Error!\n")));
                          console->PrintMessage(stringresult.Get(), 0, false, false);
                          APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

                          query->UnbindAll();
                        }

                      database->Commit();
                    }

                  /*--- READ No REGISTERS -----------------------------------------------------------------------------------------------*/

                  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Numero registros tabla"));
                  console->PrintMessage(string.Get(), 1, true,false);

                  XQWORD nrecords = 0;
                  database->Table_GetNRecords(DATABASES_TABLE_TEST_NAME, nrecords);

                  stringresult.Format(__L("%d registro(s)"), nrecords);
                  console->PrintMessage(stringresult.Get(), 0, false, true);
                  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());


                  /*--- READ REGISTER  --------------------------------------------------------------------------------------------------*/

                  querystring.Format(__L("SELECT id,name,value,date FROM %s WHERE name=\'Sir Grah\xA0m\';"), DATABASES_TABLE_TEST_NAME);
                  query->Set(querystring.Get());

                  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Leyendo registro"));
                  console->PrintMessage(string.Get(), 1, true,false);

                  status = database->Execute(query);

                  stringresult.Format((status?__L("Ok."):__L("Error!")));
                  console->PrintMessage(stringresult.Get(), 0, false, true);
                  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, __L("%s: %s")  , string.Get(), stringresult.Get());

                  if(status)
                    {
                      DB_SQL_RESULT* result = query->GetResult();
                      if(result)
                        {
                          result->ProcessRow();

                          while(result->HasNext())
                            {
                              DB_SQL_ROW*       row     = result->GetRow();
                              DB_SQL_ROWHEADER* header  = result->GetHeader();
                              XVARIANT          variant;

                              console->Printf(__L("   [%d]\n"), (int)result->GetCurrentRowIndex());

                              for(XDWORD e=0; e<result->GetNumColumns(); e++)
                                {
                                  XDWORD typerow = row->Get(e).GetType();

                                  console->Printf(__L("   [%s] = "), header->Get(e)->Get());

                                  switch(typerow)
                                    {
                                      case DB_SQL_VARIANT_TYPE_DATETIME   : { DB_SQL_DATETIME  datetime = (row->Get(e));
                                                                              XSTRING         string;

                                                                              datetime.GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
                                                                              console->Printf(__L("%s"), string.Get());
                                                                            }
                                                                            break;

                                      case DB_SQL_VARIANT_TYPE_STRING     : console->Printf(__L("%s"), (XCHAR*)row->Get(e));
                                                                            break;

                                      case DB_SQL_VARIANT_TYPE_INTEGER    : console->Printf(__L("%d"), (int)row->Get(e));
                                                                            break;

                                      case DB_SQL_VARIANT_TYPE_FLOAT      : console->Printf(__L("%f"), (float)(row->Get(e)));
                                                                            break;

                                                            default       : break;
                                    }

                                  console->Printf(__L("\n"));
                                }

                              result->Next();
                            }
                        }
                    }

                  /*--- WAIT KEY --------------------------------------------------------------------------------------------------------*/

                  console->PrintMessage(__L(" "),0,false,true);
                  console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

                  /*---------------------------------------------------------------------------------------------------------------------*/

                  delete query;
                }
            }

          database->Close();
        }
    }

  delete connection;
  connection = NULL;
  database->SetConnection(connection);

  GEN_XFACTORY.DeleteDateTime(datetime);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::Show_AppStatus()
* @brief      Show_AppStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;

  XDWORD  total;
  XDWORD  free;

  GEN_XSYSTEM.GetMemoryInfo(total,free);

  string  = __L("Memoria total");
  string2.Format(__L("%d Kb, libre %d Kb (el %d%%%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
  Show_Line(string, string2);


  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(datetime)
    {
      datetime->Read();

      string  = __L("Fecha ");
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
      Show_Line(string, string2);

      GEN_XFACTORY.DeleteDateTime(datetime);
    }


  if(xtimerglobal)
    {
      string  = __L("Tiempo de funcionamiento");
      xtimerglobal->GetMeasureString(string2, true);
      Show_Line(string, string2);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DATABASES::Show_DatabasesStatus()
* @brief      Show_DatabasesStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::Show_DatabasesStatus()
{
  XSTRING string;
  XSTRING string2;

  string  = __L("Tipo Base de datos");
  string2 = __L("N/A");

  if(database) string2 = database->GetTypeName();

  Show_Line(string, string2);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DATABASES::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DATABASES::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  if(Show_Header(false))      console->PrintMessage(__L(""),0, false, true);
  if(Show_AppStatus())        console->PrintMessage(__L(""),0, false, true);
  if(Show_DatabasesStatus())  console->PrintMessage(__L(""),0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DATABASES::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  xevent : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DATABASES::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_SCHEDULER   : { XSCHEDULER_XEVENT* event = (XSCHEDULER_XEVENT*)xevent;
                                      if(!event) return;

                                      //HandleEvent_Scheduler(event);
                                    }
                                    break;


    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DATABASES::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DATABASES::Clean()
{
  xtimerupdateconsole         = NULL;

  xmutexshowallstatus         = NULL;

  database                    = NULL;
}


#pragma endregion
