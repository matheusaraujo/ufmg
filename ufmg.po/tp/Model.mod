int QtdNavios = ...;
int QtdEtapas = ...;
int QtdPosicoes = QtdNavios;

range Navios = 1..QtdNavios;
range Etapas = 1..QtdEtapas;
range Posicoes = 1..QtdPosicoes;

float p[Navios][Etapas] = ...;
float ch[Navios] = ...;

//-----------------------------------------
dvar float s[Etapas][Posicoes];
dvar boolean z[Navios][Posicoes];

dvar float C;

minimize C;

// z[i][j] representa o navio `i` na posicao `j`
// s[m][n] representa o momento de entrada do navio de posicao `n` na maquina `m`

subject to {

	// minimizar C, sendo C = momento de entrada do ultimo navio na ultima etapa + o tempo que o navio gasta nessa etapa  
	forall(m in Etapas, n in Posicoes){
		C >= s[m][n] + sum(i in Navios)(p[i][m] * z[i][n]);
	}
	
	// garante o navio em uma unica posicao
	forall(i in Navios) {
		sum(j in Posicoes)(z[i][j]) == 1;
	}
	
	// garante um unico navio por posicao
	forall(j in Posicoes){
		sum(i in Navios)(z[i][j]) == 1;	
	}
	
	// garante que o navio na posicao j inicie depois de seu predecessor finalizar na etapa 1
	forall(j in Posicoes: j < QtdPosicoes){
		s[1][j] + sum(i in Navios)(p[i][1] * z[i][j]) == s[1][j+1]; 	
	}
	
	// garante que o navio na posicao 1 passe para a proxima etapa quando concluir a primeira
	forall(k in Etapas: k < QtdEtapas){
		s[k][1] + sum(i in Navios: i < QtdNavios)(p[i][k] * z[i][1]) == s[k+1][1];
	}	
	
	// garante que uma tarefa soh passa para a proxima etapa depois de concluir a etapa atual
	forall(j in Posicoes, k in Etapas: k < QtdEtapas){
		s[k][j] + sum(i in Navios)(p[i][k] * z[i][j]) <= s[k+1][j]; 
	}
	
	// garante que um navio nao inicie a etapa antes de seu predecessor
	forall(j in Posicoes, k in Etapas: j < QtdPosicoes && k >= 2){
		s[k][j] + sum(i in Navios)(p[i][k] * z[i][j]) <= s[k][j+1]; 
	}
	
	// garante o tempo inicial dos navios
	forall(j in Posicoes){
		 s[1][j] >= sum(i in Navios)(ch[i] * z[i][j]); 
	}
}

tuple NavioEtapa {
	key int Navio;
	key int Etapa;
	float MomentoInicio;
	int TempoGasto;	
};

sorted {NavioEtapa} NaviosResults = {};

execute{
	for(var i in Navios){
		for(var j in Posicoes){
			if(z[i][j] == 1){
				for(var k in Etapas){
					NaviosResults.add(i, k, s[k][j], p[i][k]);				
				}			
			}
		}	
	}
	writeln("Navio,Etapa,MomentoInicio,TempoGasto")
	for(var t in NaviosResults){
		writeln(t.Navio, ",", t.Etapa, ",", t.MomentoInicio, ",", t.TempoGasto);			
	}
}
