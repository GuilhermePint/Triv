# Triv
Movimentação de Mouse com HandTracking

Projeto da matéria de IHS ministrado pelo professor Bruno Prado

## Dependências
python-uinput <br>
python-opencv <br>
mediapipe <br>
Xlib

## Como rodar:
* Para fazer uso do código basta apenas dar um ```make``` na pasta do projeto.<br>
* É necessário também possuir uma webcam para fazer o uso do programa. O código foi feito para pegar o primeiro dispositivo de vídeo disponível no computador

## Uso:
* Após o comando ```make``` será necessário fornecer acesso sudo ao programa, tendo em vista que o .py não possui permissões para acessar o dispositivo Uinput disponível no Linux.
* Quando executado com sucesso o programa irá criar um frame com a imagem da WebCam em um tamanho de 640x480, a partir daí a primeira mão que for identificada pela câmera será a responsável pelos movimentos
* Para movimentar o mouse apenas o dedo indicador poderá estar levantado
* Para efetuar um clique com o botão esquerdo do mouse, o dedão e o indicador devem estar "levantados". Assim quando o dedão se distânciar suficientemente do dedo indicador, o botão esquerdo do mouse será ativado.
* Para efetuar um clique com o botão direito do mouse, o dedo do meio e o indicador devem estar levantados. Assim quando os 2 dedos estiverem próximos o suficente, o botão direito do mouse será ativado.
* Para fechar o programa, apertando a tecla "Q" do teclado ou levantando os 5 dedos da mão por 80 frames o programa será encerrado.

### Solução de alguns problemas:
>TypeError: 'numpy._DTypeMeta' object is not subscriptable

Atualizar a biblioteca numpy:
```
sudo pip install --upgrade numpy
```
<br>
