Atualizar o firmware do ESP8266
Testar o sensor via Serial
Desenvolver o sistema que:
    captura os dados do sensor de fluxo
    armazena
    verifica se tem internet. 
        Tem? Envia para o enpoint
        Não tem? Continua tentando.
    Cria o circuito
        Entra 5v
        Converte para 3.3v com até 250mA de corrente.
        Lê sensor de fluxo
        Usa o ESP8266 para comunicação via internet (Ver se vai usar direto no roteador ou em outro ESP8266)
    Enviar para fabricação
    Compra peças
Sistema:
    Criar endpoint de recebimento de dados do sensor de fluxo
    Verifica se o sensor é incapaz de comunicar e alertar
    Mostrar gráficos
    Mostrar armazenamento
Solda
Atualiza cada ESP8266
Testa
Implementa

======
Espruino
Gravando o espruino no ESP8266:
baixar o esptool.py:
https://github.com/themadinventor/esptool

baixar o espruino:
https://github.com/espruino/EspruinoBuilds/tree/master/ESP8266

conectar o ESP8266 ao USBSerial:
https://raw.githubusercontent.com/guyz/pyesp8266/master/esp8266_pinout.png
http://iot-playground.com/images/articles/016/esp8266-reflash-firmware.png

Depois, rode:
cd Sites/esptool
./esptool.py -p /dev/cu.usbserial write_flash 0x00000 EspruinoBuilds-master/ESP8266/espruino_esp8266_board_0x00000.bin 0x010000 EspruinoBuilds-master/ESP8266/espruino_esp8266_board_0x10000.bin

Vai mostrar:
Connecting...
Erasing flash...
Wrote 62464 bytes at 0x00000000 in 6.1 seconds (81.9 kbit/s)...
Erasing flash...
Wrote 371712 bytes at 0x00010000 in 36.6 seconds (81.3 kbit/s)...

Leaving...

Desplugue e plug novamente o USB

======
Comunicando com espruino:
Mude a combinação dos fios para a imagem 3

Instale no chrome a IDE:
https://chrome.google.com/webstore/detail/espruino-web-ide/bleoifhkdalbjfbobjackfdifdneehpo?hl=pt-BR

Vá em settings >> communications:
Baud Rate: 9600

Clique em connect, selecione /dev/cu.usbserial


======
NodeMCU
https://github.com/nodemcu/nodemcu-devkit/wiki/Getting-Started-on-OSX

Instalar o driver:
https://www.silabs.com/Support%20Documents/Software/Mac_OSX_VCP_Driver.zip

Gravando o espruino no ESP8266:
baixar o esptool.py:
https://github.com/themadinventor/esptool

conectar o ESP8266 ao USBSerial:
https://raw.githubusercontent.com/guyz/pyesp8266/master/esp8266_pinout.png
http://iot-playground.com/images/articles/016/esp8266-reflash-firmware.png

Baixar o NodeMCU
https://github.com/nodemcu/nodemcu-firmware/releases

Depois, rode:
cd Sites/esptool
./esptool.py --port=/dev/cu.usbserial write_flash  -fm=dio -fs=32m 0x00000 nodemcu_float_0.9.6-dev_20150704\ 2.bin

Vai mostrar:
Connecting...
Erasing flash...
Wrote 462848 bytes at 0x00000000 in 45.4 seconds (81.6 kbit/s)...

Desplugue e plug novamente o USB


======
Comunicando com NODEMCU:
Mude a combinação dos fios para a imagem 3

Abra o esplorer
Mude as configurações para:
    porta /dev/cu.usbserial
    baudrate 9600
Aperte em Open, deve aparecer:

PORT OPEN 9600

Communication with MCU...
Got answer! AutoDetect firmware...

Can't autodetect firmware, because proper answer not received.


Cole o script do lado esquerdo
https://github.com/nodemcu/nodemcu-devkit/wiki/A-Simple-First-Script

Aperte Save to ESP
Deve mostrar o script, linha por linha, na saída serial.


======
NodeLUa
http://nodelua.org/doc/tutorial/make-your-first-node/


Gravando o espruino no ESP8266:
baixar o esptool.py:
https://github.com/themadinventor/esptool

baixar o espruino:
http://nodelua.org/download_firmware

conectar o ESP8266 ao USBSerial:
https://raw.githubusercontent.com/guyz/pyesp8266/master/esp8266_pinout.png
http://iot-playground.com/images/articles/016/esp8266-reflash-firmware.png

Depois, rode:
cd Sites/esptool
./esptool.py -p /dev/cu.usbserial write_flash 0x00000 nodelua_8266.fw

Vai mostrar:
Connecting...
Erasing flash...
Wrote 62464 bytes at 0x00000000 in 6.1 seconds (81.9 kbit/s)...
Erasing flash...
Wrote 371712 bytes at 0x00010000 in 36.6 seconds (81.3 kbit/s)...

Leaving...

Desplugue e plug novamente o USB

======
Mude a combinação dos fios para a imagem 3

Instalação do minicom:
http://pbxbook.com/other/sw/minicom-2.2.zip

Configurar o minicom:
/opt/minicom/2.2/bin/minicom -s

Abra o terminal e digite:
/opt/minicom/2.2/bin/minicom -D /dev/cu.usbserial -b 115200 -c on

======
Testes rápidos
Abra o CoolTerm, conecte na porta serial com o baudRate 9600
Digite:

gpio.mode(3, gpio.OUTPUT)
gpio.write(3, gpio.UP)
gpio.write(3, gpio.DOWN)

======
URLs:
3.3V => http://kb.kaminskiengineering.com/node/171
AC to DC => http://www.elprocus.com/steps-to-convert-the-230v-ac-to-5v-dc/
GPIO API => http://esp8266.co.uk/tutorials/introduction-to-the-gpio-api/
Flow Sensor => http://www.esp8266.com/viewtopic.php?f=18&t=5624
NodeMCU API => https://github.com/nodemcu/nodemcu-firmware/wiki/nodemcu_api_en
Flow Sensor => http://labdegaragem.com/profiles/blogs/tutorial-como-utilizar-o-sensor-de-fluxo-de-agua
Flow Sensor => http://www.seeedstudio.com/wiki/G1'1/4_Water_Flow_sensor
Flow Sensor => http://www.seeedstudio.com/depot/datasheet/water%20flow%20sensor%20datasheet.pdf