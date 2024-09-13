#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*FreqPar = Listar as 15 duplas*/
typedef struct
{
    int jogo1, jogo2, freq;
} FreqPar;
/*Freqjogo = Listar os 15 números únicos */
typedef struct
{
    int jogo, freq, Ultimojogo;
} Freqjogo;
/*Este tipo Aposta = dados do apostador*/
typedef struct
{
    char nome[32], cpf[11];
    int numeros[6], numerosAc, numerojogo;
} Aposta;
/* função Gerar 5000 sorteios realmente aleatórios, em um vetor e matrizes que
 * serão usados em todo o programa.*/
void inicializa(Freqjogo freqUnica[60], FreqPar MFreqpar[][60], int totaljogo)
{
    srand(time(NULL));
    for (int i = 0; i < totaljogo; i++)
    {
        freqUnica[i].jogo = i + 1;
        freqUnica[i].freq = 0;
        freqUnica[i].Ultimojogo = -1;
        for (int j = 0; j < totaljogo; j++)
        {
            MFreqpar[i][j].jogo1 = i + 1;
            MFreqpar[i][j].jogo2 = j + 1;
            MFreqpar[i][j].freq = 0;
        }
    }
}
void gerarsorteio(int sorteios[5000][6], int indiceSorteio, int qtdNumeros,
                  int totaljogo)
{
    int numeros[totaljogo], x, Troca;
    for (int i = 0; i < totaljogo; i++)
    {
        numeros[i] = i + 1;
    }
    for (int i = 0; i < qtdNumeros; i++)
    {
        Troca = rand() % (totaljogo - i);
        x = numeros[i];
        numeros[i] = numeros[Troca + i];
        numeros[Troca + i] = x;
        sorteios[indiceSorteio][i] = numeros[i];
    }
}
/* Os sorteios armazenados na matriz sorteios[][], um sorteio em cada linha.
 */
void gerarsorteios(int sorteios[5000][6], int qtdSorteios, int qtdNumeros,
                   int totaljogo)
{
    for (int i = 0; i < qtdSorteios; i++)
    {
        gerarsorteio(sorteios, i, qtdNumeros, totaljogo);
    }
}
/*Funcao que exibe todos os sorteios realizados, imprimindo os dados contidos na
 * matriz sorteios.*/
