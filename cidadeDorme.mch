MACHINE
    cidadeDorme

SETS
	Participantes = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10};
	Status_participante = {fora, vivo, morto, atacado};
	Status_jogo = {aguardando, cadastro, distribuicao_papeis, ataque, cura, relatorio_noite, investigacao, votacao, apuracao_votos, reinicio};
	Papeis = {lobisomem, detetive, curandeiro, comum, nenhum};
	Relatorio = {sim, nao};
	Relatorio_votacao = {morreu_lobisomem, morreu_nao_lobisomem, ninguem_morreu, lobisomem_venceu}


VARIABLES
	qtd_votos, status_j, papel, status_p, votos_recebidos, ja_votou, qtd_vivos, qtd_atribuidos, participante_atacado, participante_mais_votado


INVARIANT
	qtd_votos : NATURAL
	& qtd_vivos : NATURAL 
	& status_j : Status_jogo
	& papel : Participantes --> Papeis
	& status_p : Participantes --> Status_participante
	& votos_recebidos : Participantes --> NATURAL
	& ja_votou : Participantes --> BOOL
	& qtd_atribuidos : NATURAL
	& participante_atacado : Participantes
	& participante_mais_votado : Participantes

	// Que estados não podem acontecer
    & (qtd_vivos <= card(dom(status_p |> ({vivo} \/ {atacado}))))
	& qtd_votos <= card(dom(status_p |> ({vivo} \/ {atacado})))
	& ! xx . (xx : Participantes => votos_recebidos(xx)<= qtd_vivos)
	

	// Que estados devem acontecer
	& (((qtd_vivos <= 3 & status_p[dom(papel |> {lobisomem})] = {vivo}) or (status_p[dom(papel |> {lobisomem})] = {morto})) => status_j = reinicio)

INITIALISATION
 	qtd_votos, qtd_vivos, qtd_atribuidos := 0, 0, 0 ||
    	status_j := aguardando ||
	papel := Participantes*{nenhum} ||
	status_p := Participantes * {fora} ||
	votos_recebidos := Participantes * {0} ||
	ja_votou := Participantes * {FALSE} ||
	participante_atacado := p1 ||
	participante_mais_votado := p1

OPERATIONS

cadastrar (nn) =
	PRE nn : Participantes & qtd_vivos < 10 & (status_j = aguardando or status_j = cadastro) & status_p(nn) = fora
	THEN
		status_p := status_p <+  {nn |-> vivo} ||
		qtd_vivos := qtd_vivos + 1 ||
		IF qtd_vivos = 6
        		THEN status_j := cadastro
		END
	END;

terminar_cadastro =
	PRE status_j = cadastro & qtd_vivos >= 7
	THEN
		status_j := distribuicao_papeis
	END;

