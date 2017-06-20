copy "%1..\ogreBuild\sdk\bin\%3\*.dll" "%2"
mkdir "%2config"
mkdir "%2logs"
copy "%1config\*" "%2config"