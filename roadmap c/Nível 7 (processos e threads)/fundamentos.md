# Fundamentos

- Processos: são instâncias de um programa, um processo pode ser tanto de usuário, quanto de sistema, cada um com seu grau de permissões, os processos reservam recursos, controlam os arquivos e hardwares que serão utilizados pelo programa, destinam e reservam memória. O processo é único e não consegue não possui outros processos dentro, somente Threads.

- Threads: são pequenas unidades de execução que compartilham recursos do processo. As threads permitem usar melhor os recursos reservados pelo processo, tendo em vista são menos custosas para criar e gerenciar pelo SO.

## Concorrência vs. Paralelismo 

- Concorrência: Quando os processos compartilham de um mesmo recurso, para isso o SO tem que gereênciar quando cada um irá utilizar o recurso.

- Paralelismo: Quando o uso de recursos é feito de forma simultanea, dividindo um núcleos e threads, mesmo em um sistema com vários núcleos, algumas tarefas só podem ser feitas por meio da concorrência, como é o caso do acesso a um banco de dados

# Possíveis problemas: 

- Sincronização inadequada: Acontece quando não há uma boa sincronização entre processos/threads, o que pode causar erros de inconsistência, de acesso e até mesmo travamentos.

- Condições de corrida: Quando dois processos/threads tentam acessar um mesmo recurso ao mesmo tempos

- Deadlocks: Quando ambos processos/threads esperam por recursos que o outro está utilizando, ficando travados (Proc. A precisa do recurso que B está usando e Proc. B precisa do recurso que A está utilizando.)

- Starvation: Quando um processos/threads com menor prioridade nunca recebe os recursos que precisa para continuar a operação, pois estão sendo destinados a recursos com maior prioridade.

# Estratégias para evitar conflitos:

- Locks: Estratégias para permitir que apenas um recurso seja utilizado por apenas um processos/threads por vez. São principalmente 3 estratégias (Mutex, Read/Write Lock e Spinlock)
	- Mutex: Bloqueia o recursor para ter acesso exclusivo a ele.
	- Read/Write Lock: Permite multiplas leituras, mas apenas uma escrita.
	- Spinlock: Fica monitorando se um recurso é liberado (não é recomendado quando se desesa baixo consumo)

- Atomicidade: Só libera o acesso aos recursos quando todo o processo for finalizado, ou cancela toda a operação caso ocorra algum erro, ou seja, só salva se toda a operação der certo.

- Barreiras: Só continua o processo quanto todas os processos/threads chegam no mesmo nível.

# Modelos de Execução:

- Execução preemptiva: O sistema operacional faz a gestão da liberação de recursos e coordenação dos processos/threads, é o padrão hoje em dia. Sua principal caracteristica é que pode interromper um processos/threads para liberar os recursos para outro.

- Execução cooperativa: Os próprios processos/threads se coordenam para informar se estão utilziando determinado recurso ou não, é menos usado hoje em dia, sendo mais comum em sistemas embarcados, pois é necessário confiar que nenhum processos/threads irá monopolizar um determinado recurso.

# pthread.h
- mutex: Usado para bloquear um recurso até o fim de sua utilização, evitando condições de corrida.
- condition (cond): Usando para informar a uma determinada thread que o recurso que ela espera está.

# semaphore.h
- semaphore (sem): Limita o acesso a um determinado recurso até a quantidade informado no semaphore
- Ideal para quando um recurso pode ser acessado por mais de uma thread ao mesmo tempo, mas acima de uma determinada quantidade o acesso deve ser bloqueado.
- Muito utilizada em conjunto com pthread.h para informar quantas threads podem compartilhar um mesmo recurso ao mesmo tempo, imagine uma cozinha com um chefe que faz um prato e informa quando ele está pronto (mutex), mas esse prato após pronto pode ser pego por N threads, sendo que a primeira que pegar bloqueia o prato (recurso), até entregar ao cliente.

# threads.h
- Mais intuitiva e menos verbosa que a pthread.h, entretanto também mais limitada.
- Não tem integração direta com a semaphore.h e seu uso em conjunto é desestimulado, por poder causar comportamento indeterminado.