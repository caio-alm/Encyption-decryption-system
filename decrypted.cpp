#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const int INTERVALO = 6;

bool arq_table(const string& name_file, vector<pair<char, char>>& tabela);
string ext_text(const string& name_file);
bool decriptar_string(const string& txt_encrypted, const vector<pair<char, char>>& tabela_chaves);


int main() 
{
    vector<pair<char, char>> table_key;

    if (!arq_table("encrypter.txt", table_key)) {
        cout << "Erro na criação de keys.txt" << endl;
        return 1;
    }

    string txt_encrypted = ext_text("encrypter.txt");
    if (txt_encrypted.empty()) {
        cout << "Erro: O texto encriptado está vazio." << endl;
        return 1;
    }

    if (decriptar_string(txt_encrypted, table_key)) {
        cout << "Decriptação concluída." << endl;
        cout << "Arquivo decrypted.txt criado." << endl;
        cout << "Arquivo keys.txt criado." << endl;
    } else {
        cout << "Erro: Falha ao decriptar." << endl;
        return 1;
    }

    return 0;
}

bool arq_table(const string& name_file, vector<pair<char, char>>& tabela)
{
    ifstream txt_compac(name_file);
    ofstream keys("keys.txt");

    if (!txt_compac.is_open()) {
        cout << "Erro: Não foi possível abrir o arquivo " << name_file << endl;
        return false;
    }
    
    char c;
    int cont = 0;
    char char_primeiro = '\0';
    
    while (txt_compac.get(c)) {
        if (c == ':') {
            break;
        }
        
        cont++;
        
        if (cont % INTERVALO == 0) {
            if (char_primeiro == '\0') {
                char_primeiro = c;
            } 
            else {
                tabela.push_back({char_primeiro, c});
                char_primeiro = '\0'; 
            }
        }
    }

    keys << "AscII   InputChar     AscII   OutputChar" << endl;
    for (size_t i = 0; i < tabela.size(); i++) {
        keys << int(tabela.at(i).first) << " - " << tabela.at(i).first << "                " << int(tabela.at(i).second) << " - " << tabela.at(i).second << endl;
    }
    
    txt_compac.close();
    keys.close();

    return true;
}

string ext_text(const string& name_file)
{
    ifstream txt_compac(name_file);
    string texto_extraido;
    char c;
    int cont = 0;

    if (!txt_compac.is_open()) {
        cout << "Erro: Não foi possível abrir o arquivo " << name_file << endl; 
        return ""; 
    }

    while (txt_compac.get(c)) {
        if (c == ':') {
            break;
        }

        cont++;

        if (cont % INTERVALO != 0) {
            texto_extraido += c;
        }
    }

    while(txt_compac.get(c)) {
        texto_extraido += c;
    }

    txt_compac.close();

    return texto_extraido;
}

bool decriptar_string(const string& txt_encrypted, const vector<pair<char, char>>& tabela_chaves)
{
    string texto_decriptado = txt_encrypted; 

    for (size_t i = 0; i < txt_encrypted.length(); ++i) {
        char c_cifrado = txt_encrypted[i]; 

        for (size_t j = 0; j < tabela_chaves.size(); ++j) {
            pair<char, char> par = tabela_chaves[j];
            if (c_cifrado == par.second) {
                texto_decriptado[i] = par.first; 
                break;
            }
        }
    }

    ofstream arq_out("decrypted.txt");

    if (!arq_out.is_open()) {
        cout << "Erro: Não foi possível criar/abrir o arquivo de saída: " << endl;
        return false;
    }

    arq_out << texto_decriptado;
    arq_out.close();

    return true;
}
