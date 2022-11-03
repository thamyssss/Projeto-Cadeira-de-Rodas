# Projeto-Cadeira-de-Rodas
Projeto de cadeira de rodas motorizada controlada por sinais de EOG e EEG

Cadeiras de rodas manuais são a solução de locomoção mais comum para as pessoas
com deficiência motora muscular. Entretanto, pessoas que sofrem de doenças motoras
graves como paraplegia e distrofia muscular são incapazes de se locomover de forma
independente utilizando cadeira de rodas manuais uma vez que a funcionalidade das
mãos é fortemente afetada. Na maioria dos casos, estas pessoas são conscientes e suas
habilidades mentais e de movimento dos olhos não são comprometidas. Desta forma,
soluções tecnológicas que sejam capazes de ler os sinais cerebrais EEG
(Eletroencefalograma) e de movimento dos olhos EOG (Eletro-oculograma) de forma a
promover bem-estar para pessoas com deficiência motoras graves são cada vez mais
necessárias. 

Este trabalho propõe o uso dos sinais elétricos de EEG e de EOG como
solução capaz de permitir o controle de uma cadeira de rodas motorizada que possa ser
utilizada por pessoas com deficiência motora grave. Neste trabalho são utilizados um
aparelho de headset da EMOTIV Epoc de 14 sensores para medir os sinais EEG e EOG do
usuário, um microcontrolador de alta performance ESP32 e uma cadeira de rodas com
dois motores de 300 W alimentada por um conjunto de baterias de 34Ah. Os sinais de
EEG e EOG são processados remotamente por um LAPTOP e enviados via Wi-Fi para o
dispositivo microcontrolador programado para processar os sinais e produzir comandos
elétricos sequenciais para serem processados pela cadeira de rodas.