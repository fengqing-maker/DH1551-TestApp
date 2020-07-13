@echo ######### Please select the bmp file(castpal_logo.bmp) in bmp2logo tool first!! #########
del /a /f castpal_logo.m2v
bmp2logo.exe castpal_logo.bmp
pause
@echo ######### Now add the castpal logo head after bmp2logo run ok #########
LogoCreate  castpal_logo.m2v
pause