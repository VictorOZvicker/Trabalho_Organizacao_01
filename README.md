# Trabalho de Organização de Computadores — M1

> Leitor e decodificador de instruções **Assembly RISC-V**

---

## Autores

| Alunos   |
| ------- |
| Victor Oliveira Zvicker  |
| Gabriel Joaquim Odisi |

---

## Descrição

Programa capaz de **ler instruções em Assembly RISC-V** e, a partir delas:

-  **Identificar o tipo** da instrução;
-  **Extrair os registradores** utilizados;
-  **Extrair os imediatos**;
-  **Reconstruir a instrução** de volta para Assembly.

---

## Funcionamento

```text
       Arquivo na raiz do programa com o machine code.
                            │
                            ▼
Rodar o programa e especificar o nome do arquivo (com extensão).
```


# O que fazer
---
```
       Tem que alterar o gerador de output pra gerar um vector so com as inst infos pra gente poder pegar as informações de RD pra usar dentro do hazard detector

       Depois, pra fazer o hazard detector é só usar o vector de inst infos pra poder verificar se o RD da primeira instrução será usado como registrador pras próximas instruções!

       Depois a gente pensa em como fazer a inserção de NOPS

```
---