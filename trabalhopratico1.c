#include <iostream>


using namespace std;

// ------ Processos ------

struct Processo {
  int pid;
  int tempoChegada;
  int tempoExecucao;
  int tempoConclusao;
  int tempoTurnaround;
  int tempoEspera;
};

// ----- Escalonamento Round Robin -----
void calcularTempos(Processo processos[], int n, int quantum) {
  int tempoRestante[n];
  for (int i = 0; i < n; i++) {
    tempoRestante[i] = processos[i].tempoExecucao;
  }
  int tempoAtual = 0;
  bool todosConcluidos = false;
  while (!todosConcluidos) {
    todosConcluidos = true;
    for (int i = 0; i < n; i++) {
      if (tempoRestante[i] > 0) {
        todosConcluidos = false;
        if (tempoRestante[i] > quantum) {
          tempoAtual = tempoAtual + quantum;
          tempoRestante[i] = tempoRestante[i] - quantum;
        } else {
          tempoAtual = tempoAtual + tempoRestante[i];
          processos[i].tempoConclusao = tempoAtual;
          tempoRestante[i] = 0;
        }
      }
    }
  }
}
void calcularTempoTurnaround(Processo processos[], int n) {
  for (int i = 0; i < n; i++)
    processos[i].tempoTurnaround =
        processos[i].tempoConclusao - processos[i].tempoChegada;
}

void calcularTempoEspera(Processo processos[], int n) {
  for (int i = 0; i < n; i++)
    processos[i].tempoEspera =
        processos[i].tempoTurnaround - processos[i].tempoExecucao;
}

void imprimirTabela(Processo processos[], int n) {
  cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
  cout << "|  Processo  |  Tempo de Chegada  |  Tempo de Execução  |  Tempo de Conclusão  |  Tempo de Turnaround  |  Tempo de Espera  |\n";
  cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
  for (int i = 0; i < n; i++) {
    cout << "|  " << processos[i].pid << "  |  " << processos[i].tempoChegada << "  |  " << processos[i].tempoExecucao << "  |  " << processos[i].tempoConclusao << "  |  " << processos[i].tempoTurnaround << "  |  " << processos[i].tempoEspera << "  |\n";
  }
  cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
}

int main() {
  int n, quantum;
  cout << "Digite o número de processos: ";
  cin >> n;
  cout << "Digite o quantum de tempo: ";
  cin >> quantum;

  Processo processos[n];
  cout << "Informe os detalhes dos processos:\n";
  // Le detalhes de cada processo
  for (int i = 0; i < n; i++) {
    cout << "Processo " << i + 1 << ":\n";
    processos[i].pid = i + 1;
    cout << "   Tempo de Chegada: ";
    cin >> processos[i].tempoChegada;
    cout << "   Tempo de Execução: ";
    cin >> processos[i].tempoExecucao;
  }

// Chama as funções para calcular os tempos
  calcularTempos(processos, n, quantum);
  calcularTempoTurnaround(processos, n);
  calcularTempoEspera(processos, n);

// ----- Results -----
  cout << "\nResultados do Escalonamento Round Robin:\n";
  imprimirTabela(processos, n);

  return 0;
}