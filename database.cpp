#include "database.h"

void BancoDeDados::carregarIngressos () throw (exception)
{
   // Primeiro pegamos o numero de ingressos salvos

   size_t quant;
   ifstream file;
   file.open(ticketFile, ios::in | ios::binary);
   if (!file.good()) {
      cout << "\nArquivo nao encontrado";
      return;
   }
   file.read((char*) &quant, sizeof(size_t));

   for (int i = 0; i < quant; ++i)
   {
      Ingresso ingressoC;
      unsigned ingressoNum;
      // Mais numeros magicos
      char bufferCodJogo [4];
      char bufferCpf [12];
      string codJogo, cpf;
      CodigoJogo codigo;


      file.read((char*) &ingressoNum, sizeof(unsigned));
      file.read((char*) &bufferCodJogo, sizeof(char)*3);
      file.read((char*) &bufferCpf, sizeof(char)*11);

      bufferCodJogo[3] = '\0';
      bufferCpf[11] = '\0';
      codJogo = bufferCodJogo;
      cpf = bufferCpf;
      codigo.setar(codJogo);

      ingressoC.criar(ingressoNum, codigo, cpf);
      this->ingressos.push_back(ingressoC);
   }
   file.close();
}

void BancoDeDados::carregarJogos () throw (exception)
{
   size_t quant;
   ifstream file;
   // Checar se o arquivo existe

   file.open(matchFile, ios::in | ios::binary);

   if (!file.good()) {
      cout << "\nArquivo nao encontrado";
      return;
   }

   file.read((char*) &quant, sizeof(size_t));

   for (int i = 0; i < quant; ++i)
   {
      Jogo jogoC;
      string codigo, nome, cidade, estadio, estado, cpf;
      Estado estadoSigla;
      Data data;
      Horario horario;
      char bufferCodigo [4];
      size_t bufferNomeSize;
      char bufferNome [25];
      size_t bufferCidadeSize;
      char bufferCidade [17];
      char bufferEstado[3];
      size_t bufferEstadioSize;
      char bufferEstadio [26];
      unsigned bufferTipo;
      int bufferDataAno;
      int bufferDataMes;
      int bufferDataDia;
      unsigned short bufferHora;
      unsigned short bufferMin;
      float bufferPreco;
      unsigned bufferDisp;
      char bufferCpf [12];

      file.read(bufferCodigo, sizeof(char)*3);
      bufferCodigo[3] = '\0';
      codigo = bufferCodigo;

      file.read((char*) &bufferNomeSize, sizeof(size_t));
      file.read(bufferNome, bufferNomeSize);
      bufferNome[bufferNomeSize] = '\0';
      nome = bufferNome;

      file.read((char*) &bufferCidadeSize, sizeof(size_t));
      file.read(bufferCidade, bufferCidadeSize);
      bufferCidade[bufferCidadeSize] = '\0';
      cidade = bufferCidade;

      file.read(bufferEstado, sizeof(char)*2);
      bufferEstado[2] = '\0';
      estado = bufferEstado;
      estadoSigla.setar(estado);

      file.read((char*) &bufferEstadioSize, sizeof(size_t));
      file.read(bufferEstadio, bufferEstadioSize);
      bufferEstadio[bufferEstadioSize] = '\0';
      estadio = bufferEstadio;

      file.read((char*)&bufferTipo, sizeof(unsigned));

      file.read((char*)&bufferDataAno, sizeof(int));
      file.read((char*)&bufferDataMes, sizeof(int));
      file.read((char*)&bufferDataDia, sizeof(int));
      data.setar(bufferDataAno, bufferDataMes, bufferDataDia);

      file.read((char*)&bufferHora, sizeof(unsigned short));
      file.read((char*)&bufferMin, sizeof(unsigned short));
      horario.setar(bufferHora, bufferMin);

      file.read((char*)&bufferPreco, sizeof(float));

      file.read((char*)&bufferDisp, sizeof(unsigned));

      file.read(bufferCpf, sizeof(char)*12);
      bufferCpf[11] = '\0';
      cpf = bufferCpf;

      jogoC.setar(codigo, nome, cidade, estadoSigla, estadio, bufferTipo, data,
      horario, bufferPreco, cpf);
      jogoC.setDisp(bufferDisp);

      for (int j = 0; j < ingressos.size(); ++j) {
         if (ingressos[j].getCodigoJogo().get() == codigo)
            jogoC.carregarIngresso(ingressos[j].getCodigo());
      }

      this->jogos.push_back(jogoC);
   }

   file.close();
}