//Definição dos papéis dos participantes
distribuir_papeis =
	PRE status_j = distribuicao_papeis
	THEN
		ANY aa
		WHERE aa : Participantes & status_p(aa) = vivo & papel(aa) = nenhum
		THEN
			IF not (#(xx). (xx: Participantes & papel(xx) = lobisomem))
			THEN
				papel := papel <+ {aa |-> lobisomem} ||
				qtd_atribuidos := qtd_atribuidos + 1
 			ELSE
				IF not (#(xx). (xx: Participantes & papel(xx) = detetive))
				THEN
					papel := papel <+ {aa |-> detetive} ||
					qtd_atribuidos := qtd_atribuidos + 1
				ELSE
					IF not (#(xx). (xx: Participantes & papel(xx) = curandeiro))
					THEN
						papel := papel <+ {aa |-> curandeiro} ||
						qtd_atribuidos := qtd_atribuidos + 1
					ELSE
						papel := papel <+ {aa |-> comum} ||
						qtd_atribuidos := qtd_atribuidos + 1 ||
						IF qtd_atribuidos = qtd_vivos - 1
						THEN status_j := ataque
						END
					END
				END
			END
		END
	END;

//Tentativa de ataque pelo lobisomem
atacar (pp) =
	PRE pp : Participantes & status_j = ataque & papel(pp) /= lobisomem & status_p(pp) = vivo 
	THEN
		status_p := status_p <+  {pp |-> atacado} ||
		participante_atacado := pp ||
		IF (#xx.(xx: Participantes & papel(xx) = curandeiro & status_p(xx) = vivo))
		THEN status_j := cura
		ELSE status_j := relatorio_noite
		END
	END;

//Tentativa de cura pelo curandeiro
 curar (pp) =
	PRE status_j = cura & pp : Participantes & papel(pp) /= nenhum & status_p(pp) /= morto & (#xx.(xx: Participantes & papel(xx) = curandeiro & status_p(xx) : {vivo, atacado}))
	THEN
		IF  status_p(pp) = atacado
			THEN status_p := status_p <+ {pp |-> vivo}
		END ||
		status_j := relatorio_noite
	END;


//Informe se alguém morreu ou não numa noite de potencial ataque do lobisomem
resp, mm <-- relatar_noite =
	PRE status_j = relatorio_noite
	THEN
		IF #(xx) .(xx: Participantes & status_p(xx) = atacado)
		THEN
			qtd_vivos := qtd_vivos - 1 ||
			status_p := status_p <+ {participante_atacado |-> morto} ||
			resp := sim ||
			ANY aa WHERE aa: Participantes & status_p(aa) = atacado THEN mm := aa END
		ELSE
			resp := nao
		END ||
		IF (#xx.(xx: Participantes & papel(xx) = detetive & status_p(xx) = vivo))
		THEN status_j := investigacao
		ELSE status_j := votacao
		END
	END;

resp <-- investigar(pp) =
	PRE status_j = investigacao & pp : Participantes & status_p(pp) = vivo & papel(pp) /= detetive & (#xx.(xx: Participantes & papel(xx) = detetive & status_p(xx) = vivo))
	THEN
		IF papel(pp) = comum
		THEN resp := sim
		ELSE resp := nao
		END ||
		status_j := votacao
	END;

votar_nulo(pp) =
	PRE status_j = votacao & pp : Participantes & status_p(pp) = vivo & ja_votou(pp) = FALSE
	THEN
		ja_votou := ja_votou <+ {pp |-> TRUE} ||
		qtd_votos := qtd_votos + 1 ||
		IF qtd_votos = qtd_vivos - 1
		THEN
			status_j := apuracao_votos
		END
	END;

votar(pp , qq) =
	PRE status_j = votacao & pp : Participantes & qq : Participantes & qq /= pp & status_p(pp) = vivo & status_p(qq) = vivo & ja_votou(pp) = FALSE
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
		END ||
		
		IF qtd_votos = qtd_vivos - 1
		THEN
			status_j := apuracao_votos
		END
	END;

resp <-- apurar_votos =
	PRE status_j = apuracao_votos
	THEN
		IF  (#xx.(xx: Participantes & votos_recebidos(xx) >= ((qtd_vivos / 2) + 1 ))) // checar se alguém teve votos o suficiente para ser assassinado
		THEN
			qtd_vivos := qtd_vivos - 1 ||
			status_p := status_p <+ {participante_mais_votado |-> morto} ||
			IF papel(participante_mais_votado) = lobisomem
			THEN
				resp := morreu_lobisomem ||
				status_j := reinicio
			ELSE
				IF qtd_vivos <= 4
				THEN
					status_j := reinicio ||
					resp := lobisomem_venceu	
				ELSE
					status_j := ataque ||
					resp := morreu_nao_lobisomem	
				END
			END
		ELSE
			IF qtd_vivos <= 3
			THEN	
				status_j := reinicio ||
				resp := lobisomem_venceu
			ELSE	
				status_j := ataque ||
				resp := ninguem_morreu
			END
		END ||
		qtd_votos := 0 ||
		ja_votou := Participantes * {FALSE} ||
		votos_recebidos := Participantes * {0}
	END;

// setar configurações para reiniciar jogo
reiniciar =
	PRE status_j = reinicio
	THEN
		status_j := aguardando ||
		papel := Participantes*{nenhum} ||
		status_p := Participantes * {fora} ||
		qtd_vivos := 0
	END

END
