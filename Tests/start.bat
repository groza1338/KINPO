set program=..\Executable\Gvozdkov_run.exe

mkdir .\Output

set file=results.txt

echo --------------------------------------- > %file%
echo ------------- ERROR TESTS ------------- >> %file%
echo --------------------------------------- >> %file%

set num=01
echo.  >> %file%
echo error%num%.txt - Входного файла не существует >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=02
echo.  >> %file%
echo error%num%.txt - Пустой входной файл >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=03
echo.  >> %file%
echo error%num%.txt - Невозможно создать выходной файл >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=04
echo.  >> %file%
echo error%num%.txt - Несколько строк во входном файле >> %file%
echo.  >> %file%

echo ____________error%num%.txt____________ >> %file%
type .\Errors\error%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=05
echo.  >> %file%
echo error%num%.txt - Входной параметр не является числом >> %file%
echo.  >> %file%

echo ____________error%num%.txt____________ >> %file%
type .\Errors\error%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=06
echo.  >> %file%
echo error%num%.txt - Число не в диапазоне >> %file%
echo.  >> %file%

echo ____________error%num%.txt____________ >> %file%
type .\Errors\error%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=07
echo.  >> %file%
echo error%num%.txt - Число не в диапазоне >> %file%
echo.  >> %file%

echo ____________error%num%.txt____________ >> %file%
type .\Errors\error%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.txt" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=08
echo.  >> %file%
echo error%num%.amogus - У входного или выходного файла не .txt расширение >> %file%
echo.  >> %file%

echo Console output: >> %file%
"%program%" ".\Errors\error%num%.abobus" ".\error_output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Errors\output%num%.txt (
    type .\Errors\output%num%.txt >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

echo ---------------------------------------- >> %file%
echo ------------- NORMAL TESTS ------------- >> %file%
echo ---------------------------------------- >> %file%

set num=01
echo.  >> %file%
echo input%num%.txt - Три стены одинаковой высоты >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=02
echo.  >> %file%
echo input%num%.txt - Стены идут лесенкой. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=03
echo.  >> %file%
echo input%num%.txt - Между стенами есть одна яма. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=04
echo.  >> %file%
echo input%num%.txt - Между стенами две ямы. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=05
echo.  >> %file%
echo input%num%.txt - Две стены. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=06
echo.  >> %file%
echo input%num%.txt - Одна стена. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=07
echo.  >> %file%
echo input%num%.txt - Обратная пирамида из стен. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=08
echo.  >> %file%
echo input%num%.txt - Пирамида из стен. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

set num=09
echo.  >> %file%
echo input%num%.txt - Стены со случайными высотами. >> %file%
echo.  >> %file%

echo ____________input%num%.txt____________ >> %file%
type .\Input\input%num%.txt >> %file%
echo.  >> %file%
echo ___________________________________ >> %file%
echo.  >> %file%

echo Console output: (should be empty) >> %file%
"%program%" ".\Input\input%num%.txt" ".\Output\output%num%.txt" >> %file% 2>&1
echo.  >> %file%

if exist .\Output\output%num%.txt (
    echo ____________output%num%.txt____________ >> %file%
    type .\Output\output%num%.txt >> %file%
    echo.  >> %file%
    echo ___________________________________ >> %file%
) else (
    echo File output%num%.txt wasn't created. >> %file%
)
echo.  >> %file%

echo ------------------->> %file%

echo -------- END OF FILE -------- >> %file%