echo @off

echo Sharpmake

mkdir sharpmake

xcopy tools\Sharpmake\deploy\*.* sharpmake\*.*
xcopy tools\Sharpmake\Sharpmake\bin\release\net6.0\*.dll sharpmake\*.dll
xcopy tools\Sharpmake\Sharpmake\bin\release\net6.0\*.exe sharpmake\*.exe
xcopy tools\Sharpmake\Sharpmake\bin\release\net6.0\*.json sharpmake\*.json
xcopy tools\Sharpmake\Sharpmake.Application\bin\release\net6.0\*.dll sharpmake\*.dll
xcopy tools\Sharpmake\Sharpmake.Application\bin\release\net6.0\*.exe sharpmake\*.exe
xcopy tools\Sharpmake\Sharpmake.Application\bin\release\net6.0\*.json sharpmake\*.json
xcopy tools\Sharpmake\Sharpmake.Generators\bin\release\net6.0\*.dll sharpmake\*.dll
xcopy tools\Sharpmake\Sharpmake.Generators\bin\release\net6.0\*.exe sharpmake\*.exe
xcopy tools\Sharpmake\Sharpmake.Generators\bin\release\net6.0\*.json sharpmake\*.json
