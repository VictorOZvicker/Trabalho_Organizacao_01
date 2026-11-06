# Disciplina: Arquitetura e Organização de Processadores
# Atividade: Avaliação 01 – Programação em Linguagem de Montagem
# Programa 02 - Calculadora de Multiplicação
# Nome: Victor Oliveira Zvicker, Gabriel Joaquim Schlindwein Odisi

.data
	string1: .asciz "Digite o primeiro valor: "
	string2: .asciz "Digite o segundo valor: "
.text
	#Registradores utilizados:
	#t0: Salva o primeiro produto
	#t1: Salva o segundo produto
	#t2: Resultado
	#t3: Salva a verificação do 1° bit de t1 para verificar se é = 1.

	#Escreve o string1 no console
	addi a7, zero, 4
	la a0, string1
	ecall
	
	#le o primeiro numero e salva em t0
	addi a7, zero, 5
	ecall
	add t0, zero, a0
	
	#Escreve o string2 no console
	addi a7, zero, 4
	la a0, string2
	ecall
	
	#le o segundo numero e salva em t1
	addi a7, zero, 5
	ecall
	add t1, zero, a0
	
while:	
	beq t1, zero, end_while #Enquanto o t1 (multiplicador) for diferente de 0 mult
	andi t3, t1, 1 #Verifica se o bit da primeira posicao eh 1 por meio de um and
	beq t3, zero, shifts # se nao for 1, pula para os shifts
	add t2, t0, t2  # faz a adicao
shifts: 
	slli t0, t0, 1 # faz os shifts de bits
	srli t1, t1, 1 # '''
	jal while # volta para o while
end_while:
	addi a7, zero, 1
	add a0, zero, t2
	ecall
	nop
