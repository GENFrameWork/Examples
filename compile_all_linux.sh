#!/bin/sh
echo -------------------------------------------------------------
OUTFILE="../../../../../Output.txt"
export OUTFILE
printf "Start process ... \n\n"
START_TIME=$(date +%s)
date >> Output.txt
printf "Examples Linux PC x64 ... \n\n"

printf "Examples Base Linux PC x64 ... \n"
sh ./../GEN/Batch/compile_linux.sh Base/AppBaseExample/Platforms/Linux /x64 appbaseexample
sh ./../GEN/Batch/compile_linux.sh Base/Canvas2DDisplay/Platforms/Linux /x64 canvas2ddisplay
sh ./../GEN/Batch/compile_linux.sh Base/MemCtrlExample/Platforms/Linux /x64 memctrlexample
sh ./../GEN/Batch/compile_linux.sh Base/NotAppExample/Platforms/Linux /x64 notappexample

printf "Examples Console Linux PC x64 ... \n"
sh ./../GEN/Batch/compile_linux.sh Console/BinConnPro/Platforms/Linux /x64 binconnpro
sh ./../GEN/Batch/compile_linux.sh Console/Databases/Platforms/Linux /x64 databases
sh ./../GEN/Batch/compile_linux.sh Console/MiniWebServer/Platforms/Linux /x64 miniwebserver
sh ./../GEN/Batch/compile_linux.sh Console/ScriptsExample/Platforms/Linux /x64 scriptsexample 

printf "Examples Graphics Linux PC x64 ... \n"
sh ./../GEN/Batch/compile_linux.sh Graphics/Canvas2D/Platforms/Linux /x64 canvas2d
sh ./../GEN/Batch/compile_linux.sh Graphics/UI_Options/Platforms/Linux /x64 ui_options

END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))
HOURS=$((ELAPSED_TIME / 3600))
MINUTES=$(((ELAPSED_TIME % 3600) / 60 ))
SECONDS=$((ELAPSED_TIME % 60))

printf "End process.\nProcessing time: %02d:%02d:%02d\n" "$HOURS" "$MINUTES" "$SECONDS"

