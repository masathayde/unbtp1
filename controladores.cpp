#include "controladores.h"

UserController::UserController ()
{
   usuarioLogado = false;
   usuarioAtual = NULL;
}


string UserController::receberSenha ()
{
   Senha senha0, senha1;
   string input0, input1;
   bool done = false;

   while (!done) {

      cout << "\nInserir senha: ";
      cin >> input0;
      senha0.setar(input0);
      cout << "\nConfirmar senha: ";
      cin >> input1;
      senha1.setar(input1);

      if (input0 != input1)
         cout << "\nErro: senhas diferentes!";
      else
         done = true;
      
      cin.clear();
		cin.ignore((long long)numeric_limits<streamsize>::max, '\n');

   }
   return input0;
}

string UserController::receberCpf ()
{
   string input;
   cout << "\nInserir CPF: ";
   cin >> input;
   return input;
}

CCredito UserController::receberCC ()
{
   CCredito novo;
   string numero, codseg;
   short mes, ano;

   cout << "\nInserir numero de cartao de credito: ";
   cin >> numero;
   cout << "\nInserir codigo de seguranca: ";
   cin >> codseg;
   cout << "\nInserir mes de vencimento: ";
   cin >> mes;
   cout << "\nInserir ano de vencimento: ";
   cin >> ano;

   novo.setar(numero, codseg, mes, ano);
   return novo;
}

void UserController::cadastrarUsuario (BancoDeDados& db)
{
   Usuario novo;
   bool done = false;

   while (!done) {
      string input;
      Cpf novoCpf;
      input = this->receberCpf();
      novoCpf.setar(input);

      bool usuarioExiste;
      usuarioExiste = db.verificarUsuario(novoCpf);

      if (usuarioExiste) {
         cout << "\nUsuario ja existe";
      } else {
         novo.setCpf(input);
         done = true;
      }
   }

   string senha;
   senha = this->receberSenha();
   novo.setSenha(senha);

   CCredito novoCC;
   novoCC = this->receberCC();
   novo.setCC(novoCC);

   db.salvarUsuario(&novo);
}

void UserController::logarUsuario (BancoDeDados& db) throw (logic_error)
{
   if (usuarioLogado)
      throw logic_error("Erro: Usuario ja logado");

   string inputCpf, inputSenha;
   inputCpf = this->receberCpf();
   Cpf cpfAtual;
   cpfAtual.setar(inputCpf);
   bool usuarioExiste;
   usuarioExiste = db.verificarUsuario (cpfAtual);
   if (!usuarioExiste) {
      cout << "\nUsuario nao encontrado";
      return;
   }
   this->usuarioAtual = db.escolherUsuario(cpfAtual);

   cout << "\nInserir Senha: ";
   cin >> inputSenha;
   Senha senhaAtual;
   senhaAtual.setar(inputSenha);

   if (inputSenha == usuarioAtual->getSenha()) {
      usuarioLogado = true;
      cout << "\nUsuario logado com sucesso";
   } else {
      usuarioAtual = NULL;
      cout << "\nSenha incorreta";
   }
}

void UserController::deslogarUsuario () throw (logic_error)
{
   if (!usuarioLogado)
      throw logic_error("Erro: Nenhum usuario logado");

   cout << "\nUsuario saiu com sucesso";
   usuarioLogado = false;
   usuarioAtual = NULL;
}

void UserController::deletarUsuario (BancoDeDados& db) throw (logic_error)
{
   if (!usuarioLogado)
      throw logic_error("Erro: Nenhum usuario logado");

   if (usuarioAtual->possuiJogos()) {
      cout << "\nNao e permitido deletar usuario com jogos cadastrados";
      return;
   }

   Cpf usuarioParaDeletar;
   usuarioParaDeletar.setar(usuarioAtual->getCpf());
   db.removerUsuario(usuarioParaDeletar);
   usuarioLogado = false;
   usuarioAtual = NULL;
   cout << "\nUsuario removido com sucesso";
}

