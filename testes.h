#ifndef TESTES_H_INCLUDED
#define TESTES_H_INCLUDED

#include "dominios.h"


class TUCodigoJogo {
    private:
        CodigoJogo              codigo;
        int                     estado;
        void                    testar();
        const string            valorValido {"123"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
    
};

class TUCodigoIngresso {
    private:
        CodigoIngresso          codigo;
        int                     estado;
        void                    testar();
        const unsigned          valorValidoUns {99999};
        const string            valorValidoStr {"99999"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUNomeDoJogo {
    private:
        NomeDoJogo              nome;
        int                     estado;
        void                    testar();
        const string            valorValido {"Goias x Vitoria"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUHorario {
    private:
        Horario                 horario;
        int                     estado;
        void                    testar();
        const unsigned short    valorValidoHora {15};
        const unsigned short    valorValidoMin {15};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUPreco {
    private:
        Preco                   preco;
        int                     estado;
        void                    testar();
        const float             valorValido {230.5};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUNumeroSala {
    private:
        NumeroSala              numero;
        int                     estado;
        void                    testar();
        const unsigned          valorValido {9};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUCidade {
    private:
        Cidade                  cidade;
        int                     estado;
        void                    testar();
        const string            valorValido {"Recife"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUEstado {
    private:
        Estado                  estadoClasse;
        int                     estado;
        void                    testar();
        const string            valorValido {"DF"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUDisponibilidade {
    private:
        Disponibilidade         disp;
        int                     estado;
        void                    testar();
        const unsigned          valorValido {232};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUTipoJogo {
    private:
        TipoJogo                tipo;
        int                     estado;
        void                    testar();
        const unsigned          valorValido {3};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUCpf {
    private:
        Cpf                     cpf;
        int                     estado;
        void                    testar();
        const string            valorValido {"77102555075"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUSenha {
    private:
        Senha                   senha;
        int                     estado;
        void                    testar();
        const string            valorValido {"abcDe1"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUEstadio {
    private:
        Estadio                 estadio;
        int                     estado;
        void                    testar();
        const string            valorValido {"Maracana"};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};

class TUData {
    private:
        Data                    data;
        int                     estado;
        void                    testar();
        const int               valorValidoAno {20};
        const int               valorValidoMes {11};
        const int               valorValidoDia {15};

    public:
        const static int        SUCESSO =  0;
        const static int        FALHA   = -1;
        int                     run ();
};


#endif