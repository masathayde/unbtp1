#ifndef ENTIDADES_H_INCLUDED
#define ENTIDADES_H_INCLUDED

#include <bits/stdc++.h>
#include "dominios.h"

using namespace std;

// Nome padrao do arquivo de banco de dados
#define BANCODEDADOS_NOME "dados.bin"

// Forward declarations

class BancoDeDados;

/**** ENTIDADES ****/

class Ingresso {
   private:
      CodigoIngresso          codigo;
      CodigoJogo              jogo;
      Cpf                     comprador;

   public:
      void                    criar (unsigned codigo, CodigoJogo jogo, string cpf);
      CodigoIngresso          getCodigo ();
      CodigoJogo              getCodigoJogo ();
      Cpf                     getComprador ();
};


class Jogo {
   protected:
      CodigoJogo              codigo;
      NomeDoJogo              nome;
      Cidade                  cidade;
      Estado                  estado;
      Estadio                 estadio; // !!! muito parecido com "estado"
      TipoJogo                tipo;
      Data                    data;
      Horario                 horario;
      Preco                   preco;
      Disponibilidade         disp;
      Cpf                     criador;
      vector<CodigoIngresso>  ingressos;
   
   public:
      Jogo ();
      Jogo&                   operator= (const Jogo& outro);
      void                    setar (string codigo, string nome, string cidade, Estado estado,
                                    string estadio, unsigned tipo, Data data, Horario horario,
                                    float preco, string criador);
      void                    setDisp (unsigned input);

      CodigoJogo              getCodigo () const;
      string                  getNome () const;
      string                  getCidade () const;
      Estado                  getEstado () const;
      string                  getEstadio () const;
      TipoJogo                getTipo () const;
      Data                    getData () const;
      Horario                 getHorario () const;
      float                   getPreco () const;             
      Disponibilidade         getDisp () const;
      Cpf                     getCriador () const;

      void                    venderIngresso (CodigoIngresso ingresso);
      void                    carregarIngresso (CodigoIngresso ingresso);
      unsigned                getNumIngressos ();
      vector<CodigoIngresso>  getIngressosVendidos () const;


};


// Um digito a mais para o caractere /0 de fim de string.
class CCredito {
   private:
      string                  numero;
      string                  codSeg;
      short                   validadeMes;
      short                   validadeAno;

      const short             codSegSize {3};
      const short             numSize {16};

      void                    validarNumero (string numero) throw (invalid_argument);
      void                    validarValidade (short mes, short ano) throw (invalid_argument);
      void                    validarCodSeg (string codseg) throw (invalid_argument);

// Foi necessario adicionar o qualificador "const" as funcoes que nao modificam o objeto
// para que o overload no operador '=' funcione.
   public:                 
      void                    setar (string numero, string codseg, short mes, short ano);
      string                  getNumero () const;
      string                  getCodSeg () const;
      short                   getMes () const;
      short                   getAno () const;
      short                   getCodSegSize () { return codSegSize; };
      short                   getNumSize() { return numSize; };
      CCredito&               operator=(const CCredito& outro);
};

class Usuario {
   protected:
      Cpf                     cpf;
      Senha                   senha;
      vector<CodigoJogo>      jogos;
      const unsigned          maxJogos {5};
      vector<CodigoIngresso>  ingressos;
      CCredito                cartao;

   public:
      Usuario&                operator= (const Usuario& outro);

      void                    setSenha (string senha);
      void                    setCpf (string cpf);
      void                    setCC (CCredito& ccredito);

      string                  getCpf () const;
      string                  getSenha () const;
      CCredito                getCartao () const;
      bool                    podeCadastrarJogos ();
      bool                    possuiJogos ();
      bool                    possuiIngressos ();
      vector<CodigoJogo>      getJogos () const;
      vector<CodigoIngresso>  getIngressos () const;

      void                    adicionarJogo (CodigoJogo jogo);
      void                    removerJogo (CodigoJogo codigo);
      void                    adicionarIngresso(CodigoIngresso ingresso);

};

#endif