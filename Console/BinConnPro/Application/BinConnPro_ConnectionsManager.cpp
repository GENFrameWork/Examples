/**-------------------------------------------------------------------------------------------------------------------
*
* @file       BinConnPro_ConnectionsManager.cpp
*
* @class      BINCONNPRO_CONNECTIONSMANAGER
* @brief      Example Binary Connexion Protocol Connexions class
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#include "XPublisher.h"

#include "DIOFactory.h"
#include "DIOStreamUDPLocalEnumServers.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOStreamCipher.h"

#include "CipherAES.h"

#include "BinConnPro_ApplicationData.h"
#include "BinConnPro_Protocol.h"

#include "BinConnPro_ConnectionsManager.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::BINCONNPRO_CONNECTIONSMANAGER
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CONNECTIONSMANAGER::BINCONNPRO_CONNECTIONSMANAGER() : DIOPROTOCOL_CONNECTIONSMANAGER()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::~BINCONNPRO_CONNECTIONSMANAGER
* @brief      Destructor
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
BINCONNPRO_CONNECTIONSMANAGER::~BINCONNPRO_CONNECTIONSMANAGER()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::Ini
* @brief      Initialize connection manager
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]    isserver : is Server or client mode
* @param[in]    isenumlocalactive : Is active the enum (local)
* @param[in]    port : port connection.
* @param[in]    applicationdata : application data global
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::Ini(bool isserver, bool isenumlocalactive, int port, BINCONNPRO_APPLICATIONDATA* applicationdata)
{
  this->applicationdata = applicationdata;

  diostreamTCPIPcfg = new DIOSTREAMTCPIPCONFIG();
  if(!diostreamTCPIPcfg) return false;

  if(isenumlocalactive)
    {
      diostreamudplocalenumservers = new DIOSTREAMUDPLOCALENUMSERVERS();
      if(!diostreamudplocalenumservers)  return false;

      diostreamudplocalenumservers->SetID(BINCONNPRO_CONNECTIONSMANAGER_LOCALENUMID);
      diostreamudplocalenumservers->SetPort(BINCONNPRO_CONNECTIONSMANAGER_LOCALENUMPORT);
      diostreamudplocalenumservers->SetSearchTimeout(3);

      diostreamenumservers = diostreamudplocalenumservers;
    }

  diostreamTCPIPcfg->SetRemotePort(port);

  return DIOPROTOCOL_CONNECTIONSMANAGER::Ini(isserver, diostreamTCPIPcfg, diostreamudplocalenumservers);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetNConnected
* @brief      Get number of connections connected
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetNConnected()
{
  int nprotocolconnectionsON = 0;
  int navailable              = ProtocolConnections_GetNAvailable();

  for(int c=0; c<navailable; c++)
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = ProtocolConnections_Get(c);
      if(protocolconnection)
        {
          BINCONNPRO_PROTOCOL* protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
          if(protocol)
            {
              if(protocol->IsInitialized())
                {
                  nprotocolconnectionsON++;
                }
            }
        }
    }

  return nprotocolconnectionsON;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetByDIOStream
* @brief      Get connections by DIOstream
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  diostream : diostream to search associated connection.
*
* @return     DIOPROTOCOL_CONNECTION* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* BINCONNPRO_CONNECTIONSMANAGER::ProtocolConnections_GetByDIOStream(DIOSTREAM* diostream)
{
  if(protocolconnections.IsEmpty())  return NULL;

  for(int index=0; index<ProtocolConnections_GetNAvailable(); index++)
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          BINCONNPRO_PROTOCOL* protocol = (BINCONNPRO_PROTOCOL*)protocolconnection->GetDIOProtocol();
          if(protocol)
            {
              DIOSTREAMCIPHER* diostreamcipher = (DIOSTREAMCIPHER*)protocolconnection->GetDIOProtocol()->GetDIOStream();
              if(diostreamcipher)
                {
                  if(diostreamcipher->GetDIOStreamBase() == diostream) return protocolconnection;
                }
            }
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::End
* @brief      End Connection manager
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::End()
{
  bool status = DIOPROTOCOL_CONNECTIONSMANAGER::End();

  if(diostreamTCPIPcfg)
    {
      delete diostreamTCPIPcfg;
      diostreamTCPIPcfg = NULL;
    }

  if(diostreamudplocalenumservers)
    {
      delete diostreamudplocalenumservers;
      diostreamudplocalenumservers = NULL;
    }

  return status;
}





#ifdef BINCONNPRO_CONNECTIONSMANAGER_CIPHERPROTOCOL

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol
* @brief      Create protocol instance.
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOPROTOCOL* : DIO Protocol created
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol()
{
  CIPHERAES* cipher = new CIPHERAES();
  if(!cipher) return NULL;

  XBYTE inivector[] = BINCONNPRO_CONNECTIONSMANAGER_INIKEYENCRIPTION;
  XBYTE keydata[]   = BINCONNPRO_CONNECTIONSMANAGER_KEYENCRIPTION;

  CIPHERKEYSYMMETRICAL* key = new CIPHERKEYSYMMETRICAL();
  if(!key) return NULL;

  cipher->SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipher->SetPaddingType(XBUFFER_PADDINGTYPE_ZEROS);
  cipher->SetInitVector(inivector,sizeof(inivector));

  key->Set(keydata, sizeof(keydata));

  cipher->SetKey(key);

  DIOSTREAMCIPHER* diostreamcipher = new DIOSTREAMCIPHER(diostreamcfg, cipher);
  if(diostreamcipher)
    {
      DIOSTREAMTCPIP* diostreamTCPIP = (DIOSTREAMTCPIP*)diostreamcipher->GetDIOStreamBase();
      if(diostreamTCPIP)
        {
          diostreamTCPIP->SetEnumServers(diostreamenumservers);

          BINCONNPRO_PROTOCOL* protocol = new BINCONNPRO_PROTOCOL(diostreamcipher);
          if(protocol)
            {
              protocol->SetConnectionsManager(this);
              protocol->SetMaskID(BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLMASKID | (isserver?DIOPROTOCOL_CMDTYPE_ISSERVER:0));
              protocol->SetProtocolVersion(BINCONNPRO_PROTOCOL_VERSION, BINCONNPRO_PROTOCOL_SUBVERSION, BINCONNPRO_PROTOCOL_SUBVERSIONERR);
              protocol->SetApplicationVersion(applicationversion, applicationsubversion, applicationsubversionerr);
              protocol->GetApplicationName()->Set(applicationname);


              if(isserver)
                      protocol->GetDescription()->Set(__L("EGM Protocol Server"));
                else  protocol->GetDescription()->Set(__L("EGM Protocol Client"));

              if(!applicationdata)
                {
                  BINCONNPRO_APPLICATIONDATA* protocolapplicationdatanew = new BINCONNPRO_APPLICATIONDATA();
                  if(protocolapplicationdatanew)
                    {
                      protocol->SetApplicationData(protocolapplicationdatanew);
                      protocol->SetIsOwnApplicationData(true);
                    }
                }
               else
                {
                  protocol->SetApplicationData(applicationdata);
                  protocol->SetIsOwnApplicationData(false);
                }

              return (DIOPROTOCOL*)protocol;
            }

          diostreamcipher->Close();
          delete diostreamcipher;
        }
    }

  return NULL;
}

#else

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol
* @brief      Create protocol instance.
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOPROTOCOL* : DIO Protocol created
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* BINCONNPRO_CONNECTIONSMANAGER::CreateProtocol()
{
  DIOSTREAMTCPIP* diostreamTCPIP = (DIOSTREAMTCPIP*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
  if(diostreamTCPIP)
    {
      diostreamTCPIP->SetEnumServers(diostreamenumservers);

      BINCONNPRO_PROTOCOL* protocol = new BINCONNPRO_PROTOCOL(diostreamTCPIP);
      if(protocol)
        {
          protocol->SetMaskID(BINCONNPRO_CONNECTIONSMANAGER_PROTOCOLMASKID | (isserver?DIOPROTOCOL_CMDTYPE_ISSERVER:0));

          if(isserver)
                    protocol->GetDescription()->Set(__L("EGM Protocol Server"));
              else  protocol->GetDescription()->Set(__L("EGM Protocol Client"));

          if(!applicationdata)
              {
                BINCONNPRO_APPLICATIONDATA* protocolapplicationdatanew = new BINCONNPRO_APPLICATIONDATA();
                if(protocolapplicationdatanew)
                  {
                    protocol->SetApplicationData(protocolapplicationdatanew);
                    protocol->SetIsOwnApplicationData(true);
                  }
              }
             else
              {
                protocol->SetApplicationData(applicationdata);
                protocol->SetIsOwnApplicationData(false);
              }

          return (DIOPROTOCOL*)protocol;
        }

      diostreamTCPIP->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostreamTCPIP);
    }

  return NULL;
}

#endif





#ifdef BINCONNPRO_CONNECTIONSMANAGER_CIPHERPROTOCOL

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol
* @brief      Delete Protocol instance
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  dioprotocol : DIO Protocol to delete.
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol(DIOPROTOCOL* dioprotocol)
{
  if(!dioprotocol)  return false;

  DIOSTREAMCIPHER*      diostreamcipher = (DIOSTREAMCIPHER*)dioprotocol->GetDIOStream();
  CIPHERAES*            cipher          = (CIPHERAES*)diostreamcipher->GetCipher();
  CIPHERKEYSYMMETRICAL* key             = (CIPHERKEYSYMMETRICAL*)cipher->GetKey();

  if(dioprotocol->IsOwnApplicationData())
    {
      BINCONNPRO_APPLICATIONDATA* applicationdata =  (BINCONNPRO_APPLICATIONDATA*)dioprotocol->GetApplicationData();
      if(applicationdata)
        {
          delete applicationdata;
          dioprotocol->SetApplicationData(NULL);
        }
    }

  if(diostreamcipher) diostreamcipher->Close();

  delete cipher;
  delete key;
  delete dioprotocol;

  delete diostreamcipher;

  return true;
}

#else

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol
* @brief      Delete Protocol instance
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  dioprotocol : DIO Protocol to delete.
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool BINCONNPRO_CONNECTIONSMANAGER::DeleteProtocol(DIOPROTOCOL* dioprotocol)
{
  if(!dioprotocol)  return false;

  DIOSTREAMTCPIP* diostreamTCPIP = (DIOSTREAMTCPIP*)dioprotocol->GetDIOStream();

  if(dioprotocol->IsOwnApplicationData())
    {
      BINCONNPRO_APPLICATIONDATA* applicationdata =  (BINCONNPRO_APPLICATIONDATA*)dioprotocol->GetApplicationData();
      if(applicationdata) delete applicationdata;
    }

  delete dioprotocol;

  if(diostreamTCPIP)
    {
      diostreamTCPIP->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostreamTCPIP);
    }

  return true;
}

#endif



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void BINCONNPRO_CONNECTIONSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void BINCONNPRO_CONNECTIONSMANAGER::Clean()
{
  isenumlocalactive               = false;
  applicationdata                 = NULL;
  diostreamudplocalenumservers    = NULL;
  diostreamTCPIPcfg               = NULL;
}

