#include <bitset>
#include <algorithm> // std::reverse
#include <iostream>

using namespace std;

#define MAX_CHAR 3
#define N_BITS MAX_CHAR*8 + CRC_BITS + PARITY_BIT
#define Quadro_bits bitset<N_BITS>
#define Byte bitset<8>
#define CRC_BITS 32
#define PARITY_BIT 1


class Quadro {

    public:

        Quadro_bits bits;

        Quadro() {
            bits = Quadro_bits(0);
        }

        Quadro(Quadro_bits bits) {
            this->bits = bits;
        }

        void inserir_mensagem(string mensagem) {

            string bit_string; // string para armazenar os bits

            for (int i = 0; i < mensagem.size(); i++) {
                const int int_char = (int) mensagem[i]; // pega o valor em int do caractere
                const Byte char_bits = Byte(int_char); // converte o valor em bits
                bit_string.append(char_bits.to_string()); // guarda como string de bits
            }

            bits = Quadro_bits(bit_string); // converte a string em um quadro e armazena
            bits <<= CRC_BITS + PARITY_BIT; // shift dos bits para a esquerda, para caber o CRC e bit de paridade
        }

        string retornar_mensagem() {

            string mensagem;
            string bit_string = bits.to_string();
            
            for (int i = 0; i < MAX_CHAR; i++) {

                // posicao do byte sendo lido (bitset armazena ao contrario)
                const int byte_index = N_BITS - 8 * (i + 1) - CRC_BITS - PARITY_BIT;

                // le o byte
                string bit_str;
                for (int bit_index = byte_index; bit_index < byte_index + 8; bit_index++) {
                    bit_str.push_back(bit_string[bit_index]);
                }

                // converte em char e armazena
                Byte byte_char = Byte(bit_str);
                char c = (char) byte_char.to_ulong();
                mensagem.push_back(c);

                if (c == '\0') { // fim da mensagem
                    break;
                }
            }

            // reverte a mensagem ao estado original
            reverse(mensagem.begin(), mensagem.end());

            return mensagem;
        }

        bitset<CRC_BITS> resto_divisao_CRC(string CRC) {
            
            Quadro_bits dividendo(bits);

            Quadro_bits divisor(CRC);
            divisor <<= N_BITS - CRC_BITS - PARITY_BIT;

            for (int i = 0; i < N_BITS - CRC_BITS - PARITY_BIT; i++) {
                
                const int bit = N_BITS - 2 - i;

                if (dividendo[bit] == 1) {
                    dividendo ^= divisor; // XOR
                }

                divisor >>= 1;
            }

            return bitset<CRC_BITS>(dividendo.to_ulong()); // retorna o resto com o tamanho do CRC
        }

        void inserir_CRC(string CRC) {
            string resto_string = resto_divisao_CRC(CRC).to_string();
            string novo_bits = bits.to_string().replace(N_BITS - CRC_BITS - PARITY_BIT, CRC_BITS, resto_string);
            bits = Quadro_bits(novo_bits);
        }

        bool CRC_checksum(string CRC) {
            return resto_divisao_CRC(CRC).to_ulong() == 0;
        }

        // conta paridade da mensagem sem contar o bit de paridade, retorna true se par e false se impar
        bool contarParidadeMensagem() {
            bool parity = true;

            for (int i = 0; i < bits.size() - CRC_BITS - PARITY_BIT; i++) {
                if (bits[i]) {
                    parity = !parity;
                }
            }

            return parity;
        }

        void setParidadePar() {
            if(contarParidadeMensagem()) { // se mensagem tem paridade par
                bits[bits.size() - 1] = false; // seta bit de paridade como '0'
            } else { // se mensagem tem paridade impar
                bits[bits.size() - 1] = true; // seta bit de paridade como '1'
            }
        }

        void setParidadeImpar() {
            if(contarParidadeMensagem()) { // se mensagem tem paridade par
                bits[bits.size() - 1] = true; // seta bit de paridade como '1'
            } else { // se mensagem tem paridade impar
                bits[bits.size() - 1] = false; // seta bit de paridade como '0'
            }
        }

        // conta paridade da mensagem junto com bit de paridade e verifica se é par
        bool verificarParidadePar() {
            bool msgParity = contarParidadeMensagem();
            bool bitParityValue = bits[bits.size() - 1];
            // retorna true se mensagem junto com bit de paridade tem paridade par, falso caso contrário
            if ((msgParity && !bitParityValue) || (!msgParity && bitParityValue)) {
                return true;
            } else { // não tem paridade par, teve um erro
                return false;
            }
        }

        // conta paridade da mensagem junto com bit de paridade e verifica se é impar
        bool verificarParidadeImpar() {
            bool msgParity = contarParidadeMensagem();
            bool bitParityValue = bits[bits.size() - 1];
            // retorna true se mensagem junto com bit de paridade tem paridade impar, falso caso contrário
            if ((msgParity && bitParityValue) || (!msgParity && !bitParityValue)) {
                return true;
            } else { // não tem paridade impar, teve um erro
                return false;
            }
        }
};