void mostrarsorteios(int sorteios[5000][6], int qtdSorteios, int qtdNumeros)
{
    for (int i = 0; i < qtdSorteios; i++)
    {
        printf("Jogo %04d:    ", i + 1);
        for (int j = 0; j < qtdNumeros; j++)
        {
            printf("%02d ", sorteios[i][j]);
        }
        printf("\n");
    }
}
void estatisticas(int sorteios[5000][6], int qtdSorteios, int qtdNumeros,
                  int totaljogo, Freqjogo freqUnica[60],
                  FreqPar freqPar[][60])
{
    /* Quantidade de vezes que cada número */
    for (int i = 0; i < qtdSorteios; i++)
    {
        for (int j = 0; j < qtdNumeros; j++)
        {
            int jogo1 = sorteios[i][j];
            freqUnica[jogo1 - 1].freq++;
            freqUnica[jogo1 - 1].Ultimojogo = i;
            /*as 15 duplas que mais saíram nos sorteios*/
            for (int k = j + 1; k < qtdNumeros; k++)
            {
                int jogo2 = sorteios[i][k];
                freqPar[jogo1 - 1][jogo2 - 1].freq++;
                freqPar[jogo2 - 1][jogo1 - 1].freq++;
            }
        }
    }
}
/*Ordem crescente,mais saíram nos sorteios*/
void VetorFreq(Freqjogo frequencias[60], Freqjogo freq_ordenadas[60],
               int totaljogo)
{
    int MaiorFreq;
    Freqjogo x;
    for (int i = 0; i < totaljogo; i++)
    {
        freq_ordenadas[i] = frequencias[i];
    }

    for (int i = 0; i < totaljogo; i++)
    {
        MaiorFreq = i;
        for (int j = i + 1; j < totaljogo; j++)
        {
            if (freq_ordenadas[MaiorFreq].freq < freq_ordenadas[j].freq)
            {
                MaiorFreq = j;
            }
        }
        if (MaiorFreq != i)
        {
            x = freq_ordenadas[i];
            freq_ordenadas[i] = freq_ordenadas[MaiorFreq];
            freq_ordenadas[MaiorFreq] = x;
        }
    }
}
/*mostrar na tela quantidade de vezes que cada jogo q saiu.*/
void mostrarfreqUnica(Freqjogo freq[60], int totaljogoprit)
{
    for (int i = 0; i < totaljogoprit; i++)
    {
        printf("Numero %02d = %03d vezes.\n", freq[i].jogo, freq[i].freq);
    }
}
/*  Listar as 15 duplas */
void VetorFreqPares(FreqPar MFreqpar[60][60], FreqPar vetorPares[60 * 60],
                    int totaljogo)
{
    int MaiorFreq, k = 0;
    FreqPar x;
    for (int i = 0; i < totaljogo; i++)
    {
        for (int j = i + 1; j < totaljogo; j++)
        {
            vetorPares[k] = MFreqpar[i][j];
            k++;
        }
    }
    for (int i = 0; i < k; i++)
    {
        MaiorFreq = i;
        for (int j = i + 1; j < k; j++)
        {
            if (vetorPares[MaiorFreq].freq < vetorPares[j].freq)
            {
                MaiorFreq = j;
            }
        }
        if (MaiorFreq != i)
        {
            x = vetorPares[i];
            vetorPares[i] = vetorPares[MaiorFreq];
            vetorPares[MaiorFreq] = x;
        }
    }
}
/*mostrar na tela a quantidade de vezes que cada dupla saiu.*/
void mostrarFreqPares(FreqPar freq[60 * 60], int totalDuplasImprimir)
{
    for (int i = 0; i < totalDuplasImprimir; i++)
    {
        printf("Numero %02d e %02d = %03d vezes.\n", freq[i].jogo1, freq[i].jogo2,
               freq[i].freq);
    }
}
void mostrarUltimojogo(Freqjogo freq[60], int totaljogo, int totalSorteios)
{
    for (int i = 0; i < totaljogo; i++)
    {
        printf("Numero %02d = ", freq[i].jogo);
        if (freq[i].Ultimojogo == totalSorteios - 1)
        {
            printf("saiu no ultimo sorteio.\n");
        }
        else if (freq[i].Ultimojogo == -1)
        {
            printf("nunca foi sorteado.\n");
        }
        else
        {
            printf("não sai a %02d sorteio seguido.\n",
                   totalSorteios - freq[i].Ultimojogo - 1);
        }
    }
}
/* Simular uma jogada para 3 usuários diferentes*/
void capturaApostas(Aposta apostas[3], int Apostas, int Numeros,
                    int totaljogo)
{
    for (int i = 0; i < Apostas; i++)
    {
        printf("Digite o nome do apostador:\n");
        scanf("%s", apostas[i].nome);
        printf("Digite o CPF do apostador:\n");
        scanf("%s", apostas[i].cpf);
        printf("Digite os %d numeros da aposta:\n", Numeros);
        for (int j = 0; j < Numeros;)
        {
            int valido = 1;
            scanf("%d", &(apostas[i].numeros[j]));
            if (!(apostas[i].numeros[j] >= 1 && apostas[i].numeros[j] <= totaljogo))
            {
                printf("O numero apostado eh invalido. Jogue novamente (de 1 a %d).\n",
                       totaljogo);
                valido = 0;
                continue;
            }
            for (int k = 0; k < j; k++)
            {
                if (apostas[i].numeros[j] == apostas[i].numeros[k])
                {
                    printf(
                        "O numero apostado ja foi usado neste jogo. Jogue novamente\n");
                    valido = 0;
                    break;
                }
            }
            if (valido)
            {
                j++;
            }
        }
        apostas[i].numerosAc = 0;
        apostas[i].numerojogo = 0;
    }
}
void verificaApostas(Aposta apostas[3], int Apostas, int sorteios[5000][6],
                     int QTSorteios, int QTNumeros)
{
    for (int i = 0; i < QTSorteios; i++)
    {
        for (int j = 0; j < Apostas; j++)
        {
            int acertos = 0;
            for (int k = 0; k < QTNumeros; k++)
            {
                for (int l = 0; l < QTNumeros; l++)
                {
                    if (apostas[j].numeros[k] == sorteios[i][l])
                    {
                        acertos++;
                        break;
                    }
                }
            }
            if (acertos > apostas[j].numerosAc)
            {
                apostas[j].numerosAc = acertos;
                apostas[j].numerojogo = i;
            }
        }
    }
}
void mostraApostas(Aposta apostas[3], int numApostas)
{
    for (int i = 0; i < numApostas; i++)
    {
        printf("Parabéns %s,você acertou %02d números! Sorteio %04d\n",
               apostas[i].nome, apostas[i].numerosAc, apostas[i].numerojogo + 1);
    }
}

int main(void)
{
    int sorteios[5000][6];
    Freqjogo freqUnica[60], vetorOFreq[60];
    FreqPar MFreqpar[60][60], vetorPares[60 * 60];
    Aposta apostas[3];
    inicializa(freqUnica, MFreqpar, 60);
    gerarsorteios(sorteios, 5000, 6, 60);
    estatisticas(sorteios, 5000, 6, 60, freqUnica, MFreqpar);
    VetorFreq(freqUnica, vetorOFreq, 60);
    VetorFreqPares(MFreqpar, vetorPares, 60);

    printf("\n 1) Gerar 5000 sorteios realmente aleatórios, em um vetor, cada um "
           "com 6 números únicos (01 a 60)\n\n");
    mostrarsorteios(sorteios, 5000, 6);

    printf("\n 2) a) Quantidade de vezes que cada numero saiu nos sorteios "
           "(Ordem crescente).\n\n");
    mostrarfreqUnica(freqUnica, 60);

    printf("\n\n 2) b) Listar as 15 duplas que mais sairam nos sorteios.\n\n");
    mostrarFreqPares(vetorPares, 15);

    printf("\n\n 2) c) Listar os 15 numeros unicos que mais sairam nos sorteios "
           "(Ordem decrescente de repeticoes).\n\n");
    mostrarfreqUnica(vetorOFreq, 15);

    printf("\n\n 2) d) Listar de 01 a 60 a quantidade de jogadas desde a última "
           "vez que o número foi sorteado. \n\n");
    mostrarUltimojogo(freqUnica, 60, 5000);

    printf("\n\n 3) Simular uma jogada para 3 usuários diferentes, com os "
           "seguintes dados: \n\n");
    capturaApostas(apostas, 3, 6, 60);
    verificaApostas(apostas, 3, sorteios, 5000, 6);

    printf("\n\n 4) Após as jogadas dos 3 usuários, indicar quantos números cada "
           "usuário acertou, em um único sorteio, com base nos 5000 sorteios "
           "anteriores.\n\n");
    mostraApostas(apostas, 3);

    return 0;
}