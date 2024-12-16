// Arquivo principal do projeto (main.cpp)
#include <iostream>
#include <vector>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

using namespace std;

int main() {
    vector<Cidade*> cidades;
    vector<Trajeto*> trajetos;
    vector<Transporte*> transportes;
    vector<Passageiro*> passageiros;
    vector<Viagem*> viagens;

    int opcao;
    do {
        cout << "\n--- Sistema Controlador de Viagens ---\n";
        cout << "1. Cadastrar Cidade\n";
        cout << "2. Cadastrar Trajeto\n";
        cout << "3. Cadastrar Transporte\n";
        cout << "4. Cadastrar Passageiro\n";
        cout << "5. Cadastrar Viagem\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: {
                string nome;
                cout << "Digite o nome da cidade: ";
                getline(cin, nome);
                cidades.push_back(new Cidade(nome));
                cout << "Cidade cadastrada com sucesso!\n";
                break;
            }
            case 2: {
                string origem, destino;
                char tipo;
                int distancia;

                cout << "Digite o nome da cidade de origem: ";
                getline(cin, origem);
                cout << "Digite o nome da cidade de destino: ";
                getline(cin, destino);
                cout << "Digite o tipo de trajeto (A - Aquatico, T - Terrestre): ";
                cin >> tipo;
                cout << "Digite a distancia em km: ";
                cin >> distancia;
                cin.ignore();

                Cidade* cidadeOrigem = nullptr;
                Cidade* cidadeDestino = nullptr;

                for (auto& cidade : cidades) {
                    if (cidade->getNome() == origem) cidadeOrigem = cidade;
                    if (cidade->getNome() == destino) cidadeDestino = cidade;
                }

                if (cidadeOrigem && cidadeDestino) {
                    trajetos.push_back(new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia));
                    cout << "Trajeto cadastrado com sucesso!\n";
                } else {
                    cout << "Erro: Cidade de origem ou destino nao encontrada.\n";
                }
                break;
            }
            case 3: {
                string nome, localAtual;
                char tipo;
                int capacidade, velocidade, distanciaDescanso, tempoDescanso;

                cout << "Digite o nome do transporte: ";
                getline(cin, nome);
                cout << "Digite o tipo do transporte (A - Aquatico, T - Terrestre): ";
                cin >> tipo;
                cout << "Digite a capacidade de passageiros: ";
                cin >> capacidade;
                cout << "Digite a velocidade (km/h): ";
                cin >> velocidade;
                cout << "Digite a distancia entre descansos (km): ";
                cin >> distanciaDescanso;
                cout << "Digite o tempo de descanso (horas): ";
                cin >> tempoDescanso;
                cin.ignore();
                cout << "Digite o nome da cidade atual do transporte: ";
                getline(cin, localAtual);

                Cidade* cidadeAtual = nullptr;
                for (auto& cidade : cidades) {
                    if (cidade->getNome() == localAtual) cidadeAtual = cidade;
                }

                if (cidadeAtual) {
                    transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distanciaDescanso, tempoDescanso, cidadeAtual));
                    cout << "Transporte cadastrado com sucesso!\n";
                } else {
                    cout << "Erro: Cidade atual nao encontrada.\n";
                }
                break;
            }
            case 4: {
                string nome, localAtual;

                cout << "Digite o nome do passageiro: ";
                getline(cin, nome);
                cout << "Digite o nome da cidade atual do passageiro: ";
                getline(cin, localAtual);

                Cidade* cidadeAtual = nullptr;
                for (auto& cidade : cidades) {
                    if (cidade->getNome() == localAtual) cidadeAtual = cidade;
                }

                if (cidadeAtual) {
                    passageiros.push_back(new Passageiro(nome, cidadeAtual));
                    cout << "Passageiro cadastrado com sucesso!\n";
                } else {
                    cout << "Erro: Cidade atual nao encontrada.\n";
                }
                break;
            }
            case 5: {
                string nomeTransporte, nomeOrigem, nomeDestino;
                vector<Passageiro*> passageirosViagem;

                cout << "Digite o nome do transporte: ";
                getline(cin, nomeTransporte);
                cout << "Digite o nome da cidade de origem: ";
                getline(cin, nomeOrigem);
                cout << "Digite o nome da cidade de destino: ";
                getline(cin, nomeDestino);

                Cidade* origem = nullptr;
                Cidade* destino = nullptr;
                Transporte* transporte = nullptr;

                // Encontrar cidade de origem e destino
                for (auto& cidade : cidades) {
                    if (cidade->getNome() == nomeOrigem) origem = cidade;
                    if (cidade->getNome() == nomeDestino) destino = cidade;
                }

                // Encontrar transporte
                for (auto& t : transportes) {
                    if (t->getNome() == nomeTransporte) transporte = t;
                }

                if (!origem || !destino) {
                    cout << "Erro: Cidade de origem ou destino nao encontrada.\n";
                    break;
                }

                if (!transporte) {
                    cout << "Erro: Transporte nao encontrado.\n";
                    break;
                }

                // Adicionar passageiros à viagem
                int numPassageiros;
                cout << "Digite o numero de passageiros: ";
                cin >> numPassageiros;
                cin.ignore();

                for (int i = 0; i < numPassageiros; ++i) {
                    string nomePassageiro;
                    cout << "Digite o nome do passageiro " << i + 1 << ": ";
                    getline(cin, nomePassageiro);

                    Passageiro* passageiro = nullptr;
                    for (auto& p : passageiros) {
                        if (p->getNome() == nomePassageiro) {
                            passageiro = p;
                            break;
                        }
                    }

                    if (passageiro) {
                        passageirosViagem.push_back(passageiro);
                    } else {
                        cout << "Erro: Passageiro " << nomePassageiro << " nao encontrado.\n";
                    }
                }

                // Criar a viagem
                Viagem* novaViagem = new Viagem(transporte, passageirosViagem, origem, destino);
                viagens.push_back(novaViagem); // Adiciona ao vetor de viagens

                cout << "Viagem cadastrada com sucesso!\n";
                break;
            }

            case 6:
                cout << "Saindo do sistema...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 6);

    // Liberação de memória
    for (auto& cidade : cidades) delete cidade;
    for (auto& trajeto : trajetos) delete trajeto;
    for (auto& transporte : transportes) delete transporte;
    for (auto& passageiro : passageiros) delete passageiro;
    for (auto& viagem : viagens) delete viagem;

    return 0;
}