void BancoDeDados::carregarUsuarios () throw (exception)
{
   size_t quant;
   ifstream file;
   // Checar se o arquivo existe

   file.open(userFile, ios::in | ios::binary);

   if (!file.good()) {
      cout << "\nArquivo nao encontrado";
      return;
   }

   file.read((char*) &quant, sizeof(size_t));

   for (int i = 0; i < quant; ++i)
   {
      Usuario usuarioC;
      string cpf, senha, ccNumero, ccCodSeg;
      CCredito cartao;
      char bufferCpf [12];
      char bufferSenha [7];
      char bufferCartaoNum [17];
      char bufferCodSeg [4];
      short bufferMes, bufferAno;

      file.read(bufferCpf, sizeof(char)*11);
      bufferCpf[11] = '\0';
      cpf = bufferCpf;

      file.read(bufferSenha, sizeof(char)*6);
      bufferSenha[6] = '\0';
      senha = bufferSenha;

      file.read(bufferCartaoNum, sizeof(char)*16);
      bufferCartaoNum[16] = '\0';
      ccNumero = bufferCartaoNum;

      file.read(bufferCodSeg, sizeof(char)*3);
      bufferCodSeg[3] = '\0';
      ccCodSeg = bufferCodSeg;

      file.read((char*) &bufferMes, sizeof(short));
      file.read((char*) &bufferAno, sizeof(short));
      cartao.setar(ccNumero, ccCodSeg, bufferMes, bufferAno);


      usuarioC.setCpf(cpf);
      usuarioC.setSenha(senha);
      usuarioC.setCC(cartao);

      for (int j = 0; j < this->jogos.size(); ++j) {
         if (jogos[j].getCriador().get() == usuarioC.getCpf()) {
            usuarioC.adicionarJogo(jogos[j].getCodigo());
         }
      }
      for (int j = 0; j < this->ingressos.size(); ++j) {
         if (ingressos[j].getComprador().get() == usuarioC.getCpf()) {
            usuarioC.adicionarIngresso(ingressos[j].getCodigo());
         }
      }


      this->usuarios.push_back(usuarioC);
   }

   file.close();
}

void BancoDeDados::reconstruir ()
{
   // Ordem deve ser: Ingressos -> Jogos -> Usuarios
   this->carregarIngressos();
   this->carregarJogos();
   this->carregarUsuarios();
}

void BancoDeDados::atualizarIngressos () throw (exception)
{
   ofstream file;
   file.open(ticketFile, ios::out | ios::binary);
   size_t sizeIngressos = ingressos.size();
   file.write((char*) &sizeIngressos, sizeof(size_t));

   for (int i = 0; i < ingressos.size(); ++i)
   {
      size_t length;
      unsigned temp;

      temp = ingressos[i].getCodigo().get();
      file.write((char*) &temp, sizeof(unsigned));

      length = ingressos[i].getCodigoJogo().get().size();
      file.write (ingressos[i].getCodigoJogo().get().c_str(), length);

      length = ingressos[i].getComprador().get().size();
      file.write (ingressos[i].getComprador().get().c_str(), length);
   }
   file.close();
}

void BancoDeDados::atualizarJogos () throw (exception)
{
   ofstream file;
   file.open(matchFile, ios::out | ios::binary);
   size_t sizeJogos = jogos.size();
   file.write((char*) &sizeJogos, sizeof(size_t));

   for (int i = 0; i < jogos.size(); ++i)
   {
      size_t length;
      unsigned uTemp;
      unsigned short usTemp0, usTemp1;
      int iTemp;
      float fTemp;

      length = jogos[i].getCodigo().get().size();
      file.write(jogos[i].getCodigo().get().c_str(), length);

      length = jogos[i].getNome().size();
      file.write((char*) &length, sizeof(size_t));
      file.write(jogos[i].getNome().c_str(), length);

      length = jogos[i].getCidade().size();
      file.write((char*) &length, sizeof(size_t));
      file.write(jogos[i].getCidade().c_str(), length);

      file.write(jogos[i].getEstado().getString().c_str(), sizeof(char)*2);

      length = jogos[i].getEstadio().size();
      file.write((char*) &length, sizeof(size_t));
      file.write(jogos[i].getEstadio().c_str(), length);

      uTemp = jogos[i].getTipo().get();
      file.write((char*) &uTemp, sizeof(unsigned));

      iTemp = jogos[i].getData().getAno();
      file.write((char*) &iTemp, sizeof(int));
      iTemp = jogos[i].getData().getMes();
      file.write((char*) &iTemp, sizeof(int));
      iTemp = jogos[i].getData().getDia();
      file.write((char*) &iTemp, sizeof(int));

      jogos[i].getHorario().get(&usTemp0, &usTemp1);
      file.write((char*) &usTemp0, sizeof(unsigned short));
      file.write((char*) &usTemp1, sizeof(unsigned short));

      fTemp = jogos[i].getPreco();
      file.write((char*) &fTemp, sizeof(float));

      uTemp = jogos[i].getDisp().get();
      file.write((char*) &uTemp, sizeof(unsigned));

      length = jogos[i].getCriador().get().size();
      file.write(jogos[i].getCriador().get().c_str(), length);
   }
   file.close();
}

