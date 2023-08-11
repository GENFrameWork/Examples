
function PrintStatus(status)
{
  if(status)
    {
      Printf("Ok");
    }
   else
    {
      Printf("Error!");
    }

  Printf("\n");
}


function CompileProject(projectname, projectcompiledir, projectplatform)
{
  var pathproject   = projectcompiledir + projectname;
  var pathcmakelist = pathproject + "/Platforms/CMakeLists.txt";
  var pathplatform  = pathproject + "/Platforms/" + projectplatform;
  var status        = false;

  Printf("\nCompile project %-16s ... ", projectname);

  
  if(IsItExists(pathproject) == false)
    {
      Printf("Error: Project Not found!\n");
      return status;
    }
    
  if(IsItExists(pathcmakelist) == false)
    {
      Printf("Error: CMakeList.txt Not found!\n");
      return status;
    }

  if(IsItExists(pathplatform) == true)
    {
      Printf("x32 exists\n");
      return status;
    }

  PrintStatus(status);

  return status;   
}


function main()
{
  Printf("Compile Examples ... \n");

  if(System_GetType() == "Windows")
    {
      CompileProject("AppBaseExample", "../../../../../Examples/Base/", "Windows/x32");
    }
}

