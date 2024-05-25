## Program do sterownika plc bazowanego na raspberry pi pico

### Instalacja na linux arch

  git clone --recurse-submodules https://github.com/karlowiczpl/arm-gryf1.git

#### Następnie zaaktualizuj Cmake i pobierz arm-none-eabi

  yay -Syu
  yay -S arm-none-eabi-gcc 
  yay -S cmake 

#### Kompilacja
wejdz do lokalizacji pliku
  cd <lokalizacja>/arm-gryf1/
utwórz folder na pliki kompilacyjne
  mkdir build
wejdz do tego folderu 
  cd build
zainicjuj cmake
  cmake ..
skompiluj 
  make
  
