#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <windows.h>

using namespace std;

struct Player{
	string nome, classe, raca, item;
	int forca, inteligencia, idade, destreza, carisma, xp, nivel, qntI, stamina;
	float vida;
};

struct Item{
	string nome;
	int atributo, codigo;
};

struct Inventario
{
	Item item[50];
};

struct Mob {
	string nome;
	int forca;
	float vida;
};

void separador(){
	for(int i = 0; i < 38; i++){
		cout << "=-";
	} 
}

void nomesCreditos(string fala){
    for (char L : fala){ 
        cout << L; 
        Sleep(150); 
       }
	cout << "\n"; 
}

void creditos(){
	nomesCreditos("\n\n\t\t\t\t\t\tHenrique Falasco");
	nomesCreditos("\n\n\t\t\t\t\t\tJoao Betin");
	nomesCreditos("\n\n\t\t\t\t\t\tMiguel Mendes");
	nomesCreditos("\n\n\t\t\t\t\t\tRafael Guerino");
	getchar();
}

void menu(Player &player){ // Tem player por referência pq vai mudar o valor de progresso quando escolher a opção "1. Novo jogo"
	int escolha;
	
	while(escolha != 1 && escolha != 2){
		cout << "\n\n\n\t\t";
		separador();
		cout << "\n\n\t\t\t\tELBAPH A JORNADA DO AMULETO PERDIDO\n\n\t\t";
		separador();
	
		cout << "\n\n\t\t1. Novo jogo\n\n\t\t2. Carregar jogo\n\n\t\t3. Avisos\n\n\t\t4. Creditos\n";
		cin >> escolha;
		
		switch(escolha){
			case 1:
				system("cls");
				break;
			case 2:
			system("cls");
				// Isso aqui vai ser com save
				break;
			case 3:
				system("cls");
				cout << "Ola, aqui estao algumas coisas que gostariamos de atualizar no codigo..\n";
				cout << "\n-	Adicionar mais monstros para a historia.";
				cout << "\n-	Fazer a Adicao de mais personagens e uma historia para cada tipo de classe.";
				cout << "\n-	Nao conseguimos implementar o sistema de salvamento. :( ";
				cin.ignore();
				getchar();
				system("cls");
				break;
			case 4:
				system("cls");
				creditos();
				getchar();
				system("cls");
				break;
			default:
				cout << "\n\n Valor invalido. Digite novamente.";
				break;				
		}
	}
}

void Falas(string fala){
       for (char L : fala){ // transformando string em char
           cout << L; // printando letra por letra
           Sleep(25); // delay de 150 ms para cada letra (podendo alterar)
       }
	   cout << "\n";
	   getchar(); // pausa para o player clicar para aparecer outra fala (um pouco paia pq aparece "pressione qualuqer tecla para continuar"), passivel de retirada!
}

// FALAS DOS PERSONAGENS
void falasPersonagem(string fala, string nome){
	int qtdLetras = 0;
	cout << "\n\n\t\t->" << nome << "\n\n\t\t";
	separador();
	cout << "\n";
	for (char L : fala){
		if(qtdLetras == 76){
			cout << "\n\t\t";
		} 
		cout << L; 
        Sleep(25);
		qtdLetras++; 
       }
    cout << "\n\n\t\t";
    separador();
	cout << "\n";
	getchar(); 
}

//DROPAR ITENS
void DropItem(Player &player, Item item[50], Inventario &inventario) {
    srand(time(0));
    cout << "Os itens dropados foram:\n";

    for (int i = 0; i < 2; i++) {
        int codigoItem = rand() % 18;
        while ((codigoItem >= 3 && codigoItem <= 5) || codigoItem >= 12) {
            codigoItem = rand() % 18;
        }
        inventario.item[player.qntI] = item[codigoItem];
        cout << inventario.item[player.qntI].nome << " // ";
        player.qntI++;
    }
    cout << endl;
    system("pause");
}

//EXPERIENCIA DO PLAYER
Player SomaXp(Player &player, int xp) {
	int soma = player.xp + xp;
	player.xp += xp;
	
	if (soma >= 10) {
		soma = 10;
	}
	if (soma % 10 == 0) {
		player.nivel += 1;
	}
	return player;
}