void UserController::comprarIngresso (BancoDeDados& db, MatchController mController)
{
   string input;
   cout << "\nInserir codigo do jogo: ";
   cin >> input;
   CodigoJogo codJogo;
   codJogo.setar(input);

   bool jogoExiste;
   jogoExiste = db.verificarJogo(codJogo);
   if (!jogoExiste) {
      cout << "\nJogo nao cadastrado";
      return;
   }

   Jogo* jogo;

   jogo = db.escolherJogo(codJogo);

   // Verificar disponibilidade

   mController.printarInfo(jogo);
   unsigned disponiveis = jogo->getDisp().get();

   if (disponiveis == 0) {
      cout << "\nNao ha ingressos disponiveis";
      return;
   }

   unsigned quant = 0;
   cout << "\nInserir quantidade de ingressos desejada: ";
   cin >> quant;

   if (quant > disponiveis || quant == 0) {
      cout << "\nQuantidade invalida";
      return;
   }

   // Criar ingressos

   for (int i = 0; i < quant; ++i)
   {
      Ingresso novoIngresso;
      unsigned novoCodigo = db.ingressosTotal() + 1;
      novoIngresso.criar (novoCodigo, jogo->getCodigo(), usuarioAtual->getCpf());
      db.salvarIngresso(&novoIngresso);
      jogo->venderIngresso(novoIngresso.getCodigo());
      usuarioAtual->adicionarIngresso(novoIngresso.getCodigo());
   }

   cout << "\nCompra realizada";
}

void UserController::cadastrarJogo (BancoDeDados& db, MatchController mController)
{
   if (!usuarioAtual->podeCadastrarJogos()) {
      cout << "Usuario ja cadastrou o numero maximo de jogos permitido";
      return;
   }

   Jogo* novoJogo;
   novoJogo = mController.criarJogo(db, usuarioAtual->getCpf());
   if (novoJogo == NULL)
      return;

   usuarioAtual->adicionarJogo(novoJogo->getCodigo());
   cout << "\nJogo cadastrado";
}

void UserController::listarJogos (BancoDeDados& db, MatchController mController)
{
   if (!usuarioAtual->possuiJogos()) {
      cout << "\nNenhum jogo cadastrado";
      return;
   }

   cout << "\nJogos cadastrados:\n";

   vector<CodigoJogo> jogosDoUsuario;
   jogosDoUsuario = usuarioAtual->getJogos();

   for (auto it: jogosDoUsuario)
   {
      Jogo* jogoParaPrintar = db.escolherJogo(it);
      mController.printarInfo(jogoParaPrintar);
   }
}

void UserController::printarIngresso (Ingresso* ingresso)
{
   cout << "\n####";
   cout << "\n> Ingresso >";
   cout << "\nCodigo: " << ingresso->getCodigo().getString();
   cout << "\nComprador:" << ingresso->getComprador().get();
}

void UserController::listarIngressos (BancoDeDados& db, MatchController mController)
{
   if (!usuarioAtual->possuiIngressos()) {
      cout << "\nNenhum ingresso comprado";
      return;
   }

   cout << "\nIngressos comprados:\n";

   vector<CodigoIngresso> ingressosDoUsuario;
   ingressosDoUsuario = usuarioAtual->getIngressos();

   for (auto it : ingressosDoUsuario)
   {
      Ingresso* ingressoParaPrintar = db.escolherIngresso(it.get());
      Jogo* jogoParaPrintar = db.escolherJogo(ingressoParaPrintar->getCodigoJogo());
      this->printarIngresso(ingressoParaPrintar);
      mController.printarInfo(jogoParaPrintar);
   }
}

void UserController::alterarJogo (BancoDeDados& db, MatchController mController)
{
   this->listarJogos(db, mController);
   if (!usuarioAtual->possuiJogos())
      return;

   cout << "\nInserir codigo do jogo a ser alterado: ";
   string input;
   cin >> input;
   CodigoJogo codigo;
   codigo.setar(input);

   Jogo* jogoParaAlterar;
   jogoParaAlterar = db.escolherJogo(codigo);

   // Verificar se o jogo tem ingressos vendidos

   if (jogoParaAlterar->getNumIngressos() > 0) {
      cout << "\nNao e permitido alterar jogos com ingressos vendidos";
      return;
   }

   // Essencialmente, deleta-se o jogo e recria-o

   usuarioAtual->removerJogo(codigo);
   mController.destruirJogo(db, codigo);

   Jogo* novoJogo;
   novoJogo = mController.criarJogo(db, usuarioAtual->getCpf());
   if (novoJogo == NULL)
      return;

   usuarioAtual->adicionarJogo(novoJogo->getCodigo());

}

