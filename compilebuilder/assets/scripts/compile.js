// -------------------------------------------------------------------------------------------------------
// Compile: CMake + Ninja
// ------------------------------------------------------------------------------------------------------- 

function CompileProject(projectname, projectcompiledir, projectplatform)
{
  var pathproject   = projectcompiledir + projectname;
  var pathcmakelist = pathproject + "/Platforms/CMakeLists.txt";
  var pathplatform  = pathproject + "/Platforms/" + projectplatform;
  var status        = false;

  Console_Printf("\nCompile project %-16s ... ", projectname);
    
  if(IsItExists(pathproject) == false)
    {
      Console_Printf("Error: Project Not found!\n");
      return status;
    }
    
  if(IsItExists(pathcmakelist) == false)
    {
      Console_Printf("Error: CMakeList.txt Not found!\n");
      return status;
    }

  if(IsItExists(pathplatform) == true)
    {   
      if(RemoveDir(pathplatform) == false)
        {
          return status;
        }               
    }
    
  if(MakeDir(pathplatform) == false)
    {
      return status;
    } 

  if(ChangeDir(pathplatform) == false)
    {
      return status;
    } 

  status = MakeCommand("\"C:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Auxiliary/Build/vcvarsall.bat\" amd64_x86")
  
  status = MakeCommand("cmake -G Ninja ../.. ")

  Console_PrintStatus(status);

  return status;   
}


function main()
{
  Console_Printf("Compile Examples ... \n");

  if(System_GetType() == "Windows")
    {
      CompileProject("AppBaseExample", "../../../../../Examples/Base/", "Windows/x32");
    }
}