// PLAYER COM E MOCHILA
Player SomaItem(Player &player, Item item) { 
    if (item.nome == "Pocao de Cura Pequena" || item.nome == "Pocao de Cura Media" || item.nome == "Pocao de Cura Grande") {
        player.vida += item.atributo;
    } else if (item.nome == "Espada Sem fio" || item.nome == "Espada" || item.nome == "Espada BOA") {
        player.forca += item.atributo;
    } else if (item.nome == "Escudo Desgastado" || item.nome == "Escudo" || item.nome == "Escudo Revestido") {
        player.vida += item.atributo;
    } else if (item.nome == "Capa Desgastada" || item.nome == "Capa" || item.nome == "Capa Revestida") {
        player.vida += item.atributo;
    }
    return player;
}

//STAMINA
Player CalculaStamina(Player &player, int qntS, string lugar){
	int qntP = 0;
	if (player.stamina < qntS) {
                int x = qntS - player.stamina;
                int y = 60 / x; // conta para saber quantos segundos demora para a stamina carregar!
                cout << "Espere " << y << " segundos para carregar sua barra de stamina!";

                auto start = chrono::high_resolution_clock::now();                
				Sleep(y * 1000);
                auto end = chrono::high_resolution_clock::now();

                auto duracao = chrono::duration_cast<chrono::seconds>(end - start);
				cout << "\nStamina CARREGADA!" << endl;
				Sleep(1000);
				player.stamina -= qntS;
				
				while (qntP < 4)
				{
					system("cls");
					cout << "Caminhando ";
					cout << " . ";
					Sleep(1000);
					cout << " . ";
					Sleep(1000);
					cout << " . ";
					Sleep(1000);
					qntP++;
				}
				cout << "\n\nVoce chegou " << lugar << "!";				
            }
			else{
				player.stamina -= qntS;
				while (qntP < 4)
				{
					system("cls");
					cout << "Caminhando ";
					cout << " . ";
					Sleep(1000);
					cout << " . ";
					Sleep(1000);
					cout << " . ";
					Sleep(1000);
					qntP++;
				}
				cout << "\n\nVoce chegou " << lugar << "!";
			}
	return player;
}

//SISTEMA DE LUTA
float Luta(Player player, Inventario inventario, Item item[50], Mob mob){
	system ("cls");
	bool LutaAcabou = false;
	int dadoP, dadoM, escolha, escolhaI, i, hit;
	srand(time(0));
	while (!LutaAcabou)
	{
		cout << "Vida player: " << player.vida << " || Forca player: " << player.forca << endl;
		cout << "Vida mob: " << mob.vida << " || forca mob: " << mob.forca << "\n\n";
		cout << "O que deseja fazer?\n1- Bater\n2- Usar item\n";
		cin >> escolha;
		switch (escolha)
		{
		case 1:
			cout << "\n1- " << inventario.item[0].nome << "\n2- Soco\n";
			cin >> hit;
			system ("cls");
			dadoP = rand() % 20;
			dadoM = rand() % 20;
			cout << "Resultado dos dados: " << endl;
			cout << player.nome << ": " << dadoP << endl;
			cout << mob.nome << ": " << dadoM << "\n\n";
			if (dadoP > dadoM && hit == 1){
				mob.vida -= inventario.item[0].atributo;
			}
			else if (dadoP > dadoM && hit == 2){
				mob.vida -= player.forca;
			}
			else{
				player.vida -= mob.forca;
			}
			if (player.vida <= 0){
				cout << player.nome << " desapontou aqueles que te aguardavam!";
				LutaAcabou = true;
				return 0;
			}
			else if (mob.vida <= 0){
				cout << "parabens voce VENCEU!!!";
				getchar();
				LutaAcabou = true;
			}
			break;
		case 2:
			if (player.qntI <= 1) {
				cout << "Inventario VAZIO!!!\n";
			} else {
				cout << "Escolha um item para usar:\n";
				for (i = 1; i < player.qntI; i++) {
					cout << i << ": " << inventario.item[i].nome << endl;
				}
				cin >> escolhaI;

				if (escolhaI > 0 && escolhaI < player.qntI) {
					int codigoItem = inventario.item[escolhaI].codigo;
					player = SomaItem(player, item[codigoItem]);

					cout << "Voce usou " << inventario.item[escolhaI].nome << "agora tem " << player.vida << " de vida!!!\n";
					for (int j = escolhaI; j < player.qntI - 1; j++) {
						inventario.item[j] = inventario.item[j + 1];
					}
					inventario.item[player.qntI - 1] = {"", 0, 0};
					player.qntI--;
				} else {
					cout << "Item INVALIDO!\n";
				}
			}
		}
	}	
}

