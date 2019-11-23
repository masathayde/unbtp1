#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "entidades.h"
#include "dominios.h"
#include "controladores.h"

// No comeco do programa, o banco de dados ira recuperar os dados de um arquivo
class BancoDeDados {
   private:
      vector<Usuario>         usuarios;
      vector<Jogo>            jogos;
      vector<Ingresso>        ingressos;
      
      const char*             userFile {"usuarios.dat"};
      const char*             ticketFile {"ingressos.dat"};
      const char*             matchFile {"jogos.dat"};

      void                    atualizar () throw (exception);
      void                    atualizarUsuarios () throw (logic_error);
      void                    atualizarJogos () throw (exception);
      void                    atualizarIngressos () throw (exception);

      void                    carregarIngressos () throw (exception);
      void                    carregarJogos () throw (exception);
      void                    carregarUsuarios () throw (exception);

      BancoDeDados () {};
      BancoDeDados (const BancoDeDados&);
      void operator=(const BancoDeDados&);

   public:
      static BancoDeDados& getInstance () {
         static BancoDeDados instance;
         return instance;
      }

      void                    reconstruir ();
      void                    salvarTudo ();

      void                    salvarUsuario (Usuario* novoUsuario);
      void                    removerUsuario (Cpf cpf);
      bool                    verificarUsuario (Cpf cpf);
      Usuario*                escolherUsuario (Cpf cpf);

      void                    salvarJogo (Jogo* jogo);
      void                    removerJogo (CodigoJogo codigo);
      bool                    verificarJogo (CodigoJogo codigo);
      Jogo*                   escolherJogo (CodigoJogo codigo);

      void                    salvarIngresso (Ingresso* ingresso);
      Ingresso*               escolherIngresso (unsigned codigo);
      unsigned                ingressosTotal ();
      vector<Jogo*>           consulta (Data inicio, Data fim, Sigla estado, string cidade);   

};

#endif