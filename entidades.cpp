#include "entidades.h"
#include "dominios.h"


void Ingresso::criar (unsigned _codigo, CodigoJogo _jogo, string _cpf)
{
   codigo.setar(_codigo);
   jogo = _jogo;
   comprador.setar(_cpf);
}

CodigoIngresso Ingresso::getCodigo ()
{
   return codigo;
}

CodigoJogo Ingresso::getCodigoJogo ()
{
   return jogo;
}

Cpf Ingresso::getComprador ()
{
   return comprador;
}

// --------

void CCredito::validarNumero (string input) throw (invalid_argument)
{
   if (input.size() != this->numSize)
      throw invalid_argument("Erro: Cartao invalido");

   // Algoritmo de Luhn
   int sum = 0;

   for (int i = 0; i < numSize; ++i)
   {
      if (input[i] < '0' || input[i] > '9')
         throw invalid_argument("Erro: Cartao invalido");

      int dig = (input[i] - '0') * (2 - i%2);

      if (dig > 9)
         dig -= 9;

      sum += dig;
   }

   if (sum % 10 != 0)
      throw invalid_argument("Erro: Cartao invalido");
}

void CCredito::validarValidade (short mes, short ano) throw (invalid_argument)
{
   if (mes < 1 || mes > 12)
      throw invalid_argument("Erro: Cartao invalido");

   if (ano < 0 || ano > 99)
      throw invalid_argument("Erro: Cartao invalido");
}

void CCredito::validarCodSeg (string input) throw (invalid_argument)
{
   if (input.size() != this->codSegSize)
      throw invalid_argument("Erro: Cartao invalido");

   for (auto it : input) {
      if (it < '0' || it > '9')
         throw invalid_argument("Erro: Cartao invalido");
   }
}

void CCredito::setar (string numero, string codseg, short mes, short ano)
{
   this->validarNumero(numero);
   this->validarValidade(mes, ano);
   this->validarCodSeg(codseg);
   this->numero = numero;
   this->codSeg = codseg;
   this->validadeMes = mes;
   this->validadeAno = ano;
}

string CCredito::getNumero () const
{
   return this->numero;
}

string CCredito::getCodSeg () const
{
   return this->codSeg;
}

short CCredito::getMes () const
{
   return this->validadeMes;
}

short CCredito::getAno () const
{
   return this->validadeAno;
}

CCredito& CCredito::operator=(const CCredito& outro)
{
   this->numero = outro.getNumero();
   this->codSeg = outro.getCodSeg();
   this->validadeMes = outro.getMes();
   this->validadeAno = outro.getAno();
   return *this;
}

// ----------

void Usuario::setSenha (string input)
{
   this->senha.setar(input);
}

void Usuario::setCpf (string input)
{
   this->cpf.setar(input);
}

void Usuario::setCC(CCredito& ccredito)
{
   this->cartao = ccredito;
}

string Usuario::getCpf () const
{
   return cpf.get();
}

string Usuario::getSenha () const
{
   return senha.get();
}

CCredito Usuario::getCartao () const
{
   return cartao;
}

bool Usuario::podeCadastrarJogos ()
{
   return jogos.size() < maxJogos;
}

bool Usuario::possuiJogos ()
{
   return jogos.size() > 0;
}

bool Usuario::possuiIngressos ()
{
   return ingressos.size() > 0;
}

vector<CodigoJogo> Usuario::getJogos () const
{
   return jogos;
}

vector<CodigoIngresso> Usuario::getIngressos () const
{
   return ingressos;
}

void Usuario::adicionarJogo (CodigoJogo jogo)
{
   jogos.push_back(jogo);
}

void Usuario::removerJogo (CodigoJogo codigo)
{
   for (int i = 0; i < jogos.size(); ++i) {
      if (jogos[i].get() == codigo.get()) {
         jogos.erase(jogos.begin()+i);
         break;
      }
   }
}

void Usuario::adicionarIngresso (CodigoIngresso ingresso)
{
   this->ingressos.push_back(ingresso);
}

Usuario& Usuario::operator= (const Usuario& outro)
{
   cpf.setar(outro.getCpf());
   senha.setar(outro.getSenha());
   jogos = outro.getJogos();
   ingressos = outro.getIngressos();
   cartao = outro.getCartao();
   return *this;
}

// --------

Jogo::Jogo ()
{
   this->disp.setar(disp.getMaxDisp());
}

void Jogo::setar (string nCodigo, string nNome, string nCidade,
Estado nEstado, string nEstadio, unsigned nTipo, Data nData,
Horario nHorario, float nPreco, string nCriador)
{
   this->codigo.setar(nCodigo);
   this->nome.setar(nNome);
   this->cidade.setar(nCidade);
   this->estado = nEstado;
   this->estadio.setar(nEstadio);
   this->tipo.setar(nTipo);

   int ano, mes, dia;
   ano = nData.getAno();
   mes = nData.getMes();
   dia = nData.getDia();
   this->data.setar(ano, mes, dia);

   unsigned short m, a;
   nHorario.get(&m, &a);
   this->horario.setar(m, a);
   
   this->preco.setar(nPreco);
   this->criador.setar(nCriador);
}

void Jogo::setDisp (unsigned input)
{
   this->disp.setar(input);
}

CodigoJogo Jogo::getCodigo () const
{
   return codigo;
}

string Jogo::getNome () const
{
   return this->nome.get();
}

string Jogo::getCidade () const
{
   return this->cidade.get();
}

Estado Jogo::getEstado () const
{
   return estado;
}

string Jogo::getEstadio () const
{
   return estadio.get();
}

TipoJogo Jogo::getTipo () const
{
   return tipo;
}

Data Jogo::getData () const
{
   return data;
}

Horario Jogo::getHorario () const
{
   return horario;
}

float Jogo::getPreco () const
{
   return preco.get();
}

Disponibilidade Jogo::getDisp () const
{
   return disp;
}

Cpf Jogo::getCriador () const
{
   return criador;
}

void Jogo::venderIngresso (CodigoIngresso ingresso)
{
   unsigned dispAtual = this->disp.get();
   this->disp.setar(dispAtual - 1);
   ingressos.push_back(ingresso);
}

void Jogo::carregarIngresso (CodigoIngresso ingresso)
{
   ingressos.push_back(ingresso);
}

unsigned Jogo::getNumIngressos ()
{
   return ingressos.size();
}

vector<CodigoIngresso> Jogo::getIngressosVendidos () const
{
   return ingressos;
}

Jogo& Jogo::operator= (const Jogo& outro)
{
   codigo = outro.getCodigo();
   nome.setar(outro.getNome());
   cidade.setar(outro.getCidade());
   estado = outro.getEstado();
   estadio.setar(outro.getEstadio());
   tipo.setar(outro.getTipo().get());
   data = outro.getData();
   horario = outro.getHorario();
   preco.setar(outro.getPreco());
   disp.setar(outro.getDisp().get());
   criador = outro.getCriador();
   ingressos = outro.getIngressosVendidos();

   return *this;
}