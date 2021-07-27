#include <iostream>
#include "quadro.cpp"

using namespace std;

#define CRC "100000100110000010001110110110111"

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaEnlaceDadosTransmissora(Quadro quadro);
Quadro CamadaEnlaceDadosTransmissoraControleDeErro(Quadro quadro);
Quadro CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro quadro);
Quadro CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro quadro);
Quadro CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro quadro);
void MeioDeComunicacao(Quadro fluxoBrutoDeBits);
void CamadaEnlaceDadosReceptora(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErro(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(Quadro quadro);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(Quadro quadro);
void CamadaDeAplicacaoReceptora(Quadro quadro);
void AplicacaoReceptora(string mensagem);

int tipoDeControleDeErro;

int main() {
    AplicacaoTransmissora();
    return 0;
}

void AplicacaoTransmissora() {
    cout << "Digite: \n0 para controle de erro por bit de paridade par,\n1 para controle de erro por bit de paridade ímpar \n2 para controle de erro por CRC" << endl;
    cin >> tipoDeControleDeErro;
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;
    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem) {
    Quadro quadro;
    quadro.inserir_mensagem(mensagem);
    CamadaEnlaceDadosTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissora(Quadro quadro) {
    quadro = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    MeioDeComunicacao(quadro);
}

Quadro CamadaEnlaceDadosTransmissoraControleDeErro(Quadro quadro) {
    //int tipoDeControleDeErro = 2;
    switch (tipoDeControleDeErro) {
        case 0:
            quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1:
            quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2:
            quadro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
    }

    return quadro;
}

Quadro CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(Quadro quadro) {
    quadro.setParidadePar();
    return quadro;
}

Quadro CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(Quadro quadro) {
    quadro.setParidadeImpar();
    return quadro;
}

Quadro CamadaEnlaceDadosTransmissoraControleDeErroCRC(Quadro quadro) {
    quadro.inserir_CRC(CRC);
    return quadro;
}

void MeioDeComunicacao(Quadro fluxoBrutoDeBits) {
    Quadro fluxoBrutoDeBitsPontoA = Quadro(fluxoBrutoDeBits.bits), fluxoBrutoDeBitsPontoB = Quadro();

    int erro;
    const float porcentagemDeErros = 0.2; // entre 0 e 1
    
    for (int i = 0; i < N_BITS; i++) {
        if ( (float) rand() / (float) RAND_MAX > porcentagemDeErros) {
            fluxoBrutoDeBitsPontoB.bits[i] = fluxoBrutoDeBitsPontoA.bits[i];
        } else {
            fluxoBrutoDeBitsPontoB.bits[i] = (fluxoBrutoDeBitsPontoA.bits[i] == 1) ? 0 : 1;
            erro++;
        }
    }

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBitsPontoB);
}

void CamadaEnlaceDadosReceptora(Quadro quadro) {
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    CamadaDeAplicacaoReceptora(quadro);
}

void CamadaEnlaceDadosReceptoraControleDeErro(Quadro quadro) {
    //int tipoDeControleDeErro = 2;
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
    if (!quadro.verificarParidadePar()) {
        cout << "MENSAGEM COM ERRO, MENSAGEM NÃO POSSUI PARIDADE PAR" << endl;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(Quadro quadro) {
    if (!quadro.verificarParidadeImpar()) {
        cout << "MENSAGEM COM ERRO, MENSAGEM NÃO POSSUI PARIDADE IMPAR" << endl;
    }
}

void CamadaEnlaceDadosReceptoraControleDeErroCRC(Quadro quadro) {
    if (quadro.CRC_checksum(CRC) == false) {
        cout << "ERRO ENCONTRADO POR CRC!" << endl;
    }
}

void CamadaDeAplicacaoReceptora(Quadro quadro) {
    AplicacaoReceptora(quadro.retornar_mensagem());
}

void AplicacaoReceptora(string mensagem) {
    cout << "A mensagem recebida foi:\n" << mensagem << endl;
}