void BancoDeDados::atualizarUsuarios () throw (logic_error)
{
   // Assim serao salvos os usuarios
   // Quantidade de usuarios primeiro

   ofstream file;
   file.open(userFile, ios::out | ios::binary);

   if (!file.good())
      throw logic_error("Erro: Nao foi possivel salvar dados");

   size_t sizeUsuarios = usuarios.size();
   file.write((char*) &sizeUsuarios, sizeof(size_t));
   
   // Para cada usuario
   // 1 - CPF 
   // 2 - Senha sem \0
   // 3 - Cartao de credito

   for (int i = 0; i < usuarios.size(); ++i)
   {
      size_t length;
      short temp;

      length = usuarios[i].getCpf().length();
      //cout << "\n!!" << length << "\n\n";
      file.write(usuarios[i].getCpf().c_str(), length);

      length = usuarios[i].getSenha().length();
      //cout << "\n!!" << length << "\n\n";
      file.write(usuarios[i].getSenha().c_str(), length);

      // Numeros magicos
      file.write(usuarios[i].getCartao().getNumero().c_str(), sizeof(char)*16);
      file.write(usuarios[i].getCartao().getCodSeg().c_str(), sizeof(char)*3);

      temp = usuarios[i].getCartao().getMes();
      file.write((char*) &temp, sizeof(short));
      temp = usuarios[i].getCartao().getAno();
      file.write((char*) &temp, sizeof(short));
   }

   file.close();
}

void BancoDeDados::atualizar () throw (exception)
{
   this->atualizarIngressos();
   this->atualizarJogos();
   this->atualizarUsuarios();
}

void BancoDeDados::salvarTudo ()
{
   this->atualizar();
}

void BancoDeDados::salvarUsuario (Usuario* novoUsuario)
{
   this->usuarios.push_back(*novoUsuario);
   this->atualizarUsuarios();
}

void BancoDeDados::salvarJogo (Jogo* novoJogo)
{
   this->jogos.push_back(*novoJogo);
   this->atualizarJogos();
}

void BancoDeDados::salvarIngresso (Ingresso* novoIngresso)
{
   this->ingressos.push_back(*novoIngresso);
   this->atualizarIngressos();
}

bool BancoDeDados::verificarUsuario (Cpf cpf)
{
   // Debug
   // cout << "\n\n!!!!!!!" << usuarios.size() << "\n\n";
   for (auto it : usuarios) {

      if (it.getCpf() == cpf.get())
         return true;
   }
   return false;
}

bool BancoDeDados::verificarJogo (CodigoJogo jogo)
{
   for (auto it : jogos) {
      if (it.getCodigo().get() == jogo.get())
         return true;
   }
   return false;
}

Usuario* BancoDeDados::escolherUsuario (Cpf cpf)
{
   for (vector<Usuario>::iterator it = usuarios.begin(); it != usuarios.end(); it++)
   {
      if (it->getCpf() == cpf.get())
         return &(*it);
   }
   return NULL;
}

Jogo* BancoDeDados::escolherJogo (CodigoJogo jogo)
{
   for (vector<Jogo>::iterator it = jogos.begin(); it != jogos.end(); it++)
   {
      if (it->getCodigo().get() == jogo.get())
         return &(*it);
   }
   return NULL;
}

Ingresso* BancoDeDados::escolherIngresso (unsigned codigo)
{
   for (vector<Ingresso>::iterator it = ingressos.begin(); it != ingressos.end(); it++)
   {
      if (it->getCodigo().get() == codigo)
         return &(*it);
   }
   return NULL;
}

void BancoDeDados::removerUsuario (Cpf cpf)
{
   for (vector<Usuario>::iterator it = usuarios.begin(); it != usuarios.end(); ++it) {
      if (it->getCpf() == cpf.get()) {
         usuarios.erase(it);
         break;
      }
   }
   this->atualizar();
}

void BancoDeDados::removerJogo (CodigoJogo codigo)
{
   for (vector<Jogo>::iterator it = jogos.begin(); it != jogos.end(); ++it) {
      if (it->getCodigo().get() == codigo.get()) {
         jogos.erase(it);
         break;
      }
   }
   this->atualizar();
}

unsigned BancoDeDados::ingressosTotal ()
{
   return (unsigned) this->ingressos.size();
}

vector<Jogo*> BancoDeDados::consulta (Data inicio, Data fim, Sigla estado, string cidade)
{
   vector<Jogo*> result;

   for (vector<Jogo>::iterator it = jogos.begin(); it != jogos.end(); it++)
   {
      // Checar data
      if (it->getData().getAno() < inicio.getAno() || it->getData().getAno() > fim.getAno())
         continue;
      if (it->getData().getAno() == inicio.getAno() && it->getData().getMes() < inicio.getMes())
         continue;
      if (it->getData().getAno() == fim.getAno() && it->getData().getMes() > fim.getMes())
         continue;
      if (it->getData().getAno() == inicio.getAno() && it->getData().getMes() == inicio.getMes() && it->getData().getDia() < inicio.getDia())
         continue;
      if (it->getData().getAno() == fim.getAno() && it->getData().getMes() == fim.getMes() && it->getData().getDia() > fim.getDia())
         continue;
      if (it->getEstado().getSigla() != estado)
         continue;
      if (it->getCidade() != cidade)
         continue;

      result.push_back(&(*it));
   }

   return result;
}
