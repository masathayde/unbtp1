#ifndef CONTROLADORES_H_INCLUDED
#define CONTROLADORES_H_INCLUDED
#include "dominios.h"
#include "entidades.h"
#include "database.h"

class MatchController;

class UserController {
   private:
      bool                  usuarioLogado;
      Usuario*              usuarioAtual;

      string                receberSenha ();
      string                receberCpf ();
      CCredito              receberCC ();

      void                  printarIngresso (Ingresso* ingresso);

   public:
      UserController ();
      void                  menu (BancoDeDados& db, MatchController& mController);
      void                  cadastrarUsuario (BancoDeDados& db);
      void                  logarUsuario (BancoDeDados& db) throw (logic_error);
      void                  deslogarUsuario () throw (logic_error);
      void                  deletarUsuario (BancoDeDados& db) throw (logic_error);
      void                  comprarIngresso (BancoDeDados& db, MatchController mController);
      bool                  usuarioAtualMaxJogos ();

      void                  cadastrarJogo (BancoDeDados& db, MatchController mController);
      void                  listarJogos (BancoDeDados& db, MatchController mController);
      void                  listarIngressos (BancoDeDados& db, MatchController mController);
      void                  alterarJogo (BancoDeDados& db, MatchController mController);
      void                  deletarJogo (BancoDeDados& db, MatchController mController);
};


class MatchController {
   private:
      string                receberCodigo ();
      string                receberNome ();
      string                receberCidade ();
      Estado                receberEstado ();
      string                receberEstadio ();
      unsigned              receberTipo ();
      void                  receberData (int* ano, int* mes, int* dia);
      void                  receberHorario (unsigned short* hora, unsigned short* minuto);
      float                 receberPreco ();

   public:
      Jogo*                 criarJogo (BancoDeDados& db, string cpf);
      void                  consultarJogo (BancoDeDados& db);
      void                  destruirJogo (BancoDeDados& db, CodigoJogo codigo);
      void                  printarInfo (Jogo* jogo);
   
};

#endif