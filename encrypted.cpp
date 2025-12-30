
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>

using namespace std;

vector<pair<int,char>> table();
bool compare_freq(const pair<int,char> &a, const pair<int,char> &b);
vector<pair<int,char>> table_order(vector<pair<int,char>> table);
bool encrypt(vector<pair<int,char>> table, string name_file);
bool encrypted_table();


int main()
{
    vector<pair<int,char>> table_m = table();

    vector<pair<int,char>> table_ordered = table_order(table_m);

    encrypt(table_ordered, "input.txt");

    encrypted_table();

    return 0;
}

vector<pair<int,char>> table()
{
    ifstream input_arq("input.txt");
    char c;

    vector<pair<int,char>> conv;
    
    while (input_arq.get(c)) {
        conv.push_back({static_cast<int>(c), c});
    }

    input_arq.close();
    return conv;
}

bool compare_freq(const pair<int,char> &a, const pair<int,char> &b)
{
    return a.first > b.first;
}

vector<pair<int,char>> table_order(vector<pair<int,char>> table)
{
    ofstream table_ord("tabela_ordenada.txt");
    vector<pair<int,char>> v_table;

    if (!table_ord.is_open()) {
        cout << "Erro ao abrir o arquivo de saida." << endl;
        return v_table;
    }

    int freq[256] = {0};
    int idx;

    for (size_t i = 0; i < table.size(); i++) {
        idx = table[i].second;
        freq[idx]++;
    }

    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            v_table.push_back({freq[i], static_cast<char>(i)});
        }
    }
    stable_sort(v_table.begin(), v_table.end(), compare_freq);

    for (size_t i = 0; i < v_table.size(); i++) {
        table_ord << v_table[i].first << " - " << v_table[i].second << endl;
    }
    table_ord.close();

    return v_table;
}

bool encrypt(vector<pair<int,char>> table_ord, string name_file)
{
    ofstream table_cod("tabela_codificacao.txt");
    ofstream txt_encoded("encoded_text.txt"); 
    string tabela_out = "";
    string tabela_in = "";

    ofstream string_comp("string_comp.txt");

    if (!table_cod.is_open() || !txt_encoded.is_open()) {
        cout << "Erro ao criar um dos arquivos de saida." << endl;
        return false;
    }

    int ascii_i = 97, original_ascii;
    char subs[256], original_char, encoded_char;

    for(int i = 0; i < 256; ++i) {
        subs[i] = static_cast<char>(i); 
    }

    table_cod << "AscII   InputChar     AscII   OutputChar" << endl;
    for (size_t i = 0; i < table_ord.size(); ++i) {
        original_char = table_ord[i].second;
        original_ascii = static_cast<char>(original_char);

        encoded_char = static_cast<char>(ascii_i + i);

        subs[original_ascii] = encoded_char;
        tabela_in += original_char;
        tabela_out += encoded_char;

    }

    shuffle(tabela_out.begin(), tabela_out.end(), mt19937(time(NULL)));

    for (size_t i = 0; i < table_ord.size(); ++i) {
        subs[static_cast<int>(tabela_in[i])] = tabela_out[i];
    }

    for (size_t i = 0; i < table_ord.size(); ++i) {
        string_comp << tabela_in[i];
        string_comp << tabela_out[i];
    }

    string parada = ":";
    string_comp << parada;

    for (size_t i = 0; i < table_ord.size(); ++i) {
        table_cod << int(tabela_in[i]) << " - " << tabela_in[i] << "                " << int(tabela_out[i]) << " - " << tabela_out[i] << endl;
    }

    table_cod.close();
    cout << "Tabela de codificacao legivel criada em 'tabela_codificacao.txt'." << endl;
    
    ifstream input_arq(name_file);
    
    if (!input_arq.is_open()) {
        cout << "Erro ao abrir arquivo de entrada para codificacao." << endl;
        return false;
    }
    
    char c;
    int char_index;

    while(input_arq.get(c)) {
        char_index = static_cast<char>(c);
        encoded_char = subs[char_index];
        
        txt_encoded << encoded_char;
    }

    input_arq.close();
    txt_encoded.close();
    cout << "Texto codificado salvo em 'encoded_text.txt'." << endl;

    return true;
}

bool encrypted_table()
{
    ifstream txt_encoded("encoded_text.txt");
    ifstream table_code("string_comp.txt");
    ofstream table_encrypted("encrypter.txt");

    if (!txt_encoded.is_open() || !table_code.is_open() || !table_encrypted.is_open()) {
        cout << "Erro ao abrir um ou mais arquivos de codificacao/tabela." << endl;
        return false;
    }

    int intervalo = 5;
    int cont = 0;
    char text_char;
    char table_char;

    while (txt_encoded.get(text_char)) {

        table_encrypted << text_char;
        cont++;

        if (cont % intervalo == 0) {

            if (table_code.get(table_char)) {
                table_encrypted << table_char;
            }
        }
    }

    while (table_code.get(table_char)) {
        table_encrypted << table_char;
    }

    txt_encoded.close();
    table_code.close();
    table_encrypted.close();

    cout << "Codificacao com a tabela concluida em 'encrypter.txt'." << endl;
    return true;
}
