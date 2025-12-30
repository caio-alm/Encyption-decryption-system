# Encryption and Decryption System

Este é um projeto desenvolvido para realizar a criptografia e descriptografia de mensagens e arquivos de forma simples e segura.

## Funcionalidades
- **Criptografia:** Transforma texto puro em um formato cifrado.
- **Descriptografia:** Converte mensagens cifradas de volta ao formato original.
- **Interface:** Via terminal.

## Tecnologias Utilizadas
- **Linguagem:** C++
- **Algoritmo:** Cifra de Substituição Monoalfabética.

## Como instalar e executar
1. **Clone o repositório:**
   ```bash
   git clone [https://github.com/caio-alm/Encyption-decryption-system.git](https://github.com/caio-alm/Encyption-decryption-system.git)

2. **Navegue até a pasta:**
   ```bash
   cd Encyption-decryption-system
   
3. **Funcionamento encrypted.cpp:**
 
   -Na pasta **input.txt** insira o texto desejado para realizar a encriptação.
   
   -Compile:
   ```bash
   g++ encrypted.cpp -o exeEncrypt
   ```
   -Execute a encriptação:
   ```bash
   ./exeEncrypt
   ```
   - Serão criadas os arquivos **tabela_codicacao.txt**, **encoded_text.txt**, **encrypter.txt** e **tabela_ordenada.txt**.
   - **tabela_codificacao.txt:** Em seu conteúdo estarão os novos valores atribuidos aos caracteres após a encryptação. 
   - **encoded_text.txt:** O texto encriptado estará aqui.
   - **encrypter.txt:** Neste arquivo se encontrará o texto encriptado e a tabela de codificação mesclados. A cada 5 caracteres será colocado
    1 item da tabela.
   - **tabela_ordenada.txt:**  Segue a mesma lógica da tabela codificada, porém é ordenado de acordo com a quantidade de caracteres dentro
    do arquivo **input.txt**.

 5. **Funcionamento decrypted.cpp:**
    
     -Como o arquivo **encrypet.txt** contêm a tabela de encriptação mesclada com o texto decriptado, o objetivo de **decrypted.cpp** é
     retirar a tabela e coloca-la em **keys.txt**. O que sobra será o texto encriptado que o mesmo sera decriptado e armazenado em **decrypted.txt**.
    
     -Compile:
     ```bash
     g++ decrypted.cpp -o exeDecrypt
     ```
     -Execute a decriptação:
     ```bash
     ./exeDecrypt
     ```
     -Assím será criado o arquivo **decrypted.txt** e **keys.txt**.
   


   
