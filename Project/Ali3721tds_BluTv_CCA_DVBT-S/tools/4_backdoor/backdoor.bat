
set /p choice="(1. allfalsh 2. NoEncryptapp 3.Encryptapp ):"
if %choice% EQU 1 mk_rs232 param_allfalsh.ini
if %choice% EQU 2 mk_rs232 param_NoEncryptapp.ini
if %choice% EQU 3 mk_rs232 param_encrypted_app.ini
@echo move Jxn9I3Uj2Lo3pv_goLmmLg_F.pem.up
pause