
function Console_PrintStatus(status)
{
  if(status)
    {
      Console_Printf("Ok");
    }
   else
    {
      Console_Printf("Error!");
    }

  Console_Printf("\n");
}


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
      Console_Printf("x32 exists\n");
      return status;
    }

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

