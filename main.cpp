#include <iostream>
#include <bitset>

#define TAM_QUADRO 256

typedef bitset<TAM_QUADRO> Quadro;

using namespace std;

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaEnlaceDadosTransmissora(Quadro quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro(Quadro quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro quadro);
void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaEnlaceDadosReceptora(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErro(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(Quadro quadro);
void CamadaDeAplicacaoReceptora(Quadro quadro);
void AplicacaoReceptora(string mensagem);


int main() {
    AplicacaoTransmissora();
    return 0;
}

void AplicacaoTransmissora() {
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;
    CamadaDeAplicacaoTransmissora(mensagem);
}

// converte uma string em um bitset de tamanho fixo
Quadro str_to_bitset(string str) {

    string quadro_str;

    for (int i = 0; i < str.size(); i++) {
        // converte o caractere para um bitset de 1 byte e armazena em uma string
        quadro_str.append(bitset<8>((int) str[i]).to_string());
    }

    quadro_str.append(bitset<8>((int) '\0').to_string());

    return Quadro(quadro_str);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
    Quadro quadro = str_to_bitset(mensagem);
    MeioDeComunicacao(quadro);
}

void CamadaEnlaceDadosTransmissora(Quadro quadro) {
    // TODO
}

void CamadaEnlaceDadosTransmissoraControleDeErro(Quadro quadro) {
    int tipoDeControleDeErro = 0;
    switch (tipoDeControleDeErro) {
        case 0:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1:
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2:
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro quadro) {
    // TODO
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro quadro) {
    // TODO
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro quadro) {
    // TODO
}

void MeioDeComunicacao(Quadro quadro) {
    Quadro fluxoBrutoDeBitsPontoA = quadro, fluxoBrutoDeBitsPontoB(0);

    int erro;
    const int porcentagemDeErros = 0; // entre 0 e 1
    
    for (int i = 0; i < TAM_QUADRO; i++) {
        if ( (float) rand() / (float) RAND_MAX > porcentagemDeErros) {
            fluxoBrutoDeBitsPontoB[i] += fluxoBrutoDeBitsPontoA[i];
        } else {
            fluxoBrutoDeBitsPontoB[i] = (fluxoBrutoDeBitsPontoA[i] == 1) ? 0 : 1;
            erro++;
        }
    }

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaEnlaceDadosReceptora(Quadro quadro) {
    // TODO
}

void CamadaEnlaceDadosReceptoraControleDeErro(Quadro quadro) {
    int tipoDeControleDeErro = 0;
    switch (tipoDeControleDeErro) {
        case 0:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
            break;
        case 1:
            CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2:
            CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            break;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(Quadro quadro) {
    // TODO
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(Quadro quadro) {
    // TODO
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC(Quadro quadro) {
    // TODO
}

void CamadaDeAplicacaoReceptora(Quadro quadro) {
    // TODO
}

void AplicacaoReceptora(string mensagem) {
    cout << "A mensagem recebida foi:\n" << mensagem << endl;
}