int main() {

	Player player;
	Inventario inventario;
	player.qntI = 1; // Inicializa player.qntI
	player.stamina = 1; // esse valor pode mudar!
	string fala;
	menu(player);
	cin.ignore();

	int classe, raca;
	Item item[50];
	//POÇOES
	item[0] = {"Pocao de Cura Pequena", 3, 0}; 
	item[1] = {"Pocao de Cura Media", 9, 1};
	item[2] = {"Pocao de Cura Grande", 18, 2};
	// ESPADAS
	item[3] = {"Espada Sem fio", 3, 3};
	item[4] = {"Espada", 6, 4};
	item[5] = {"Espada BOA", 9, 5};
	//ESCUDOS
	item[6] = {"Escudo Desgastado", 3, 6};
	item[7] = {"Escudo", 9, 7};
	item[8] = {"Escudo Revestido", 18, 8};
	//CAPAS
	item[9] = {"Capa Desgastada", 3, 9};
	item[10] = {"Capa", 9, 10};
	item[11] = {"Capa Revestida", 18, 11};
	//MACHADO
	item[12] = {"Machado Desgastado", 4, 12};
	item[13] = {"Machado", 8, 13};
	//ARCOS
	item[14] = {"Arco Desgastado", 3, 14};
	item[15] = {"Arco", 9, 15};
	//CAJADO
	item[16] = {"Cajado Rachado", 3, 16};
	item[17] = {"Cajado de Madeira", 6, 17};
	item[18] = {"Cajado Pau-Brasil", 9, 18};

	srand(time(0));
	player.xp = 0;
	player.nivel = 1;

	cout << "Digite o nome do seu jogador: ";
	getline(cin, player.nome);
	cout << "Insira sua idade: ";
	cin >> player.idade;
	system("cls");

	cout << "Selecione sua raca: \n1- Elfo  \n2- Humano \n3- Orc\n\n";
	cin >> raca;
	system("cls");

	switch (raca) {
		case 1:
			player.raca = "Elfo";
			player.vida += 2;
			player.forca += 1;
			player.inteligencia += 3;
			player.carisma += 1;
			player.destreza += 2;
		break;
		case 2:
			player.raca = "Humano";
			player.vida += 1;
			player.forca += 2;
			player.inteligencia += 1;
			player.carisma += 2;
			player.destreza += 1;
		break;
		case 3:
			player.raca = "Orc";
			player.vida += 5;
			player.forca += 4;
			player.inteligencia -= 2;
			player.destreza += 5;
		break;		
	}

	cout << "Selecione sua classe:\n1- Mago\n2- Guerreiro\n3- Arqueiro\n\n";
	cin >> classe;
	system("cls");

	switch (classe) {		
		case 1:
			player.classe = "Mago";
			player.vida = 10;
			player.forca = (rand() % 6) + 1;
			player.inteligencia = (rand() % 11) + 1;
			player.carisma = (rand() % 11) + 1;
			player.destreza = (rand() % 11) + 1;
			inventario.item[0] = item[16];
		break;		
		case 2:
			player.classe = "Guerreiro";
			player.vida = 10;
			player.forca = (rand() % 6) + 1;
			player.inteligencia = (rand() % 11) + 1;
			player.carisma = (rand() % 11) + 1;
			player.destreza = (rand() % 11) + 1;
			inventario.item[0] = item[3];
		break;		
		case 3:
			player.classe = "Arqueiro";
			player.vida = 10;
			player.forca = (rand() % 6) + 1;
			player.inteligencia = (rand() % 11) + 1;
			player.carisma = (rand() % 11) + 1;
			player.destreza = (rand() % 11) + 1;
			inventario.item[0] = item[14];
		break;
	}

	cout << "A classe selecionada foi: " << player.classe << endl;
	cout << "Seus atributos sorteados foram:" << endl;
	cout << "Vida: " << player.vida << endl;
	cout << "Forca: " << player.forca << endl;
	cout << "Inteligencia: " << player.inteligencia << endl;
	cout << "Carisma: " << player.carisma << endl;
	cout << "Destreza: " << player.destreza << endl;
	system("pause");
	system("cls");
	
	cout << "\n";

	//INTRODUÇAO A HISTORIA
	Falas("Voce e um aventureiro vagando pelo vasto mundo de Elbaph...");
    Falas("Cansado e faminto, encontra uma vila aparentemente tranquila.");
    Falas("No entanto, logo percebe que os aldeoes enfrentam algo terrivel.");
    Falas("Doencas misteriosas assolam o lugar, e nem magos nem curandeiros conseguem ajuda-los.");
    Falas("Voce entra em uma taverna em busca de respostas...");
    Falas("Um anao de nome Leo se aproxima. Seus olhos brilham com esperanca.");
    falasPersonagem("\n\n\t\tHa muito tempo um amuleto lendario foi perdido na Dungeon desta vila.", "Leo");
	system("cls");
    falasPersonagem("\n\n\t\tDizem que esse artefato pode curar qualquer enfermidade.", "Leo");
	system("cls");
    falasPersonagem("\n\n\t\tEu sinto algo especial em voce... algo que diz que e o heroi que esperavamos.", "Leo");
	system("cls");
    Falas("Ele lhe entrega um mapa da Dungeon e pede que encontre o amuleto.");
    Falas("Cheio de esperancas" );
	fala = player.nome;
	Falas(fala);
	Falas("pega a seu(a)");
	fala = inventario.item[0].nome;
	Falas(fala);
	Falas("vai avante a Dungeon salvar a vila"); 
    system("cls");

	//INDO PRA DUNGEON, E ENCONTRO COM O THIAGO (SALVE PROFESSOR)
	Falas("Ao sair da taverna voce abre o mapa e percebe que a caminhada e longa");
	Falas("sem perder muito tempo pega os suprimentos necessarios e parte a Dungeon"); 

	Falas("Apos alguns minutos de caminhada voce chega ate o seu local de Destino.");
	Falas("Uma floresta densa, mas ate entao nao ha nada do que temer alias tudo esta bem normal ate agora, voce diz em voz alta");
	Falas("Cheio de esperança voce inspira fundo e da o primeiro passo ate a boca da Caverna");
	Falas("Ao olhar a um arbusto proximo voce se depara com um Mochileiro, chorando...");
	Falas("Ele parece exausto, segurando firmemente um pedaço de pano rasgado.");
	system("cls");

	falasPersonagem("\n\n\t\tEi... voce esta bem? O que aconteceu?",player.nome);
	system("cls");

	falasPersonagem("\n\n\t\tE-eles... eles se foram... Todos eles!", "Jovem");
	Falas("Ele soluca enquanto aponta para o pano que segura. Parece ser parte do manto de alguem.");
	system("cls");

	falasPersonagem("\n\n\t\tCalma... respire fundo. Me conte o que houve.", player.nome);
	system("cls");

	falasPersonagem("\n\n\t\tE-estavamos tentando encontrar o amuleto... Mas fomos atacados! Goblins... muitos deles!", "Jovem");
	Falas("Ele se encolhe ao lembrar do ocorrido.");
	system("cls");

	falasPersonagem("\n\n\t\tEu sinto muito... Nao foi culpa sua. Ninguem poderia prever isso.",player.nome);
	system("cls");
	Falas("Voce se abaixa para ficar na mesma altura dele.");
	falasPersonagem("\n\n\t\tMas sabe o que me mantem em pe? A certeza de que eles nao gostariam que voce desistisse.", player.nome);
	system("cls");

	falasPersonagem("\n\n\t\tVoce acha... que eles me perdoariam?", "Jovem");
	system("cls");

	falasPersonagem("\n\n\t\tNao ha nada a perdoar. Voce fez o que podia. Agora, honre a memoria deles vivendo e seguindo em frente.", player.nome);
    Falas("Voce coloca uma mao firme em seu ombro.");
	system("cls");

	falasPersonagem("\n\n\t\tObrigado... Eu... eu tentarei ser mais forte.", "Jovem");
	system("cls");
	falasPersonagem("\n\n\t\tAlias, o que voce esta fazendo aqui?", "Jovem");
	system("cls");

	falasPersonagem("\n\n\t\tUm anao me disse sobre a lenda do Amuleto e disse que eu era predestinado.",player.nome);
	system("cls");

	falasPersonagem("\n\n\t\tAquele filho da puta fala isso pra todo mundo, viemos aqui por causa dele, ele nao menciona o quao dificil e.", "Jovem");
	system("cls");

	falasPersonagem("\n\n\t\tEntao todos sao predestinados..., Bom mesmo assim eu vou tentar salvar essa vila.",player.nome);
	system("cls");

	falasPersonagem("\n\n\t\tEi, talvez possa ser muito cedo ainda mas eu poderia acompanhar voce?, eu preciso cumprir o que prometi aos meus amigos.", "Jovem");
	system("cls");

	falasPersonagem("\n\n\t\tClaro sera um prazer ter voce ao meu lado!",player.nome);
	system("cls");
	falasPersonagem("\n\n\t\tAntes preciso saber.. Qual o seu nome?",player.nome);
	system("cls");

	falasPersonagem("\n\n\t\tMuito Prazer meu nome e Thiago Nicola, muito obrigado por ter me ajudado.","Thiago Nicola");
	system("cls");
	falasPersonagem("\n\n\t\tVou ficar responsavel por pegar os itens aos quais a gente pode vender ao sair daqui, eu acredito em voce...","Thiago Nicola");
	system("cls");

	falasPersonagem("\n\n\t\tTer voce comigo sera de grande ajuda!",player.nome);
	system("cls");

	//ENTRADA DA DUNGEON
	Falas("Voces descem as escadas escuras da Dungeon...");
	Falas("Thiago Nicola: eu reconheco esse lugar e o Salao Negro.. foram aqui que cercaram meus amigos...");
    Falas("O ar e pesado e o silencio e perturbador...");
	Falas("Apos alguns passos...");

	//GOBLIN	
	Falas("Voces se deparam com um Goblin afiando sua adaga com uma pedra");
	Falas("O Goblin sente seu cheiro!");
	Falas("A QUANTO TEMPO NAO VEJO ALGUEM DA SUA ESPECIE, O QUE FAZ AQUI? diz o Goblin\""); 
	Falas("Eu reconheço esse menininho ai ao seu lado, ainda bem que voltou!!!!!");
	Falas("O GLOBLIN ATACA VOCES");

	Mob mob;
	mob.vida = 5;
	mob.forca = 1;
	mob.nome = "Goblin";
	Luta(player, inventario, item,mob);
	getchar();
	system("cls");

	cout << "Vida: " << player.vida << endl;
	cout << "Forca: " << player.forca << endl;
	cout << "Inteligencia: " << player.inteligencia << endl;
	cout << "Carisma: " << player.carisma << endl;
	cout << "Destreza: " << player.destreza << endl;
	getchar();
	system("cls");

	falasPersonagem("\n\n\t\tConsegui!, ele caiu... foi mais dificil do que eu imaginava, nao estava preparado.",player.nome);
	falasPersonagem("\n\n\t\tIncrivel.. eu nunca teria conseguido sem voce...","Thiago Nicola");
	falasPersonagem("\n\n\t\tBom agora que ja pegamos tudo o que precisamos vamo em frente.", player.nome);

	//SLIME
	Falas("Voces avistam um corredor escuro, apesar de estarem com medo e receosos os aventureiros encaram o medo.");
	Falas("Apos andar por um tempo Thiago percebe que o chão e viscoso e escorregadio. Cada passo faz um som pegajoso, como se algo estivesse grudando em seus pes..");

	Falas("Uma substancia estranha começa a se mover no chão...");
	Falas("De repente, ela se levanta e ganha forma!");
	Falas("Um Slime Pegajoso aparece e avança na direção de Thiago, tentando engoli-lo!");

	Mob mob2;
	mob.vida = 10;
	mob.forca = 2;
	mob.nome = "slime";
	Luta(player, inventario, item,mob);
	getchar();
	system("cls");

	cout << "Vida: " << player.vida << endl;
	cout << "Forca: " << player.forca << endl;
	cout << "Inteligencia: " << player.inteligencia << endl;
	cout << "Carisma: " << player.carisma << endl;
	cout << "Destreza: " << player.destreza << endl;
	getchar();
	system("cls");

	falasPersonagem("\n\n\t\tVoce esta bem Thiago??? foi ferido?",player.nome);
	system("cls");
	falasPersonagem("\n\n\t\tHahahaha tava bem gelado mas esta tudo bem","Thiago Nicola");
	system("cls");
	falasPersonagem("\n\n\t\tBom, eu acho que devemos para por hoje.. Vamos procurar algum lugar para descansar e comer",player.nome);
	system("cls");

	//ZUMBI
	Falas("Os aventureiros param para descansar e fazem uma fogueira com os suprimentos que possuiam");
	Falas("durante um tempo os dois, conversam sobre suas vidas e o que irão fazer após a aventura...");
	Falas("apos algum tempo de conversa os aventureiros caem no sono...");
	Falas("Thiago acorda e fica imovel como se tivesse visto um monstro");
	falasPersonagem("\n\n\t\tBom dia.. que cara e essa??",player.nome);
	system("cls");
	falasPersonagem("\n\n\t\tZzz-uuumm-biiiiiiii","Thiago Nicola");
	system("cls");

	Falas("O aventureiro estava agarrado a um Zumbi..");
	Falas("A luta se inicia...");

	Mob mob3;
	mob.vida = 12;
	mob.forca = 3;
	mob.nome = "Zumbi";
	Luta(player, inventario, item,mob);
	getchar();
	system("cls");

	cout << "Vida: " << player.vida << endl;
	cout << "Forca: " << player.forca << endl;
	cout << "Inteligencia: " << player.inteligencia << endl;
	cout << "Carisma: " << player.carisma << endl;
	cout << "Destreza: " << player.destreza << endl;
	getchar();
	system("cls");

	Falas("Apos o susto os aventureiros seguiram destruindo os monstros da masmorra 1 por um..");
	Falas("Os aventureiros encontram um Esqueleto zumbi..");

	//ESQUELETO ZUMBI
	Mob mob4;
	mob.vida = 12;
	mob.forca = 3;
	mob.nome = "Esqueleto zumbi";
	Luta(player, inventario, item,mob);
	getchar();
	system("cls");

	cout << "Vida: " << player.vida << endl;
	cout << "Forca: " << player.forca << endl;
	cout << "Inteligencia: " << player.inteligencia << endl;
	cout << "Carisma: " << player.carisma << endl;
	cout << "Destreza: " << player.destreza << endl;
	getchar();
	system("cls");

	Falas("Apos derrotar o Esqueleto Zumbi, os aventureiros se deparam com uma porta.");
	Falas("Porta essa que ali dentro esta um grande inimigo..");
	falasPersonagem("\n\n\t\tTalvez estejamos pertos do nosso objetivo Thiago.. e Ele esta atras dessa porta..",player.nome);
	system("cls");
	falasPersonagem("\n\n\t\tVamos juntos??","Thiago Nicola");
	system("cls");
	falasPersonagem("\n\n\t\tBora!!",player.nome);
	system("cls");

	//CHEFE DOS GOBLINS 
	Mob mob5;
	mob.vida = 14;
	mob.forca = 4;
	mob.nome = "Chefe dos Goblins";
	Luta(player, inventario, item,mob);
	getchar();
	system("cls");

	cout << "Vida: " << player.vida << endl;
	cout << "Forca: " << player.forca << endl;
	cout << "Inteligencia: " << player.inteligencia << endl;
	cout << "Carisma: " << player.carisma << endl;
	cout << "Destreza: " << player.destreza << endl;
	getchar();
	system("cls");

	Falas("Após uma batalha feroz contra o Ciclope Gigante, a sala está em silêncio.");
	Falas("O corpo colossal do inimigo cai ao chão com um estrondo ensurdecedor, fazendo a terra tremer.");
	Falas("Você, exausto, segura sua espada, enquanto Thiago Nicola, seu leal companheiro, se apoia em seu escudo quebrado, mas com um sorriso satisfeito.");
	system("cls");

falasPersonagem("\n\n\t\tConseguimos, meu amigo! Esse Ciclope nao foi páreo para nós.",player.nome);
system("cls");
falasPersonagem("\n\n\t\tFoi por pouco... ele quase nos pegou naquele último golpe.","Thiago Nicola");
system("cls");
falasPersonagem("\n\n\t\tMas o que importa é que vencemos. Agora o amuleto é nosso.",player.nome);
system("cls");


Falas("Ambos olham para o pedestal brilhando no centro da sala.\n");
Falas("\nVocê se aproxima, cada passo ecoando pela vasta câmara...\n");
Falas("\nO amuleto reluz em um brilho dourado, emanando uma aura calorosa e reconfortante.");

falasPersonagem("\n\n\t\tIncrível... Ele realmente existe. Agora podemos salvar a vila.","Thiago Nicola");
system("cls");
falasPersonagem("\n\n\t\tSim, Thiago. Essa jornada foi longa, mas valeu a pena.",player.nome);

Falas("Você guarda o amuleto com cuidado e olha para Thiago.");
Falas("Vamos voltar. A vila precisa de nós.");

Falas("Thiago sorri e bate no ombro do aventureiro.\n");
Falas("\nE depois disso, quem sabe, um pouco de descanso na taverna.");
Falas("\nCom certeza. E a primeira rodada é por minha conta.");

cout<< "	\n\n\t\t\t\t\t\tMUITO";
cout<< "	\n\n\t\t\t\t\t\tOBRIGADO";
cout<< "	\n\n\t\t\t\t\t\tPOR";
cout<< "	\n\n\t\t\t\t\t\tJOGAR";
getchar();
return 0;

}