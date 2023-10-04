import os
import time

# Abra o arquivo do dispositivo do mouse para escrita
mouse_device = os.open("/dev/input/mouse2", os.O_WRONLY)

# Emule um clique do botão direito do mouse (pressionando)
os.write(mouse_device, bytearray(b'\n\x00\x00'))
time.sleep(1)  # Aguarde um curto período de tempo para simular o clique
# Emule a liberação do botão direito do mouse
os.write(mouse_device, bytearray(b'\x08\x00\x00'))

# Feche o arquivo do dispositivo do mouse
os.close(mouse_device)