## Program do sterownika plc bazowanego na raspberry pi pico

### Instalacja na linux arch

```bash
git clone --recurse-submodules https://github.com/karlowiczpl/arm-gryf1.git
````
#### Następnie zaaktualizuj Cmake i pobierz arm-none-eabi

  ```bash
  yay -Syu
  yay -S arm-none-eabi-gcc 
  yay -S cmake
  ```
#### Kompilacja
```bash
  cd <lokalizacja>/arm-gryf1/
  mkdir build
  cd build
  cmake ..
  make
```