void UserController::deletarJogo (BancoDeDados& db, MatchController mController)
{
   this->listarJogos(db, mController);
   if (!usuarioAtual->possuiJogos())
      return;

   cout << "\nInserir codigo do jogo a ser deletado: ";
   string input;
   cin >> input;
   CodigoJogo codigo;
   codigo.setar(input);

   Jogo* jogoParaDeletar;
   jogoParaDeletar = db.escolherJogo(codigo);

   // Verificar se o jogo tem ingressos vendidos

   if (jogoParaDeletar->getNumIngressos() > 0) {
      cout << "\nNao e permitido deletar jogos com ingressos vendidos";
      return;
   }

   usuarioAtual->removerJogo(codigo);
   mController.destruirJogo(db, codigo);
}

void UserController::menu (BancoDeDados& db, MatchController& mController)
{
   int escolha = 0;
   bool done = false;

   while(!done) {

      cout << "\n\n\n##############";
      cout << "\nMenu Principal";

      if (usuarioLogado) {
         cout << "\n\n(1) - Consultar jogo";
         cout << "\n(2) - Comprar ingresso";
         cout << "\n(3) - Cadastrar jogo";
         cout << "\n(4) - Alterar jogo";
         cout << "\n(5) - Deletar jogo";
         cout << "\n(6) - Listar jogos cadastrados";
         cout << "\n(7) - Listar ingressos comprados";
         cout << "\n(8) - Deslogar";
         cout << "\n(9) - Deletar conta";
         cout << "\n(0) - Sair";

         cout << "\nDigite escolha: ";
         cin >> escolha;
         cin.clear();
		   cin.ignore((long long)numeric_limits<streamsize>::max, '\n');

         switch (escolha) {
            case 1:  mController.consultarJogo(db);
                     break;
            case 2:  comprarIngresso(db, mController);
                     break;
            case 3:  cadastrarJogo(db, mController);
                     break;
            case 4:  alterarJogo(db, mController);
                     break;
            case 5:  deletarJogo(db, mController);
                     break;
            case 6:  listarJogos(db, mController);
                     break;
            case 7:  listarIngressos(db, mController);
                     break;
            case 8:  deslogarUsuario();
                     break;
            case 9:  deletarUsuario(db);
                     break;

            case 0:  done = true;
                     cout << "\nSaindo do programa";
                     break;

            default: cout << "\nOpcao invalida";
                     break;
         }

      } else {
         cout << "\n\n(1) - Consultar jogo";
         cout << "\n(2) - Cadastrar-se";
         cout << "\n(3) - Logar";
         cout << "\n(0) - Sair";
         
         cout << "\nDigite escolha: ";
         cin >> escolha;
         cin.clear();
		   cin.ignore((long long)numeric_limits<streamsize>::max, '\n');

         switch (escolha) {
            case 1:  mController.consultarJogo(db);
                     break;
            case 2:  cadastrarUsuario(db);
                     break;
            case 3:  logarUsuario(db);
                     break;
            
            case 0:  done = true;
                     cout << "\nSaindo do programa";
                     break;
            
            default: cout << "\nOpcao invalida";
                     break;

         }
      }
   }
}


// --------------


string MatchController::receberCodigo ()
{
   string input;
   cout << "\nInserir codigo do jogo: ";
   cin >> input;
   return input;
}

string MatchController::receberNome ()
{
   string input;
   cin.clear();
   cin.ignore((long long)numeric_limits<streamsize>::max, '\n');
   cout << "\nInserir nome do jogo: ";
   getline(cin, input);
   return input;
}

string MatchController::receberCidade ()
{
   string input;
   cin.clear();
   cin.ignore((long long)numeric_limits<streamsize>::max, '\n');
   cout << "\nInserir cidade do jogo: ";
   getline(cin, input);
   return input;
}

Estado MatchController::receberEstado ()
{
   string input;
   Estado novoEstado;
   cout << "\nInserir Estado do jogo (sigla): ";
   cin >> input;
   novoEstado.setar(input);
   return novoEstado;
}

string MatchController::receberEstadio ()
{
   string input;
   cin.clear();
   cin.ignore((long long)numeric_limits<streamsize>::max, '\n');
   cout << "\nInserir estadio do jogo: ";
   getline(cin, input);
   return input;
}

unsigned MatchController::receberTipo ()
{
   unsigned input;
   cout << "\nInserir tipo de jogo";
   cout << "\n(1 - Local)\n(2 - Estadual)\n(3 - Nacional)\n(4 - Internacional)\n: ";
   cin >> input;
   return input;
}

