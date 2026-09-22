# Disciplina: Arquitetura e Organização de Processadores
# Atividade: Avaliação 01 – Programação em Linguagem de Montagem
# Programa 01 - Controle de faltas
# Nome: Victor Oliveira Zvicker, Gabriel Joaquim Schlindwein Odisi

.data
	dias: .word -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	string1: .asciz "Entre com o número da aula (de 0 a 15): "
	string2: .asciz "Entre com o número do aluno (de 0 a 31):"
	string3: .asciz "Entre com o tipo do registro (presença = 1; ausência = 0):"
	string4: .asciz "Deseja continuar e alterar mais algo? (1 = sim)"
.text
	la s0, dias #Guarda a refenrencia de dias em s0.
	#Serao utilizados os seguintes registradores:
	#s0: Referencia do Array de dias
	#s1: Posição do Array de dias que ira alterar 
	#t0: posicao de memoria calculada
	#t1: posicao de memoria efetiva: s0 + t0
	#t2: valor do array[t1] a ser alterado e salvo
	#s2: O numero do aluno a ser alterado
	#s3: O tipo de registro, presença ou ausencia
	#t3: Mascara de bits para alterar o aluno.
	
	#t6: delimitador do numero maximo do input da questao

pergunta_1:
	addi t6, zero, 15 #Delimita o numero maximo de posicao do array
	#faz a primeira pergunta: Entre com o número do dia da aula (de 0 a 15)
	addi a7, zero, 4
	la a0, string1
	ecall
	#Guarda em s1 o dia da aula que sera alterada
	addi a7, zero, 5
	ecall
	add s1, zero, a0
	
	bgt zero, s1, pergunta_1 # Caso o s1 for menor que 0, pergunta denovo
	bgt s1, t6, pergunta_1 # Caso o s1 for maior que 15, pergunta denovo
	
	#calcula a posicao do array de dias a ser alterado
	add t0, zero, zero #reinicia o t0 para evitar possiveis falhas
array_pos:
	beq s1, zero, end_array_pos
	addi t0, t0, 4 # Adicionar 4 em t0
	addi s1, s1, -1 # Subtrai 1 em s1
	jal array_pos # volta para o loop de adicionar 4 em t0 ate que s1 seja 0
end_array_pos:
	add t1, t0, s0
	lw t2, 0(t1)
	
pergunta_2:
	addi t6, zero, 31 #Delimita o numero maximo para os alunos
	#faz a segunda pergunta: Entre com o número do aluno (de 0 a 31)
	addi a7, zero, 4
	la a0, string2
	ecall
	#Guarda em s2 o aluno a ser alterado
	addi a7, zero, 5
	ecall
	add s2, zero, a0
	
	bgt zero, s2, pergunta_2 # Caso o s2 for menor que 0, pergunta denovo
	bgt s2, t6, pergunta_2 # Caso o s2 for maior que 31, pergunta denovo
	
pergunta_3:
	addi t6, zero, 1 #Delimita o numero maximo para o registro
	#faz a terceira pergunta: Entre com o tipo do registro (presença = 1; ausência = 0)
	addi a7, zero, 4
	la a0, string3
	ecall
	#Guarda em s3 o registro a ser aplicado
	addi a7, zero, 5
	ecall
	add s3, zero, a0
	
	bgt zero, s3, pergunta_3 # Caso o s3 for menor que 0, pergunta denovo
	bgt s3, t6, pergunta_3 # Caso o s3 for maior que 1, pergunta denovo
	
	beq s3, zero, ausencia
presenca:
	#cria a mascara de bit para alterar o registro do aluno X
	addi t3, zero, 1 #Inicia t3 com 1
	sll t3, t3, s2   #Faz o shift left ate que chegue no aluno a ser alterado
	or t2, t2, t3    #Faz o OR para da presença somente ao aluno que foi selecionado
	jal salvamento   #Pula para o fim
ausencia:
	addi t3, zero, 1 #Inicia t3 com 1
	sll t3, t3, s2   #Faz o shift left ate que chegue no aluno a ser alterado
	xori t3, t3, -1  #Inverte os bits do controle de ausencia e presença
	and t2, t2, t3   #Faz o AND para que somente o aluno selecionado leve falta
salvamento:
	#Fim do programa, salva os dados do aluno para a memoria do vetor novamente e volta para o começo
	sw t2, 0(t1)
	#Pergunta se o usuario gostaria de fazer mais alguma ateração (1 = Sim)
	addi a7, zero, 4
	la a0, string4
	ecall
	#Recebe a resposta da pergunta
	addi a7, zero, 5
	ecall
	add s1, zero, a0
	#Se SIM, volta para o inicio.
	beq s1, t6, pergunta_1
	#Se qualquer outra coisa, encerra.
	nop
