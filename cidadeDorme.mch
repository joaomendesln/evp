MACHINE
    cidadeDorme
    
SETS
	Participantes = {j1, j2, j3, j4, j5, j6, j7, j8, j9, j10};
	Status_participante = {fora, vivo, morto, atacado};
	Status_jogo = {aguardando, p0, p1, p2, p3, p4, p5, p6, p7,p8};
	Papeis = {lobisomem, detetive, curandeiro, comum, nenhum};
	Relatorio = {sim, nao};
	Relatorio_votacao = {morreu_lobisomem, morreu_nao_lobisomem, ninguem_morreu} // isso aqui não funfa
    
    
VARIABLES
	qtd_votos, status_j, papel, status_p, votos_recebidos, ja_votou, qtd_vivos, qtd_atribuidos, participante_atacado, participante_mais_votado
    
    
INVARIANT
	qtd_votos : NATURAL
	& qtd_vivos : NATURAL & qtd_vivos <= card(Participantes)
	& status_j : Status_jogo
	& papel : Participantes --> Papeis
	& status_p : Participantes --> Status_participante
	& votos_recebidos : Participantes --> NATURAL
	& ja_votou : Participantes --> BOOL
	& qtd_atribuidos : NATURAL
	& participante_atacado : Participantes
	& participante_mais_votado : Participantes
  
INITIALISATION
 	qtd_votos, qtd_vivos, qtd_atribuidos := 0, 0, 0 ||
    	status_j := aguardando ||
	papel := Participantes*{nenhum} ||
	status_p := Participantes * {fora} ||
	votos_recebidos := Participantes * {0} ||
	ja_votou := Participantes * {FALSE} ||
	participante_atacado := j1 ||
	participante_mais_votado := j1
 
OPERATIONS
    
cadastro (nn) =
	PRE qtd_vivos < 10 & (status_j = aguardando or status_j = p0) & status_p(nn) = fora
	THEN
		status_p := status_p <+  {nn |-> vivo} ||
		qtd_vivos := qtd_vivos + 1 ||
		IF qtd_vivos = 6
        		THEN status_j := p0
		END
	END;

terminar_cadastro =
	PRE status_j = p0 & qtd_vivos >= 7
	THEN
		status_j := p1
	END;

//Definição dos papéis dos participantes
distribuicao =
	PRE status_j = p1
	THEN
		ANY a
		WHERE a : Participantes & status_p(a) = vivo & papel(a) = nenhum
		THEN
			IF not (#(x). (papel(x) = lobisomem))
			THEN
				papel := papel <+ {a |-> lobisomem} ||
				qtd_atribuidos := qtd_atribuidos + 1
 			ELSE
				IF not (#(x). (papel(x) = detetive))
				THEN
					papel := papel <+ {a |-> detetive} ||
					qtd_atribuidos := qtd_atribuidos + 1
				ELSE
					IF not (#(x). (papel(x) = curandeiro))
					THEN
						papel := papel <+ {a |-> curandeiro} ||
						qtd_atribuidos := qtd_atribuidos + 1
					ELSE
						papel := papel <+ {a |-> comum} ||
						qtd_atribuidos := qtd_atribuidos + 1 ||
						IF qtd_atribuidos = qtd_vivos - 1
						THEN status_j := p2
						END
					END
				END
			END
		END
	END;

//Tentativa de ataque pelo lobisomem

atacar (pp) =
	PRE status_j = p2 & papel(pp) /= lobisomem & status_p(pp) = vivo
	THEN
		status_p := status_p <+  {pp |->atacado} ||
		participante_atacado := pp ||
		status_j := p3
	END;

//Tentativa de cura pelo curandeiro
 curar (pp) =
	PRE status_j = p3 & pp : Participantes & papel(pp) /= nenhum & status_p(pp) /= morto & (#x.(papel(x) = curandeiro & status_p(x) = vivo))
	THEN
		IF  status_p(pp) = atacado
			THEN status_p := status_p <+ {pp |-> vivo}
		END ||
		status_j := p4
	END;


//Informe se alguém morreu ou não numa noite de potencial ataque do lobisomem
resp <-- relatorio =
	PRE status_j = p4
	THEN
		status_j := p5 ||	
		IF #(x) .(status_p(x) = atacado)
		THEN
			qtd_vivos := qtd_vivos - 1 ||
			status_p := status_p <+ {participante_atacado |-> morto} ||
			resp := sim
		ELSE
			resp := nao
		END
	END; // fata dizer quem morreu

resp <-- investigar(pp) =
	PRE status_j = p5 & pp : Participantes & status_p(pp) = vivo & papel(pp) /= detetive & (#x.(papel(x) = detetive & status_p(x) = vivo))
	THEN
		IF papel(pp) = comum
		THEN resp := sim
		ELSE resp := nao
		END ||
		status_j := p6
	END;

votar(pp , qq) =
	PRE status_j = p6 & pp : Participantes & qq : Participantes & status_p(pp) = vivo & status_p(qq) = vivo & ja_votou(pp) = FALSE // add opção do voto nulo & tirar opção de participante votar em si mesmo & não tá considerando o último voto
	THEN
		IF  qtd_votos < qtd_vivos - 1
		THEN
			ja_votou := ja_votou <+ {pp |-> TRUE} ||
			votos_recebidos := votos_recebidos <+ {qq |-> votos_recebidos(qq) + 1} ||
			qtd_votos := qtd_votos + 1 ||

			IF qtd_votos = 0
			THEN
				participante_mais_votado := qq		
			ELSE 
				IF votos_recebidos(qq) = votos_recebidos(participante_mais_votado)
				THEN participante_mais_votado := qq
				END
			END
		ELSE
			status_j := p7 ||
			qtd_votos := 0 ||
			ja_votou := Participantes * {FALSE}
		END
	END;  // fata dizer quem morreu

resp <-- result_votos =
	PRE status_j = p7
	THEN
		IF  (#x.(votos_recebidos(x) >= ((qtd_vivos / 2) + 1 )))
		THEN  
			status_p := status_p <+ {participante_mais_votado |-> morto} ||
			votos_recebidos := Participantes * {0} ||
			ja_votou := Participantes * {FALSE} ||
			IF papel(participante_mais_votado) = lobisomem
			THEN
				resp := morreu_lobisomem ||
				status_j := p8
			ELSE
				IF qtd_vivos <= 3
				THEN  
					resp := morreu_nao_lobisomem ||
					status_j := p8
				ELSE
					status_j := p2
				END
			END
		ELSE
			status_j := p2 ||
			resp := ninguem_morreu ||
			votos_recebidos := Participantes * {0}
		END
	END;

// setar configurações para recomeçar
reiniciar =
	PRE status_j = p8
	THEN
		status_j := aguardando ||
		papel := Participantes*{nenhum} ||
		status_p := Participantes * {fora} ||
		qtd_vivos := 0
	END

END