void MatchController::receberData (int* ano, int* mes, int* dia)
{
   cout << "\nInserir ano do jogo (ultimos dois digitos) : ";
   cin >> *ano;
   cout << "\nInserir mes do jogo: ";
   cin >> *mes;
   cout << "\nInserir dia do jogo: ";
   cin >> *dia;
}

void MatchController::receberHorario (unsigned short* hora, unsigned short* min)
{
   cout << "\nInserir hora de inicio do jogo: ";
   cin >> *hora;
   cout << "\nInserir minuto de inicio do jogo: ";
   cin >> *min;
}

float MatchController::receberPreco ()
{
    float input;
    cout << "\nInserir preco do jogo (ate R$1000): ";
    cin >> input;
    return input;
}

Jogo* MatchController::criarJogo (BancoDeDados& db, string cpf)
{
   Jogo novoJogo;
   string codigo;
   string nome;
   string cidade;
   Estado estado;
   string estadio;
   unsigned tipo;
   Data data;
   Horario horario;
   int ano, mes, dia;
   unsigned short hora, minuto;
   float preco;

   codigo = this->receberCodigo();
   CodigoJogo codigoAtual;
   codigoAtual.setar(codigo);
   bool jogoExiste;
   jogoExiste = db.verificarJogo(codigoAtual);

   if (jogoExiste) {
       cout << "\nJogo ja cadastrado";
       return NULL;
   }

   nome = this->receberNome();
   cidade = this->receberCidade();
   estado = this->receberEstado();
   estadio = this->receberEstadio();
   tipo = this->receberTipo();

   this->receberData(&ano, &mes, &dia);
   data.setar(ano, mes, dia);

   this->receberHorario(&hora, &minuto);
   horario.setar(hora, minuto);

   preco = this->receberPreco();

   novoJogo.setar(codigo, nome, cidade, estado, estadio, tipo, data, horario,
   preco, cpf);

   db.salvarJogo(&novoJogo);
   return db.escolherJogo(codigoAtual);
}

void MatchController::destruirJogo (BancoDeDados& db, CodigoJogo codigo)
{
   db.removerJogo(codigo);
}

void MatchController::printarInfo (Jogo* jogo)
{
   unsigned short hora, min;
   jogo->getHorario().get(&hora, &min);

   cout << "\n#######";
   cout << "\n>";
   cout << "\nCodigo: " << jogo->getCodigo().get();
   cout << "\nNome: " << jogo->getNome();
   cout << "\nCidade: " << jogo->getCidade();
   cout << "\nEstado: " << jogo->getEstado().getString();
   cout << "\nEstadio: " << jogo->getEstadio();
   cout << "\nTipo: " << jogo->getTipo().getString();
   cout << "\nData: ";
   printf("%2d/%2d/20%2d", jogo->getData().getDia(), jogo->getData().getMes(), jogo->getData().getAno());
   cout << "\nHorario: ";
   printf("%2d:%2d", hora, min);
   cout << "\nPreco: R$" << jogo->getPreco();
   cout << "\nIngressos disponiveis: " << jogo->getDisp().get();
}

void MatchController::consultarJogo (BancoDeDados& db)
{
   Data inicio, fim;
   Estado estado;
   string cidadeInput, estadoInput;
   int anoIn, mesIn, diaIn;

   cout << "\nInserir ano inicial de consulta: ";
   cin >> anoIn;
   cout << "\nInserir mes inicial de consulta: ";
   cin >> mesIn;
   cout << "\nInserir dia inicial de consulta: ";
   cin >> diaIn;
   inicio.setar(anoIn, mesIn, diaIn);

   cout << "\nInserir ano final de consulta: ";
   cin >> anoIn;
   cout << "\nInserir mes final de consulta: ";
   cin >> mesIn;
   cout << "\nInserir dia final de consulta: ";
   cin >> diaIn;
   fim.setar(anoIn, mesIn, diaIn);

   cout << "\nInserir sigla do Estado para consulta: ";
   cin >> estadoInput;
   estado.setar(estadoInput);

   cout << "\nInserir cidade para consulta: ";
   cin >> cidadeInput;

   vector<Jogo*> resultados;
   resultados = db.consulta(inicio, fim, estado.getSigla(), cidadeInput);

   if (resultados.size() == 0) {
      cout << "\nNenhum resultado encontrado";
      return;
   }

   cout << "\n" << resultados.size() << " jogo(s) encontrado(s)";
   for (int i = 0; i < resultados.size(); ++i)
   {
      cout << endl;
      this->printarInfo(resultados[i]);
   }

}