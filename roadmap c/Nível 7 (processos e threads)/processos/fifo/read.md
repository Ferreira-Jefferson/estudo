O fico é um o uso de pipes ou processos nomeados são a maneira que se usa para criar comunicação entre processos que não compartilham de um mesmo pai.

para isso e criado um arquivo especial que será utilizado na comunicação entre os processos, isso pode ser feito com o comando: mkfifo nome_fifo

Produtor: é chamado de produtor o processo que irá enviar/criar a mensagem.
Consumidor: o consumidor é aquele que irá consumir a mensagem criada pelo produtor

Como a comunicação entre fifos é unidimensional, em alguns momentos um processo pode se o produtor em outros o consumidor

É importante saber o caminho exato do aonde o arquivo fifo está para que a comunicação ocorra, algumas estratégias são criar o fifo sempre em uma pasta comum, passar o caminho do arquivo via argumento do programa, ou o uso de sockets